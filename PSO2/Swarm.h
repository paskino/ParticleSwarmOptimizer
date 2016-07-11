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
#include "FitnessEvaluator.h"
#include "SortAndRetrieve.h"
#include <cmath>

using namespace std;


class Swarm {
	//vector<double> bird;
	vector<Bird> swarm; // the swarm is made of more birds
	FitnessEvaluator<double, vector<double>> F;
public:
	int N;
	int dims;
	const double c0 = 0.5 , c1 = 0.5 , c2 = 0.5;
	double tolerance;
	int gbest, max_iteration = 10;
	vector<double> gbest_p;
	vector<double> deltaLbest;
	Swarm(const int,const int, double *bbounds);
	Swarm(const int, const int);
	virtual ~Swarm();
	bool initialize(double * bbounds);
	double rnd();
	bool updatePositionAndVelocity();
	bool calculateLocalBestGlobalBest();
	bool stepSwarm(){
		bool a = calculateLocalBestGlobalBest();
		a = a && updatePositionAndVelocity();
		return a;
	}
	bool doTheSwarming();
	Bird getGlobalBest();
	Bird getLocalBest(int);
//	std::vector<std::pair<int, double>> sortGbest();
//	std::vector<std::pair<int, double>>sortByValueKeepIndices(std::vector<double>);

	void setData(vector<double>x , vector<double>y, vector<double>dy){
		try {
			F.setData(x,y,dy);
		} catch (const std::length_error& le) {
		    std::cerr << "Length error: " << le.what() << std::endl;
		}
	}
	void setData(vector<double>x , vector<double>y){
		try {
			F.setData(x,y);
		} catch (const std::length_error& le) {
			std::cerr << "Length error: " << le.what() << std::endl;
		}
	}
};

#endif /* SWARM_H_ */
