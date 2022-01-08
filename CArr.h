#pragma once
#include <iostream>
#include <cassert>
//����ü ���ø�
template<typename T>
struct tListNode
{
	T data;
	tListNode<T>* pNext;
	tListNode<T>* pPrev;
	tListNode() : data(0), pNext(nullptr), pPrev(nullptr)
	{ 

	}
	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext)
		: data(_data)
		, pPrev(_pPrev)
		, pNext(_pNext)
	{

	}
};

template<typename T>
class CList
{
private:
	tListNode<T>* pHeadNode;
	tListNode<T>* p_Tail;
	int iCount;
public:
	void push_back(const T& _Data);
	void push_front(const T& _Data);
	void Print();

public:
	class iterator;
	iterator begin();
	iterator end();	
	iterator erase(iterator& _iter);
	iterator insert(iterator& _iter, const T& _data);
public:
	CList();
	~CList();

	class iterator 
	{
	private:
		CList<T>* m_pList;
		tListNode<T>* m_pNode; //null�� ��� end()�� ����
	public:
		//�־��� ������ Ÿ�� T, �����ϱ� ���� ���۷��� ������ ����
		T& operator* ()
		{
			return m_pNode->data;
		}
		bool operator== (const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return true;
			}
			return false;
		}
		bool operator !=(const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return false;
			}
			return true;
		}

		iterator operator ++(int)
		{
			iterator copyiter = *this;
			++(*this);
			return copyiter;
		}
		iterator operator --(int)
		{
			iterator copyiter = *this;
			--(*this);
			return copyiter;
		}
		iterator& operator++()
		{
			//end���� ++�� ���
			if (m_pNode == nullptr)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pNext; //������ ����Ŵ
			return *this;
		}
		iterator& operator--()
		{
			//ó�� �ּҿ��� --�� ���
			if (m_pNode == pHeadNode)
			{
				static_assert(nullptr);
			}
			m_pNode = m_pNode->pPrev; //(��)�� ����Ŵ
			return *this;
		}
	public:
		iterator() : m_pList(nullptr), m_pNode(nullptr)
		{
		}
		iterator(CList<T>* _pList, tListNode<T>* _pNode) 
			: m_pList(_pList)
			, m_pNode(_pNode)
		{
		}
		~iterator()
		{

		}
		friend class CList;

	};
};

template<typename T>
void CList<T>::push_front(const T& _Data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_Data, nullptr, nullptr); //�����Ҵ�(TlistNode �ڷ��� ũ�⸸ŭ)

	//���� ������ ����� ������ ���� ������� �ּҰ��� ����(�ϸ� : �˲�ġ�� ���)
	pHeadNode->pPrev = pNewNode;

	//����Ʈ�� ���� ������ ��带 ���ο� ����ּҷ� �����Ѵ�.
	pHeadNode = pNewNode;
	iCount++;
}

template<typename T>
void CList<T>::push_back(const T& _Data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_Data, nullptr, nullptr); //�����Ҵ�(TlistNode �ڷ��� ũ�⸸ŭ)
	//ó�� �Էµ� �����Ͷ��
	if (pHeadNode == nullptr)
	{
		this->pHeadNode = pNewNode;
		this->p_Tail = pNewNode;
	}
	else
	{
		//�����Ͱ� 1�� �̻��̶� �ִٸ�
		//���� ���� ������ ������(tail) �� �����ϰ� �ִ� ����
		//���� ������ ��尡 ���� ����Ű����
		p_Tail->pNext = pNewNode;
		pNewNode->pPrev = p_Tail;

		//List�� ������ ����� �ּҰ��� ���� �Էµ� ���� �����Ѵ�.
		p_Tail = pNewNode;
	}
	iCount++;
}

template<typename T>
void CList<T>::Print()
{
	tListNode<T>* pLists = pHeadNode;
	for (int i = 0; i < iCount; i++)
	{
		printf("%c", pLists->data);
		pLists = pLists->pNext;
	}
}

template<typename T>
CList<T>::CList() : pHeadNode(nullptr), p_Tail(nullptr), iCount(0)
{

}

template<typename T>
CList<T>::~CList()
{
	tListNode<T>* pDeletNode = pHeadNode;
	while (pDeletNode) //ù���� ���ǹ����� ����� > �ι�° ���ǹ������� ���� ���, ���� ���ǹ����ʹ� ��尡 �ִ��� Ȯ����.
	{
		tListNode<T>* pNext = pDeletNode->pNext;
		delete(pDeletNode);
		pDeletNode = pNext;
	}
}

template<typename T>
inline typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this, pHeadNode);
}
template<typename T>
inline typename CList<T>::iterator CList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::insert(iterator& _iter, const T& _data)
{
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);


	//���� -��� ����� ���
	if (_iter.m_pNode == pHeadNode)
	{
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;

		pHeadNode = pNode;
	}
	//iter �� ����Ű�� �ִ� ���� �ּҷ� ����
	//���� ��� �ּ� ��Ʈ�� ������ ���� ����
	_iter.m_pNode->pPrev->pNext = pNode;
	//����
	pNode->pPrev = _iter.m_pNode->pPrev;
	_iter.m_pNode->pPrev = pNode;
	pNode->pNext = _iter.m_pNode;	

	iCount++;
	return iterator(this, pHeadNode);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::erase(iterator& _iter)
{

	//head�� �� ����ó��
	if (_iter.m_pNode == pHeadNode)
	{
		_iter.m_pNode->pNext->pPrev = nullptr;
		pHeadNode = _iter.m_pNode->pNext;
		iCount--;
		return iterator(this, pHeadNode);
	}
	//���� �� �����(�ϸ� : ���� �ڸ���)
	_iter.m_pNode->pPrev->pNext = _iter.m_pNode->pNext;
	_iter.m_pNode->pNext->pPrev = _iter.m_pNode->pPrev;
	iCount--;
	return iterator(this, pHeadNode);
}