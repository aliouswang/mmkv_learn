//
// Created by aliouswang on 2019-12-10.
//

#include "MMKV.h"

void MMKV::setToken(string token) {
    this->token = token;
}

void MMKV::put(string key, string value) {
    pair<string, string> v(key, value);
    this->mMap.insert(v);
}

string MMKV::get(string key) {
    return this->mMap[key];
}