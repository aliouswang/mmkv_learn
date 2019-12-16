/*
 * Tencent is pleased to support the open source community by making
 * MMKV available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MMKVLog.h"
#include "native_bridge.h"
#include <string>

#ifdef ENABLE_MMKV_LOG

using namespace std;

#    define APPNAME "MMKV"

bool g_isLogRedirecting = false;

#    ifndef NDEBUG
MMKVLogLevel g_currentLogLevel = MMKVLogDebug;
#    else
MMKVLogLevel g_currentLogLevel = MMKVLogInfo;
#    endif

bool g_isContentChangeNotifying = false;

const char *_getFileName(const char *path) {
    const char *ptr = strrchr(path, '/');
    if (!ptr) {
        ptr = strrchr(path, '\\');
    }
    if (ptr) {
        return ptr + 1;
    } else {
        return path;
    }
}

static android_LogPriority MMKVLogLevelDesc(MMKVLogLevel level) {
    switch (level) {
        case MMKVLogDebug:
            return ANDROID_LOG_DEBUG;
        case MMKVLogInfo:
            return ANDROID_LOG_INFO;
        case MMKVLogWarning:
            return ANDROID_LOG_WARN;
        case MMKVLogError:
            return ANDROID_LOG_ERROR;
        default:
            return ANDROID_LOG_UNKNOWN;
    }
}

void _MMKVLogWithLevel(
    MMKVLogLevel level, const char *file, const char *func, int line, const char *format, ...) {
    if (level >= g_currentLogLevel) {
        string message;
        char buffer[16];

        va_list args;
        va_start(args, format);
        auto length = std::vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        if (length < 0) { // something wrong
            message = {};
        } else if (length < sizeof(buffer)) {
            message = string(buffer, static_cast<unsigned long>(length));
        } else {
            message.resize(static_cast<unsigned long>(length), '\0');
            va_start(args, format);
            std::vsnprintf(const_cast<char *>(message.data()), static_cast<size_t>(length) + 1,
                           format, args);
            va_end(args);
        }

        if (g_isLogRedirecting) {
//            mmkv::mmkvLog((int) level, file, line, func, message);
        } else {
            __android_log_print(MMKVLogLevelDesc(level), APPNAME, "<%s:%d::%s> %s", file, line,
                                func, message.c_str());
        }
    }
}

#endif // ENABLE_MMKV_LOG
