/*
 * Swarm.h
 *
 *  Created on: Jul 8, 2016
 *      Author: edo
 */

#ifndef SWARM_H_
#define SWARM_H_

#include <vector>
#include <random>
#include <cstdlib>
#include <algorithm>
#include "Bird.h"

using namespace std;


class Swarm {
	//vector<double> bird;
	vector<Bird> swarm; // the swarm is made of more birds

public:
	int N;
	int dims;
	const double c0 = 0.5 , c1 = 0.5 , c2 = 0.5;
	int gbest;
	vector<double> deltaLbest;
	Swarm(const int,const int, double *bbounds);
	Swarm(const int, const int);
	virtual ~Swarm();
	bool initialize(double * bbounds);
	double rnd();
	bool updatePositionAndVelocity();
	Bird getGlobalBest();
	Bird getLocalBest(int);
//	std::vector<std::pair<int, double>> sortGbest();
//	std::vector<std::pair<int, double>>sortByValueKeepIndices(std::vector<double>);
};

#endif /* SWARM_H_ */
