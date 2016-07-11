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

using namespace std;
class MultiplyByTwo
{
  public:
    int operator()(int value )
    {
      return value*2;
    }
};
template<typename F, typename Value, typename Container>
class MyFunction {
	public:
		Value operator()(Container x, Container pars){
			vector<double> ret = vector<double>(size(x));
				double a = pars[0];
				double b = pars[1];
				for (int i=0;i<size(x);++i){
					ret[i] = a* sin(b*x[i])/x[i];
				}
				return ret;
			return g(x,pars);
		};
		Value g(Container, Container);
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
		ret[i] = a* sin(b*x[i])/x[i];
	}
	return ret;
};



template< typename F >
void ffunction( F f, int value )
{
 std::cout << "value = " << f(value) << std::endl;
}


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

		vector<double> x = vector<double> (20);
		double i = -3.14;
		for (int j=0 ; j<20;j++){
			x[i] = -3.14 + i * (6.28 / 20);
		}
		vector<double> pp = vector<double>(2); pp[0] = 1; pp[1]=1;
		vector<double> y = f(x , pp);

		//vector<double> yy = myfunction(f,x,pp);
		MultiplyByTwo edo ;
		ffunction(edo,4);

	} catch (const std::length_error& le) {
	    std::cerr << "Length error: " << le.what() << '\n';
	    return 1;
	}
	return 0;
}



