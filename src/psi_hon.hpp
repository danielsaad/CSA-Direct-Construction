/*
 * psi.hpp
 *
 *  Created on: 30/06/2015
 *      Author: daniel
 */

#ifndef SRC_PSI_HON_HPP_
#define SRC_PSI_HON_HPP_


#include <cstdint>
#include <array>
#include <sdsl/int_vector.hpp>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/util.hpp>
#include <cmath>
#include <vector>
#include "csa_hon.hpp"

template<	class csa_t
		>
class psi_hon{
public:
	//default constructor

    psi_hon() :
    _csa(nullptr) {

    }
    //csa constructor

    psi_hon(csa_t* csa) :
    _csa(csa),
    _last_coded_quotient(_alphabet_size),
    _last_set_bit(_alphabet_size),
    _psi_quotient(_alphabet_size),
    _psi_quotient_select_support(_alphabet_size),
    _psi_quotient_size(_alphabet_size),
    _psi_remainder(_alphabet_size, sdsl::int_vector<0>(1, 0, 1)),
    _psi_remainder_size(_alphabet_size) {
        reset();
    }
    //copy constructor
    //move constructor

    psi_hon(psi_hon&& other) {
        _csa = (std::move(other._csa));
        _last_coded_quotient = std::move(other._last_coded_quotient);
        _last_set_bit = std::move(other._last_set_bit);
        _psi_quotient = std::move(other._psi_quotient);
        _psi_quotient_select_support = std::move(other._psi_quotient_select_support);
        _psi_quotient_size = std::move(other._psi_quotient_size);
        _psi_remainder = std::move(other._psi_remainder);
        _psi_remainder_size = std::move(other._psi_remainder);
        _word_size = std::move(other._word_size);
    }

    psi_hon& operator=(psi_hon&& other) {
        if (this != &other) {
            _csa = nullptr;
            _csa = (std::move(other._csa));
            _last_coded_quotient.clear();
            _last_coded_quotient = std::move(other._last_coded_quotient);
            _last_set_bit.clear();
            _last_set_bit = std::move(other._last_set_bit);
            _psi_quotient.clear();
            _psi_quotient = std::move(other._psi_quotient);
            _psi_quotient_select_support.clear();
            _psi_quotient_select_support = std::move(other._psi_quotient_select_support);
            _psi_quotient_size.clear();
            _psi_quotient_size = std::move(other._psi_quotient_size);
            _psi_remainder.clear();
            _psi_remainder = std::move(other._psi_remainder);
            _psi_remainder_size.clear();
            _psi_remainder_size = std::move(other._psi_remainder_size);
            _word_size = std::move(other._word_size);
        }
        return *this;
    }

    void set(int64_t i, int64_t value) {
        int64_t ch = _csa->get_start_symbol(i);
        int64_t quo = value >> _psi_remainder_size[ch];
        int64_t mask = sdsl::bits::lo_set[_psi_remainder_size[ch]];
        value = value & mask;
        int64_t rem = value;
        int64_t diff = quo - _last_coded_quotient[ch];
        int64_t ith = i - _csa->get_lex_smaller_symbols(ch);
        if (_psi_quotient_size[ch] > 0) {
            _last_set_bit[ch] += diff + 1;
            _psi_quotient[ch][_last_set_bit[ch]] = 1;
        }
        if (_psi_remainder_size[ch] > 0) {
            _psi_remainder[ch][ith] = rem;
        }
        _last_coded_quotient[ch] = quo;
    }

    void set(int64_t ith, int64_t value, int64_t ch) {
        int64_t quo = value >> _psi_remainder_size[ch];
        int64_t mask = sdsl::bits::lo_set[_psi_remainder_size[ch]];
        value = value & mask;
        int64_t rem = value;
        int64_t diff = quo - _last_coded_quotient[ch];
        if (_psi_quotient_size[ch] > 0) {
            _last_set_bit[ch] += diff + 1;
            _psi_quotient[ch][_last_set_bit[ch]] = 1;
        }
        if (_psi_remainder_size[ch] > 0) {
            _psi_remainder[ch][ith] = rem;
        }
        _last_coded_quotient[ch] = quo;
    }

