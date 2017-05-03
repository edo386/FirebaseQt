package org.qtproject.firebasedemo;

import com.google.firebase.database.FirebaseDatabase;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static final String TAG = "MainActivity";
    private static MainActivity m_instance = null;

    public static MainActivity instance(){
        return m_instance;
    }

    public MainActivity()
    {
        m_instance = this;
        FirebaseDatabase.getInstance().setPersistenceEnabled(true);
    }

}
