// vector.h
#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "dsa.h"
#include "fib.h"
#include <cstdlib>
_DSA_BEGIN
typedef int Rank; // ��
#define DEFAULT_CAPACITY 3 // Ĭ�ϵĳ�ʼ����

template <typename T>
class Vector {
protected:
	Rank _size; int _capacity; T* _elem; // ��ģ��������������
	void copyForm(T const* A, Rank lo, Rank hi); // ������������A[lo, hi)
	void expand(); // �ռ䲻��ʱ����
	void shrink(); // װ�����ӹ�Сʱѹ��
	bool bubble(Rank lo, Rank hi); // ɨ�轻��
	void bubbleSort(Rank lo, Rank hi); // ���������㷨
	Rank max(Rank lo, Rank hi); // ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi); // ѡ�������㷨
	void insertSort(Rank lo, Rank hi); // ���������㷨
	void merge(Rank lo, Rank mi, Rank hi); // �鲢�㷨
	void mergeSort(Rank lo, Rank hi); // �鲢�����㷨
	Rank partition(Rank lo, Rank hi); // ��㹹���㷨
	void quickSort(Rank lo, Rank hi); // ���������㷨
	void heapSort(Rank lo, Rank hi); // �������㷨
public:
	// ���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) // ����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{
		_elem = new T[_capacity = c]; 		
		for (_size = 0; _size < s; _elem[_size++] = v); // s<=c
	}
	Vector(T const* A, Rank n) { copyForm(A, 0, n); } // �������帴��
	Vector(T const* A, Rank lo, Rank hi) { copyForm(A, lo, hi); } // ����
	Vector(Vector<T> const& v) { copyForm(v._elem, 0, v._size); } // �������帴��
	Vector(Vector<T> const& v, Rank lo, Rank hi) { copyForm(v._elem, lo, hi); } // ����
	// ��������
	~Vector() { delete[] _elem; } // �ͷ��ڲ��ռ�
	// ֻ�����ʽӿ�
	Rank size() const { return _size; } // ��ģ
	bool empty() const { return !_size; } // �п�
	int disordered() const; // �ж������Ƿ�������
	Rank find(T const& e) const { return find(e, 0, _size); } // ���������������
	Rank find(T const& e, Rank lo, Rank hi) const; // ���������������
	Rank search(T const& e) const // ���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const; // ���������������
	// ��д���ʽӿ�
	T& operator[] (Rank r) const; // �����±������������������������ʽ���ø�Ԫ��
	Vector<T>& operator=(Vector<T> const&); // ���ظ��Ʋ��������Ա�ֱ�ӿ�¡����
	T remove(Rank r); // ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi); // ɾ������[lo, hi)֮���Ԫ��
	Rank insert(Rank r, T const& e); // ����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); }  // Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi); // ��[lo, hi)����
	void sort() { sort(0, _size); } // ��������
	void unsort(Rank lo, Rank hi); // ��[lo, hi)����
	void unsort() { unsort(0, _size); } // ��������
	int deduplicate(); // ����ȥ��
	int uniquify(); // ����ȥ��
	// ����
	void traverse(void(*visit)(T&)); // ������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	template<typename VST> void traverse(VST& visit); // ������ʹ�ú������󣬿�ȫ�����޸ģ�
}; // Vector

/*
template<typename T>
void permute(Vector<T>& V) { // �������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
	for (int i = V.size(); i > 0; i--) { // �Ժ���ǰ
		swap(V[i - 1], V[rand() % i]); // V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
	}
}
*/

/*
// ���ֲ����㷨���汾A��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= size
template<typename T> 
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	while (lo < hi) { // ÿ����������Ҫ�����αȽ��жϣ���������֧
		Rank mi = (lo + hi) >> 1; // ���е�Ϊ��
		if (e < A[mi]) hi = mi; // ����ǰ���[lo, mi)��������
		else if (A[mi] < e) lo = mi + 1; // �������(mi, hi)��������
		else return mi; // ��mi������
	} // �ɹ����ҿ�����ǰ��ֹ
	return -1; // ����ʧ��
} // �ж������Ԫ�ص�ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��
*/

