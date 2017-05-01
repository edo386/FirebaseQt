#ifndef FIREBASEMESSAGINGLISTENER_H
#define FIREBASEMESSAGINGLISTENER_H

#include <QDebug>
#include <QObject>

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

public:
    explicit FirebaseMessaging(QObject *parent = 0);
    static FirebaseMessaging *instance();

    virtual void OnTokenReceived(const char* token);
    virtual void OnMessage(const ::firebase::messaging::Message& message);

    QString fcmToken();    
    Q_INVOKABLE void subscribe(QString topic);
    QStringList topicFilter() const;

signals:
    void fcmTokenChanged(QString fcmToken);
    void messageReceived(QVariantMap message);
    void topicFilterChanged(QStringList topicFilter);

public slots:

void setTopicFilter(QStringList topicFilter);
void messageReceivedFilter(QVariantMap message);

protected:
    static QPointer<FirebaseMessaging> m_instance;

private:
    QString m_fcmToken = "";
    QStringList m_topicFilter;
};

#endif // FIREBASEMESSAGINGLISTENER_H
