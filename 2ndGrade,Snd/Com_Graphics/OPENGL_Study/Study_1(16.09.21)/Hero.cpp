#include "Hero.h"



CHero::CHero()
{
	m_prev = nullptr;
	m_next = nullptr;
}

CHero::CHero(bool InsertDirect)
{
	cout << "Insert Name";
	cin >> m_name;
	cout << "Hp :: ";
	cin >> m_hp;
	cout << "Mp :: ";
	cin >> m_mp;
	cout << "Attk :: ";
	cin >> m_attack;

	m_prev = nullptr;
	m_next = nullptr;
}

CHero::~CHero()
{
}

void CHero::LinkPrevNode(CHero * X)
{
	m_prev = X;
}


void CHero::LinkNextNode(CHero * X)
{
	m_next = X;
}

void CHero::Isalive()
{
	if (m_hp > 0) {
		cout << m_name << " Is Alive , WInner.." << endl;
		cout << "HP :: " <<m_hp << "|";
		cout << "MP :: " << m_mp << "|";
		cout << "ATTK :: " << m_attack << "|";
	}



}

int CHero::Attack()
{
	cout << m_name << " Do attack!!" << endl;
	return m_attack;
}

void CHero::InterActHero(int attk)
{
	m_hp -= attk;
	cout << m_name << " is Damaged,, Remain Hp is " << m_hp << endl;
	if (m_hp <= 0) cout << m_name << " is Dead,, " << endl;
}