// Fibonacci�����㷨���汾A��������������������[lo, hi)�ڲ���e��0 <= lo <= hi <= size
template<typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
	Fib fib(hi - lo); // ��O(log_phi(n = hi -lo))ʱ�䴴��Fib����
	while (lo < hi) { // ÿ�ε�������Ҫ�������жϣ���������֧
		while (hi - lo < fib.get()) fib.prev(); // ͨ����ǰ˳����ң���̯O(1)��
		Rank mi = lo + fib.get() - 1; // ȷ������Fib(k)-1�����
		if (e < A[mi]) hi = mi; // ����ǰ���[lo, mi)��������
		else if (A[mi] < e) lo = mi + 1; // �������(mi, hi)��������
		else return mi; // ��mi������
	} // �ɹ����ҿ�����ǰ��ֹ
	return -1; // ����ʧ��
} // �ж������Ԫ�ص�ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��

/*
// ���ֲ����㷨���汾B��������������������[lo, hi)�ڲ���e��0 <= lo <= hi <= size
template<typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	while (1 < hi - lo) { // ÿ������������һ�αȽ��жϣ���������֧���ɹ����Ҳ�����ǰ��ֹ
		Rank mi = (lo + hi) >> 1; // ���е�Ϊ��
		(e < A[mi]) ? hi = mi : lo = mi; // ���Ƚ�ȷ������[lo, mi)��[mi, hi)
	} // ����ʱhi = lo + 1�������������һ��Ԫ��A[lo]
	return (e == A[lo]) ? lo : -1; // ���ҳɹ�����ʱ��Ӧ���ȣ�����ͳһ����-1
} // �ж������Ԫ�ص�ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��
*/

// ���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���e��0 <= lo <= hi <= size
template<typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	while (lo < hi) { // ÿ������������һ�αȽ��жϣ���������֧
		Rank mi = (lo + hi) >> 1; // ���е�Ϊ��
		(e < A[mi]) ? hi = mi : lo = mi + 1; // ���Ƚ�ȷ������[lo, mi)��[mi, hi)
	} // �ɹ����Ҳ�����ǰ��ֹ
	return --lo; // ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
} // �ж������Ԫ�ص�ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��

template<typename T>
void Vector<T>::copyForm(T const* A, Rank lo, Rank hi) { // ����������A[lo, hi)Ϊ������������
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0; // ����ռ䣬��ģ����
	while (lo < hi) {  // A[lo, hi)�ڵ�Ԫ����һ����
		_elem[_size++] = A[lo++]; // ������_elem[0, hi - lo)
	}
}

template<typename T>
void Vector<T>::expand() { // �����ռ䲻��ʱ����
	if (_size < _capacity) return; // ��δ��Աʱ����������
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; // ��������С����
	T* oldElem = _elem; _elem = new T[_capacity <<= 1]; // �����ӱ�
	for (int i = 0; i < _size; i++) {
		_elem[i] = oldElem[i]; // ����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
	}
	delete[] oldElem; // �ͷ�ԭ�ռ�
}

template<typename T>
void Vector<T>::shrink() { // װ�����ӹ�Сʱѹ��������ռ�ռ�
	if (_capacity < DEFAULT_CAPACITY << 1) return; // ����������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity) return; // ��25%Ϊ��
	T* oldElem = _elem; _elem = new T[_capacity >>= 1]; // ��������
	for (int i = 0; i < _size; i++) {
		_elem[i] = oldElem[i]; // ����ԭ��������
	}
	delete[] oldElem; // �ͷ�ԭ�ռ�
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) { // һ��ɨ�轻��
	bool sorted = true; // ���������־
	while (++lo < hi) { // �������ң���һ����������Ԫ��
		if (_elem[lo] < _elem[lo - 1]) { // ��������
			sorted = false;  // ��ζ�����岻���򣬲���Ҫ
			swap(_elem[lo], _elem[lo - 1]); // ͨ������ʹ�ֲ�����
		}
	}
	return sorted; // ���������־
}

template<typename T> // ������������
void Vector<T>::bubbleSort(Rank lo, Rank hi) { // assert: 0 <= lo < hi <= size
	while (!bubble(lo, hi--)); // ������ɨ�轻����ֱ��ȫ��
}

template<typename T>
inline Rank Vector<T>::max(Rank lo, Rank hi) { // ��[lo, hi]���ҳ������
	Rank mx = hi;
	while (lo < hi--) { // ����ɨ��
		if (_elem[hi] > _elem[mx]) { // ���ϸ�Ƚ�
			mx = hi; // ������max�ж��ʱ��֤�������ȣ�������֤selectionSort�ȶ�
		}
	}
	return mx;
}

