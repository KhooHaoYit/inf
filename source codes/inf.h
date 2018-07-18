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
	data_t* _data_back = NULL;	//At the end of the array or right (Start, because binary is right to left)
public:
	///
	//	Function
	///
	data_t* _data_front() const;
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
//	Private
///

///
//	Public
///

///
//		Function
///
inline data_t* inf::_data_front() const {
	if (_data_back) {
		return _data_back - (size - 1);
	}
	return NULL;
}
inline inf& inf::assign(data_t const*const& _R, size_T const& _R_size) {
	delete[] _data_front();
	size = _R_size;
	if (_R_size) {
		_data_back = copy_n_in(_R, _R_size, new data_t[_R_size]);
	}
	else {
		_data_back = NULL;
	}
	return *this;
}
inline inf& inf::clear() {
	fill_back_n_in(_data_back, size, 0);
	return *this;
}
inline inf& inf::size_increase(size_T const& input) {
	if (input) {
		data_t* temp = fill_n_in(new data_t[size + input], input, 0);
		if (size) {
			temp = copy_n_in(_data_front(), size, ++temp);
		}
		delete[] _data_front();
		_data_back = temp;
		size += input;
	}
	return *this;
}
inline inf& inf::size_decrease(size_T const& input) {
	if (input) {
		if (input >= size) {
			delete[] _data_front();
			_data_back = NULL;
			size = 0;
		}
		else {
			data_t* temp = new data_t[size -= input];
			temp = copy_n_in(_data_front(), input, temp);
			delete[] _data_front();
			_data_back = temp;
		}
	}
	return *this;
}
inline inf& inf::size_set(size_T const& input) {
	if (!input) {
		delete[] _data_front();
		_data_back = NULL;
	}
	else if (!size) {
		_data_back = fill_n_in(new data_t[size = input], input, 0);
	}
	else if (input > size) {
		data_t* temp = copy_n_in(_data_front(), size, new data_t[input]);
		delete[] _data_front();
		_data_back = fill_n_out(temp, input - size, 0);
		size = input;
	}
	else if (size > input) {
		 data_t* temp = copy_n_in(_data_front(), input, new data_t[size = input]);
		delete[] _data_front();
		_data_back = temp;
	}
	return *this;
}
inline inf& inf::size_free() {
	size_T remain = size;
	for (data_t* _check = _data_back; remain; --remain, --_check) {
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
			data_t* _RW = _data_back - (ratio - 1);
			for (size_T FA = _R_size / ratio; FA; --FA, _RW -= ratio) {	//Fast add
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
			_RW += (ratio - 1);
			for (uint8_t A = _R_size % ratio; A; --A, --_RW) {	//Normal add
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
				*_data_front() = 1;
			}
		}
		else {
			if (size) {
				if (size < _R_size) {
					size_set(_R_size);
				}
				bool carry = false;
				data_t* _RW = _data_back - (ratio - 1);
				for (size_T FA = _R_size / ratio; FA; --FA, _RW -= ratio, _R -= ratio) {	//Fast add
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
				_RW += (ratio - 1);
				for (uint8_t A = _R_size % ratio; A; --A, --_RW, --_R) {	//Normal add
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
					for (size_T remain = size - _R_size; remain; --remain) {
						if (++*--_RW) {
							return *this;
						}
					}
					size_increase(1);
					*_data_front() = 1;
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
template<typename number_t>
inf::inf(number_t const& input) {
	this->assign((data_t*)&input, sizeof(input));
}
template<>
inf::inf(inf const& input) {
	this->assign(input._data_back, input.size);
}
template<typename data, typename number_t>
inf::inf(data const*const& _R, number_t const& length) {
	this->assign(_R, length);
}
inf::~inf() {
	delete[] _data_front();
}

///
//		Increment Decrement
///
inline inf& inf::operator++() {
	data_t* _RW = _data_back;
	for (size_T remain = size; remain; --remain) {
		if (++*--_RW) {
			return *this;
		}
	}
	size_increase(1);
	*_data_front() = 1;
	return *this;
}
inline inf const inf::operator++(int) {
	inf output(*this);
	++*this;
	return output;
}
inline inf& inf::operator--() {
	data_t* _RW = _data_back;
	for (size_T remain = size; remain; --remain) {
		if (*--_RW) {
			--*_RW;
			return *this;
		}
		--*_RW;
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
//		Template
///

///
//			Logical operators
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
//			Arithmetic operation
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
//			Assignment opeartors
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
	this->assign((data_t*)&input, sizeof(number_t));
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
//		inf
///

///
//			Logical operators
///
template<>
inline const bool inf::operator&&<inf>(const inf& input) const {
	if (size && input.size) {
		return true;
	}
	return false;
}

///
//			Comparison operators
///
template<>
inline const bool inf::operator==<inf>(const inf& input) const {
	const inf& large = (size >= input.size ? this : &input);
	const inf& small = (size >= input.size ? &input : this);
	data_t* _LR = large._data_back + large.size;
	size_T compare = large.size - small.size;
	for (++compare; --compare; ) {
		if (*--_LR) {
			return false;
		}
	}
	data_t* _SR = small._data_back + small.size;
	compare = small.size;
	for (++compare; --compare; ) {
		if (*--_LR != *--_SR) {
			return false;
		}
	}
	return true;
}

///
//			Arithmetic operation
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
//			Assignment opeartors
///
template<>
inline inf& inf::operator<<=<inf>(const inf& input) {
	if (input.size) {
		if (*input._data_back) {
			assert(!(*input._data_back > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
			data_t* _RW = _data_front();
			uint8_t reverse = UINTL_S * 8 - *input._data_back;
			for (uint8_t FS = size / ratio; FS; ++FS) {	//Fast shift
				data_t* temp = _RW;
				(*(uintL_t*)temp <<= *input._data_back) |= *(uintL_t*)(_RW += ratio) >> reverse;
			}
			if (uint8_t S = size % ratio) {	//Normal shift
				reverse -= (UINTL_S - DATA_S) * 8;
				while (--S) {
					data_t* temp = _RW;
					(*temp <<= *input._data_back) |= *++_RW >> reverse;
				}
				*_RW <<= *input._data_back;
			}
		}
	}
	return *this;
}
template<>
inline inf& inf::operator>>=<inf>(const inf& input) {
	if (input.size) {
		if (*input._data_back) {
			assert(!(*input._data_back > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
			data_t* _RW = _data_back;
			uint8_t reverse = UINTL_S * 8 - *input._data_back;
			if (uint8_t FS = size / ratio) {	//Fast shift
				for (++FS; --FS; ) {
					data_t* temp = _RW;
					(*(uintL_t*)temp >>= *input._data_back) |= *(uintL_t*)(_RW -= ratio) << reverse;
				}
			}
			if (uint8_t S = size % ratio) {	//Normal shift
				reverse -= (UINTL_S - DATA_S) * 8;
				while (--S) {
					data_t* temp = _RW;
					(*temp >>= *input._data_back) |= *--_RW << reverse;
				}
				*_RW >>= *input._data_back;
			}
		}
	}
	return *this;
}
template<>
inline inf& inf::operator=<inf>(const inf& input) {
	this->assign(input._data_back, input.size);
	return *this;
}
template<>
inline inf& inf::operator+=<inf>(const inf& input) {
	add(input._data_back, input.size);
	return *this;
}
template<>
inline inf& inf::operator*=<inf>(const inf& input) {
	if (*this && input) {
		size_T read = input.size;
		data_t* _R;
		if (this == &input) {
			_R = new data_t[input.size];
			copy_n_in(input._data_back, input.size, _R);
		}
		else{
			_R = input._data_back;
		}
		this->size_set(size + input.size);
		inf temp(*this);
		this->clear();
		inf ShiftHowMuch = 0;
		for (++read; --read; ++_R) {
			for (uint8_t readbit = 8; readbit; ++ShiftHowMuch) {	//data_t must be uint8_t
				if (*_R & bit8B[--readbit]) {
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
		delete[] _data_front();
		_data_back = NULL;
		size = 0;
	}
	return *this;
}