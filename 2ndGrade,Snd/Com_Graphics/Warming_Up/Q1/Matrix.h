#pragma once

#include<iostream>
#include<cstdlib>

using namespace std;

typedef enum{
	Three,Four
}State;

class CMatrix
{
private:
	int elem[4][4]{};
	int state = Three;
public:
	CMatrix();
	~CMatrix();
	friend ostream& operator<<(ostream& os, const CMatrix& p);

	void ChangeState();
};

