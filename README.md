<img src="assets/FirebaseQt.png" align="right" width="120"/>

# QtFirebase C++ Demo
A simple implementation of Firebase C++ SDK for Qt 5

Download and unzip the [Firebase C++ SDK](https://firebase.google.com/docs/cpp/setup) into `firebase_cpp_sdk` folder at the project roor (or wherever you want it, but take note of the path), this project was tested with version 3.1.0 of the C++ SDK

## How it Works

QObject wrappers where created extending QObject and a corresponding class for each Firebase module (Messaging only for now), a singleton was used in each class to keep track of the static references required, in particular to the `firebase::App`

The first time a `FirebaseMessaging` is instantiated in QML a singleton is assigned and set as the listener for the `OnMessage` and `OnTokenReceived`, following object instances are connected to this singleton signals to propagate, a topic filter is implemented allowing a particular instance of this class to emit messages for specific topics.

Create a `FirebaseApp`object, not required but useful to check if the app is ready.
```
import Firebase 1.0

...

FirebaseApp{
    id: firebaseApp
    Component.onCompleted: {
        console.log("FirebaseApp "+ready)
    }
}
```

Instantiate anywhere a `FirebaseMessaging` object and call `subscribe(<topic_name>)` on the `onCompleted`, if the `topicFilter` property is set only messages for those topics are received here, if not it will receive all messages.
```
FirebaseMessaging{
    topicFilter: ["your_topic"]
    onFcmTokenChanged: {
        console.log("FCM Token " + fcmToken);
    }
    Component.onCompleted: {
      subscribe("your_topic");
    }
}
```

# Android
Go to the project settings in Qt and create a template for the Android app, this will create gradle specific files and ask you to overwrite the AndroidManifest.xml (go ahead if you want a different config), add the corresponding lines in the `gradle.properties` and `local.properties` as described in the [Firebase Docs](https://firebase.google.com/docs/cpp/setup#setup_for_android)

`gradle.properties`
```
systemProp.firebase_cpp_sdk.dir=~/your_local_firebase_sdk_dir
```

`local.properties`
```
ndk.dir=~/your_local_ndk_dir
```
This last step is probably managed by Qt Creator

Please note that a reference to the library is located at the .pro file:


```
android{...

LIBS += -L$$PWD/firebase_cpp_sdk/libs/android/armeabi-v7a/gnustl/ -lmessaging -ldatabase -lauth -lapp \

INCLUDEPATH  += $$PWD/firebase_cpp_sdk/include
DEPENDPATH += $$PWD/firebase_cpp_sdk/libs/android/armeabi-v7a/gnustl/
}

```
`-lapp` must be the last library linked otherwise you will get a linker error.

The Google Firebase dependencies are set in the `build.gradle` file:

`build.gradle`
```

repositories {
  flatDir {
    dirs System.getProperty('firebase_cpp_sdk.dir') + "/libs/android"
  }
}

dependencies {
    compile fileTree(dir: 'libs', include: ['*.jar'])
    compile 'com.google.firebase:firebase-core:10.2.4'
    compile 'com.google.firebase:firebase-messaging:10.2.4'
    compile 'com.google.firebase:firebase-analytics:10.2.4'
    compile 'com.google.firebase:firebase-database:10.2.4'
    compile 'com.google.firebase:firebase-crash:10.2.4'
    compile 'com.google.firebase:firebase-auth:10.2.4'
    compile 'com.google.firebase.messaging.cpp:firebase_messaging_cpp@aar'
    compile 'com.google.android.gms:play-services-base:10.2.4'
}

apply plugin: 'com.google.gms.google-services'
```
Set your package name in the same file:

```
  defaultConfig {
      applicationId "org.qtproject.firebasedemo"
  }
```

At this point Qt should build the application but gradle can complain about a version so set it to `gradle-2.14.1-all.zip` at the `gradle-wrapper.properties` file.

Remember to generate your `google-services.json` file and place it in the `android` folder

# iOS
