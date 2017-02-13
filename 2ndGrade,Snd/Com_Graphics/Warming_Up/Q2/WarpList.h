#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////

template<typename Ty> // 선언만 우선적으로 해 놓는다.
class WarpList;

template<typename Ty> // 세미콜론 여기다 붙이지 마라
class WarpNode {
private:
	friend class WarpList<Ty>;

	WarpNode* m_pNext{ nullptr };
	WarpNode* m_pPrev{ nullptr }; // 초기값은 nullptr 로 중괄호 초기화
public:
	Ty m_Elem; // Ty는 클래스

			   //생성자
	WarpNode() = default;
	WarpNode(Ty& elem) : m_Elem(elem) {};
	WarpNode(Ty&& elem) : m_Elem(move(elem)) {};

	WarpNode* prev() { return m_pPrev; }
	WarpNode* next() { return m_pNext; }
};

/////////////////////////////////////////////////////////

//반복자를 만드러보자;
template<typename Ty>
class WarpIterator {
public:

	friend class WarpList<Ty>;
	using Node = WarpNode<Ty>;

private:

	explicit WarpIterator(Node* p) : m_pNode(p) {	}
	Node* m_pNode = nullptr;

public:

	Ty& operator*() { return m_pNode->m_Elem; }
	Ty* operator->() { return &(m_pNode->m_Elem); }
	WarpIterator operator=(WarpIterator& other) { m_pNode = other.m_pNode; return *this; }

	bool operator==(WarpIterator& other) const { return (m_pNode == other.m_pNode); }
	bool operator!=(WarpIterator& other) const { return (m_pNode != other.m_pNode); }

	WarpIterator& operator++() { m_pNode = m_pNode->next(); return *this; }
	WarpIterator operator++(int)
	{
		auto p = *this;
		//m_pNode = m_pNode->next();
		++(*this);
		return p;
	}

	WarpIterator& operator--() { m_pNode = m_pNode->prev(); return *this; }
	WarpIterator operator--(int)
	{
		auto p = *this;
		//m_pNode = m_pNode->next();
		--(*this);
		return p;
	}

};

template<typename Ty> // !! 바로 여기에
class WarpList {
public:
	using type = Ty; // WarpList 안에 Ty라는 자료형이 있다.
	using Node = WarpNode<Ty>; // using 을 쓴다.
	using iterator = WarpIterator<Ty>;
private:
	Node m_wnHead;
	Node m_wnTail; // 이거 포인터가 아니다. 항상 헤드 테일은 남아있다.

public:


	//WarpNode m_wnhead -> 그냥 이렇게 하면 오류나고
	//WarpNode<Ty> m_wnhead; -> 해도 오류가 나니까 !!부분에 (위에 11번줄) 템플릿 한번 더 선언
	//생성자
	WarpList()
	{
		m_wnHead.m_pNext = &m_wnTail;
		m_wnTail.m_pPrev = &m_wnHead; // 서로 연결을 시킨다. 
	}


	void push_front(Ty elem) // 뒤로 밀어넣기
	{
		Node *newNode = new Node(elem);
		Node *& oldFirst = m_wnHead.m_pNext; // 헤드의 다음꺼

		oldFirst->m_pPrev = newNode;
		newNode->m_pNext = oldFirst;

		newNode->m_pPrev = &m_wnHead;
		m_wnHead.m_pNext = newNode;
	}

	void push_back(Ty elem) // 뒤로 밀어넣기
	{
		Node *newNode = new Node(elem);
		Node *& oldLast = m_wnTail.m_pPrev; //테일의 이전꺼

		oldLast->m_pNext = newNode;
		newNode->m_pPrev = oldLast;

		newNode->m_pNext = &m_wnTail;
		m_wnTail.m_pPrev = newNode;
	}