template<typename T> // ����ѡ������
void Vector<T>::selectionSort(Rank lo, Rank hi) { // assert: 0 < lo <= hi <= size
	while (lo < --hi) {
		swap(_elem[max(lo, hi)], _elem[hi]); // ��[hi]��[lo, hi]�е�����߽���
	}
}

template<typename T> // ������������
inline void Vector<T>::insertSort(Rank lo, Rank hi) { // assert: 0 < lo <= hi <= size
	for (int j = lo + 1; j < hi; j++) { // ѭ���²����Ԫ��
		T key = _elem[j]; // �����²����Ԫ��
		int i = j - 1; // ���������е����һ��Ԫ��
		while (i >= lo && key < _elem[i]) { // ������������дӺ���ǰ�Ƚ�
			_elem[i + 1] = _elem[i]; // �����²���Ԫ�ص�������
			i--; 
		}
		_elem[i + 1] = key; // ������Ԫ��
	}
}

template<typename T> // ���������Ĺ鲢
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { // ���������������[lo, mi)��[mi, hi)
	T* A = _elem + lo; // �ϲ�������A[0, hi - lo) = _elem[lo, hi)
	int lb = mi - lo; T* B = new T[lb]; // ǰ������B[0, lb) = _elem[lo, mi)
	for (Rank i = 0; i < lb; i++) B[i] = A[i]; // ����������
	int lc = hi - mi; T* C = _elem + mi; // ��������C[0, lc) = _elem[mi, hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) { // B[j]��C[k]�е�С������Aĩβ
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) A[i++] = C[k++];
	}
	delete[] B; // �ͷ���ʱ�ռ�B
} // �鲢��õ���������������[lo, hi)

template<typename T> // �����鲢����
void Vector<T>::mergeSort(Rank lo, Rank hi) { //  assert: 0 <= lo < hi <= size
	if (hi - lo < 2) return; // ��Ԫ��������Ȼ���򣬷���...
	int mi = (lo + hi) >> 1; // ���е�Ϊ��
	mergeSort(lo, mi); mergeSort(mi, hi); // �ֱ�����
	merge(lo, mi, hi); // �鲢
}

template<typename T> // ��㹹���㷨��ͨ������Ԫ��λ�ù�������[lo, hi]����㣬����������
Rank Vector<T>::partition(Rank lo, Rank hi) { // �汾A��������ʽ
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]); // ��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; // ����Ԫ��Ϊ��ѡ��㡪�������Ͻ�������Ч�����ѡȡ
	while (lo < hi) { // �����������˽�������м�ɨ��
		while ((lo < hi) && (pivot <= _elem[hi])) // �ڲ�С��pivot��ǰ����
			hi--; // �����ؿ���������
		_elem[lo] = _elem[hi]; // С��pivot�߹������������
		while ((lo < hi) && (_elem[lo] <= pivot)) // �ڲ�����pivot��ǰ����
			lo++; // �����ؿ���������
		_elem[hi] = _elem[lo]; // ����pivot�����Ҳ�������
	} // assert: lo == hi
	_elem[lo] = pivot; // �����ݵ�����¼����ǰ����������֮��
	return lo; // ����������
}

template<typename T> // ������������
void Vector<T>::quickSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
	if (hi - lo < 2) return; // ��Ԫ��������Ȼ���򣬷���...
	Rank mi = partition(lo, hi - 1); // ��[lo, hi - 1]�ڹ������
	quickSort(lo, mi); // ��ǰ׺�ݹ�����
	quickSort(mi + 1, hi); // �Ժ�׺�ݹ�����
}

template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
	PQ_ComplHeap<T> H(_elem + lo, hi - lo); // �����������佨��һ����ȫ����ѣ�O(n)
	while (!H.empty()) { // ������ժ�����Ԫ������������ĺ�׺ֱ���ѿ�
		_elem[--hi] = H.delMax(); // ��Ч�ڶѶ���ĩԪ�ضԻ�������
	}
}

template<typename T>
int Vector<T>::disordered() const { // ������������������Ԫ�ضԵ�����
	int n = 0; // ������
	for (int i = 1; i < _size; i++) {
		if (_elem[i] < _elem[i - 1]) {
			n++; // ���������
		}
	}
	return n; // ���������ҽ���n = 0
}

