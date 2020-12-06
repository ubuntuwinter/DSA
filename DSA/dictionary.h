// dictionary.h
#pragma once
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__
#include "dsa.h"
_DSA_BEGIN
template<typename K, typename V>
struct Dictionary { // �ʵ�Dictionaryģ����
	virtual int size() const = 0;
	virtual bool put(K, V) = 0; // �����������ֹ��ͬ����ʱ����ʧ�ܣ�
	virtual V* get(K k) = 0; // ��ȡ����
	virtual bool remove(K k) = 0; // ɾ������
};
_DSA_END
#endif // !__DICTIONARY_H__
