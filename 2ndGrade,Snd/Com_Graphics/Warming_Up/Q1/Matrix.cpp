#include "Matrix.h"


CMatrix::CMatrix()
{

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			elem[i][j] = rand() % 2;
		}
	}

}

CMatrix::~CMatrix()
{
}

void CMatrix::ChangeState()
{
	switch (state) {
	case State::Three:
		state = State::Four;
		break;
	case State::Four:
		state = State::Three;
		break;
	}
}

ostream &operator<<(ostream &os, const CMatrix& p)
{
	switch (p.state) {
	case State::Three:
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				cout << p.elem[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	break;
	case State::Four:
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cout << p.elem[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	break;
	}
	return os;
}
