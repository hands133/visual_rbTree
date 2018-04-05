#pragma once
#ifndef changeLength1D_
#define changeLength1D_

#include "myExceptions.h"

using std::copy;

template <class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
	if (newLength < 0)
		throw illegalParameterValue("new length must be >= 0");
	T* temp = new T[newLength];
	int number = (oldLength > newLength) ? newLength : oldLength;
	copy(a, a + number, temp);
	a = temp;
}










#endif