import QtQuick 2.4
import Firebase 1.0

DatabaseForm {
    Component{
        id: userModel
        QtObject{
            id: dbObject
            property alias key: dbObject.objectName
            property string kind: "user"
            property string path
            property string name: ""
            property var phones: []
            onNameChanged: {
                updateField("name",name)
            }
            signal updateField(var path,var value)
        }
    }

    FirebaseDatabase{
        id: databaseUser
        baseComponent: userModel
        basePath: "user/mike"
        onValueChanged: {
            console.log("Value",JSON.stringify(value,null,2))
        }
        onValueObjChanged: {
            console.log(JSON.stringify(valueObj));
        }
    }
    FirebaseDatabase{
        id: databaseUser2
        baseComponent: userModel
        basePath: "user/rob"
        onValueChanged: {
            console.log("Value",JSON.stringify(value,null,2))
        }
        onValueObjChanged: {
            console.log(JSON.stringify(valueObj));
        }
    }
//    FirebaseDatabase{
//        id: databaseSingle
//        basePath: "single_value"
//        onValueChanged: {
//            console.log("Value",JSON.stringify(value,null,2))
//        }
//    }
    FirebaseDatabase
    {
        basePath: "dial"
        onValueChanged: dial1.value = value
    }

    FirebaseDatabase{
        id: senderDatabase
        basePath: "dial"

    }

    dial.onValueChanged: {
        senderDatabase.setValue(dial.value)
    }


    button.onClicked: {
        databaseUser.valueObj.name = textField.text
    }
}
