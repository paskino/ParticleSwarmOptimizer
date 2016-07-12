/*
 * PSO2.cpp
 *
 *  Created on: Jul 9, 2016
 *      Author: edo
 */


#include <iostream>
#include <cmath>
#include "Swarm.h"
#include "Bird.h"
#include "SortAndRetrieve.h"
#include "FitnessEvaluator.h"

double tryme (double x, vector<double>pars){
	double Mz0 = pars[0];
	double T10 = pars[1];

	double f = (  (1 - 2 * exp(-x / T10) ) );
	f *= f;
	f = Mz0 * sqrt(f);
	return f;

}

template<typename Value, typename Container>
vector<Value> toVector(Container c, Value x0) {
	int N = sizeof(c);
	vector<Value> v = vector<Value> (N);
	for (int i=0;i!=N;++i){
		v[i] = c[i] - x0;
	}
	return v;
};

int main(){
	try{
		double bb[] = {0.,1000.0, 0.0,1000.0}; // bounding box;
		Swarm my_swarm = Swarm(200,2);

		my_swarm.setFunc (tryme);
		my_swarm.setMaxNumberOfIterations(1000);


		double raw_x[] = {70.,168.,266.,365.,463.,561.,659.,757.,855.};
		double raw_y[] = {492.75,  242.75,   50.25,   54.  ,  146.  ,  212.5 ,  264.  ,
		        307.5 ,  336.5};
		double raw_dy[] = {13.66336342,   5.06828373,  11.51900603,  10.9772492 ,
		         5.24404424,  10.98863049,  13.3041347 ,  12.1346611 ,   8.76070773};
		double par[] = {10,20};
		vector<double> x = toVector<double>(raw_x,raw_x[0]);
		vector<double> y = toVector<double>(raw_y,0);
		vector<double> dy = toVector<double>(raw_dy,0);
		vector<double> pp = toVector<double>(par,0);
		my_swarm.setData(x,y,dy);

		my_swarm.initialize(bb);
		std::cout << "initialized!"  << std::endl;

		my_swarm.doTheSwarming();


		my_swarm.getGlobalBest().print();

	} catch (const std::length_error& le) {
	    std::cerr << "Length error: " << le.what() << '\n';
	    return 1;
	}
	return 0;
}



