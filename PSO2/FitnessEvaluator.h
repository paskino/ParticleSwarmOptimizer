/*
 * FitnessEvaluator.h
 *
 *  Created on: Jul 11, 2016
 *      Author: edo
 */

#include <stdexcept>
#include <cstdlib>
#include "SortAndRetrieve.h"

#ifndef FITNESSEVALUATOR_H_
#define FITNESSEVALUATOR_H_

//template<typename T>
//int mlen(const T& c){
//	return c.end() - c.begin();
//}

template< typename Value, typename Container>
class FitnessEvaluator {
		Value (*_func)(Value, Container); // pointer to a function that eats
										  // Value and Container and
										  // yields Value
	public:
		Container _data_x;
		Container _data_y;
		Container _data_dy;
		FitnessEvaluator(){
			_func = nullptr;
		};
		virtual ~FitnessEvaluator() {
			// do something
		};
		Value operator()(Value x, Container pars){
			return _func(x,pars);
		};
		Container operator()(Container x, Container pars){
			Container ret;
			for (auto p:x){
				ret.push_back(_func(p,pars));
			}
			return ret;
		};

		void setFunc (Value (*p)(Value, Container)){
			_func = p; // function to be evaluated
		};
		void setData(Container x, Container y){
			if (len(x) != len(y)) throw std::length_error("Data of different length");
			_data_x = x;
			_data_y = y;
			for (int i = 0;i<len(x);++i){
				_data_dy.push_back(-1);
			}
		};
		void setData(Container x, Container y, Container dy){
			if ((len(x) == len(y)) && (len(x) == len(dy))) {
				_data_x  = x;
				_data_y  = y;
				_data_dy = dy;
			} else throw std::length_error("Data of different length");
		};
		Value ChiSquare (Container pars){
			Value chi2 = 0 ;
			int N = len(_data_x);
			if ( _data_dy[0] > 0) {
				for (int i=0 ; i <  N; ++i ){
					chi2 += ( operator()(_data_x[i], pars) - _data_y[i] ) * ( operator()(_data_x[i], pars) - _data_y[i] ) / _data_dy[i];
				}
			} else {
				for (int i=0 ; i < N ; ++i ){
					chi2 += ( operator()(_data_x[i], pars) - _data_y[i] ) * ( operator()(_data_x[i], pars) - _data_y[i] );
				}
			}
			return chi2;
		};

	};

#endif /* FITNESSEVALUATOR_H_ */
