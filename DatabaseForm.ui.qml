import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias textField: textField
    property alias button: button
    property alias dial1: dial1
    property alias dial: dial
    Flickable {
        id: flickable
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            //width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter

            RowLayout {
                id: rowLayout
                width: 100
                height: 100

                TextField {
                    id: textField
                    placeholderText: qsTr("Change Name")
                }

                Button {
                    id: button
                    text: qsTr("Update")
                }
            }

            Dial {
                id: dial
                to: 1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Dial {
                id: dial1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }
    }
}
