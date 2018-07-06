#pragma once
#include <iostream>
using namespace std;
typedef uint8_t uintS_t;
typedef uint64_t uintL_t;
#define UINTS_S sizeof(uintS_t)
#define UINTL_S sizeof(uintL_t)
#define ratio uint8_t(UINTL_S / UINTS_S)
typedef uint8_t size_T;
typedef uint8_t data_t;	//Don't change to bigger type yet!
#define DATA_S sizeof(data_t)

static_assert(!(UINTL_S % UINTS_S), "Ratio have fraction");

class inf {
private:
	size_T size;
	data_t* _data;
public:
	///
	//	Function
	///
	inf& size_increase(const size_T& input);
	inf& size_decrease(const size_T& input);
	inf& size_set(const size_T& input);
	inf& add(const data_t*, const size_T&);
	///
	//	Default constructors & destructors
	///
	inf();
	template<typename T>
	inf(const T&);
	~inf();
	///
	//	Arithmetic operators
	///
	template<typename T>
	const inf operator+(const T&) const;
	template<typename T>
	const inf operator*(const T&) const;
	///
	//	Assignment opeartors
	///
	template<typename T>
	inf& operator=(const T&);
	template<typename T>
	inf& operator+=(const T&);
};

///
//	Function
///
inline inf& inf::size_increase(const size_T& input) {
	uintS_t* temp = new uintS_t[size + input];
	copy_n(_data, size, temp);
	delete[] _data;
	_data = temp;
	fill_n(temp += size, input, 0);
	size += input;
	return *this;
}
inline inf& inf::size_decrease(const size_T& input) {
	uintS_t* temp = new uintS_t[size -= input];
	copy_n(_data, size, temp);
	delete[] _data;
	_data = temp;
	return *this;
}
inline inf& inf::size_set(const size_T& input) {
	if (!input) {
		delete[] _data;
		_data = NULL;
	}
	else if (!_data) {
		uintS_t* temp = new uintS_t[input];
		fill_n(temp, size = input, 0);
	}
	else if(input > size){
		uintS_t* temp = new uintS_t[input];
		copy_n(_data, size, temp);
		delete[] _data;
		fill_n(temp += size, input - size, 0);
		_data = temp;
		size = input;
	}
	else if (size > input) {
		uintS_t* temp = new uintS_t[input];
		copy_n(_data, size, temp);
		delete[] _data;
		_data = temp;
		size = input;
	}
	return *this;
}
inline inf& inf::add(const data_t* _R, const size_T& _R_size) {
	bool carry = false;
	if (size < _R_size) {
		size_set(_R_size);
	}
	data_t* _RW = _data;
	if (uint8_t FA = _R_size / UINTL_S) {	//Fast add
		for (++FA; --FA; ) {
			if (carry) {
				if (++(*(uintS_t*)_RW += *(uintS_t*)_R) > *(uintS_t*)_R) {
					carry = false;
				}
			}
			else {
				if ((*(uintS_t*)_RW += *(uintS_t*)_R) < *(uintS_t*)_R) {
					carry = true;
				}
			}
			_RW += UINTL_S;
			_R += UINTL_S;
		}
	}
	if (uint8_t A = _R_size % UINTL_S) {	//Normal add
		for (++A; --A; ) {
			if (carry) {
				if (++(*(uintL_t*)_RW += *(uintL_t*)_R) > *(uintL_t*)_R) {
					carry = false;
				}
			}
			else {
				if ((*(uintL_t*)_RW += *(uintL_t*)_R) < *(uintL_t*)_R) {
					carry = true;
				}
			}
			++_RW;
			++_R;
		}
	}
	if (carry) {
		if (size_T remain = size - _R_size) {
			for (++remain; --remain; ++_RW) {
				if (++*_RW) {
					return *this;
				}
			}
		}
		size_increase(1);
		_data[size - 1] = 1;
	}
	return *this;
}

///
//	Template
///

///
//		Default constructor & destructor
///
template<typename T>
inf::inf(const T& input) {
	*this = input;
}

///
//		Arithmetic operation
///
template<typename T>
inline const inf inf::operator+(const T& input) const {
	inf output;
	if (size >= sizeof(input)) {
		output = input;
		output += *this;
	}
	else {
		output = *this;
		*(*T)_data += input;
	}
	return output;
}
template<typename T>
inline const inf inf::operator*(const T& input) const {
	inf output(*this);

	return output;
}

///
//		Assignment opeartors
///
template<typename T>
inline inf& inf::operator=(const T& input) {
	_data = new uintS_t[sizeof(input) / UINTS_S];
	*(*T)_data = input;
	return *this;
}
template<typename T>
inline inf& inf::operator+=(const T& input) {
	add(&input, sizeof(input));
	return *this;
}

///
//	inf
///

///
//		Default constructor & destructor
///
inf::inf() {}
inf::~inf() {
	delete[] _data;
}

///
//		Arithmetic operation
///
template<>
inline const inf inf::operator+<inf>(const inf& input) const {
	const inf* large;
	const inf* small;
	if (size >= input.size) {
		large = this;
		small = &input;
	}
	else {
		large = &input;
		small = this;
	}
	inf output(*large);
	return output += *small;
}

///
//		Assignment opeartors
///
template<>
inline inf& inf::operator=<inf>(const inf& input) {
	_data = new uintS_t[size = input.size];
	copy_n(input._data, size, _data);
	return *this;
}
template<>
inline inf& inf::operator+=<inf>(const inf& input) {
	add(input._data, input.size);
	return *this;
}