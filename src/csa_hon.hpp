
#ifndef SRC_CSA_HON_HPP_
#define SRC_CSA_HON_HPP_

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <divsufsort64.h>
#include <sdsl/bit_vectors.hpp>
#include "csa_hon_helper.hpp"
#include "psi_hon.hpp"
#include "suffixSorting.hpp"

template< int64_t t_sample_rate = 5,
int64_t t_number_of_blocks = 20
>
class csa_hon {
public:

    //constructor

    csa_hon() :
    _old_psi(this),
    _new_psi(this) {
        _wm = nullptr;
        _size = 0;
        _m = nullptr;
        _im = nullptr;
        _current_block_size = 0;
        _l = 0;
        _symbol_counter.resize(_alphabet_size + 1);
        std::fill(_symbol_counter.begin(), _symbol_counter.end(), 0);
        _number_of_blocks = t_number_of_blocks;
        _sample_rate = t_sample_rate;
    }

    //move constructor

    //move assignment

    csa_hon& operator=(const csa_hon<t_number_of_blocks, t_sample_rate>&& other) {
        if (this != other) {
            sdsl::util::clear(*this);
            _current_block_size = std::move(other._current_block_size);
            _im = std::move(other._im);
            _l = std::move(other._l);
            _m = std::move(other._m);
            _new_block = std::move(other._new_block);
            _new_psi = std::move(other._new_psi);
            _old_block = std::move(other._old_block);
            _old_psi = std::move(other._old_psi);
            _size = std::move(other._old_psi);
            _symbol_counter = std::move(other._symbol_counter);
            _text = std::move(other._text);
            _wm = std::move(other._wm);
        }
        return *this;
    }
    //copy constructor

    //copy assignment


    //public interface

    int64_t operator[](const uint64_t i) const {
        if (_sa_sampled_positions[i] == 1) {
            return (_sampled_sa[_sa_sampled_positions_rank.rank(i)]);
        } else {
            int64_t k = 0;
            int64_t rank = i;
            while (_sa_sampled_positions[rank] == 0) {
                rank = psi(rank);
                k++;
            }
            int64_t value = _sampled_sa[_sa_sampled_positions_rank.rank(rank)] - k;
            if (value < 0) {
                value += _size;
            }
            return value;
        }
    }

    void construct(std::string text_file) {
        int64_t n, start, end;
        _text = parse_text(text_file);
        int64_t text_size = _text.size();
        int64_t remaining_text_size = _text.size();
        _size = 0;
        start = 0;
        end = 0;
        _wm = new int64_t[(_block_size + 1) * 4];
        if (text_size <= _block_size) {
            n = 0;
            _current_block_size = text_size;
            remaining_text_size = 0;
        } else {
            _current_block_size = _block_size;
            remaining_text_size -= _current_block_size;
            n = (std::ceil((double) remaining_text_size / _block_size));
            end = std::min(start + _current_block_size - 1, text_size);
        }
        _old_block = _text.substr(0, _current_block_size);
        _size += _current_block_size;
        base_case();
        start = end + 1;
        for (int64_t i = 0; i < n; i++) {
            std::cout << "Iteration " << i + 1 << " of " << n << "\n";
            end = std::min(start + _block_size - 1, text_size - 1);
            _new_block = _text.substr(start, end - start + 1);
            _current_block_size = std::min(end - start + 1, remaining_text_size);
            _size += _current_block_size; //update csa size
            compute_rank_long();
            compute_rank_short();
            compute_psi();
            start = end + 1;
            remaining_text_size -= _current_block_size;
            _old_psi.swap(_new_psi);
            _new_psi.reset();
            _old_block = std::move(_new_block);
//            for (int64_t i = 0; i < _size; i++) {
//                std::cout << "PSI(" << i << ") = " << _old_psi.psi(i) << "\n";
//            }
        }
        _new_psi = std::move(_old_psi);
        sample_sa();
        sample_isa();
    }

    int64_t sigma() const {
        return _alphabet_size;
    }

    int64_t size() const {
        return _size;
    }

    int64_t psi(uint64_t i) const {
        return _new_psi.psi(i);
    }

    int64_t lf(uint64_t i) const {
        return 0;
    }

    std::string extract(uint64_t i, uint64_t j) const {
        std::string s("");
        return s;
    }

    int64_t get_symbol_quantity(int64_t i) const {
        return (_symbol_counter[i + 1] - _symbol_counter[i]);
    }

    int64_t get_lex_smaller_symbols(int64_t i) const {
        return _symbol_counter[i];
    }
    //gives the ith lexicographically smaller symbol
    //TODO: optimize

    int64_t get_start_symbol(int64_t ith) const {
        int64_t l, r, ch, m;
        l = 0;
        r = _alphabet_size;
        ch = l;
        while (l < r) {
            m = (l + r) / 2;
            if (_symbol_counter[m] <= ith) {
                l = m + 1;
                ch = m;
            } else {
                r = m - 1;
            }
        }
        if (l == r) {
            if (_symbol_counter[l] <= ith) {
                ch = l;
            }
        }
        return (ch);
    }

