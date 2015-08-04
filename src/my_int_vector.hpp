/* 
 * File:   my_int_vector.hpp
 * Author: daniel
 *
 * Created on 28 de Julho de 2015, 19:29
 */

#ifndef MY_INT_VECTOR_HPP
#define	MY_INT_VECTOR_HPP
#include <vector>
#include <cstdint>
#include <sdsl/bits.hpp>
template<uint8_t t_width=0>
class my_int_vector{
public:	
	my_int_vector(const uint64_t size=0,const uint64_t width=0){
		_width = width;
		this->resize(size);
	}
	// Copy Constructor
	my_int_vector(my_int_vector& copy){
		_v = copy._v;
		_width = copy._width;
	}
	// Move constructor
	my_int_vector(my_int_vector&& other){
		_v = std::move(other._v);
		_width = other._width;
	}
	void resize(int64_t new_size){
		int64_t n_blocks = std::ceil((double) (_v.size()*_width)/64);
		int64_t new_blocks = std::ceil((double)(new_size*_width)/64);
		if(n_blocks!=new_blocks){
			_v.resize(new_blocks);
		}
	}
	void change_width(const uint8_t width){
		if(width>_width){
			my_int_vector<0> v2(width);
			v2.resize(_size);
			for(int64_t i=0;i<_size;i++){
				v2.set_int(i,get_int(i));
			}
			*this = std::move(v2);
			_width = width;
		} 
	}
	int64_t size() const{
		return(_size);
	}
	
	void swap(my_int_vector& other){
		if(this!=&other){
			std::swap(*this,other);
		}
	}
	
	void reset(){
		std::fill(_v.begin(),_v.end(),0);
	}
	inline int64_t get_int(const uint64_t i) const{
		int64_t block = i>>6;
		int64_t start = i & 0xffffff;
		return(read_int(block,start));
	}
	
	inline void set_int(const uint64_t i, int64_t value){
		int64_t block = i>>6;
		int64_t start = i & 0xffffff;
		write_int(block,start,value);
	}
	
	void operator=(const my_int_vector& copy){
		if(this!=&copy){
			_v.clear();
			_v = copy._v;
			_width = copy._width;
			_size = copy._size;
		}
	}
	
	void operator=(const my_int_vector&& other){
		if(this!=&other){
			_v.clear();
			_v = std::move(other._v);
			_width = _width;
			_size = other._size;
		}
	}
	~my_int_vector(){
		_v.clear();
	}
	
	
private:
	std::vector<int64_t> _v;
	int64_t _size;
	uint8_t _width;
	
	inline int64_t read_int(uint64_t block,uint64_t start) const{
		uint64_t end = (start+_width-1) & 0xffffff;
		int64_t value = 0;
		if(start<=end){
			value = (_v[block] >> (63-end)) & sdsl::bits::lo_set[_width];
		}
		else{
			value = (_v[block] & sdsl::bits::lo_set[63 - start]) << (end+1);
			value |= _v[block+1] >> (63-end);
		}
		return value;
	}
	
	inline void write_int(uint64_t block,uint64_t start,int64_t value){
		uint64_t end = (start+_width-1) & 0xffffff;
		uint64_t mask;
		if(start<=end){
			mask = sdsl::bits::lo_set[63-end] | 
			sdsl::bits::lo_unset[63-start];
			_v[block] = (_v[block] & mask) | (value << (63-end));
		}
		else{
			_v[block] = (_v[block] & sdsl::bits::lo_unset[63-start]) | 
				(value >> (end+1));
			_v[block+1] = (_v[block+1] & sdsl::bits::lo_set[63-end]) |
				(value & sdsl::bits::lo_set[end+1]);
		}
	}
};



#endif	/* MY_INT_VECTOR_HPP */

