#include <NTL/ZZX.h>

using namespace std;

int main() {
	cout << "Testing" << endl;
	
	NTL::ZZX pol;

	cout << pol << endl;

	SetCoeff(pol, 4);	// pol = x^4

	cout << "x^4? " << pol << endl;

	NTL::ZZX pol2;

	SetCoeff(pol2, 3);
	SetCoeff(pol2, 2, 5);	// pol2 = x^3 + 5x^2

	NTL::ZZX pol3;

	add(pol3, pol, pol2);

	cout << "x^4 + x^3 + 5x^2? " << pol3 << endl;

	add(pol3, pol3, pol2);

	cout << "x^4 + 2x^3 + 10x^2? " << pol3 << endl;

	mul(pol, pol, pol);

	cout << "x^8? " << pol << endl;

	NTL::ZZX pol4;		// pol4 = 1 + x
	SetCoeff(pol4, 0);
	SetCoeff(pol4, 1);

	NTL::ZZX cpy(pol4);
	for (int i = 0; i < 3; ++i) {
		pol4 *= cpy;
	}
	
	cout << "x^4 + 4x^3 + 6x^2 + 4x + 1? " << pol4 << endl;
}
