import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: messagingItem
    property alias fcmReady: tokenReady.checked
    property alias copyTokenButton: copyTokenButton
    property alias fcmTokenText: fcmTokenText
    property alias payload: payload
    property alias subscribeField: subscribeField
    property alias subscribeButton: subscribeButton
    property alias unsubscribeCheckBox: unsubscribeCheckBox
    property alias topicsListView: topicsListView

    Flickable {
        id: flickable
        anchors.fill: parent
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.VerticalFlick
        contentHeight: columnLayout.height

        ColumnLayout {
            id: columnLayout
            width: parent.width
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            RowLayout {
                id: rowLayout1
                width: 100
                height: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                TextField {
                    id: subscribeField
                    text: qsTr("")
                    renderType: Text.NativeRendering
                    placeholderText: qsTr("Topic")
                }

                Button {
                    id: subscribeButton
                    text: unsubscribeCheckBox.checked ? qsTr("Unsubscribe") :  qsTr("Subscribe!")
                }
                CheckBox {
                    id: unsubscribeCheckBox
                    text: qsTr("Unsubscribe")
                }
            }

            RowLayout {
                id: rowLayout
                width: 100
                height: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                CheckBox {
                    id: tokenReady
                    text: qsTr("FCM Token Ready")
                    enabled: false
                    checkable: false
                }

                Button {
                    id: copyTokenButton
                    text: qsTr("Copy Token")
                    enabled: tokenReady.checked
                }
            }

            TextArea {
                id: fcmTokenText
                text: qsTr("")
                enabled: false
                rightPadding: 10
                visible: tokenReady.checked
                Layout.fillWidth: true
                wrapMode: Text.WrapAnywhere
            }

            Text {
                id: payload
                text: qsTr("")
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                Layout.fillWidth: true
            }

            Repeater {
                id: topicsListView
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                width: parent.width

                delegate: ItemDelegate {
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: itemDelegate
                    width: parent.width
                    text: modelData
                    height: 15
                }
            }
        }
    }
}
