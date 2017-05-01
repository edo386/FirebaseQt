import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import Firebase 1.0


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    FirebaseApp{
        id: firebaseApp
        Component.onCompleted: {
            console.log("FirebaseApp "+ready)
        }
    }

    FirebaseMessaging{
        id: baseMessaging
        onFcmTokenChanged: {
            console.log("FCM Token " + fcmToken);
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Label {
                id: labelPage2
                text: qsTr("Second page")
                anchors.centerIn: parent
                FirebaseMessaging{
                    topicFilter: ["page2"]
                    onMessageReceived: {
                        if(message.data.value)
                        {
                            labelPage2.text = message.data.value
                        }
                    }
                    Component.onCompleted: {
                        subscribe("page2")
                    }
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
