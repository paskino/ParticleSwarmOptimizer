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

class MrFunc: public FitnessEvaluator<double, vector<double>>{};



template< typename Value, typename Container>
class MyFunction {
	public:
		//F g;
		Value operator()(Value x, Container pars){
			Value ret ;
			Value a = pars[0];
			Value b = pars[1];
//			for (int i=0;i<size(x);++i){
//				if (x[i] == 0 ) ret[i] = a;
//				else ret[i] = a* sin(b*x[i])/x[i];
//			}
			if (x == 0) return a;
			else return a * sin (b*x)/x;
		};
		//void setFunction(F f) {g = f;} ;
	};

/**
 * def F(x,pars):
    f = zeros(len(x))
    Mz0 = pars[0]
    T10 = pars[1]
    for i in range(len(x)):
        f[i] = Mz0 * sqrt((  (1 - 2 * exp(-x[i] / T10) ) )**2)
    return f
 */
vector<double> f(vector<double> x, vector<double>pars){
	vector<double> ret = vector<double>(size(x));
	double a = pars[0];
	double b = pars[1];
	for (int i=0;i<size(x);++i){
		if (x[i] == 0 ) ret[i] = a;
		else ret[i] = a* sin(b*x[i])/x[i];
	}
	return ret;
};



template< typename F >
void ffunction( F f, int value )
{
 std::cout << "value = " << f(value) << std::endl;
}
template< typename F , typename Container>
Container ffunction( F f, Container x , Container pp )
{
	int n = size(x);
	Container ret = Container(size(x));
	for (int i = 0 ; i< size(x); ++i){
		 ret[i] = f(x[i],pp);

	}
	return ret;
}
int mfunc(int (*p)(int) , int k ) {
	return p(k);
}

int sxt(int k) { return k * (k+1) ;}

double prova (double x, vector<double> pars){
	if ( x == 0 ) return pars[0];
	else {
		return pars[0] * sin(pars[1]*x)/x;
	}
}

int main(){
	try{
		double bb[] = {2.0,3.0, 4.0,5.0}; // bounding box;
		Swarm my_swarm = Swarm(180,2);



		vector<double> x = vector<double> (20);
		for (int j=0 ; j<20;j++){
			x[j] = -3.14 + j * (6.28 / 20);
			std::cout << "x value = " << x[j] << std::endl;
		}
		vector<double> pp = vector<double>(2); pp[0] = 1; pp[1]=1;
		vector<double> y = f(x , pp);

		for (auto p : y){
			std::cout << "calculated value = " << p << std::endl;
		}
		//vector<double> yy = myfunction(f,x,pp);

		// defined above
		FitnessEvaluator<double, vector<double>> F;
		F.setFunc(prova);
		vector<double> yy = F(x, pp);
		cout << "size " << size(yy) << std::endl;
		for (auto p : yy){
			std::cout << "pointer func value = " << p << std::endl;
		}
		std::cout << "mfunc(2) " << mfunc(sxt,2) << std::endl;

	} catch (const std::length_error& le) {
	    std::cerr << "Length error: " << le.what() << '\n';
	    return 1;
	}
	return 0;
}



