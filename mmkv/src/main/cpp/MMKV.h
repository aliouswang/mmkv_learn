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

#include "ThreadLock.h"
#include "InterProcessLock.h"

#include "MMBuffer.h"

using namespace std;

class MMKV {
private:
    string token;
    map<string, string> mMap;

    int m_fd;
    char *m_ptr;
    size_t m_size;
    size_t m_actualSize;


//    ThreadLock m_lock;
//    FileLock m_fileLock;

public:
    void setToken(string token);

    MMKV() {
//        mMap = new map<string, string>();
    }

    void put(string key, string value);
    string get(string key);

    bool setStringForKey(string key, string value);

    bool setDataForKey(MMBuffer &&data, const std::string &key);

    bool appendDataWithKey(const MMBuffer &data, const std::string &key);
};


#endif //MMKV_LEARN_MMKV_H
