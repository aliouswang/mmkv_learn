//
// Created by aliouswang on 2019-12-10.
//

#ifndef MMKV_LEARN_MMKV_H
#define MMKV_LEARN_MMKV_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdio.h>

using namespace std;

class MMKV {
private:
    string token;
    map<string, string> mMap;

public:
    void setToken(string token);

    MMKV() {
//        mMap = new map<string, string>();
    }

    void put(string key, string value);
    string get(string key);
};


#endif //MMKV_LEARN_MMKV_H
