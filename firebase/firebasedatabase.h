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


public:
    explicit FirebaseDatabase(QObject *parent = 0);

    void OnValueChanged(const firebase::database::DataSnapshot& snapshot) override;

    void OnChildAdded(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling) override;
    void OnChildChanged(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling) override;
    void OnChildMoved(const firebase::database::DataSnapshot& snapshot, const char* previous_sibling) override;
    void OnChildRemoved(const firebase::database::DataSnapshot& snapshot) override;

    void OnCancelled(const firebase::database::Error& error_code, const char* error_message) override;

    QUrl basePath() const
    {
        return m_basePath;
    }

    QQmlComponent * baseComponent() const
    {
        return m_baseComponent;
    }

    static QVariant VariantToQVariant(firebase::Variant *val);


    QVariant value() const
    {
        return m_value;
    }

signals:

    void basePathChanged(QUrl basePath);

    void baseComponentChanged(QQmlComponent * baseComponent);

    void valueChanged(QVariant value);

public slots:

void setBasePath(QUrl basePath)
{
    if (m_basePath == basePath)
        return;

    m_basePath = basePath;
    qDebug() << "Base Path" << basePath.path().remove(0,1);
    if( m_database )
    {
        m_database_ref = new firebase::database::DatabaseReference( m_database->GetReference(basePath.path().remove(0,1).toStdString().c_str()) );
        m_database_ref->AddChildListener(this);
        m_database_ref->AddValueListener(this);
        m_database_ref->GetValue();
        m_database_ref->SetKeepSynchronized(true);

        qDebug() <<"Database Reference URL"<< m_database_ref->url().c_str();
    }
    emit basePathChanged(basePath);
}

void setBaseComponent(QQmlComponent * baseComponent)
{
    if (m_baseComponent == baseComponent)
        return;

    m_baseComponent = baseComponent;
    emit baseComponentChanged(baseComponent);
}

void setValue(QVariant value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged(value);
}

private:
    firebase::database::DatabaseReference * m_database_ref;
    firebase::database::Database * m_database;
    QUrl m_basePath;
    QQmlComponent * m_baseComponent;
    QVariant m_value;
};

#endif // FIREBASEDATABASE_H
