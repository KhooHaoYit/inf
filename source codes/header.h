#pragma once
using namespace std;
//_R and _W should be at (last item) + 1, return _W[-size] or (First item)
template<typename _R, typename number_t, typename _W>
inline _W* copy_back_n_out(_R* _R, number_t size, _W* _W) {
	for (++size; --size; *--_W = *--_R) {}
	return _W;
}
//_R and _W should be at (last item), return _W[1 - size] or (First item)
template<typename _R, typename number_t, typename _W>
inline _W* copy_back_n_in(_R* _R, number_t size, _W* _W) {
	for (++size, ++_R, ++_W; --size; *--_W = *--_R) {}
	return _W;
}
//_W should be at (last item) + 1, return _W[-size] or (First item)
template<typename _W, typename number_t, typename _R>
inline _W* fill_back_n_out(_W* _W, number_t size, _R _R) {
	for (++size; --size; *--_W = _R) {}
	return _W;
}
//_W should be at (last item), return _W[1 - size] or (First item)
template<typename _W, typename number_t, typename _R>
inline _W* fill_back_n_in(_W* _W, number_t size, _R _R) {
	for (++size, ++_W; --size; *--_W = _R) {}
	return _W;
}