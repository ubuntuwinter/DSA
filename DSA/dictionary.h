// dictionary.h
#pragma once
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__
#include "dsa.h"
_DSA_BEGIN
template<typename K, typename V>
struct Dictionary { // 词典Dictionary模板类
	virtual int size() const = 0;
	virtual bool put(K, V) = 0; // 插入词条（禁止雷同词条时可能失败）
	virtual V* get(K k) = 0; // 读取词条
	virtual bool remove(K k) = 0; // 删除词条
};
_DSA_END
#endif // !__DICTIONARY_H__
