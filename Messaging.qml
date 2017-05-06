import QtQuick 2.7

import Firebase 1.0

MessagingForm {
    FirebaseMessaging{
        id: fcm
        onFcmTokenChanged: {
            fcmTokenText.text = fcmToken
            fcmReady = true
        }
        onMessageReceived: {
            console.log(JSON.stringify(message,null,2))
            payload.text = JSON.stringify(message,null,2)
        }
    }
    copyTokenButton.onClicked: {
        console.log("Copy FCM Token",fcm.fcmToken)
        fcmTokenText.selectAll();
        fcmTokenText.copy();
        fcmTokenText.deselect();
    }

    subscribeButton.onClicked: {
        console.log("Subscribe to",subscribeField.text)
        if(subscribeField.text !== "")
        {
            subscribeField.text = subscribeField.text.toLowerCase()
            if(!unsubscribeCheckBox.checked)
            {
                fcm.subscribe(subscribeField.text)
            }else{
                fcm.unSubscribe(subscribeField.text)
            }
        }
    }
    topicsListView.model: fcm.topics
}
