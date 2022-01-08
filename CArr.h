#pragma once
#include <iostream>
#include <cassert>
//구조체 탬플릿
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
		tListNode<T>* m_pNode; //null인 경우 end()로 간주
	public:
		//넣어준 데이터 타입 T, 수정하기 위해 래퍼런스 변수로 받음
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
			//end에서 ++한 경우
			if (m_pNode == nullptr)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pNext; //다음을 가리킴
			return *this;
		}
		iterator& operator--()
		{
			//처음 주소에서 --한 경우
			if (m_pNode == pHeadNode)
			{
				static_assert(nullptr);
			}
			m_pNode = m_pNode->pPrev; //(전)을 가리킴
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
	tListNode<T>* pNewNode = new tListNode<T>(_Data, nullptr, nullptr); //동적할당(TlistNode 자료형 크기만큼)

	//새로 생성된 노드의 다음을 현재 헤드노드의 주소값을 변경(일명 : 똥꼬치기 기법)
	pHeadNode->pPrev = pNewNode;

	//리스트가 새로 생성된 노드를 새로운 헤드주소로 갱신한다.
	pHeadNode = pNewNode;
	iCount++;
}

template<typename T>
void CList<T>::push_back(const T& _Data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_Data, nullptr, nullptr); //동적할당(TlistNode 자료형 크기만큼)
	//처음 입력된 데이터라면
	if (pHeadNode == nullptr)
	{
		this->pHeadNode = pNewNode;
		this->p_Tail = pNewNode;
	}
	else
	{
		//데이터가 1개 이상이라도 있다면
		//현재 가장 마지막 데이터(tail) 를 저장하고 있는 노드와
		//새로 생성된 노드가 서로 가르키도록
		p_Tail->pNext = pNewNode;
		pNewNode->pPrev = p_Tail;

		//List가 마지막 노드의 주소값을 새로 입력된 노드로 갱신한다.
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
	while (pDeletNode) //첫번쨰 조건문에서 헤드노드 > 두번째 조건문에서는 현재 노드, 다음 조건문부터는 노드가 있는지 확인함.
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


	//만약 -헤드 노드일 경우
	if (_iter.m_pNode == pHeadNode)
	{
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;

		pHeadNode = pNode;
	}
	//iter 가 가리키고 있는 이전 주소로 가서
	//다음 노드 주소 파트를 생성한 노드로 지정
	_iter.m_pNode->pPrev->pNext = pNode;
	//연결
	pNode->pPrev = _iter.m_pNode->pPrev;
	_iter.m_pNode->pPrev = pNode;
	pNode->pNext = _iter.m_pNode;	

	iCount++;
	return iterator(this, pHeadNode);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::erase(iterator& _iter)
{

	//head일 떄 예외처리
	if (_iter.m_pNode == pHeadNode)
	{
		_iter.m_pNode->pNext->pPrev = nullptr;
		pHeadNode = _iter.m_pNode->pNext;
		iCount--;
		return iterator(this, pHeadNode);
	}
	//연결 고리 덮어쓰기(일명 : 꼬리 자르기)
	_iter.m_pNode->pPrev->pNext = _iter.m_pNode->pNext;
	_iter.m_pNode->pNext->pPrev = _iter.m_pNode->pPrev;
	iCount--;
	return iterator(this, pHeadNode);
}