template<typename T> // ����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ���ǣ�����lo - 1
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const { // assert: 0 <= lo < hi <= size
	while ((lo < hi--) && (e != _elem[hi])); // �Ӻ���ǰ��˳�����
	return hi; // ��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}

template<typename T> // ����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const { // assert: 0 <= lo < hi <= size
	/*
	return (rand() % 2) ? // ����50%�������ʹ�ö��ֲ��һ�Fibonacci����
		binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
		*/
	return binSearch(_elem, e, lo, hi);
}

template<typename T>
T& Vector<T>::operator[](Rank r) const { // �����±������
	return _elem[r]; // assert: 0 <= r < _size
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) { // ����
	if (_elem) delete[] _elem; // �ͷ�ԭ������
	copyForm(V._elem, 0, V.size()); // ���帴��
	return *this; // ���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template<typename T>
T Vector<T>::remove(Rank r) { // ɾ����������Ϊr��Ԫ�أ�0 <= r < size
	T e = _elem[r]; // ���ݱ�ɾ��Ԫ��
	remove(r, r + 1); // ��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; // ���ر�ɾ����Ԫ��
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) { // ɾ������[lo, hi)
	if (lo == hi) return 0; // ����Ч�ʿ��ǣ����������˻����������remove(0, 0)
	while (hi < _size) _elem[lo++] = _elem[hi++]; // [hi, _size)˳��ǰ��hi - lo����λ
	_size = lo; // ���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
	shrink(); // ���б�Ҫ��������
	return hi - lo; // ���ر�ɾ��Ԫ�ص���Ŀ
}

template<typename T> // ��e��Ϊ��ΪrԪ�ز���
Rank Vector<T>::insert(Rank r, T const& e) { // assert: 0 <= r <= size
	expand(); // ���б�Ҫ������
	for (int i = _size; i > r; i--) {
		_elem[i] = _elem[i - 1]; // �Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
	}
	_elem[r] = e; _size++; // ������Ԫ�ز���������
	return r; // ������
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) { // ��������[lo, hi)����
	/*
	switch (rand()%5) { // ���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������
	case 1: bubbleSort(lo, hi); break; // ��������
	case 2: selectionSort(lo, hi); break; // ѡ������
	case 3: mergeSort(lo, hi); break; // �鲢����
	case 4: heapSort(lo, hi); break; // ������
	default: quickSort(lo, hi); break; // ��������
	}
	*/
	quickSort(lo, hi);
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) { // �ȸ��������������[lo, hi)
	T* V = _elem + lo; // ��������_elem[lo,hi)������һ����V[0,hi - lo)
	for (Rank i = hi - lo; i > 0; i--) { // �Ժ���ǰ
		swap(V[i - 1], V[rand() % i]); // ��V[i - 1]��V[0, i)��ĳһԪ���������
	}
}

template<typename T>
int Vector<T>::deduplicate() { // ɾ�������������ظ�Ԫ�أ���Ч��)
	int oldSize = _size; // ��¼ԭ��ģ
	Rank i = 1; // ��_elem[1]��ʼ
	while (i < _size) { // ��ǰ�����һ�����Ԫ��_elem[i]
		(find(_elem[i], 0, i) < 0) ? // ����ǰ׺��Ѱ����֮��ͬ�ߣ�����һ����
			i++ : remove(i); // ������ͬ�ͼ����������̣�����ɾ����ͬ��
	}
	return oldSize - _size; // ������ģ�仯��������ɾ��Ԫ������
}

template<typename T>
int Vector<T>::uniquify() { // ���������ظ�Ԫ���޳��㷨
	Rank i = 0, j = 0; // ���Ի��조����Ԫ�ص��ȡ�
	while (++j < _size) { // ��һɨ�裬ֱ��ĩԪ��
		if (_elem[i] != _elem[j]) { // ������ͬ��
			_elem[++i] = _elem[j]; // ���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
		}
	}
	_size = ++i; shrink(); // ֱ�ӽس�β������Ԫ��
	return j = i; // ������ģ�仯��������ɾ��Ԫ������
}

template<typename T>
void Vector<T>::traverse(void(*visit)(T&)) { // ��������ָ�����
	for (int i = 0; i < _size; i++) visit(_elem[i]); // ��������
}

template<typename T> template<typename VST> // Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) { // ���������������
	for (int i = 0; i < _size; i++) visit(_elem[i]); // ��������
}

_DSA_END
#endif // !__VECTOR_H__
