#include <iostream>
#include "Vec3D.h"
using namespace std;

int main() {
	

	while (1) {
		 Vector3D<float>point[4];

		cout << "Input 4 vertex" << endl;
		for (int i = 0; i < 4; ++i) {
			cin >> point[i].x >> point[i].y >> point[i].z;
		}
		cout << "<==Polygon==>" << endl;

		float A;
		float B;
		float C;
		float D;
		//

/*


n-> = BA-> X CA-> = (a,b,c)
ax+by+cz+d = 0;

*/
		A = - point[0].y * ((point[1].z)-(point[2].z)) +
			point[0].z * ((point[1].y)-(point[2].y)) -
			((point[1].y*point[2].z) - (point[2].y*point[1].z));


		B = point[0].x * ((point[1].z)-(point[2].z)) +
			point[0].z * ((point[1].x)-(point[2].x)) -
			((point[1].x*point[2].z) - (point[2].x*point[1].z));

		C = point[0].x * ((point[1].y)-(point[2].y)) -
			point[0].y * ((point[1].x)-(point[2].x)) -
			((point[1].x*point[2].y) - (point[2].x*point[1].y));

		D = point[0].x * ((point[1].y*point[2].z) - (point[2].y*point[1].z)) -
			point[0].y * ((point[1].x*point[2].z) - (point[2].x*point[1].z)) +
			point[0].z * ((point[1].x*point[2].y) - (point[2].x*point[1].y));

		/*
		X1 = point[0].x
		X2 = point[1].x
		X3 = point[2].x
		Y1 = point[0].y
		Y2 = point[1].y
		Y3 = point[2].y
		Z1 = point[0].z
		Z2 = point[1].z
		Z3 = point[2].z

		X1 | Y1 | Z1 | 1 
		X2 | Y2 | Z2 | 1
		X3 | Y3 | Z3 | 1

		A = - Y1 * ((Z2)-(Z3)) +
		Z1 * ((Y2)-(Y3)) -
		((Y2*Z3)-(Y3*Z2));
		

		B = X1 * ((Z2)-(Z3)) +
		Z1 * ((X2)-(X3)) - 
		((X2*Z3)-(X3*Z2));

		C = X1 * ((Y2)-(Y3)) -
		Y1 * ((X2)-(X3)) - 
		((X2*Y3)-(X3*Y2));

		D = X1 * ((Y2*Z3)-(Y3*Z2)) -
		Y1 * ((X2*Z3)-(X3*Z2)) +
		Z1 * ((X2*Y3)-(X3*Y2));
		*/

		cout << "Ax + By + Cz+ D = 0 ==>" << endl;
		cout << "A :: " << A << endl; 
		cout << "B :: " << B << endl;
		cout << "C :: " << C << endl;
		cout << "D :: " << D << endl;
		cout << "<==Line==>" << endl;

		cout << point[0] << "- " << point[1] << "::" << (point[0] - point[1]).Length() << endl;
		cout << point[1] << "- " << point[2] << "::" << (point[1] - point[2]).Length() << endl;
		cout << point[2] << "- " << point[3] << "::" << (point[2] - point[3]).Length() << endl;
		cout << point[3] << "- " << point[0] << "::" << (point[3] - point[0]).Length() << endl;

		cout << "<==Vertex==>" << endl;
		for (int i = 0; i < 4; ++i) {
			cout << point[i];
		}
		cout << endl;
	}
}