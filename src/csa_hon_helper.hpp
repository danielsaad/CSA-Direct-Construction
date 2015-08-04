/*
 * csa_hon_helper.hpp
 *
 *  Created on: 10/07/2015
 *      Author: daniel
 */

#ifndef SRC_CSA_HON_HELPER_HPP_
#define SRC_CSA_HON_HELPER_HPP_

class csa_hon_tuple{
public:
	int64_t _p;
	int64_t _q;
	int64_t _index;
	bool operator<(const csa_hon_tuple& other) const{
		if(_p<other._p){
			return true;
		}
		else if(_p==other._p){
			if(_q<other._q){
				return true;
			}
			return false;
		}
		return false;
	}
};



#endif /* SRC_CSA_HON_HELPER_HPP_ */
