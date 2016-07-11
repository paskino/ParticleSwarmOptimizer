/*
 * SortAndRetrieve_test.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: edo
 */

#include "SortAndRetrieve.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;


int unit_test_sar(){
	std::vector<double> vec = std::vector<double>(4);

	vec[0] = 4;vec[1] = 3;vec[2] = 2;vec[3] = 1;
	std::vector<pair<int,double>> sorted = sortByValueKeepIndices(vec);


	for (int i=0;i<4;++i){
		cout << "unsorted[" << i << "]: " << vec[i] << "\n" ;
	}
	cout << "\n";
	for (auto p : sorted){
		cout << "sorted[" << p.first << "]: " << p.second << "\n" ;
	}
	cout << "\n";
	return 0;
}
