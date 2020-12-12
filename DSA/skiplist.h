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
	int size() const override { return List<Quadlist<Entry<K, V>>*>::empty() ? 0 : List<Quadlist<Entry<K, V>>*>::last()->data->size(); } // 底层Quadlist的规模
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
bool Skiplist<K, V>::put(K k, V v) { // 跳转表词条插入算法
	Entry<K, V> e = Entry<K, V>(k, v); // 待插入的词条（将被随机地插入多个副本）
	if (List<Quadlist<Entry<K, V>>*>::empty()) List<Quadlist<Entry<K, V>>*>::insertAsFirst(new Quadlist<Entry<K, V>>); // 插入首个Entry
	ListNode<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first(); // 从顶层四联表的
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); // 从首节点出发
	if (skipSearch(qlist, p, k)) // 查找适当的插入位置
		while (p->below) p = p->below; // 若已有雷同词条，则需强制转到塔底
	qlist = List<Quadlist<Entry<K, V>>*>::last(); // 以下，紧邻于p的右侧，一座新塔将自底而上逐层生长
	QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p); // 新节点b即新塔基底
	while (rand() & 1) { // 经投硬币，若确定新塔需要再长高一层，则
		while (qlist->data->valid(p) && !p->above) p = p->pred; // 找不出不低于此高度的最近前驱
		if (!qlist->data->valid(p)) { // 若该前驱是header
			if (qlist == List<Quadlist<Entry<K, V>>*>::first()) // 且当前已是最顶层，则意味着必须
				List<Quadlist<Entry<K, V>>*>::insertAsFirst(new Quadlist <Entry<K, V>>); // 首先创建新的一层，然后
			p = qlist->pred->data->first()->pred; // 将p转至上一层Skiplist的header
		}
		else { // 否则，可径直
			p = p->above; //　将ｐ提升至该高度
		}
		qlist = qlist->pred; // 上升一层，并在该层
		b = qlist->data->insertAfterAbove(e, p, b); // 将新节点插入p之后、b之上
	}
	return true; // Dictionary允许重复元素，故插入必成功——这与Hashtable等Map略有差异
}

template<typename K, typename V>
V* Skiplist<K, V>::get(K k) { // 跳转表词条查找算法
	if (List<Quadlist<Entry<K, V>>*>::empty()) return NULL;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first(); // 从顶层Quadlist的
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); // 首节点开始
	return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL; // 查找并报告
} // 有多个命中时靠后者优先

template<typename K, typename V>
bool Skiplist<K, V>::remove(K k) { // 跳转表词条删除算法
	if (List<Quadlist<Entry<K, V>>*>::empty()) return false; // 空表情况
	ListNode<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first(); // 从顶层Quadlist的
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); // 首节点开始
	if (!skipSearch(qlist, p, k)) return false; // 目标词条不存在，直接返回
	do {
		QuadlistNode<Entry<K, V>>* lower = p->below; // 记住下一层节点，并
		qlist->data->remove(p); // 删除当前层节点
		p = lower; qlist = qlist->succ; // 转入下一层
	} while (qlist->succ); // 如上不断重复，直到塔基
	while (!List<Quadlist<Entry<K, V>>*>::empty() && List<Quadlist<Entry<K, V>>*>::first()->data->empty()) { // 逐一地
		List<Quadlist<Entry<K, V>>*>::remove(List<Quadlist<Entry<K, V>>*>::first()); // 清除已可能不含词条的顶层Quadlist 
	}
	return true; // 删除操作成功完成
}

_DSA_END
#endif // !__SKIPLIST_H__
