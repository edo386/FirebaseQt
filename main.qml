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

    //    FirebaseMessaging{
    //        id: baseMessaging
    //        onFcmTokenChanged: {
    //            console.log("FCM Token " + fcmToken);
    //        }
    //    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
//            FirebaseMessaging{
//                //topicFilter: ["page2"]
//                onMessageReceived: {
//                    if(message.data.value)
//                    {
//                        labelPage2.text = message.data.value
//                    }
//                }
//                Component.onCompleted: {
//                    subscribe("page2")
//                }
//            }
            FirebaseDatabase{
                id: testObjectRef
                basePath: "testObject"
                baseComponent: Component{
                    QtObject{
                        property string kind: "MyKind"
                        property var path
                        property var value
                        Component.onCompleted: {
                            console.log(path,value)
                        }
                    }
                }
                onValueChanged: {
                    console.log("Value" + JSON.stringify(value,null,2))
                    //labelPage2.text = value
                }
                onValueObjChanged: {
                    console.log("ValueObj" + JSON.stringify(valueObj));
                    //objectPathText.text = testObjectRef.valueObj.path ? testObjectRef.valueObj.path : ""
                }
            }

//            FirebaseDatabase{
//                id: obj2Ref
//                basePath: "obj2"
//                write: false
//                onValueChanged: {
//                    console.log("Value "+ basePath + JSON.stringify(value,null,2))
//                }
//            }

            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                TextInput{
                    id: inText
                    text: "ChangeMe!"
                    height: 60
                    onTextChanged: {testObjectRef.value = text}
//                    onAccepted: {
//                        testObjectRef.value = inText.text
//                    }
                }

                Button{
                    onClicked: {
//                        obj2Ref.value.single = inText.text
                    }
                }

                Label {
                    id: labelPage2
                    text: testObjectRef.valueObj.path
                }
                Text{
                    id: objectPathText
//                    text: obj2Ref.value.single + obj2Ref.value.array[0]
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
