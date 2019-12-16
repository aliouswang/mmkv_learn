//
// Created by aliouswang on 2019-12-16.
//

#ifndef MMKV_LEARN_NATIVE_BRIDGE_H
#define MMKV_LEARN_NATIVE_BRIDGE_H

#include <string>

namespace mmkv {

    void mmkvLog(int level,
                 const std::string &file,
                 int line,
                 const std::string &function,
                 const std::string &message);

}

#endif //MMKV_LEARN_NATIVE_BRIDGE_H
