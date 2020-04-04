#pragma once

/** @defgroup Template Functions
* @{
*
* Template Functions declaration
*/
#include <vector>
using namespace std;

/**
* @brief Classic insertion sort template function
*
* @param v vector of objets to sort
*/
template <class Comparable>
void insertionSort(vector<Comparable> &v)
{
	for (unsigned int p = 1; p < v.size(); p++)
	{
		Comparable tmp = v[p];
		int j;
		for (j = p; j > 0 && tmp < v[j - 1]; j--)
			v[j] = v[j - 1];
		v[j] = tmp;
	}
}