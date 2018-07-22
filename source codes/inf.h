#pragma once
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
#include "header.h"
using namespace std;
typedef uint64_t uintL_t;
#define UINTL_S sizeof(uintL_t)
typedef uint8_t data_t;
#define DATA_S sizeof(data_t)
typedef uint8_t size_T;
#define ratio uint8_t(UINTL_S / DATA_S)

static_assert(!(UINTL_S % DATA_S), "Ratio have fraction");
static_assert(UINTL_S >= DATA_S, "uintL_t must be bigger than data_t");

static const uint8_t bit8S[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
static const uint8_t bit8B[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };

class inf {
private:
	size_T size = 0;
	data_t* _data = NULL;	//At the start of the array or left
public:
	///
	//	Function
	///
	data_t* _data_back() const;
	inf& assign(data_t const*const&, size_T const&);
	inf& clear();
	inf& size_increase(size_T const&);
	inf& size_decrease(size_T const&);
	inf& size_set(size_T const&);
	inf& size_free();
	inf& add(data_t const*, size_T const&);
	///
	//	Default constructors & destructors
	///
	inf();
	inf(inf const& input);
	template<typename number_t>
	inf(number_t const&);
	template<typename data, typename number_t>
	inf(data const*const&, number_t const&);
	~inf();
	///
	//	Increment & Decrement operators
	///
	inf& operator++();
	inf const operator++(int);
	inf& operator--();
	inf const operator--(int);	//Done changing
	///
	//	Logical operators
	///
	template<typename number_t>
	bool const operator&&(number_t const&) const;
	template<typename number_t>
	bool const operator||(number_t const&) const;
	///
	//	Comparison operators
	///
	template<typename number_t>
	bool const operator==(number_t const&) const;
	template<typename number_t>
	bool const operator!=(number_t const&) const;
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
	///
	//	Arithmetic operators
	///
	template<typename number_t>
	inf const operator+(number_t const&) const;
	template<typename number_t>
	inf const operator*(number_t const&) const;
	template<typename number_t>
	inf const operator<<(number_t const&) const;
	template<typename number_t>
	inf const operator>>(number_t const&) const;
};
///
//	Private
///

///
//	Public
///

///
//		Function
///
inline data_t* inf::_data_back() const {
	if (_data) {
		return _data + (size - 1);
	}
	return NULL;
}
inline inf& inf::assign(data_t const*const& _R, size_T const& _R_size) {
	delete[] _data;
	if (size = _R_size) {
		copy_n_in(_R, _R_size, _data = new data_t[_R_size]);
	}
	else {
		_data = NULL;
	}
	return *this;
}
inline inf& inf::clear() {
	fill_n_in(_data, size, 0);
	return *this;
}
inline inf& inf::size_increase(size_T const& input) {
	if (input) {
		data_t* temp = new data_t[size + input];
		if (size) {
			copy_n_in(_data, size, temp);
		}
		delete[] _data;
		_data = temp;
		fill_n_in(temp += input, size, 0);
		size += input;
	}
	return *this;
}
inline inf& inf::size_decrease(size_T const& input) {
	if (input) {
		if (input >= size) {
			delete[] _data;
			_data = NULL;
			size = 0;
		}
		else {
			assert(size - input < input);
			data_t* temp = new data_t[size -= input];
			copy_n_in(_data, input, temp);
			delete[] _data;
			_data = temp;
		}
	}
	return *this;
}
inline inf& inf::size_set(size_T const& input) {
	if (!input) {
		delete[] _data;
		_data = NULL;
		size = 0;
	}
	else if (!size) {
		fill_n_in(_data = new data_t[size = input], input, 0);
	}
	else if (input > size) {
		data_t* temp = new data_t[input];
		if (size) {
			copy_n_in(_data, size, temp);
		}
		delete[] _data;
		_data = temp;
		fill_n_in(temp += size, input - size, 0);
		size = input;
	}
	else if (size > input) {
		data_t* temp = new data_t[size = input];
		copy_n_in(_data, input, temp);
		delete[] _data;
		_data = temp;
	}
	return *this;
}
inline inf& inf::size_free() {
	size_T remain = size;
	for (data_t* _check = _data_back(); remain; --remain, --_check) {
		if (*_check) {
			break;
		}
	}
	size_set(remain);
	return *this;
}
inline inf& inf::add(data_t const* _R, size_T const& _R_size) {
	if (_R_size) {
		if (this->_data_back == _R) {
			bool carry = false;
			data_t* _RW = _data;
			for (size_T FA = _R_size / ratio; FA; --FA, _RW += ratio) {	//Fast add
				if (*_RW | bit8B[0]) {
					*(uintL_t*)_RW *= 2;
					if (carry) {
						++*(uintL_t*)_RW;
					}
					carry = true;
				}
				else {
					*(uintL_t*)_RW *= 2;
					if (carry) {
						++*(uintL_t*)_RW;
					}
					carry = false;
				}
			}
			for (uint8_t A = _R_size % ratio; A; --A, ++_RW) {	//Normal add
				if (*_RW | bit8B[0]) {
					*_RW *= 2;
					if (carry) {
						++*_RW;
					}
					carry = true;
				}
				else {
					*_RW *= 2;
					if (carry) {
						++*_RW;
					}
					carry = false;
				}
			}
			if (carry) {
				size_increase(1);
				*_data_back() = 1;
			}
		}
		else {
			if (size) {
				if (size < _R_size) {
					size_set(_R_size);
				}
				bool carry = false;
				data_t* _RW = _data;
				for (size_T FA = _R_size / ratio; FA; --FA, _RW += ratio, _R += ratio) {	//Fast add
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
				}
				for (uint8_t A = _R_size % ratio; A; --A, ++_RW, ++_R) {	//Normal add
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
				}
				if (carry) {
					for (size_T remain = size - _R_size; remain; --remain, ++_RW) {
						if (++*_RW) {
							return *this;
						}
					}
					size_increase(1);
					*_data_back() = 1;
				}
			}
			else {
				assign(_R, _R_size);
			}
		}
	}
	return *this;
}

///
//		Default constructor & destructor
///
inf::inf() {}
inf::inf(inf const& input) {
	this->assign(input._data_back, input.size);
}
template<typename number_t>
inf::inf(number_t const& input) {
	this->assign((data_t*)&input, sizeof(input));
}
template<typename data, typename number_t>
inf::inf(data const*const& _R, number_t const& length) {
	this->assign(_R, length);
}
inf::~inf() {
	delete[] _data;
}

///
//		Increment Decrement
///
//			operator++
inline inf& inf::operator++() {
	if (size) {
		data_t* _RW = _data;
		for (size_T remain = size; remain; --remain, ++_RW) {
			if (++*_RW) {
				return *this;
			}
		}
	}
	size_increase(1);
	*_data_back() = 1;
	return *this;
}
inline inf const inf::operator++(int) {
	inf output(*this);
	++*this;
	return output;
}
//			operator--
inline inf& inf::operator--() {
	if (size) {
		data_t* _RW = _data;
		for (size_T remain = size; remain; --remain, ++_RW) {
			if (*_RW) {
				--*_RW;
				return *this;
			}
			--*_RW;
		}
	}
	size_decrease(1);
	return *this;
}
inline inf const inf::operator--(int) {
	inf output(*this);
	--*this;
	return output;
}

///
//		Logical operators
///
//			operator&&
template<typename number_t>
inline bool const inf::operator&&(number_t const& input) const {
	if (size && input) {
		return true;
	}
	return false;
}
template<>
inline bool const inf::operator&&<inf>(inf const& input) const {
	if (size && input.size) {
		return true;
	}
	return false;
}
//			operator||
template<typename number_t>
inline bool const inf::operator||(number_t const& input) const {
	if (size || input) {
		return true;
	}
	return false;
}

///
//		Comparison operators
///
//			operator==
template<>
inline bool const inf::operator==<inf>(inf const& input) const {
	const inf& large = (size >= input.size) ? *this : input;
	const inf& small = (size >= input.size) ? input : *this;
	data_t* _LR = large._data_back();
	for (size_T check = large.size - small.size; check; --check, --_LR) {
		if (*_LR) {
			return false;
		}
	}
	data_t* _SR = small._data_back();
	for (size_T compare = small.size; compare; --compare, --_LR, --_SR) {
		if (*_LR != *_SR) {
			return false;
		}
	}
	return true;
}
//			operator!=
template<>
inline bool const inf::operator!=<inf>(inf const& input) const {
	return !(*this == input);
}

///
//		Assignment opeartors
///
//			operator<<=
template<typename number_t>
inline inf& inf::operator<<=(const number_t& input) {
	if (input) {
		assert(!(input > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
		data_t* _RW = _data.back();
		uint8_t reverse = DATA_S * 8 - input;
		if (uint8_t S = size) {	//Normal shift
			while (--S) {
				data_t* temp = _RW;
				(*temp <<= input) |= *--_RW >> reverse;
			}
			*_RW <<= input;
		}
	}
	return *this;
}
template<>
inline inf& inf::operator<<=<inf>(const inf& input) {
	if (input.size) {
		if (*input._data_back) {
			assert(!(*input._data > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
			data_t* _RW = _data_back();
			uint8_t reverse = DATA_S * 8 - *input._data;
			if (uint8_t S = size) {	//Normal shift
				while (--S) {
					data_t* temp = _RW;
					(*temp <<= *input._data) |= *--_RW >> reverse;
				}
				*_RW <<= *input._data;
			}
		}
	}
	return *this;
}
//			operator>>=
template<typename number_t>
inline inf& inf::operator>>=(const number_t& input) {
	if (input) {
		assert(!(input > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
		data_t* _RW = _data;
		uint8_t reverse = DATA_S * 8 - input;
		if (uint8_t S = size) {	//Normal shift
			while (--S) {
				data_t* temp = _RW;
				(*temp >>= input) |= *++_RW << reverse;
			}
			*_RW >>= input;
		}
	}
	return *this;
}
template<>
inline inf& inf::operator>>=<inf>(const inf& input) {
	if (input.size) {
		if (*input._data_back) {
			assert(!(*input._data > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
			data_t* _RW = _data;
			uint8_t reverse = DATA_S * 8 - *input._data;
			if (uint8_t S = size) {	//Normal shift
				while (--S) {
					data_t* temp = _RW;
					(*temp >>= *input._data) |= *++_RW << reverse;
				}
				*_RW >>= *input._data;
			}
		}
	}
	return *this;
}
//			operator=
template<typename number_t>
inline inf& inf::operator=(const number_t& input) {
	this->assign((data_t*)&input, sizeof(number_t));
	return *this;
}
template<>
inline inf& inf::operator=<inf>(const inf& input) {
	this->assign(input._data_back, input.size);
	return *this;
}
//			operator+=
template<typename number_t>
inline inf& inf::operator+=(const number_t& input) {
	add((data_t*)&input, sizeof(number_t));
	return *this;
}
template<>
inline inf& inf::operator+=<inf>(const inf& input) {
	add(input._data_back, input.size);
	return *this;
}
//			operator*=
template<typename number_t>
inline inf& inf::operator*=(const number_t& input) {
	inf temp(input);
	*this *= temp;
	return *this;
}
template<>
inline inf& inf::operator*=<inf>(const inf& input) {
	if (*this && input) {
		size_T read = input.size;
		data_t* _R;
		if (this == &input) {
			_R = new data_t[input.size];
			copy_n_in(input._data, input.size, _R);
		}
		else {
			_R = input._data;
		}
		this->size_set(size + input.size);
		inf temp(*this);
		this->clear();
		inf ShiftHowMuch;
		for (++read; --read; ++_R) {
			for (uint8_t readbit = 8; readbit; ++ShiftHowMuch) {	//data_t must be uint8_t
				if (*_R & bit8B[--readbit]) {
					*this += (temp <<= ShiftHowMuch);
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

///
//		Arithmetic operation
///
//			operator+
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
template<>
inline const inf inf::operator+<inf>(const inf& input) const {
	inf output;
	if (size >= input.size) {
		output = *this;
		output += input;
	}
	else {
		output = input;
		output += *this;
	}
	return output;
}
//			operator*
template<typename number_t>
inline const inf inf::operator*(const number_t& input) const {
	inf output(*this);
	return output *= input;
}
//			operator<<
template<typename number_t>
inline const inf inf::operator<<(const number_t& input) const {
	inf output(*this);
	return output <<= input;
}
//			operator>>
template<typename number_t>
inline const inf inf::operator>>(const number_t& input) const {
	inf output(*this);
	return output >>= input;
}
