#pragma once
#include<iostream>

using namespace std;

class CHero
{
private:
	char m_name[20];
	int m_hp;
	int m_mp;
	int m_attack;

	CHero * m_prev;
	CHero * m_next;
public:
	CHero();
	CHero(bool InsertDirect);
	~CHero();

	void InterActHero(int attk);
	int Attack();
	void Isalive();

	void LinkPrevNode(CHero * X);
	void LinkNextNode(CHero * X);
	CHero * GetPrev() { return m_prev; }
	CHero * GetNext() { return m_next; }

	
	int GetHP() const { return m_hp; }
	
};

