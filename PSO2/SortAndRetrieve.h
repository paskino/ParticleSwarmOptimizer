/*
 * SortAndRetrieve.h
 *
 *  Created on: Jul 10, 2016
 *      Author: edo
 *      Stroustrup explains the issue in his book
 *      "Programming Principles and Practice Using C++:
 *
 *		As usual, the benefits have corresponding weaknesses. For templates, the main
 *		problem is that the flexibility and performance come at the cost of poor
 *		separation between the "inside" of a template (its definition) and its interface
 *		(its declaration).
 *		When compiling a use of a template, the compiler "looks into" the template and
 *		also into the template argument types. It does do to get the information to
 *		generate optimal code. To have all the information available, current compilers
 *		tend to require that a template must be fully defined whenever it is used.
 *		That includes all of its member functions and all template functions called from
 *		those. Consequently, template writers tend to place template definition in header
 *		files. That is not actually required by the standard, but until improved
 *		implementations are widely available, we recommend that you do so for your own
 *		templates: place the definition of any template that is to be used in more than
 *		one translation unit in a header file.
 *      http://www.bogotobogo.com/cplusplus/template_declaration_definition_header_implementation_file.php
 */

#ifndef SORTANDRETRIEVE_H_
#define SORTANDRETRIEVE_H_

#include <cstdlib>
#include <vector>
#include <algorithm>

// Template Declaration
template<typename T>
	bool comp (std::pair<int, T> a, std::pair<int, T> b);

template<typename T>
	std::vector<std::pair<int, T>> sortByValueKeepIndices(std::vector<T>&);

template<typename T>
	int size (const T& );

template<typename T>
	int len (const T& );

template<typename Container, typename Value>
	Value sum(const Container& c, Value v);




// Template definition
template<typename T>
bool comp (std::pair<int, T> a, std::pair<int, T> b) {
	return a.second < b.second;
}

template<typename T>
std::vector<std::pair<int, T>> sortByValueKeepIndices(std::vector<T>& vec){

	std::vector<std::pair<int, T>> pairs ;

	for (unsigned int i = 0; i < vec.size(); ++i){
		std::pair<int, T> p = std::pair<int, T>();
		p.first = i; p.second = vec[i];
		//std::pair<int, double> (i, vec[i])
	    pairs.push_back(p);
	}
	sort(pairs.begin(), pairs.end(), comp<T> );
	return pairs;

}


template<typename T>
int size(const T& c){
	return c.end() - c.begin();
}

template<typename T>
int len(const T& c){
	return c.end() - c.begin();
}

template<typename Container, typename Value>
Value sum(const Container& c, Value v){
	for (auto x:c){
		v+=x;
	}
	return v;
}
#endif /* SORTANDRETRIEVE_H_ */
