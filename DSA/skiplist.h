// skiplist.h
#pragma once
#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__
#include "dsa.h"
#include "list.h"
#include "entry.h"
#include "quadlist.h"
#include "dictionary.h"
_DSA_BEGIN
template<typename K, typename V> // key, value
class Skiplist :public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*> {
protected:
	bool skipSearch(
		ListNode<Quadlist<Entry<K, V>>*>*& qlist,
		QuadlistNode<Entry<K, V>>*& p,
		K& k);
public:
	int size() const override { return empty ? 0 : last()->data->size(); } // 底层Quadlist的规模
	int level() { return List<Quadlist<Entry<K, V>>*>::size(); } // 层高 == #Quadlist, 不一定要开放
	bool put(K, V) override; // 插入（注意与Map有别——Skiplist允许词条重复，故必然成功）
	V* get(K k) override; // 读取
	bool remove(K k) override; // 删除
};

/*********************************************************************
* Skiplist词条查找算法（供内部调用）
* 入口：qlist为顶层列表，p为qlist首节点
* 出口：若成功，p为命中关键码所属塔的顶部节点，qlist为p所属列表
*		否则，p为所属塔的基座，该塔对应于不大于k的最大且最靠右关键码，qlist为空
* 约定：多个词条命中时，沿四联表取最靠后者
*********************************************************************/
template<typename K, typename V>
bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>*& qlist, // 从指定层qlist的
	QuadlistNode<Entry<K, V>>*& p, // 首节点p出发
	K& k) { // 向右、向下查找目标关键码k
	while (true) { // 在每一层
		while (p->succ && (p->entry.key <= k)) // 从前往后查找
			p = p->succ; // 直到出现更大的key或溢出至trailer
		p = p->pred; // 此时倒回一步，即可判断是否
		if (p->pred && (k == p->entry.key)) return true; // 命中
		qlist = qlist->succ; // 否则转入下一层
		if (!qlist->succ) return false; // 若已穿透到底层，则意味着失败
		p = (p->pred) ? p->below : qlist->data->first(); // 否则转至当前塔的下一节点
	}
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K, V) { // 跳转表词条插入算法
	
}

template<typename K, typename V>
V* dsa::Skiplist<K, V>::get(K k) { // 跳转表词条查找算法
	if (empty()) return NULL;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first(); // 从顶层Quadlist的
	QuadlistNode<Entry<K, V>>* q = qlist->data->first(); // 首节点开始
	return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL; // 查找并报告
} // 有多个命中时靠后者优先

_DSA_END
#endif // !__SKIPLIST_H__
