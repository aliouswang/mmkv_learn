//
// Created by aliouswang on 2019-12-10.
//

#include "MMKV.h"
#include "MiniPBCoder.h"
#include "ScopedLock.hpp"
#include "PBUtility.h"

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

bool MMKV::setStringForKey(string key, string value) {
    if (key.empty()) {
        return false;
    }
    auto data = MiniPBCoder::encodeDataWithObject(value);

}

bool MMKV::setDataForKey(MMBuffer &&data, const std::string &key) {
    if (data.length() == 0 || key.empty()) {
        return false;
    }

}

bool MMKV::appendDataWithKey(const MMBuffer &data, const std::string &key) {
//    size_t keyLength = key.length();
//    // size needed to encode the key
//    size_t size = keyLength + pbRawVarint32Size((int32_t) keyLength);
//    // size needed to encode the value
//    size += data.length() + pbRawVarint32Size((int32_t) data.length());
//
//    SCOPEDLOCK(m_exclusiveProcessLock);
//
//    bool hasEnoughSize = ensureMemorySize(size);
//
//    if (!hasEnoughSize || !isFileValid()) {
//        return false;
//    }
//
//    m_output->writeString(key);
//    m_output->writeData(data); // note: write size of data
//
//    auto ptr = (uint8_t *) m_ptr + Fixed32Size + m_actualSize;
//    if (m_crypter) {
//        m_crypter->encrypt(ptr, ptr, size);
//    }
//    m_actualSize += size;
//    updateCRCDigest(ptr, size);

    return true;
}