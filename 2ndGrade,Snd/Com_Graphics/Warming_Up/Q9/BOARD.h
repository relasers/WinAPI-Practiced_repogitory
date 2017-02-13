#pragma once

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

class CBOARD
{
private:
	int number;
	bool ischecked;
public:
	CBOARD();
	CBOARD(int x);
	~CBOARD();
	void InsertNumber(int x);
	void Changestate();
	void Swap(CBOARD x);
	int GetNumber() { return number; }
	friend ostream& operator<< (ostream & os, const CBOARD & p);
};
