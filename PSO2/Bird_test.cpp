/*
 * Bird_test.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: edo
 */


#include "Bird.h"

bool test_bird(){
	double bb[] = {2.0,3.0, 4.0,5.0};

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
	//cout << "mb4 ";
	mb4.print();
	//cout << "mb4 *2.0 ";
	(mb4*2.0).print();
	// the following does not work! because the first operator is a number.
	//	cout << "2.0 * mb4 ";
	//  (2.0*mb4).print();
	//cout << "mb4/2.0 ";
	(mb4/2.0).print();
	return true;
}
