#ifndef FIREBASEAPP_H
#define FIREBASEAPP_H

#include <QObject>
#include <QPointer>
#include <QDebug>
#include "firebase/app.h"

class FirebaseApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ready READ ready NOTIFY readyChanged)

    int m_ready;

public:
    explicit FirebaseApp(QObject *parent = 0);
    FirebaseApp(QObject *parent, firebase::App *app);

    static FirebaseApp *instance();

    int ready() const
    {
        return instance()->appReady();
    }

    firebase::App *getApp(){
//        qDebug() << "FirebaseApp: Returning App" << m_app;
        return m_app;
    }

    bool appReady(){
        return m_app != NULL;
    }

signals:

    void readyChanged(int ready);

public slots:

protected:
    static QPointer<FirebaseApp> m_instance;
    firebase::App *m_app = NULL;

    void setApp(firebase::App *app){
//        qDebug() << "Setting APP " << app << m_app;
        if(m_app == NULL)
        {
            m_app = app;
//            qDebug() << "App set " << m_app;
        }
    }


};

#endif // FIREBASEAPP_H
