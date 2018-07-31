#pragma once
#ifdef _DEBUG
#include <cstdlib>
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#endif

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <string>
#include "header.h"
using namespace std;
typedef uint64_t uintL_t;
#define UINTL_S sizeof(uintL_t)
typedef uint8_t data_t;
#define DATA_S sizeof(data_t)
typedef uint8_t size_T;
#define SIZE_S sizeof(size_T)
#define SIZE_M (size_T(0) - 1)

#define ratio uint8_t(UINTL_S / DATA_S)

static_assert(!(UINTL_S % DATA_S), "Ratio have fraction");
static_assert(UINTL_S >= DATA_S, "uintL_t must be bigger than data_t");

#include <array>
array<data_t, DATA_S * 8> const data_bitS_init() {
	array<data_t, DATA_S * 8> output = {};
	output[DATA_S * 8 - 1] = 1 << (DATA_S * 8 - 1);
	for (uint8_t write = DATA_S * 8; --write; (output[write - 1] = output[write]) >>= 1) {}
	return output;
}
static array<data_t, DATA_S * 8> const data_bitS = data_bitS_init();
array<data_t, DATA_S * 8> const data_bitB_init() {
	array<data_t, DATA_S * 8> output = {};
	output[DATA_S * 8 - 1] = 1;
	for (uint8_t write = DATA_S * 8; --write; (output[write - 1] = output[write]) <<= 1) {}
	return output;
}
static array<data_t, DATA_S * 8> const data_bitB = data_bitB_init();