    int64_t psi(int64_t i) const {
        int64_t ch = _csa->get_start_symbol(i);
        int64_t ith = i - _csa->get_lex_smaller_symbols(ch);
        int64_t q, r;
        q = r = 0;
        if (_psi_quotient_size[ch] > 0) {
            q = _psi_quotient_select_support[ch].select(ith+1) - ith;
        }
        if (_psi_remainder_size[ch] > 0) {
            r = _psi_remainder[ch][ith];
        }
        int64_t psi_value = (q << _psi_remainder_size[ch]) | r;
        return (psi_value);
    }

    void configure(const std::vector<int64_t>& symbol_counter) {
        _word_size = 1+sdsl::bits::hi(symbol_counter[_alphabet_size]);
        for (int64_t i = 0; i < _alphabet_size; i++) {
            int64_t symbol_quantity = symbol_counter[i + 1] - symbol_counter[i];
            if (symbol_quantity > 0) {
                _psi_quotient_size[i] = std::floor(std::log2(symbol_quantity));
                _psi_remainder_size[i] = _word_size - _psi_quotient_size[i];
                _psi_remainder[i].resize(symbol_quantity);
                _psi_quotient[i].resize(2 * symbol_quantity);
                sdsl::util::expand_width(_psi_remainder[i],_psi_remainder_size[i]);
                sdsl::util::set_to_value(_psi_quotient[i], 0);
            }
        }
    }

    void configure() {
        _word_size = 1+sdsl::bits::hi(_csa->size());
        for (int64_t i = 0; i < _alphabet_size; i++) {
            int64_t symbol_quantity = _csa->get_symbol_quantity(i);
            if (symbol_quantity > 0) {
                _psi_quotient_size[i] = std::floor(std::log2(symbol_quantity));
                _psi_remainder_size[i] = _word_size - _psi_quotient_size[i];
                _psi_quotient[i].resize(2 * symbol_quantity);
                _psi_remainder[i].resize(symbol_quantity);
                sdsl::util::expand_width(_psi_remainder[i],_psi_remainder_size[i]);
                sdsl::util::set_to_value(_psi_quotient[i], 0);
            }
        }
    }

    void post_configure() {
        for (int i = 0; i < _alphabet_size; i++) {
            if (_csa->get_symbol_quantity(i) > 0) {
                sdsl::util::init_support(_psi_quotient_select_support[i], &_psi_quotient[i]);
            }
        }
    }

    void swap(psi_hon& other) {
        if (this != &other) {
            std::swap(_csa, other._csa);
            std::swap(_last_coded_quotient, other._last_coded_quotient);
            std::swap(_last_set_bit, other._last_set_bit);
            std::swap(_psi_quotient, other._psi_quotient);
            std::swap(_psi_quotient_select_support, other._psi_quotient_select_support);
            std::swap(_psi_quotient_size, other._psi_quotient_size);
            std::swap(_psi_remainder, other._psi_remainder);
            std::swap(_psi_remainder_size, other._psi_remainder_size);
            std::swap(_word_size, other._word_size);
        }
    }

    void reset() {
        _word_size = 0;
        std::fill(_last_set_bit.begin(), _last_set_bit.end(), -1);
        std::fill(_last_coded_quotient.begin(), _last_coded_quotient.end(), 0);
        std::fill(_psi_quotient_size.begin(), _psi_quotient_size.end(), 0);
        for (int64_t i = 0; i < _alphabet_size; i++) {
            sdsl::util::set_to_value(_psi_quotient[i], 0);
            sdsl::util::set_to_value(_psi_remainder[i],0);
            _last_set_bit[i] = -1;
        }
    }
private:
    static const int64_t _alphabet_size = 256;
    const csa_t* _csa;
    std::vector<int64_t> _last_coded_quotient;
    std::vector<int64_t> _last_set_bit;
    std::vector<sdsl::bit_vector> _psi_quotient;
    std::vector<sdsl::select_support_mcl < 1 >> _psi_quotient_select_support;
    std::vector<int64_t> _psi_quotient_size;
    std::vector<sdsl::int_vector<0>> _psi_remainder;
    std::vector<int64_t> _psi_remainder_size;
    int64_t _word_size;
};

#endif /* SRC_PSI_HON_HPP_ */
