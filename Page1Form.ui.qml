import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1
    property alias textField1: textField1
    property alias button1: button1
    property alias fcmTokenText: fcmToken
    property alias messageTextArea: messageTextArea

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        RowLayout {
            clip: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            anchors.top: parent.top

            TextField {
                id: textField1
                placeholderText: qsTr("Text Field")
            }

            Button {
                id: button1
                text: qsTr("Press Me")
            }
        }
        TextArea {
            id: fcmToken
            width: parent.width
            text: ""
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WrapAnywhere
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextArea {
            id: messageTextArea
            text: qsTr("FCM Messages will be shown here")
            horizontalAlignment: Text.AlignLeft
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: false
            wrapMode: Text.WordWrap
        }
    }
}
