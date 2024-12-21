/*
 * Elias Alemayehu <ewalemayehu@scu.edu>
 * For CSEN79 Take Home Midterm
 */
#include <iostream>
#include <cstring>	// memcpy
#include <string>
#include <exception>
#include "bignum.h"

namespace ewalemayehucsen79 {

/* BigNum implementation */

// constructor with a decimal number, in the form of a string
// this is the BigNum equivalent of "strtol", only simpler
BigNum::BigNum(const std::string s): BigNum() {
	auto it = s.begin();	// use string iterator
	// first check if there's a sign character
	if (*it == '+' || *it == '-') {
		if (*it == '-')
			sign = -1;
		it++;	// and skip it from processing
	}

	/*
	 * Incoming digits are interpreted in the form of
	 * ((((xn*10+x(n-1)*10+x(n-2)*10)+....+x0
	 * For every new incoming digit, therefore, the value must be multiplied by 10.
	 * That's the first loop.
	 * The second loop takes in that incoming digit's value.
	 * Each loop implements the concept of "carrying" to the higher order digit.
	 * 
	 * We separated these loops for readability.
	 */
	while (it != s.end()) {
		int idx;
		buffer_t buffer;

		// with each incoming decimal digit, multiply all digits by 10
		for (idx = 0, buffer = 0; idx < high || buffer > 0; ++idx) {
			checkCapacity(idx);
			buffer += digits[idx] * 10;
			if (buffer < StoreCap) {
				digits[idx] = buffer;
				buffer = 0;
			} else {
				// After the carry, the current digit is left with the remainder
				// Preload buffer with whatever carried. That will be handled by the next iteration.
				digits[idx] = buffer % StoreCap;
				buffer = static_cast<store_t>(buffer / StoreCap);
			}
			if (high <= idx + 1)
				high = idx + 1;
		}

		idx = 0;
		bool carry(false);
		// now we take in the next decimal digit
		checkCapacity(idx);
		buffer = digits[idx] + int(*it) - int('0');
		do {
			checkCapacity(idx);
			carry = buffer >= StoreCap;		// does it carry?
			if (!carry)
				digits[idx] = buffer;	// simple case.  we're done.
			else {
				// same algorithm as above
				digits[idx] = buffer % StoreCap;
				checkCapacity(idx+1);
				buffer = digits[idx+1] + static_cast<store_t>(buffer / StoreCap);
				++idx;
			}
			if (high <= idx + 1)
				high = idx + 1;
		} while (carry);
		++it;
	}
}

bool BigNum::checkCapacity(int n) {
	bool good = n < capacity;
	if (!good) {
		size_t newcap = n / INCREMENT * INCREMENT + INCREMENT;	// round up
		store_t *p = new (std::nothrow) store_t[newcap];
		good = p != nullptr;
		if (good) {
			memset((void *)p, 0, sizeof(store_t)*newcap);
			if (digits != nullptr) {
				memcpy(p, digits, sizeof(store_t)*high);
				delete digits;
			}
			capacity = newcap;
			digits = p;
		} else
			throw std::bad_alloc();
	}
	return good;
}

// debug version of operator<<
// output the polynomial form of digits.  designed to be verified by Python.
// check the syntax to the verifier of your choice
std::ostream &BigNum::osdebug(std::ostream &os) const {
	if (sign < 0)
		os << "-";
	// Display the polynomial
	if (sign < 0)
		os << "(";
	for (int i = high - 1; i > 0; --i) 
		os << static_cast<short>(digits[i]) << "*256**" << i << "+";
    os << static_cast<short>(digits[0]);
	if (sign < 0)
		os << ")";
	return os;
}

}
