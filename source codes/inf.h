#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
typedef uint64_t uintL_t;
#define UINTL_S sizeof(uintL_t)
typedef uint8_t data_t;
#define DATA_S sizeof(data_t)
typedef uint8_t size_T;
#define ratio uint8_t(UINTL_S / DATA_S)

static_assert(!(UINTL_S % DATA_S), "Ratio have fraction");
static_assert(UINTL_S >= DATA_S, "uintL_t must be bigger than data_t");

class inf {
private:
	size_T size;
	data_t* _data;
public:
	///
	//	Function
	///
	inf& size_increase(const size_T&);
	inf& size_decrease(const size_T&);
	inf& size_set(const size_T&);
	inf& size_free();
	template<typename number_t>
	inf& add(const data_t*, const number_t&);
	///
	//	Default constructors & destructors
	///
	inf();
	template<typename T>
	inf(const T&);
	~inf();
	///
	//	Increment Decrement
	///
	inf& operator++();
	inf& operator++(int);
	inf& operator--();
	inf& operator--(int);
	///
	//	Arithmetic operators
	///
	template<typename number_t>
	const inf operator+(const number_t&) const;
	template<typename number_t>
	const inf operator*(const number_t&) const;
	///
	//	Assignment opeartors
	///
	template<typename number_t>
	inf& operator=(const number_t&);
	template<typename number_t>
	inf& operator+=(const number_t&);
	template<typename number_t>
	inf& operator<<=(const number_t&);
	template<typename number_t>
	inf& operator>>=(const number_t&);
};

///
//	Function
///
inline inf& inf::size_increase(const size_T& input) {
	if (input) {
		data_t* temp = new data_t[size + input];
		copy_n(_data, size, temp);
		delete[] _data;
		_data = temp;
		fill_n(temp += size, input, 0);
		size += input;
	}
	return *this;
}
inline inf& inf::size_decrease(const size_T& input) {
	if (input) {
		data_t* temp = new data_t[size -= input];
		copy_n(_data, size, temp);
		delete[] _data;
		_data = temp;
	}
	return *this;
}
inline inf& inf::size_set(const size_T& input) {
	if (!input) {
		delete[] _data;
		_data = NULL;
	}
	else if (!_data) {
		data_t* temp = new data_t[input];
		fill_n(temp, size = input, 0);
	}
	else if(input > size){
		data_t* temp = new data_t[input];
		copy_n(_data, size, temp);
		delete[] _data;
		fill_n(temp += size, input - size, 0);
		_data = temp;
		size = input;
	}
	else if (size > input) {
		data_t* temp = new data_t[input];
		copy_n(_data, size, temp);
		delete[] _data;
		_data = temp;
		size = input;
	}
	return *this;
}
inline inf& inf::size_free() {
	size_T size_after = size;
	for (data_t* _check = _data + size; size_after; --size_after) {
		if (*_check) {
			break;
		}
	}
	size_set(size_after);
	return *this;
}
template<typename number_t>
inline inf& inf::add(const data_t* _R, const number_t& _R_size) {
	bool carry = false;
	if (size < _R_size) {
		size_set(_R_size);
	}
	data_t* _RW = _data;
	if (uint8_t FA = _R_size / ratio) {	//Fast add
		for (++FA; --FA; ) {
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
			_RW += ratio;
			_R += ratio;
		}
	}
	if (uint8_t A = _R_size % ratio) {	//Normal add
		for (++A; --A; ) {
			if (carry) {
				if (++(*_RW += *_R) > *_R) {
					carry = false;
				}
			}
			else {
				if ((*_RW += *_R) < *_R) {
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
//	Default constructor & destructor
///
inf::inf() {
	size = 0;
	_data = NULL;
}
template<typename T>
inf::inf(const T& input) {
	*this = input;
}
inf::~inf() {
	delete[] _data;
}

///
//	Increment Decrement
///
inline inf& inf::operator++() {
	data_t* _RW = _data;
	size_T remain = size;
	for (++remain; --remain; ++_RW) {
		if (++*_RW) {
			return *this;
		}
	}
	size_increase(1);
	_data[size - 1] = 1;
	return *this;
}
inline inf& inf::operator++(int) {
	inf output(*this);
	++*this;
	return output;
}
inline inf& inf::operator--() {
	data_t* _RW = _data;
	size_T remain = size;
	for (++remain; --remain; ++_RW) {
		if (*_RW) {
			--*_RW;
			return *this;
		}
		--*_RW;
	}
	size_decrease(1);
	return *this;
}
inline inf& inf::operator--(int) {
	inf output(*this);
	--*this;
	return output;
}

///
//	Template
///

///
//		Arithmetic operation
///
template<typename number_t>
inline const inf inf::operator+(const number_t& input) const {
	inf output;
	if (size >= sizeof(input)) {
		output = input;
		output += *this;
	}
	else {
		output = *this;
		output += input;
	}
	return output;
}
template<typename number_t>
inline const inf inf::operator*(const number_t& input) const {
	inf output(*this);

	return output;
}

///
//		Assignment opeartors
///
template<typename number_t>
inline inf& inf::operator=(const number_t& input) {
	_data = new uintS_t[sizeof(input) / UINTS_S];
	*(*T)_data = input;
	return *this;
}
template<typename number_t>
inline inf& inf::operator+=(const number_t& input) {
	add(&input, sizeof(input));
	return *this;
}
template<typename number_t>
inline inf& inf::operator<<=(const number_t& input) {
	assert(!(input > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
	data_t* _RW = _data;
	uint8_t reverse = UINTL_S * 8 - input;
	if (uint8_t FS = size / ratio) {	//Fast shift
		for (++FS; --FS; ) {
			data_t* temp = _RW;
			(*(uintL_t*)temp <<= input) |= *(uintL_t*)(_RW += ratio) >> reverse;
		}
	}
	if (uint8_t S = size % ratio) {	//Normal shift
		reverse -= (UINTL_S - DATA_S) * 8;
		while (--S) {
			data_t* temp = _RW;
			(*temp <<= input) |= *++_RW >> reverse;
		}
		*_RW <<= input;
	}
	return *this;
}
template<typename number_t>
inline inf& inf::operator>>=(const number_t& input) {
	assert(!(input > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
	data_t* _RW = _data + size;
	uint8_t reverse = UINTL_S * 8 - input;
	if (uint8_t FS = size / ratio) {	//Fast shift
		for (++FS; --FS; ) {
			data_t* temp = _RW;
			(*(uintL_t*)temp >>= input) |= *(uintL_t*)(_RW -= ratio) << reverse;
		}
	}
	if (uint8_t S = size % ratio) {	//Normal shift
		reverse -= (UINTL_S - DATA_S) * 8;
		while (--S) {
			data_t* temp = _RW;
			(*temp >>= input) |= *--_RW << reverse;
		}
		*_RW >>= input;
	}
	return *this;
}

///
//	inf
///

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
	_data = new data_t[size = input.size];
	copy_n(input._data, size, _data);
	return *this;
}
template<>
inline inf& inf::operator+=<inf>(const inf& input) {
	add(input._data, input.size);
	return *this;
}