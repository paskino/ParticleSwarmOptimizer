/*
 * Bird.h
 *
 *  Created on: Jul 9, 2016
 *      Author: edo
 */

#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <limits>
#include "Swarm.h"

using namespace std;

#ifndef BIRD_H_
#define BIRD_H_



class Bird {

public:
	vector<double> position;
	vector<double> velocity;
	vector<double> lbest;
	double best_dist;
	int nparams;
	double * bbounds;

	Bird(int);
	virtual ~Bird();
	bool initialize(double* bbounds);
	void set_position(int,double);
	void set_velocity(int,double);
	double rnd();
	void update_position_and_velocity(const Bird&, const double*);
	void update_position_and_velocity(const vector<double>gbestv, const double* cc);
	Bird& operator+= (const Bird&); //operates between velocity and position
	Bird& operator-= (const Bird&); //operates on position
	Bird& operator*= (const Bird&);
	Bird& operator/= (const Bird&);
	Bird& operator*= (const double);
	Bird& operator/= (const double);
	friend Bird operator+(Bird lhs, const Bird& rhs){
	    lhs += rhs; // reuse compound assignment
	    return lhs; // return the result by value (uses move constructor)
	  };
	friend Bird operator-(Bird lhs, const Bird& rhs){
		    lhs -= rhs; // reuse compound assignment
		    return lhs; // return the result by value (uses move constructor)
		  };
	friend Bird operator*(Bird lhs, const Bird& rhs){
		    lhs *= rhs; // reuse compound assignment
		    return lhs; // return the result by value (uses move constructor)
		  };
	friend Bird operator/(Bird lhs, const Bird& rhs){
		    lhs /= rhs; // reuse compound assignment
		    return lhs; // return the result by value (uses move constructor)
		  };
	friend Bird operator*(Bird lhs, const double rhs){
			    lhs *= rhs; // reuse compound assignment
			    return lhs; // return the result by value (uses move constructor)
			  };
	friend Bird operator/(Bird lhs, const double rhs){
			lhs /= rhs; // reuse compound assignment
			return lhs; // return the result by value (uses move constructor)
		  };
	void print();

};

#endif /* BIRD_H_ */
