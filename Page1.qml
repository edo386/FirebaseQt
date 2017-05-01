import QtQuick 2.7

import Firebase 1.0

Page1Form {
    button1.onClicked: {
        console.log("Button Pressed. Entered text: " + textField1.text);
    }
    fcmTokenText.onPressAndHold: {
        fcmTokenText.selectAll();
        fcmTokenText.copy();
        console.log(baseMessaging.fcmToken);
    }
    fcmTokenText.text: "FCM Token\n " + baseMessaging.fcmToken

    FirebaseMessaging{
        topicFilter: ["page1"]
        onFcmTokenChanged: {
            console.log("Hey Second one! " + fcmToken)
        }

        onMessageReceived: {
            console.log(JSON.stringify(message,null,2))
            if(message.data.value)
            {
                messageTextArea.text = message.data.value;
            }
        }
        Component.objectName: {
            subscribe("page1");
        }
    }

}
