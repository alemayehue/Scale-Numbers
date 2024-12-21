/*
 * Elias Alemayehu <ewalemayehu@scu.edu>
 * For CSEN79 Take Home Midterm
 */
#include <iostream>
#include "bignum.h"

namespace ewalemayehucsen79 {

// trivial and lazy implementations.  consider enhancing these.
BigNum::~BigNum() { // Destructor
    delete [] digits;
    digits = nullptr;
}

BigNum::BigNum(const BigNum &rhs) { // Copy constructor
    this->operator=(rhs);
}

BigNum& BigNum::operator=(const BigNum &rhs) { // Assignment Operator 
    if (this != &rhs) {
        delete[] digits;
        this->deepCopy(rhs);
    }
    return *this;
}

BigNum& BigNum::operator=(BigNum &&rhs) noexcept {
    if (this != &rhs) {  // Check for self-assignment
        delete[] digits;

        digits = rhs.digits;
        high = rhs.high;
        sign = rhs.sign;
        capacity = rhs.capacity;

        rhs.digits = nullptr;
        rhs.high = 0;
        rhs.capacity = 0;
        rhs.sign = 1;
    }
    return *this;
}


// implement these three
BigNum::BigNum(const long &n) { // Constructor
    digits = new store_t[capacity];
    long temp = n < 0 ? -n : n;

    int index = 0;
    while (temp > 0) {
        if (index >= capacity) {
            checkCapacity(index);
        }
        digits[index++] = static_cast<store_t>(temp % StoreCap);
        temp = temp / StoreCap;
    }
    high = index - 1;
}

BigNum &BigNum::operator+(const BigNum &op) {
    // Determine the result's capacity
    int maxDigits = std::max(this->high, op.high) + 2;
    BigNum* result = new BigNum();
    result->capacity = maxDigits;
    result->digits = new store_t[maxDigits];
    result->sign = this->sign; 

    buffer_t carry = 0;
    int index = 0;
    for (; index <= std::max(this->high, op.high) || carry; ++index) {
        if (index >= result->capacity) {
            result->checkCapacity(index);
        }
        buffer_t sum = carry;
        if (index <= this->high) sum += this->digits[index];
        if (index <= op.high) sum += op.digits[index];
        result->digits[index] = static_cast<store_t>(sum % StoreCap);
        carry = sum / StoreCap;
    }

    result->high = index - 1;
    return *result;
}


void BigNum::deepCopy(const BigNum &rhs) {
    if (this == &rhs) return;

    delete[] digits;

    capacity = rhs.capacity;
    high = rhs.high;
    sign = rhs.sign;

    digits = new store_t[capacity];
    for (unsigned int i = 0; i <= high; i++) {
        digits[i] = rhs.digits[i];
    }
}

bool BigNum::checkCapacity(int index) {
    if (index < capacity) return true;

    size_t newCapacity = capacity * INCREMENT;
    store_t* newDigits = new store_t[newCapacity];

    for (size_t i = 0; i < capacity; i++) {
        newDigits[i] = digits[i];
    }

    delete[] digits;
    digits = newDigits;
    capacity = newCapacity;
    return true;
}


// Formatted output
std::ostream& operator<<(std::ostream &os, const BigNum &n) {
    // if we want to be fancy
    if (os.flags() & os.dec) { /* print in decimal */}
    else if (os.flags() & os.hex) { /* print in hex */}
    else if (os.flags() & os.oct) { /* print in oct */}

    // since they did nothing
    return n.osdebug(os);
}

}