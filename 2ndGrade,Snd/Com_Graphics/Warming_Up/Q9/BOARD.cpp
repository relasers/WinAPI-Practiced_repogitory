#include "BOARD.h"



CBOARD::CBOARD()
{
	ischecked = false;
}

CBOARD::CBOARD(int x)
{
	ischecked = false;
	number = x;
}


CBOARD::~CBOARD()
{
}

void CBOARD::Changestate()
{
	ischecked = true;
}

void CBOARD::InsertNumber(int x) 
{
	number = x;
}


ostream &operator<<(ostream &os, const CBOARD& p)
{
	if (p.ischecked)
		os << setw(3) << "¡Ú";
	if (!p.ischecked)
		os << setw(3) <<p.number << " ";
	return os;
}