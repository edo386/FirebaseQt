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
    Q_INVOKABLE void subscribe(QString topic)
    {
        qDebug() << "Subscribing to " << topic;
        firebase::messaging::Subscribe( topic.toStdString().c_str() );
    }

    QStringList topicFilter() const
    {
        return m_topicFilter;
    }

signals:
    void fcmTokenChanged(QString fcmToken);
    void messageReceived(QVariantMap message);
    void topicFilterChanged(QStringList topicFilter);

public slots:

void setTopicFilter(QStringList topicFilter)
{
    qDebug() << "Setting topic filter" << topicFilter;
    if (m_topicFilter == topicFilter)
        return;

    disconnect(instance(),0,this,0);
    m_topicFilter = topicFilter;
    QObject::connect(instance(),SIGNAL(messageReceived(QVariantMap)),this,SLOT(messageReceivedFilter(QVariantMap)));
    emit topicFilterChanged(topicFilter);
}

void messageReceivedFilter(QVariantMap message){
    qDebug() << "Receive to filter" << message.value("from");
    QString topicFrom = message.value("from").toString();
    if(topicFrom.contains("/topics/"))
    {
        topicFrom = topicFrom.split("/").last();

    }else{
        return;
    }

    qDebug() << "Filtering for topic" << topicFrom;
    if(!m_topicFilter.contains(topicFrom))
    {
        return;
    }

    emit messageReceived(message);
}

protected:
    static QPointer<FirebaseMessaging> m_instance;

private:
    QString m_fcmToken = "";
    QStringList m_topicFilter;
};

#endif // FIREBASEMESSAGINGLISTENER_H