    ~csa_hon() {
        delete[] _wm;
        _symbol_counter.clear();
    }

private:
    //members
    static const int64_t _alphabet_size = 256; //TODO: CHANGE FOR GENERAL ALPHABETS, IT IS ONLY WORKING FOR ASCII ALPHABET
    int64_t _number_of_blocks; //size block
    int64_t _sample_rate; //sample rate of the Suffix Array
    int64_t _size;
    int64_t _block_size;
    int64_t _current_block_size;
    std::string _text;
    int64_t* _wm; //working memory
    int64_t *_m; // $M$ array
    int64_t* _im; // $M^{-1}$ array
    int64_t* _l; //L array
    psi_hon<csa_hon<t_sample_rate, t_number_of_blocks>> _old_psi;
    psi_hon<csa_hon<t_sample_rate, t_number_of_blocks>> _new_psi;
    std::vector<int64_t> _symbol_counter;
    std::vector<int64_t> _sampled_sa;
    std::vector<int64_t> _sampled_isa;
    sdsl::bit_vector _sa_sampled_positions;
    sdsl::bit_vector::rank_1_type _sa_sampled_positions_rank;
    std::string _new_block;
    std::string _old_block;
    //methods

    void base_case() {
        //sort suffixes
        auto sa = _wm;
        const unsigned char* t = (const unsigned char*) _old_block.c_str();
        divsufsort64(t, sa, this->_current_block_size);
        //obtain ISA
        auto isa = &_wm[_current_block_size];
        for (int64_t i = 0; i < _current_block_size; i++) {
            isa[sa[i]] = i;
        }
        //build psi
        auto psi_values = &_wm[_current_block_size * 2];
        for (int64_t i = 0; i < _current_block_size; i++) {
            psi_values[i] = isa[(sa[i] + 1) % _current_block_size];
        }
        std::vector<int64_t> _new_symbol_counter(_alphabet_size + 1, 0);
        for (uint64_t i = 0; i < _old_block.size(); i++) {
            _new_symbol_counter[_old_block[i]]++;
        }
        int64_t temp = _new_symbol_counter[0];
        _new_symbol_counter[0] = 0;
        for (int64_t i = 1; i <= _alphabet_size; i++) {
            int64_t aux = _new_symbol_counter[i];
            _new_symbol_counter[i] = _new_symbol_counter[i - 1] + temp;
            temp = aux;
        }
        _symbol_counter = std::move(_new_symbol_counter);
        //compress psi_information for next iterations
        _old_psi.configure();
        for (int64_t i = 0; i < _current_block_size; i++) {
            _old_psi.set(i, psi_values[i]);
        }
        _old_psi.post_configure();
    }

    void compute_rank_long() {
        int* isa = (int*) &_wm[0];
        int* sa = (int*) &_wm[2 * _current_block_size + 1];
        for (int64_t i = 0; i < _current_block_size; i++) {
            isa[i] = (int) _new_block[i];
        }
        for (int64_t i = _current_block_size; i < 2 * _current_block_size; i++) {
            isa[i] = (int) _old_block[i - _current_block_size];
        }
        suffixSort(isa, sa, 2 * _current_block_size, _alphabet_size, 0, _current_block_size);
        csa_hon_tuple* tuples = (csa_hon_tuple*) & _wm[_current_block_size];
        tuples[0]._q = _old_psi.psi(0);
        tuples[0]._p = isa[0];
        tuples[0]._index = 0;
        for (int64_t i = 1; i < _current_block_size; i++) {
            tuples[i]._index = i;
            tuples[i]._p = isa[i];
            tuples[i]._q = _old_psi.psi(tuples[i - 1]._q);
        }
        std::sort(tuples, tuples + _current_block_size);
        _m = _wm;
        //compute $M$
        for (int64_t i = 0; i < _current_block_size; i++) {
            _m[tuples[i]._index] = i;
        }
        //Compute $M^{-1}$
        _im = &_wm[_current_block_size];
        for (int64_t i = 0; i < _current_block_size; i++) {
            _im[_m[i]] = i;
        }

    }

    void compute_rank_short() {
        int64_t ch;
        int64_t i;
        _l = &_wm[2 * _current_block_size];
        i = _current_block_size;
        _l[i] = _old_psi.psi(0);
        i--;
        while (i >= 0) {
            /**Compute a binary Search**/
            ch = _new_block[i];
            _l[i] = bsearch_rank(_l[i + 1], ch);
            i--;
        }
    }

