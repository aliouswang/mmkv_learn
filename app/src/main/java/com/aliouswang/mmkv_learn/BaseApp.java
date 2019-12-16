package com.aliouswang.mmkv_learn;

import android.app.Application;
import android.util.Log;

import com.aliouswang.mmkv.MMKV;

public class BaseApp extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        String result = MMKV.initialize(this);

        Log.e("mmkv_learn", "init:" + result);
    }
}
