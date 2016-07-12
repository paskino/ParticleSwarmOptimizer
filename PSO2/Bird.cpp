/*
 * Bird.cpp
 *
 *  Created on: Jul 9, 2016
 *      Author: edo
 */

#include "Bird.h"
#include "SortAndRetrieve.h"

using namespace std;

Bird::Bird(int nparams) {
	Bird::nparams = nparams;
	position = std::vector<double>(nparams);
	velocity = std::vector<double>(nparams, 0.0); // velocity 0
	lbest = std::vector<double>(nparams);
	bbounds = nullptr;
	best_dist = std::numeric_limits<double>::max(); // the max double! Anything is better
}

Bird::~Bird() {
	// TODO Auto-generated destructor stub
}

void Bird::set_position(int m, double val){
	if (m > Bird::nparams && m < 0)
		throw length_error("Cannot set position out of range.");
	position[m] = val;
}

void Bird::set_velocity(int m, double val){
	if (m > Bird::nparams && m < 0)
			throw length_error("Cannot set position out of range.");
		velocity[m] = val;
}

/// initialize Bird within boundary
/**  */
bool Bird::initialize(double * bbounds){
	Bird::bbounds = bbounds;
	int dims = Bird::nparams;
	--dims;
	while (dims>=0){
		// X = x_min + rand()*(x_max - x_min)
		//double xmin = *(bbounds+2*j);
		//double xmax = *(bbounds+2*j+1);
		position[dims] = *(bbounds+2*dims) + Bird::rnd() * (*(bbounds+2*dims+1) - (*(bbounds+2*dims)) );
		velocity[dims] = Bird::rnd();
		lbest[dims] = position[dims];
		//lbest[i+j] = x[i+j];
		--dims;
	}
	return true;
}
double Bird::rnd(){ return ((double)rand()/(double)RAND_MAX); }

Bird& Bird::operator+=(const Bird& other){

	if ( nparams !=
			other.nparams) throw length_error ("Birds with different size!");
	int i;
	for (i=0;i<Bird::nparams;++i){
		position[i] += other.position[i];
	}
	return *this;
}
/// Compound *= operator between birds
/** Detailed description. */
Bird& Bird::operator*=(const Bird& other){

	if ( nparams !=
			other.nparams) throw length_error ("Birds with different size!");
	int i;
	for (i=0;i<Bird::nparams;++i){
		position[i] *= other.position[i];
	}
	return *this;
}
/// Compound *= operator with numbers
/** Detailed description. */
Bird& Bird::operator*=(const double other){

	int i;
	for (i=0;i<Bird::nparams;++i){
		position[i] *= other;
	}
	return *this;
}
/// Compound *= operator with numbers
/** Detailed description. */
Bird& Bird::operator/=(const double other){

	int i;
	for (i=0;i<Bird::nparams;++i){
		position[i] /= other;
	}
	return *this;
}
/// Compound /= operator
/** Detailed description. */
Bird& Bird::operator/=(const Bird& other){

	if ( nparams !=
			other.nparams) throw length_error ("Birds with different size!");
	int i;
	for (i=0;i<Bird::nparams;++i){
		position[i] /= other.position[i];
	}
	return *this;
}
/// Compound -= operator
/** Detailed description. */
Bird& Bird::operator-=(const Bird& other){

	if ( nparams !=
			other.nparams) throw length_error ("Birds with different size!");
	int i;
	for (i=0;i<Bird::nparams;++i){
		position[i] -= other.position[i];
	}
	return *this;
}
/// Print content of position
/** Detailed description. */
void Bird::print(){
	int dims = Bird::nparams;
	cout << "Position: [ ";
	while (dims>0){
		cout << position[Bird::nparams - dims] << " " ;
		--dims;
	}
	cout << "] ";
	dims = Bird::nparams;
	cout << "Velocity: [ ";
	while (dims>0){
		cout << velocity[Bird::nparams - dims] << " " ;
		--dims;
	}
	cout << "]\n" ;
}
/// Updates the velocity and position of the bird according to the global and local best
/** Detailed description. */
void Bird::update_position_and_velocity(const Bird& gbest, const double* cc){
	/********************
	//		const double c0 = 0.5 , c1 = 0.5 , c2 = 0.5;
	//		self.velocity = c0 * self.velocity + \
	//						c1 * random.rand() * (self.globalbest - self.position) + \
	//						c2 * random.rand() * (self.localbest - self.position)
	//		self.position = self.position + self.velocity
	//		#return position, velocity
	 *************************/
	double r1 {Bird::rnd()}, r2 {Bird::rnd()};
	int dims = Bird::nparams;

	while (dims>0){
		int i = Bird::nparams-dims;
		double deltaGb = gbest.position[i] - position[i];
		double deltaLb = lbest[i] - position[i];
		velocity[i] = *(cc) * velocity[i] +
					  *(cc + 1 ) * r1 * deltaGb +
					  *(cc + 2 ) * r2 * deltaLb;
		double p = position[i] + velocity[i];
		/// if the new position is outside of the bounding box
		/** make the bird bounce on that plane
		    this assumes that the bounce will make the bird remain in the bounding box
		*/
		if (p > *(bbounds + i + 1) || p < *(bbounds + i )) {
			velocity[i] = - velocity[i];
			p = position[i] + velocity[i];
		}
		position[i] = p;
		--dims;
	}
}
void Bird::update_position_and_velocity(const vector<double> gbestv, const double* cc){
		Bird v = Bird(len(gbestv));
		for (int i = 0 ; i!= len (gbestv) ; ++i){
			v.set_position(i, gbestv[i]);
		}
		update_position_and_velocity(v, cc);
	}
