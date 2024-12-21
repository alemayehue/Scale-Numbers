/*
 * Elias Alemayehu <ewalemayehu@scu.edu>
 * For CSEN79 Take Home Midterm
 */
#ifndef BIGNUM_H
#define BIGNUM_H

namespace ewalemayehucsen79 {
/* Integer of near infinitive capacity */
class BigNum {
public:
	using store_t = unsigned char;		// must be half of buffer_t, used as "BigNum::store_t"
	using buffer_t = unsigned short;	// must be twice bigger than store_t

	/*
	 * by default, construct a BigNum with maximum storage capacity of the storage type.
	 * For a storage type of "n bytes", the base is then 256 * n.
	 */ 
	BigNum(): digits(nullptr), high(0), sign(1), capacity(0) {}
	BigNum(const BigNum &);	// copy constructor
	BigNum(const long &);	// conversion constructor
	BigNum(const std::string);	// construct with a string of 10-based digits

	~BigNum();
	BigNum &operator=(const BigNum &);	// assignment operator
	BigNum &operator=(BigNum &&) noexcept;	// move operator
	BigNum &operator+(const BigNum &);

private:
	store_t *digits;
	char sign;
	unsigned int high;	// most significant index
	size_t capacity;	// how many bytes in the current buffer
	static const int INCREMENT = 2;	// used to resize buffer each time
	static const size_t StoreCap = std::numeric_limits<store_t>::max()+1;	// used to resize buffer each time
	inline bool checkCapacity(int);
	void deepCopy(const BigNum &);
	std::ostream &osdebug(std::ostream &) const;
public:
	friend std::ostream& operator<<(std::ostream &os, const BigNum &n);
};

}
#endif // BIGNUM_H
