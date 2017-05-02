QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    firebase/firebasemessaging.cpp \
    firebase/firebaseapp.cpp

HEADERS += \
    firebase/firebasemessaging.h \
    firebase/firebaseapp.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/firebase

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android{
    QT += androidextras

    DISTFILES += \
        android/src/org/qtproject/firebasedemo/MainActivity.java \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat \
        android/src/org/qtproject/firebasedemo/MainActivity.java
        android/gradle.properties \
        android/local.properties

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    LIBS += -L$$PWD/firebase_cpp_sdk/libs/android/armeabi-v7a/gnustl/ -lmessaging -ldatabase -lauth -lapp \

    INCLUDEPATH  += $$PWD/firebase_cpp_sdk/include
    DEPENDPATH += $$PWD/firebase_cpp_sdk/libs/android/armeabi-v7a/gnustl/
}

ios{
    QMAKE_INFO_PLIST = $$PWD/iOS/Info.plist
    INCLUDEPATH  += $$PWD/firebase_cpp_sdk/include

    QMAKE_LFLAGS += -L$$PWD/firebase_cpp_sdk/libs/frameworks/ios/

    QMAKE_LFLAGS +=  -framework "FirebaseCore" \
                     -framework "FirebaseDatabase" \
                     -framework "FirebaseMessaging"

}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/android/openssl/libcrypto.so \
        $$PWD/android/openssl/libssl.so
}


