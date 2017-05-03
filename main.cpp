#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <QGuiApplication>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#endif

#include "firebase/firebasemessaging.h"

#include "firebase/app.h"
#include "firebase/variant.h"
#include "firebase/database.h"
#include "firebase/messaging.h"
#include "firebase/auth.h"

/**! Firebase Plugin */
#include "firebase/firebaseapp.h"
#include "firebase/firebasemessaging.h"
#include "firebase/firebasedatabase.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<FirebaseApp>("Firebase",1,0,"FirebaseApp");
    qmlRegisterType<FirebaseMessaging>("Firebase",1,0,"FirebaseMessaging");
    qmlRegisterType<FirebaseDatabase>("Firebase",1,0,"FirebaseDatabase");

#ifdef Q_OS_ANDROID
    QAndroidJniEnvironment environment;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/firebasedemo/MainActivity","instance","()Lorg/qtproject/firebasedemo/MainActivity;");
    if(activity.isValid())
    {
        FirebaseApp *firebaseApp = new FirebaseApp( &app, firebase::App::Create(firebase::AppOptions(), environment, activity.object<jobject>()));
    }else{
        qWarning() << "Firebase App not created, activity is invalid";
    }
#else
    FirebaseApp *firebaseApp = new FirebaseApp( &app, firebase::App::Create(firebase::AppOptions()) );
#endif
    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
