package com.aliouswang.mmkv;

import android.content.Context;

public class MMKV {

    public static String initialize(Context context) {
        String root = context.getFilesDir().getAbsolutePath() + "/mmkv_learn";

        System.loadLibrary("mmkv");
        return jniInitialize(root, 0);
    }

    public static MMKV defaultMMKV() {
        return new MMKV(getDefaultMMKV());
    }

    public MMKV(long handle) {
        this.nativeHandle = handle;
    }

    public void put(String key, String value) {
        put(nativeHandle, key, value);
    }

    public String get(String key) {
        return get(nativeHandle, key);
    }

    // jni
    private long nativeHandle;

    private static native String jniInitialize(String rootDir, int level);

    private static native long getDefaultMMKV();

    private native void put(long handle, String key, String value);

    private native String get(long handle, String key);

}
