#ifndef FIREBASEMESSAGINGLISTENER_H
#define FIREBASEMESSAGINGLISTENER_H

#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QSettings>
#include <QStringList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

#include "firebase/firebaseapp.h"
#include "firebase/messaging.h"

class FirebaseMessaging : public QObject, public firebase::messaging::Listener
{
    Q_OBJECT
    Q_PROPERTY(QString fcmToken READ fcmToken NOTIFY fcmTokenChanged)
    Q_PROPERTY(QStringList topicFilter READ topicFilter WRITE setTopicFilter NOTIFY topicFilterChanged)
    Q_PROPERTY(QSettings * localSettings READ localSettings NOTIFY localSettingsChanged)
    Q_PROPERTY(QStringList topics READ topics NOTIFY topicsChanged)

public:
    explicit FirebaseMessaging(QObject *parent = 0);
    static FirebaseMessaging *instance();

    virtual void OnTokenReceived(const char* token);
    virtual void OnMessage(const ::firebase::messaging::Message& message);

    QString fcmToken();    
    Q_INVOKABLE void subscribe(QString topic);
    Q_INVOKABLE void unSubscribe(QString topic);
    QStringList topicFilter() const;

    QSettings * localSettings() const
    {
        return m_localSettings;
    }

    QStringList topics();

signals:
    void fcmTokenChanged(QString fcmToken);
    void messageReceived(QVariantMap message);
    void topicFilterChanged(QStringList topicFilter);
    void localSettingsChanged(QSettings * localSettings);
    void topicsChanged(QStringList topics);

public slots:

void setTopicFilter(QStringList topicFilter);
void messageReceivedFilter(QVariantMap message);

protected:
    static QPointer<FirebaseMessaging> m_instance;
    static QStringList m_topics;
    static QSettings * m_localSettings;

private:
    QString m_fcmToken = "";
    QStringList m_topicFilter;
};

#endif // FIREBASEMESSAGINGLISTENER_H
