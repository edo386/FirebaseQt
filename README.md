<img src="assets/FirebaseQt.png" align="right" width="120"/>

# QtFirebase C++ Demo
A simple implementation of Firebase C++ SDK for Qt 5

Download and unzip the [Firebase C++ SDK](https://firebase.google.com/docs/cpp/setup) into `firebase_cpp_sdk` folder at the project roor (or wherever you want it, but take note of the path), this project was tested with version 3.1.0 of the C++ SDK

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

At this point Qt should build the application but gradle can complain about a version so set it to `gradle-2.14.1-all.zip` at the `gradle-wrapper.properties` file.

Remember to generate your `google-services.json` file and place it in the `android` folder

# iOS
