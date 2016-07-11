/*
 * Swarm.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: edo
 */


#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

#include "Swarm.h"
/***
 * Constructor
 * parameter n: number of birds in the swarm
 * parameter dims: number of parameter of the fit
 */
Swarm::Swarm(int n, int dims, double* bbounds) {
	Swarm::dims = dims;
	Swarm::N = n;
	Bird mybird = Bird(dims);
	swarm = vector<Bird>();
	--n; --dims;
	while (n >= 0){
		while (dims>=0){
			// X = x_min + rand()*(x_max - x_min)
			//double xmin = *(bbounds+2*j);
			//double xmax = *(bbounds+2*j+1);
			mybird.position[dims] = *(bbounds+2*dims) + Swarm::rnd() * (*(bbounds+2*dims+1) - (*(bbounds+2*dims)) );
			mybird.velocity[dims] = Swarm::rnd();
			//lbest[i+j] = x[i+j];
			cout << "dims " << dims << " " << mybird.position[dims] << " " ;
			--dims;
		}
		cout << "\n";
		swarm.push_back(mybird);
		dims = Swarm::dims -1;
		--n;
	}

}
/**
 *
 */
Swarm::Swarm(int n, int dims) {
	Swarm::dims = dims;
	Swarm::N = n;
	Swarm::deltaLbest = std::vector<double>(n, 0.0);
}

Swarm::~Swarm() {
	// TODO Auto-generated destructor stub
}

bool Swarm::initialize(double *bbounds){

		int n = Swarm::N;
		Bird mybird = Bird(dims);
		swarm = vector<Bird>();
		--n;
		while (n >= 0){
			mybird.initialize(bbounds);
			cout << "\n";
			swarm.push_back(mybird);
			--n;
		}
	return true;
}

double Swarm::rnd(){ return ((double)rand()/(double)RAND_MAX); }

bool Swarm::updatePositionAndVelocity(){
//		const double c0 = 0.5 , c1 = 0.5 , c2 = 0.5;

//		self.velocity = c0 * self.velocity + \
//						c1 * random.rand() * (self.globalbest - self.position) + \
//						c2 * random.rand() * (self.localbest - self.position)
//		self.position = self.position + self.velocity
//		#return position, velocity
	int n = Swarm::N;
	double cc[] = {Swarm::c0, Swarm::c1 , Swarm::c2};


	while (n > 0){
		swarm[Swarm::N-n].update_position_and_velocity(swarm[gbest],cc);
		--n;
	}

	return true;
}


