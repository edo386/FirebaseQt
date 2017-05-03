#include "firebasedatabase.h"

FirebaseDatabase::FirebaseDatabase(QObject *parent) : QObject(parent)
{
    if( FirebaseApp::instance()->getApp() )
    {
        m_database = firebase::database::Database::GetInstance(FirebaseApp::instance()->getApp());
        m_database->set_persistence_enabled(true);
    }
}

void FirebaseDatabase::OnValueChanged(const firebase::database::DataSnapshot &snapshot) {
    firebase::Variant * val = new firebase::Variant(snapshot.value());
    qDebug() << "Value Changed" << VariantToQVariant( val );
    setValue(VariantToQVariant( val ));
}

void FirebaseDatabase::OnChildAdded(const firebase::database::DataSnapshot &snapshot, const char *previous_sibling)
{

}

void FirebaseDatabase::OnChildChanged(const firebase::database::DataSnapshot &snapshot, const char *previous_sibling)
{
    qDebug() << "Child Changed";
}

void FirebaseDatabase::OnChildMoved(const firebase::database::DataSnapshot &snapshot, const char *previous_sibling)
{

}

void FirebaseDatabase::OnChildRemoved(const firebase::database::DataSnapshot &snapshot)
{

}

void FirebaseDatabase::OnCancelled(const firebase::database::Error &error_code, const char *error_message)
{

}

QVariant FirebaseDatabase::VariantToQVariant(firebase::Variant *val)
{
    QVariant retVal;
    //qDebug() << firebase::Variant::TypeName(val->type());
    switch (val->type()) {
    case firebase::Variant::kTypeBool:
        retVal = QVariant(val->bool_value());
        break;
    case firebase::Variant::kTypeInt64:
        retVal = QVariant(val->int64_value());
        break;
    case firebase::Variant::kTypeDouble:
        retVal = QVariant(val->double_value());
        break;
    case firebase::Variant::kTypeMutableString:
        retVal = QVariant( QString( val->mutable_string().c_str() ));
        break;
    case firebase::Variant::kTypeMap:
        {
            QMap<QString,QVariant> varMap;
            for(auto const& mpVal : val->map() )
            {
                firebase::Variant keyVariant = firebase::Variant(mpVal.first);
                firebase::Variant valueVariant = firebase::Variant(mpVal.second);
                varMap.insert(VariantToQVariant( &keyVariant ).toString(),VariantToQVariant(&valueVariant));
            }
            retVal = QVariant(varMap);
            break;
        }
    case firebase::Variant::kTypeVector:
    {
        QList<QVariant> varList;
        for(auto const& mpVal : val->vector() )
        {
            firebase::Variant valueVariant = firebase::Variant(mpVal);
            varList.append(VariantToQVariant( &valueVariant) );
        }
        retVal = QVariant( varList );
        break;
    }
    case firebase::Variant::kTypeNull:
        retVal = QVariant();

    default:
        break;
    }
    return retVal;
}
