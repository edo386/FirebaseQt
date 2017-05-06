#ifndef FIREBASEDATABASE_H
#define FIREBASEDATABASE_H

#include <QObject>
#include <QQmlComponent>
#include <QUrl>
#include <QDebug>

#include "firebase/firebaseapp.h"
#include "firebase/database.h"
#include "firebase/variant.h"

class FirebaseDatabase : public QObject, public firebase::database::ChildListener, public firebase::database::ValueListener
{
    Q_OBJECT
    Q_PROPERTY(QQmlComponent * baseComponent READ baseComponent WRITE setBaseComponent NOTIFY baseComponentChanged)
    Q_PROPERTY(QUrl basePath READ basePath WRITE setBasePath NOTIFY basePathChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QObject *valueObj READ valueObj WRITE setValueObj NOTIFY valueObjChanged)
    Q_PROPERTY(bool write READ write WRITE setWrite NOTIFY writeChanged)
    Q_PROPERTY(bool hasChild READ hasChild NOTIFY hasChildChanged)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)

public:
    explicit FirebaseDatabase(QObject *parent = 0);

    void OnValueChanged(const firebase::database::DataSnapshot& snapshot) override;
    void OnChildAdded(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling) override;
    void OnChildChanged(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling) override;
    void OnChildMoved(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling) override;
    void OnChildRemoved(const firebase::database::DataSnapshot& snapshot) override;
    void OnCancelled(const firebase::database::Error& error_code, const char* error_message) override;

    QUrl basePath() const;
    QQmlComponent *baseComponent() const;
    QVariant value() const;

    static QVariant VariantToQVariant(firebase::Variant *val);
    static firebase::Variant QVariantToVariant(QVariant val);

    QObject *valueObj();
    bool write() const;

    Q_INVOKABLE void createNewObject(QString name);
    Q_INVOKABLE QObject *getChild(QString name);
    Q_INVOKABLE void updateValue(QString value_path, QVariant value);

    bool hasChild() const
    {
        return m_hasChild;
    }

    QString key() const
    {
        return m_key;
    }

signals:

    void basePathChanged(QUrl basePath);
    void baseComponentChanged(QQmlComponent * baseComponent);
    void valueChanged(QVariant value);
    void valueObjChanged(QObject *valueObj);
    void writeChanged(bool write);
    void hasChildChanged(bool hasChild);

    void keyChanged(QString key);

public slots:

    void setBasePath(QUrl basePath);
    void setBaseComponent(QQmlComponent * baseComponent);
    void setValue(QVariant value, bool write = true);
    void setValueObj(QObject *valueObj);
    void setWrite(bool write);
    void setHasChild(bool hasChild);

    Q_INVOKABLE void updateValue(QVariant value_path, QVariant value);

    void setKey(QString key)
    {
        if (m_key == key)
            return;

        m_key = key;
        emit keyChanged(key);
    }

private:
    firebase::database::DatabaseReference * m_database_ref;
    firebase::database::Database * m_database;
    QUrl m_basePath;
    QQmlComponent * m_baseComponent = NULL;
    QVariant m_value;
    QObject *m_valueObj = NULL;
    bool m_write = true;
    bool m_hasChild = false;
    QString m_key;
};

#endif // FIREBASEDATABASE_H
