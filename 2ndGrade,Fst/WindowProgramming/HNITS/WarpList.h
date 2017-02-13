#pragma once
template<typename Ty> // !! �ٷ� ���⿡
class WarpList;

template<typename Ty> // �����ݷ� ������ ����
class WarpNode {
private:
	friend class WarpList<Ty>;

	WarpNode* m_pNext{ nullptr };
	WarpNode* m_pPrev{ nullptr }; // �ʱⰪ�� nullptr �� �߰�ȣ �ʱ�ȭ

public:
	Ty m_Elem; // Ty�� Ŭ����

	//������
	WarpNode() = default;
	WarpNode(Ty& elem) : m_Elem(elem) {};
	WarpNode(Ty&& elem) : m_Elem(move(elem)) {};

	WarpNode* GetNext() { return m_pNext; }
	WarpNode* GetPrev() { return m_pPrev; }
};

template<typename Ty>
class WarpIterator {
public:

	friend class WarpList<Ty>;
	using Node = WarpNode<Ty>;

private:

	explicit WarpIterator(Node* p) : m_pNode(p) { }
	Node* m_pNode{ nullptr };

public:

	Ty& operator*() { return m_pNode->m_Elem; }
	Ty* operator->() { return &(m_pNode->m_Elem); }
	WarpIterator& operator=(WarpIterator& other) { m_pNode = other.m_pNode; return *this; }

	bool operator==(WarpIterator& other) const { return (m_pNode == other.m_pNode); }
	bool operator!=(WarpIterator& other) const { return (m_pNode != other.m_pNode); }

	WarpIterator& operator++() { m_pNode = m_pNode->GetNext(); return *this; }
	WarpIterator operator++(int)
	{
		auto p = *this;
		++(*this);
		return p;
	}

	WarpIterator& operator--() { m_pNode = m_pNode->Getprev(); return *this; }
	WarpIterator operator--(int)
	{
		auto p = *this;
		--(*this);
		return p;
	}
};

template<typename Ty> // !! �ٷ� ���⿡
class WarpList {

public:
	using type = Ty;
	using Node = WarpNode<Ty>; // using �� ����.
	using iterator = WarpIterator<Ty>;

public:

	//WarpNode m_wnhead -> �׳� �̷��� �ϸ� ��������
	//WarpNode<Ty> m_wnhead; -> �ص� ������ ���ϱ� !!�κп� (���� 11����) ���ø� �ѹ� �� ����
	Node m_wnHead;
	Node m_wnTail; // �̰� �����Ͱ� �ƴϴ�. �׻� ��� ������ �����ִ�.

	//������
	WarpList()
	{
		m_wnHead.m_pNext = &m_wnTail;
		m_wnTail.m_pPrev = &m_wnHead; // ���� ������ ��Ų��. 
	}

	iterator begin() const { return iterator(m_wnHead.m_pNext); }
	iterator end() { return iterator(&m_wnTail); }
	
	void push_front(Ty elem) // �ڷ� �о�ֱ�
	{
		Node *newNode = new Node(elem);
		Node *& oldFirst = m_wnHead.m_pNext; // ����� ������

		oldFirst->m_pPrev = newNode;
		newNode->m_pNext = oldFirst;

		newNode->m_pPrev = &m_wnHead;
		m_wnHead.m_pNext = newNode;
	}

	void push_back(Ty elem) // �ڷ� �о�ֱ�
	{
		Node *newNode = new Node(elem);
		Node *& oldLast = m_wnTail.m_pPrev; //������ ������

		oldLast->m_pNext = newNode;
		newNode->m_pPrev = oldLast;

		newNode->m_pNext = &m_wnTail;
		m_wnTail.m_pPrev = newNode;
	}

	bool insert(Ty elem, iterator Where) 
	{ // where�� �տ� ����, ���а��ɼ� ������ bool �� ��ȯ
		iterator p = begin();

		while (p != iterator(nullptr))
		{
			if (p == Where)
			{
				Node *findNode = p.m_pNode->m_pPrev;
				Node *whereNode = findNode->m_pNext;
				Node *newNode = new Node(elem);

				findNode->m_pNext = newNode;
				newNode->m_pPrev = findNode;

				newNode->m_pNext = whereNode;
				whereNode->m_pPrev = newNode;


				return true; // ���������� true;
			}
			++p;
		}
		return false;
	}

	bool remove(Ty elem, bool AllRemove = true)
	{//elem ���� �Ȱ��� ��쿡�� �ڸ���
		Node*p = m_wnHead.m_pNext;
		size_t szdeleteCount = 0;
		while (p->m_pNext != nullptr)
		{
			if (p->m_Elem == elem)
			{
				Node* oldNext = p->m_pNext;
				Node* oldPrev = p->m_pPrev;
	
				oldNext->m_pPrev = oldPrev;
				oldPrev->m_pNext = oldNext;
	
				delete p;
	
				if (AllRemove == true)
				{
					p = oldNext;
					szdeleteCount++;
					continue;
				}
				else return true;
				
			}
			p = p->m_pNext;
		}
		return (szdeleteCount > 0); // ��ȣ�� ���� --> bool
	}
	
	template<typename Fn>
	bool remove_if(Fn& fn)//bool �Լ������Ͱ� �ִٰ� ��������
	{//elem ���� �Ȱ��� ��쿡�� �ڸ���
		Node* p = m_wnHead.m_pNext;
		size_t szDeleteCount = 0;

		while (p->m_pNext != nullptr)
		{
			if (fn(p->m_Elem))
			{
				Node* oldNext = p->m_pNext;
				Node* oldPrev = p->m_pPrev;

				oldNext->m_pPrev = oldPrev;
				oldPrev->m_pNext = oldNext;

				p->m_pPrev = nullptr;
				p->m_pNext = nullptr;
				delete p;
				p = nullptr;
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
		for (iterator p = begin(); p != end(); ++p)
		{
			if (elem == *p) return p;
		}
		return iterator(nullptr);
	}

	Ty pop_front()
	{
		Ty retval = move(m_wnHead.m_pNext->m_Elem);
		 
		Node* oldBegin = m_wnHead.m_pNext;
		Node* oldNext = m_wnHead.m_pNext->m_pNext;
		Node* oldPrev = &m_wnHead;
	
		oldNext->m_pPrev = oldPrev;
		oldPrev->m_pNext = oldNext;
	
		delete oldBegin;
	
		return move(retval);
	}
	
	Ty pop_back()
	{
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