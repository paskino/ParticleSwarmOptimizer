/*
 * PSO2.cpp
 *
 *  Created on: Jul 9, 2016
 *      Author: edo
 */


#include <iostream>
#include "Swarm.h"
#include "Bird.h"
#include "SortAndRetrieve.h"

using namespace std;

int main(){
	try{
		double bb[] = {2.0,3.0, 4.0,5.0};
		Swarm my_swarm = Swarm(180,2);
		//double bb[] = {2.0,3.0, 4.0,5.0};
		my_swarm.initialize(bb);
		Bird mb = Bird(2);
		mb.initialize(bb);
		mb.print();
		Bird mb2 = Bird(2);
		mb2.initialize(bb);
		mb2.print();
		Bird mb3 = mb + mb2;
		mb3.print();
		Bird mb4 = Bird(2);
		mb4.set_position(0,1.); mb4.set_position(1,1.);
		mb3-=mb;
		mb3.print();
		cout << "mb4 ";
		mb4.print();
		cout << "mb4 *2.0 ";
		(mb4*2.0).print();
		// the following does not work! because the first operator is a number.
		//	cout << "2.0 * mb4 ";
		//  (2.0*mb4).print();
		cout << "mb4/2.0 ";
		(mb4/2.0).print();


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

		cout << "sum of vector " << sum(vec,0.0) << "\n";
		cout << "size of vector " << size(vec) << "\n";

	} catch (const std::length_error& le) {
	    std::cerr << "Length error: " << le.what() << '\n';
	    return 1;
	}
	return 0;
}



