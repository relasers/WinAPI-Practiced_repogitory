#include <iostream>
#include <conio.h>
#include "Hero.h"

using namespace std;

constexpr int N_of_hero = 2;

CHero * hero_A = new CHero();
CHero * hero_B = new CHero();

void CreateHero();
void Battle();
void Result();

int main()
{
	CreateHero();
	Battle();
	Result();

	return 0;
}

void CreateHero()
{

	CHero * p = hero_A;
	for (int i = 0; i < N_of_hero; ++i) {
		CHero * new_hero = new CHero(true);
		new_hero->LinkPrevNode(p);
		p->LinkNextNode(new_hero);
		hero_B->LinkNextNode(new_hero);
		p = p->GetNext();
	}

}

void Battle()
{
	while (1) {

		hero_A->GetNext()->InterActHero(
			hero_B->GetNext()->Attack()
		);

		if (hero_A->GetNext()->GetHP() <= 0) return;
		hero_B->GetNext()->InterActHero(
			hero_A->GetNext()->Attack()
		);

		if (hero_B->GetNext()->GetHP() <= 0) return;
	}

}

void Result()
{
	CHero * p = hero_A->GetNext();
	while (p != nullptr) {
		p->Isalive();
		p = p->GetNext();
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////
/*

0보다 크거나 작은 값을 물어보는 함수를 작성할 경우
bool CheckDead() {  return(hp <= 0) } --> 이렇게 간략화 시켜라

 더 나아가 { if(IsDead) 이런 식으로}

 코드는 문단 형식으로 {의미 단위로 줄을 나누어라}
 :: 이 단위는 어떤 의미를 가지고 있구나 :: 파악 가능

 협업시 무조건 글꼴을 고정너비 글꼴을 사용하라 
 --> 참조 :: 네이버 D2Coding, Consolas
*/
/////////////////////////////////////////////////////////////////////////////////////////