class inf {
private:
	size_T size = 0;
	data_t* _data = NULL;	//At the start of the array or left
public:
	///
	//	Input Output
	///
	friend ostream& operator<<(ostream&, inf const&);
	///
	//	Function
	///
	data_t* _data_back() const;
	inf& assign(data_t const*const&, size_T const&);
	inf& Ge)
	inf& data_set(data_t const& input = 0);
	inf& size_increase(size_T const&);
	inf& size_decrease(size_T const&);
	inf& size_set(size_T const&);
	//Is this useless?
	inf& size_set_no_copy(size_T const&);
	size_T GetUsed() const;
	inf count() const;
	inf& size_free();
	inf& add(data_t const*, size_T const&);
	inf& add_at(data_t const*, size_T const&, size_T const&);
	inf& sub(data_t const*, size_T const&);
	//Didn't check 0x, input hex without 0x
	inf& assign_hex(string const&);
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
	template<typename number_t>
	bool const operator<(number_t const&) const;
	template<typename number_t>
	bool const operator>(number_t const&) const;
	template<typename number_t>
	bool const operator<=(number_t const&) const;
	template<typename number_t>
	bool const operator>=(number_t const&) const;
	///
	//	Assignment opeartors
	///
	template<typename number_t>
	inf& operator<<=(number_t const&);
	template<typename number_t>
	inf& operator>>=(number_t const&);
	template<typename number_t>
	inf& operator=(number_t const&);
	template<typename number_t>
	inf& operator+=(number_t const&);
	template<typename number_t>
	inf& operator-=(number_t const&);
	template<typename number_t>
	inf& operator*=(number_t const&);
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
//		Input Output 
///
inline ostream& operator<<(ostream& os, inf const& input) {
	if (cout.hex) {
		if (input.size) {
			data_t* _R = input._data_back();
			for (size_T HowMuch = input.size; HowMuch; --HowMuch, --_R) {
				cout << setfill('0') << setw(2 * sizeof(data_t));
				if (sizeof(data_t) > 1) {
					cout << setfill('0') << setw(2 * DATA_S) << *_R;
				}
				else {
					cout << setfill('0') << setw(2 * DATA_S) << (uint16_t)*_R;
				}
			}
		}
		else {
			cout << '0';
		}
	}
	else {
		cout << "Other than hexadecimal (base16), the rest is not implement yet!\n";
	}
	return os;
}

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
inline inf& inf::data_set(data_t const& input) {
	fill_n_in(_data, size, input);
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
		fill_n_in(temp += size, input, 0);
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
		copy_n_in(_data, size, temp);
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
inline inf& inf::size_set_no_copy(size_T const& input) {
	if (!input) {
		delete[] _data;
		_data = NULL;
	}
	else if (!size) {
		_data = new data_t[input];
	}
	else if (size != input) {
		delete[] _data;
		_data = new data_t[input];
	}
	size = input;
	data_set();
	return *this;
}
inline size_T inf::GetUsed() const {
	size_T remain = size;
	for (data_t* _check = _data_back(); remain; --remain, --_check) {
		if (*_check) {
			break;
		}
	}
	return remain;
}
inline inf inf::count() const {
	inf output;
	data_t* _R = _data;
	for (size_T remain = size; remain; --remain, ++_R) {
		for (data_t check = *_R; check; check &= check - 1, ++output) {}
	}
	return output;
}
inline inf& inf::size_free() {
	size_set(size - GetUsed());
	return *this;
}
inline inf& inf::add(data_t const* _R, size_T const& _R_size) {
	if (_R_size) {
		if (this->_data == _R) {
			bool carry = false;
			data_t* _RW = _data;
			for (size_T FA = _R_size / ratio; FA; --FA, _RW += ratio) {	//Fast add
				if (*_RW | data_bitB[0]) {
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
				if (*_RW | data_bitB[0]) {
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
//Didn't check for same pointer yet
inline inf& inf::add_at(data_t const* _R, size_T const& _R_size, size_T const& at) {
	if (_R_size) {
		if (_R_size + at > size) {
			size_set(_R_size + at);
		}
		bool carry = false;
		data_t* _RW = _data + at;
		size_T remain = size - at;
		for (; remain >= 8; remain -= 8) {
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
		for (; remain; --remain) {
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
	return *this;
}
inline inf& inf::sub(data_t const* _R, size_T const&_R_size) {
	if (_R_size) {
		if (size > _R_size) {

		}
		else {

		}
	}
	return *this;
}
inline inf& inf::assign_hex(string const& input) {
	//Check required length and set the lekru ngth
	string::size_type length = (input.size() + (2 * DATA_S - 1)) / (2 * DATA_S);
	if (length > SIZE_M) {
		throw overflow_error("Not enough size to convert to inf");
	}
	size_set_no_copy(length);
	//Set data
	length = input.size();
	data_t* _W = _data;
	uint8_t Offset = 0;
	for (char const* _R = &input[input.size() - 1]; length; --length, --_R) {
		switch (*_R) {
		case '0':
			*_W |= 0x0 << 4 * Offset;
			break;
		case '1':
			*_W |= 0x1 << 4 * Offset;
			break;
		case '2':
			*_W |= 0x2 << 4 * Offset;
			break;
		case '3':
			*_W |= 0x3 << 4 * Offset;
			break;
		case '4':
			*_W |= 0x4 << 4 * Offset;
			break;
		case '5':
			*_W |= 0x5 << 4 * Offset;
			break;
		case '6':
			*_W |= 0x6 << 4 * Offset;
			break;
		case '7':
			*_W |= 0x7 << 4 * Offset;
			break;
		case '8':
			*_W |= 0x8 << 4 * Offset;
			break;
		case '9':
			*_W |= 0x9 << 4 * Offset;
			break;
		case 'A':
		case 'a':
			*_W |= 0xA << 4 * Offset;
			break;
		case 'B':
		case 'b':
			*_W |= 0xB << 4 * Offset;
			break;
		case 'C':
		case 'c':
			*_W |= 0xC << 4 * Offset;
			break;
		case 'D':
		case 'd':
			*_W |= 0xD << 4 * Offset;
			break;
		case 'E':
		case 'e':
			*_W |= 0xE << 4 * Offset;
			break;
		case 'F':
		case 'f':
			*_W |= 0xF << 4 * Offset;
			break;
		default:
			throw invalid_argument("The string contain non-hex charachers");
		}
		if (++Offset >= 2 * DATA_S) {	//*2 because 2 char = 1 byte
			Offset = 0;
			++_W;
		}
	}
	return *this;
}

///
//		Default constructor & destructor
///
inf::inf() {}
inf::inf(inf const& input) {
	this->assign(input._data, input.size);
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
	size_T remain = GetUsed();
	if (remain == input.GetUsed()) {
		for (data_t* _R1 = _data, _R2 = input._data; remain; --remain, ++_R1, ++_R2) {
			if (*_R1 != *_R2) {
				return false;
			}
		}
	}
	return true;
}
//			operator!=
template<>
inline bool const inf::operator!=<inf>(inf const& input) const {
	return !(*this == input);
}
//			operator<
//			operator>
//			operator<=
//			operator>=

///
//		Assignment opeartors
///
//			operator<<=
template<typename number_t>
inline inf& inf::operator<<=(number_t const& input) {
	if (input) {
		assert(!(input > DATA_S * 8));	//Shift more than DATA_S byte is not supported yet
		data_t* _RW = _data_back();
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
inline inf& inf::operator<<=<inf>(inf const& input) {
	if (input.size) {
		if (*input._data) {
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
inline inf& inf::operator>>=(number_t const& input) {
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
inline inf& inf::operator>>=<inf>(inf const& input) {
	if (input.size) {
		if (*input._data) {
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
inline inf& inf::operator=(number_t const& input) {
	this->assign((data_t*)&input, sizeof(number_t));
	return *this;
}
template<>
inline inf& inf::operator=<inf>(inf const& input) {
	this->assign(input._data, input.size);
	return *this;
}
//			operator+=
template<typename number_t>
inline inf& inf::operator+=(number_t const& input) {
	add((data_t*)&input, sizeof(number_t));
	return *this;
}
template<>
inline inf& inf::operator+=<inf>(inf const& input) {
	add(input._data, input.size);
	return *this;
}
//			operator-=
template<typename number_t>
inline inf& inf::operator-=(number_t const& input) {
	*this -= inf(input);
	return *this;
}
//			operator*=
template<typename number_t>
inline inf& inf::operator*=(number_t const& input) {
	*this *= inf(input);
	return *this;
}
template<>
inline inf& inf::operator*=<inf>(inf const& input) {
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
		this->data_set();
		inf ShiftHowMuch;
		for (++read; --read; ++_R) {
			for (uint8_t readbit = 8; readbit; ++ShiftHowMuch) {	//data_t must be uint8_t
				if (*_R & data_bitB[--readbit]) {
					*this += (temp <<= ShiftHowMuch);
					ShiftHowMuch.data_set();
				}
			}
		}
		if (this == &input) {
			delete[](_R - input.size / 2);
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
inline inf const inf::operator+(number_t const& input) const {
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
inline inf const inf::operator+<inf>(inf const& input) const {
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
inline inf const inf::operator*(number_t const& input) const {
	inf output(*this);
	return output *= input;
}
//			operator<<
template<typename number_t>
inline inf const inf::operator<<(number_t const& input) const {
	inf output(*this);
	return output <<= input;
}
//			operator>>
template<typename number_t>
inline inf const inf::operator>>(number_t const& input) const {
	inf output(*this);
	return output >>= input;
}