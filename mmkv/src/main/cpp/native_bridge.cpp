//
// Created by aliouswang on 2019-12-16.
//

#include "native_bridge.h"
#include <jni.h>
#include <string>
#include "MMKVLog.h"
#include "MMKV.h"

using namespace std;

static jclass g_cls = nullptr;
static jfieldID g_fileID = nullptr;
static jmethodID g_callbackOnCRCFailID = nullptr;
static jmethodID g_callbackOnFileLengthErrorID = nullptr;
static jmethodID g_mmkvLogID = nullptr;
static jmethodID g_callbackOnContentChange = nullptr;
static JavaVM *g_currentJVM = nullptr;
int g_android_api = __ANDROID_API_L__;

static int registerNativeMethods(JNIEnv *env, jclass cls);

extern "C" JNIEXPORT JNICALL jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    g_currentJVM = vm;
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    if (g_cls) {
        env->DeleteGlobalRef(g_cls);
    }
    static const char *clsName = "com/aliouswang/mmkv/MMKV";
    jclass instance = env->FindClass(clsName);
    if (!instance) {
        MMKVError("fail to locate class: %s", clsName);
        return -2;
    }
    g_cls = reinterpret_cast<jclass>(env->NewGlobalRef(instance));
    if (!g_cls) {
        MMKVError("fail to create global reference for %s", clsName);
        return -3;
    }
    int ret = registerNativeMethods(env, g_cls);
    if (ret != 0) {
        MMKVError("fail to register native methods for class %s, ret = %d", clsName, ret);
        return -4;
    }
    g_fileID = env->GetFieldID(g_cls, "nativeHandle", "J");
    if (!g_fileID) {
        MMKVError("fail to locate fileID");
        return -5;
    }

//    g_callbackOnCRCFailID =
//            env->GetStaticMethodID(g_cls, "onMMKVCRCCheckFail", "(Ljava/lang/String;)I");
//    if (!g_callbackOnCRCFailID) {
//        MMKVError("fail to get method id for onMMKVCRCCheckFail");
//    }
//    g_callbackOnFileLengthErrorID =
//            env->GetStaticMethodID(g_cls, "onMMKVFileLengthError", "(Ljava/lang/String;)I");
//    if (!g_callbackOnFileLengthErrorID) {
//        MMKVError("fail to get method id for onMMKVFileLengthError");
//    }
//    g_mmkvLogID = env->GetStaticMethodID(
//            g_cls, "mmkvLogImp", "(ILjava/lang/String;ILjava/lang/String;Ljava/lang/String;)V");
//    if (!g_mmkvLogID) {
//        MMKVError("fail to get method id for mmkvLogImp");
//    }
//    g_callbackOnContentChange =
//            env->GetStaticMethodID(g_cls, "onContentChangedByOuterProcess", "(Ljava/lang/String;)V");
//    if (!g_callbackOnContentChange) {
//        MMKVError("fail to get method id for onContentChangedByOuterProcess()");
//    }

    // get current API level by accessing android.os.Build.VERSION.SDK_INT
    jclass versionClass = env->FindClass("android/os/Build$VERSION");
    if (versionClass) {
        jfieldID sdkIntFieldID = env->GetStaticFieldID(versionClass, "SDK_INT", "I");
        if (sdkIntFieldID) {
            g_android_api = env->GetStaticIntField(versionClass, sdkIntFieldID);
            MMKVInfo("current API level = %d", g_android_api);
        } else {
            MMKVError("fail to get field id android.os.Build.VERSION.SDK_INT");
        }
    } else {
        MMKVError("fail to get class android.os.Build.VERSION");
    }

    return JNI_VERSION_1_6;
}

static string jstring2string(JNIEnv *env, jstring str) {
    if (str) {
        const char *kstr = env->GetStringUTFChars(str, nullptr);
        if (kstr) {
            string result(kstr);
            env->ReleaseStringUTFChars(str, kstr);
            return result;
        }
    }
    return "";
}

static jstring string2jstring(JNIEnv *env, const string &str) {
    return env->NewStringUTF(str.c_str());
}

#define MMKV_JNI static

namespace mmkv {
    MMKV_JNI jstring jniInitialize(JNIEnv *env, jobject obj, jstring rootDir, jint logLevel) {
        string name = "From jni";
        return env->NewStringUTF(name.c_str());
    }

    MMKV_JNI jlong getDefaultMMKV(JNIEnv *env, jobject obj) {
        MMKV *kv = new MMKV();
        return (jlong) kv;
    }

    MMKV_JNI void put(JNIEnv *env, jobject obj, jlong handle, jstring okey, jstring ovalue) {
        if(handle > 0) {
            MMKV *kv = reinterpret_cast<MMKV *>(handle);

            kv->put(jstring2string(env, okey), jstring2string(env, ovalue));
        }
    }

    MMKV_JNI jstring get(JNIEnv *env, jobject obj, jlong handle, jstring key) {
        MMKV *kv = reinterpret_cast<MMKV *>(handle);
        return string2jstring(env, kv->get(jstring2string(env, key)));
    }


    MMKV_JNI jboolean encodeString(JNIEnv *env, jobject obj, jlong handle, jstring okey, jstring ovalue) {
        MMKV *kv = reinterpret_cast<MMKV *>(handle);
        if (kv && okey) {
            string key = jstring2string(env, okey);
            if (ovalue) {
                string value = jstring2string(env, ovalue);

            }
        }
        return (jboolean) true;
    }

}

//"(J" + S + S + ")V"

#define S "Ljava/lang/String;"
static JNINativeMethod g_methods[] = {
        {"jniInitialize", "(Ljava/lang/String;I)Ljava/lang/String;", (void *) mmkv::jniInitialize},
        {"getDefaultMMKV", "()J", (void *) mmkv::getDefaultMMKV},
        {"put", "(JLjava/lang/String;Ljava/lang/String;)V", (void *) mmkv::put},
        {"get", "(JLjava/lang/String;)Ljava/lang/String;", (void *) mmkv::get},
        {"encodeString", "(JLjava/lang/String;Ljava/lang/String;)Z", (void *) mmkv::encodeString},
};

static int registerNativeMethods(JNIEnv *env, jclass cls) {
    return env->RegisterNatives(cls, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
}