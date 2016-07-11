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
	Swarm::gbest_p = std::vector<double>(dims, 0.0);
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

	int n = Swarm::N;
	double cc[] = {Swarm::c0, Swarm::c1 , Swarm::c2};

	// parallel with openmp
	int i=0;
	#pragma omp parallel shared(i)
	{
		for (i=0;i<n;++i){
			swarm[i].update_position_and_velocity(swarm[gbest],cc); //swarm[i] is a Bird
		}
	} // end pragma

	/*********************
	// non parallel code
	while (n > 0){
		swarm[Swarm::N-n].update_position_and_velocity(swarm[gbest],cc); //swarm[i] is a Bird
		--n;
	}
	**/
	return true;
}

bool Swarm::calculateLocalBestGlobalBest(){
	// temporary save the global best chi2
	double tmp_best = deltaLbest[gbest];
	// calculate the local best
	int n = Swarm::N;
	--n;
	while (n >= 0){
		vector<double> pars = swarm[Swarm::N-n].position; // parameters of the fit
		double chi2 = sqrt(F.ChiSquare(pars)); // sqrt of X^2
		if (chi2 < swarm[Swarm::N-n].best_dist) {
			swarm[Swarm::N-n].best_dist = chi2;
			swarm[Swarm::N-n].lbest = pars;
		}
		deltaLbest[Swarm::N-n] = chi2;
		--n;
	}
	// calculate global best by sorting the localBest birds
	std::vector<pair<int,double>> sorted = sortByValueKeepIndices(deltaLbest);


	if (sorted[0].second < tmp_best){ // check the distance with the previous best
		gbest = sorted[0].first; //the actual best Bird
		gbest_p = swarm[sorted[0].first].position;
	}
	return true;
}

bool Swarm::doTheSwarming(){
	// define the tolerance
	if (&F._data_dy[0] > 0) tolerance = sum (F._data_dy,0.0);
	else {
		tolerance = 1e-3 * len(F._data_x);
	}
	// calculate bests
	bool a = calculateLocalBestGlobalBest();
	int iteration = 0;
	while (tolerance > swarm[gbest].best_dist || iteration < max_iteration) {
		a = a && updatePositionAndVelocity();
		++iteration;
		a = a && calculateLocalBestGlobalBest();
	}



	return a;
	//return true;
}

