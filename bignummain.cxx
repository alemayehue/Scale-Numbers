#include <string>
#include <iostream>
#include <exception>
#include "bignum.h"

using namespace std;
using namespace ewalemayehucsen79;

/*
 * Write your own "main" as tester.  Exercise all code you wrote.  Make sure to cover boundary conditions.
 * Come up with a way to fake "new" failures.  (call fault injection)
 */

int main(void) {
	std::string str;
	while (true) {
		cout << "#Enter number or 'q': ";
		cin >> str;
		cout << endl;
		if (str[0] == 'q' || str[0] == 'Q')
			break;
		try {
			BigNum bn1(str);	// String constructor test
			// this output is meant for Python to execute
			cout << "orig=" << str << endl;
			cout << "bn1=" << bn1 << endl;
			cout << "print('yes' if orig==bn1 else 'no')" << endl;
			cout << endl;

			BigNum bn2(bn1); // Copy constructor test
			cout << "bn1=" << bn1 << endl;
			cout << "bn2=" << bn2 << endl;
			cout << "print('yes' if bn1==bn2 else 'no')" << endl;
			cout << endl;

			bn2 = 504210; // Deep copy constructor test
			cout << "bn1=" << bn1 << endl;
			cout << "bn2=" << bn2 << endl;
			cout << "print('no' if bn1==bn2 else 'yes')" << endl;
			cout << endl;

			bn1 = bn2; // Assignment operator test
			cout << "bn1=" << bn1 << endl;
			cout << "bn2=" << bn2 << endl;
			cout << "print('yes' if bn1==012405 else 'no')" << endl;
			cout << endl;

			bn1 = bn1; // Self-assignment test
			cout << "bn1=" << bn1 << endl;
			cout << "print('yes' if bn1==bn1 else 'no')" << endl;
			cout << endl;

			cout << "All test complete!";
		} 

		catch (std::bad_alloc const &e) {
			cerr << "failed to allocate memory for " << str << endl;
		}
	}

	return EXIT_SUCCESS;
}
