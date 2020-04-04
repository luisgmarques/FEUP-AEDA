#pragma once

/** @defgroup Template Functions
* @{
*
* Template Functions declaration
*/
#include <vector>
using namespace std;

/**
* @brief Searches for an object of class Comparable in a vector of pointers to objects of the same class
*
* @param v vector of pointers to objets to search for
* @param x object to search for 
*
* @return object's index on vector, -1 if it does not exist
*/
template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x)
{

		for (unsigned int i = 0; i < v.size(); i++)
			if ((*v[i]) == x)
				return i;
		return -1;

}

/**
* @brief Searches for an object of class Comparable in a vector of objects of the same class
*
* @param v vector containing the objets to search for
* @param x object to search for
*
* @return object's index on vector, -1 if it does not exist
*/
template <class Comparable>
int sequentialSearchNoPointer(const vector<Comparable> &v, Comparable x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i]== x)
			return i;
	return -1;
}