#ifndef FIREBASEAPP_H
#define FIREBASEAPP_H

#include <QObject>
#include <QPointer>
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
        return m_app;
    }

signals:

    void readyChanged(int ready);

public slots:

protected:
    static QPointer<FirebaseApp> m_instance;

    firebase::App *m_app;

    void setApp(firebase::App *app){
        if(m_app == NULL)
        {
            m_app = app;
        }
    }

    bool appReady(){
        return m_app != NULL;
    }
};

#endif // FIREBASEAPP_H