	bool insert(Ty elem, iterator Where) /*   // Node* 는 하나니까 중복이 될 수 없다*/
	{ // where의 앞에 삽입, 실패가능성 있으니 bool 로 반환
		iterator p = begin();

		while (p.m_pNode != nullptr)
		{
			if (p == Where)
			{
				Node *FindNode = p.m_pNode->m_pPrev;
				Node * WhereNode = FindNode->m_pNext;
				Node *newNode = new Node(elem);

				FindNode->m_pNext = newNode;
				newNode->m_pPrev = FindNode;

				newNode->m_pNext = WhereNode;
				WhereNode->m_pPrev = newNode;


				return true; // 성공했으니 true;
			}
			++p;
		}
		return false;
	}

	bool remove(Ty elem, bool AllRemove = true)
	{//elem 값이 똑같을 경우에만 자르자
		Node*p = m_wnHead.m_pNext;
		size_t szDeleteCount = 0;
		while (p->m_pNext != nullptr)
		{
			if (p->m_Elem == elem)
			{
				Node* oldNext = p->m_pNext;
				Node* oldPrev = p->m_pPrev;
				// Node*& 하면 oldprev 이런거까지 싹 바뀌기 때문에 참조는 다매요
				oldNext->m_pPrev = oldPrev;
				oldPrev->m_pNext = oldNext;

				delete p;

				if (AllRemove == true)
				{
					p = oldNext;
					szDeleteCount++;
					continue;
				}
				else return true;

			}
			p = p->m_pNext;
		}
		return (szDeleteCount > 0); // 괄호는 보험 --> bool
	}

	template<typename Fn>
	bool remove_if(Fn& fn)//bool 함수포인터가 있다고 가정하자
	{//elem 값이 똑같을 경우에만 자르자
		Node*p = m_wnHead.m_pNext;
		size_t szDeleteCount = 0;

		while (p->m_pNext != nullptr)
		{
			if (fn(p->m_Elem))
			{
				Node* oldNext = p->m_pNext;
				Node* oldPrev = p->m_pPrev;

				oldNext->m_pPrev = oldPrev;
				oldPrev->m_pNext = oldNext;

				delete p;
				szDeleteCount++;
				p = oldNext;
				continue;
			}
			p = p->m_pNext;
		}
		return (szDeleteCount > 0);
	}

	iterator find(Ty elem)
	{
		for (iterator p = begin(); p != end(); p = ++p)
		{
			if (elem == *p) return p;
		}
		return (end());
	}

	iterator begin()
	{
		return iterator(m_wnHead.m_pNext);
		// 헤드도 정적할당된 필드이기 때문에
		// -> 이 아닌 . 으로 연결한다.
	} // 센티널 노드 참조 :: 보충 노드 

	  // const Node* end() 로 쓰면 문법상으로 무시되지만 (지금 이거 안쓰면 망하지만)
	  // 다른 이에게 넘겨줄때 이 함수값이 변형되면 안된다는 사실을 명시 할 수 있다.
	iterator end() // const 로 상수화 하여 값을 못 바꾸게 한다.
	{
		return iterator(&m_wnTail);
		// 테일은 정적할당된 필드이기 때문에
		// End를 Delete할려고 하면 에러가 난다.
	}

	// Ty값을 이동반환하자
	Ty pop_front()
	{
		Ty retval = move(m_wnHead.next()->m_Elem);

		Node* oldBegin = m_wnHead.next();
		Node* oldNext = oldBegin->m_pNext;
		Node* oldPrev = &m_wnHead;

		oldNext->m_pPrev = oldPrev;
		oldPrev->m_pNext = oldNext;

		delete oldBegin;


		return move(retval);
	}

	Ty pop_back()
	{
		//Ty retval = move(*(end()--));
		Ty retval = move(m_wnTail.m_pPrev->m_Elem);

		Node* oldEnd = m_wnTail.m_pPrev;
		Node* oldNext = &m_wnTail;
		Node* oldPrev = oldEnd->m_pPrev;

		oldNext->m_pPrev = oldPrev;
		oldPrev->m_pNext = oldNext;

		delete oldEnd;

		return move(retval);
	}
};