    void compute_psi() {
        //rank of long suffixes ammong all suffixes
        for (int64_t i = 0; i < _current_block_size; i++) {
            _m[i] += _l[i];
        }
        std::sort(_l, _l + _current_block_size);
        sdsl::bit_vector bv(_size + _current_block_size);
        int64_t last_set_bit = _l[0];
        bv[_l[0]] = 1;
        for (int64_t i = 1; i < _current_block_size; i++) {
            bv[last_set_bit + _l[i] - _l[i - 1] + 1] = 1;
            last_set_bit += _l[i] - _l[i - 1] + 1;
        }
        int64_t r0 = 0;
        int64_t r1 = 0;
        sdsl::bit_vector::select_0_type s0(&bv);

        std::vector<int64_t> new_symbol_counter(_alphabet_size + 1, 0);
        for (int64_t i = 0; i < _current_block_size; i++) {
            new_symbol_counter[_new_block[i]]++;
        }
        int64_t tmp = new_symbol_counter[0];
        new_symbol_counter[0] = 0;
        for (int64_t i = 1; i <= _alphabet_size; i++) {
            int64_t tmp2 = new_symbol_counter[i];
            new_symbol_counter[i] = new_symbol_counter[i - 1] + tmp;
            tmp = tmp2;
        }
        for (int64_t i = 0; i <= _alphabet_size; i++) {
            new_symbol_counter[i] += _symbol_counter[i];
        }
        _new_psi.configure(new_symbol_counter);
        int64_t ch = 0;
        _new_psi.set(0, _m[0], ch);
        r0++;
        for (int64_t i = 1; i < _size; i++) {
            while (new_symbol_counter[ch + 1] <= i && ch < _alphabet_size) {
                ch++;
            }
            int64_t ith = i - new_symbol_counter[ch];
            //is a short suffix
            if (bv[i] == 0) {
                //count the number of short suffixes seem until now
                int64_t r = r0;
                r0++;
                int64_t p = _old_psi.psi(r);
                int64_t psi_value = s0.select(p + 1);
                _new_psi.set(ith, psi_value, ch);
            } else {
                int64_t r = r1;
                r1++;
                int64_t k = _im[r];
                if (k < _current_block_size - 1) {
                    _new_psi.set(ith, _m[k + 1], ch);
                } else {
                    int64_t p = _old_psi.psi(0);
                    int64_t psi_value = s0.select(p + 1);
                    _new_psi.set(ith, psi_value, ch);
                }
            }
        }
        _symbol_counter = std::move(new_symbol_counter);
        _new_psi.post_configure();
    }

    int64_t bsearch_rank(int64_t rank_next_suffix, int64_t ch) {
        int64_t rank = 0;
        int64_t l = _symbol_counter[ch];
        int64_t r = _symbol_counter[ch + 1] - 1;
        int64_t m_psi;
        rank = l;
        /**Binary search**/
        while (l < r) {
            int64_t m = (l + r) / 2;
            m_psi = _old_psi.psi(m);
            if (m_psi < rank_next_suffix) {
                rank = m + 1;
                l = m + 1;
            } else if (m_psi == rank_next_suffix) {
                rank = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (l == r) {
            m_psi = _old_psi.psi(l);
            if (m_psi < rank_next_suffix) {
                rank = l + 1;
            } else if (m_psi == rank_next_suffix) {
                rank = l;
            }
        }
        return (rank);
    }

    std::string parse_text(std::string text_file) {
        std::ifstream t;
        try {
            t.open(text_file, std::ifstream::binary | std::ifstream::in);
        } catch (std::ifstream::failure e) {
            std::cout << "Error: " << e.what() << "\n";
            exit(EXIT_FAILURE);
        }
        t.seekg(0, t.end);
        auto size = t.tellg();
        t.seekg(t.beg);
        t.clear();
        std::cout << "Text size in bytes = " << size << std::endl;
        std::string str(size, ' ');
        _block_size = std::ceil(((double) size) / _number_of_blocks);
        t.seekg(0);
        t.read(&str[0], str.size());
        str.push_back(0);
        //reverse text
        for (uint64_t i = 0; i < str.size() / 2; i++) {
            std::swap(str[i], str[str.size() - i - 1]);
        }
        //define blocks
        for (int64_t i = 0; i < _number_of_blocks; i++) {
            int64_t start = i*_block_size;
            int64_t end = std::min((uint64_t) (i + 1)*(_block_size), str.size());
            for (int64_t j = start; j < (end + start) / 2; j++) {
                std::swap(str[j], str[end - j + start - 1]);
            }
        }
        t.close();
        return str;
    }

    void sample_sa() {
        int64_t sampled_terms = std::ceil((double) (_size + 1) / _sample_rate);
        _sa_sampled_positions.resize(_size);
        sdsl::util::set_to_value(_sa_sampled_positions, 0);
        _sampled_sa.resize(sampled_terms);
        int64_t rank = psi(0); //pos = ISA[0]
        for (int64_t i = 0; i < _size; i++) {
            if (i % _sample_rate == 0) {
                _sa_sampled_positions[rank] = 1;
            }
            rank = psi(rank);
        }
        sdsl::util::init_support(_sa_sampled_positions_rank, &_sa_sampled_positions);
        rank = psi(0);
        for (int64_t i = 0; i < _size; i++) {
            //i contains a sampled_rate suffix
            if (_sa_sampled_positions[rank] == 1) {
                _sampled_sa[_sa_sampled_positions_rank.rank(rank)] = i;
            }
            rank = psi(rank);
        }
    }

    void sample_isa() {

    }
};

#endif
