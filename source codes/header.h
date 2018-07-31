#pragma once
using namespace std;
//_R and _W should be at (First item) - 1, return _W[size + 1] or (Last item)
template<typename _R_t, typename number_t, typename _W_t>
inline _W_t* copy_n_out(_R_t* _R, number_t size, _W_t* _W) {
	for (; size; --size, *++_W = *++_R) {}
	return _W;
}
//_R and _W should be at (First item), return _W[size] or (Last item)
template<typename _R_t, typename number_t, typename _W_t>
inline _W_t* copy_n_in(_R_t* _R, number_t size, _W_t* _W) {
	for (--_R, --_W; size; --size, *++_W = *++_R) {}
	return _W;
}
//_R and _W should be at (Last item) + 1, return _W[-size] or (First item)
template<typename _R_t, typename number_t, typename _W_t>
inline _W_t* copy_back_n_out(_R_t* _R, number_t size, _W_t* _W) {
	for (; size; --size, *--_W = *--_R) {}
	return _W;
}
//_R and _W should be at (Last item), return _W[1 - size] or (First item)
template<typename _R_t, typename number_t, typename _W_t>
inline _W_t* copy_back_n_in(_R_t* _R, number_t size, _W_t* _W) {
	for (++_R, ++_W; size; --size, *--_W = *--_R) {}
	return _W;
}

//_R and _W should be at (First item) - 1, return _W[size + 1] or (Last item)
template<typename _W_t, typename number_t, typename _R_t>
inline _W_t* fill_n_out(_W_t* _W, number_t size, _R_t _R) {
	for (; size; --size, *++_W = _R) {}
	return _W;
}
//_R and _W should be at (First item), return _W[size] or (Last item)
template<typename _W_t, typename number_t, typename _R_t>
inline _W_t* fill_n_in(_W_t* _W, number_t size, _R_t _R) {
	for (--_W; size; --size, *++_W = _R) {}
	return _W;
}
//_W should be at (Last item) + 1, return _W[-size] or (First item)
template<typename _W_t, typename number_t, typename _R_t>
inline _W_t* fill_back_n_out(_W_t* _W, number_t size, _R_t _R) {
	for (; size; --size, *--_W = _R) {}
	return _W;
}
//_W should be at (Last item), return _W[1 - size] or (First item)
template<typename _W_t, typename number_t, typename _R_t>
inline _W_t* fill_back_n_in(_W_t* _W, number_t size, _R_t _R) {
	for (++_W; size; --size, *--_W = _R) {}
	return _W;
}
