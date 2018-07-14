#pragma once

#define copy_n _Copy_n_unchecked

#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#endif

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

static const uint8_t bitS[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
static const uint8_t bitB[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };

class inf {
private:
	size_T size;
	data_t* _data;
public:
	///
	//	Function
	///
	inf& clear();
	inf& size_increase(const size_T&);
	inf& size_decrease(const size_T&);
	inf& size_set(const size_T&);
	inf& size_free();
	inf& add(const data_t*, const size_T&);
	///
	//	Default constructors & destructors
	///
	inf();
	inf(const inf&);
	template<typename number_t>
	inf(const number_t&);
	template<typename data, typename number_t>
	inf(const data*&, const number_t&);
	~inf();
	///
	//	Increment & Decrement operators
	///
	inf& operator++();
	inf& operator++(int);
	inf& operator--();
	inf& operator--(int);
	///
	//	Logical operators
	///
	template<typename number_t>
	const bool operator&&(const number_t&) const;
	template<typename number_t>
	const bool operator||(const number_t&) const;
	///
	//	Comparison operators
	///
	template<typename number_t>
	const bool operator==(const number_t&) const;
	///
	//	Arithmetic operators
	///
	template<typename number_t>
	const inf operator+(const number_t&) const;
	template<typename number_t>
	const inf operator*(const number_t&) const;
	template<typename number_t>
	const inf operator<<(const number_t&) const;
	template<typename number_t>
	const inf operator>>(const number_t&) const;
	///
	//	Assignment opeartors
	///
	template<typename number_t>
	inf& operator<<=(const number_t&);
	template<typename number_t>
	inf& operator>>=(const number_t&);
	template<typename number_t>
	inf& operator=(const number_t&);
	template<typename number_t>
	inf& operator+=(const number_t&);
	template<typename number_t>
	inf& operator*=(const number_t&);
};

///
//	Function
///
inline inf& inf::clear() {
	if (_data) {
		fill_n(_data, size, 0);
	}
	return *this;
}
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
	else if (input > size) {
		data_t* temp = new data_t[input];
		copy_n(_data, size, temp);
		delete[] _data;
		_data = temp;
		fill_n(temp += size, input - size, 0);
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
	size_T remain = size;
	for (data_t* _check = _data + size; remain; --remain) {
		if (*_check) {
			break;
		}
	}
	size_set(remain);
	return *this;
}
inline inf& inf::add(const data_t* _R, const size_T& _R_size) {
	if (_R_size) {
		if (size) {
			if (size < _R_size) {
				size_set(_R_size);
			}
			bool carry = false;
			data_t* _RW = _data;
			if (size_T FA = _R_size / ratio) {	//Fast add
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
		}
		else {
			_data = new data_t[size = _R_size];
			copy_n(_R, _R_size, _data);
		}
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
template<typename number_t>
inf::inf(const number_t& input) {
	_data = new data_t[size = sizeof(number_t)];
	*(number_t*)_data = input;
}
inf::inf(const inf& input) {
	_data = new data_t[size = input.size];
	copy_n(input._data, size, _data);
}
template<typename data, typename number_t>
inf::inf(const data*& _R, const number_t& length) {
	_data = new data_t[size = sizeof(data) * length];
	copy_n(_R, length, _data);
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
//		Logical operators
///
template<typename number_t>
inline const bool inf::operator&&(const number_t& input) const {
	if (size && input) {
		return true;
	}
	return false;
}
template<typename number_t>
inline const bool inf::operator||(const number_t& input) const {
	if (size || input) {
		return true;
	}
	return false;
}

///
//		Arithmetic operation
///
template<typename number_t>
inline const inf inf::operator+(const number_t& input) const {
	inf output;
	if (size >= sizeof(number_t)) {
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
	return output *= input;
}
template<typename number_t>
inline const inf inf::operator<<(const number_t& input) const {
	inf output(*this);
	return output <<= input;
}
template<typename number_t>
inline const inf inf::operator>>(const number_t& input) const {
	inf output(*this);
	return output >>= input;
}

///
//		Assignment opeartors
///
template<typename number_t>
inline inf& inf::operator<<=(const number_t& input) {
	if (input) {
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
	}
	return *this;
}
template<typename number_t>
inline inf& inf::operator>>=(const number_t& input) {
	if (input) {
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
	}
	return *this;
}
template<typename number_t>
inline inf& inf::operator=(const number_t& input) {
	if (size < sizeof(number_t)) {
		delete[] _data;
		_data = new data_t[size = sizeof(number_t)];
	}
	else {
		fill_n(_data + sizeof(number_t), size - sizeof(number_t), 0);
	}
	*(number_t*)_data = input;
	return *this;
}
template<typename number_t>
inline inf& inf::operator+=(const number_t& input) {
	add((data_t*)&input, sizeof(number_t));
	return *this;
}
template<typename number_t>
inline inf& inf::operator*=(const number_t& input) {
	inf temp(input);
	*this *= temp;
	return *this;
}

///
//	inf
///

///
//		Logical operators
///
template<>
inline const bool inf::operator&&<inf>(const inf& input) const {
	if (size && input.size) {
		return true;
	}
	return false;
}

///
//		Comparison operators
///
template<>
inline const bool inf::operator==<inf>(const inf& input) const {
	const inf* large = (size >= input.size ? this : &input);
	const inf* small = (size >= input.size ? &input : this);
	data_t* _LR = (*large)._data + (*large).size;
	size_T compare = (*large).size - (*small).size;
	for (++compare; --compare; ) {
		if (*--_LR) {
			return false;
		}
	}
	data_t* _SR = (*small)._data + (*small).size;
	compare = (*small).size;
	for (++compare; --compare; ) {
		if (*--_LR != *--_SR) {
			return false;
		}
	}
	return true;
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
	return output += small;
}

///
//		Assignment opeartors
///
template<>
inline inf& inf::operator<<=<inf>(const inf& input) {
	if (input.size) {
		if (*input._data) {
			assert(!(*input._data > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
			data_t* _RW = _data;
			uint8_t reverse = UINTL_S * 8 - *input._data;
			if (uint8_t FS = size / ratio) {	//Fast shift
				for (++FS; --FS; ) {
					data_t* temp = _RW;
					(*(uintL_t*)temp <<= *input._data) |= *(uintL_t*)(_RW += ratio) >> reverse;
				}
			}
			if (uint8_t S = size % ratio) {	//Normal shift
				reverse -= (UINTL_S - DATA_S) * 8;
				while (--S) {
					data_t* temp = _RW;
					(*temp <<= *input._data) |= *++_RW >> reverse;
				}
				*_RW <<= *input._data;
			}
		}
	}
	return *this;
}
template<>
inline inf& inf::operator>>=<inf>(const inf& input) {
	if (input.size) {
		if (*input._data) {
			assert(!(*input._data > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
			data_t* _RW = _data + size - 1;
			uint8_t reverse = UINTL_S * 8 - *input._data;
			if (uint8_t FS = size / ratio) {	//Fast shift
				for (++FS; --FS; ) {
					data_t* temp = _RW;
					(*(uintL_t*)temp >>= *input._data) |= *(uintL_t*)(_RW -= ratio) << reverse;
				}
			}
			if (uint8_t S = size % ratio) {	//Normal shift
				reverse -= (UINTL_S - DATA_S) * 8;
				while (--S) {
					data_t* temp = _RW;
					(*temp >>= *input._data) |= *--_RW << reverse;
				}
				*_RW >>= *input._data;
			}
		}
	}
	return *this;
}
template<>
inline inf& inf::operator=<inf>(const inf& input) {
	delete[] _data;
	_data = new data_t[size = input.size];
	copy_n(input._data, size, _data);
	return *this;
}
template<>
inline inf& inf::operator+=<inf>(const inf& input) {
	add(input._data, input.size);
	return *this;
}
template<>
inline inf& inf::operator*=<inf>(const inf& input) {
	if (*this && input) {
		size_T read = input.size;
		data_t* _R;
		if (this == &input) {
			_R = new data_t[input.size];
			copy_n(input._data, input.size, _R);
		}
		else{
			_R = input._data;
		}
		this->size_set(size + input.size);
		inf temp(*this);
		this->clear();
		inf ShiftHowMuch = 0;
		for (++read; --read; ++_R) {
			for (uint8_t readbit = 8; readbit; ++ShiftHowMuch) {	//data_t must be uint8_t
				if (*_R & bitB[--readbit]) {
					*this += (temp >>= ShiftHowMuch);
					ShiftHowMuch.clear();
				}
			}
		}
		if (this == &input) {
			delete[] (_R - input.size / 2);
		}
	}
	else {
		delete[] _data;
		_data = NULL;
		size = 0;
	}
	return *this;
}