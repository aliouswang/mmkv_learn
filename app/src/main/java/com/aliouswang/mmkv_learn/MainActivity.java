package com.aliouswang.mmkv_learn;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.aliouswang.mmkv.MMKV;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        MMKV mmkv = MMKV.defaultMMKV();
        mmkv.put("userId", "123");
        mmkv.put("timestamp", System.currentTimeMillis() + "");

        Log.e("mmkv_test", "userId:" + mmkv.get("userId"));
        Log.e("mmkv_test", "timestamp:" + mmkv.get("timestamp"));

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
