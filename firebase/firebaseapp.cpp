#include "firebaseapp.h"

QPointer<FirebaseApp> FirebaseApp::m_instance;

FirebaseApp::FirebaseApp(QObject *parent) : QObject(parent)
{

}

FirebaseApp::FirebaseApp(QObject *parent, firebase::App *app)
{
    instance()->setApp(app);
    instance()->readyChanged(1);
}

FirebaseApp *FirebaseApp::instance(){
    if(!m_instance)
    {
        m_instance = new FirebaseApp();
    }
    return m_instance;
}
