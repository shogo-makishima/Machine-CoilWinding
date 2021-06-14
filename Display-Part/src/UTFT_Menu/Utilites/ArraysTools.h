#ifndef _ARRAYS_TOOLS_H_
#define _ARRAYS_TOOLS_H_

template<class T, size_t N>
constexpr size_t size(T (&)[N]) { return N; }

#endif