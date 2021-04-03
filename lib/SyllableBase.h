//
// Created by Firedog on 08.03.2021.
//



#ifndef GENERATOR_SLOW_SYLLABLEBASE_H
#define GENERATOR_SLOW_SYLLABLEBASE_H

#include <random>
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>

#include "../lib/Options.h"
#include "../lib/Dictionary.h"

class SyllableBase {
    //-------------------
    //everything connected to rng
    //-------------------
    unsigned seed;              //plant this seed well, it will bloom into beautiful, ugh, word
    std::mt19937_64 generator;  //one rng to rule them all

    //-------------------
    //generating word base
    //-------------------
    class Word {

        int n_syllable = 0;
    public:
        Word(std::vector<int>, int);
        std::vector<int> syllable;
        int get_syl(int);
        int get_n() const { return n_syllable; }
        Word& operator= (const Word&);
    };

    //stores every available syllable length combination
    //may be big? Although im not sure
    //2 dimentional array, rows have different lengths of words
    std::vector< std::vector<Word> > word_base;

    /* generates every acceptable word as combination on syllables
     * but only their lengths. Vowel position will be generated later
     * each generated row has different word length so as drawing will first determine word length and then syllable lengths distribution
     * generation process goes rougly like thet:
     *   1. var k will represent current word length
     *   2. then z_min and z_max are determined, which are number of divisions into syllables
     *   3. for given k and z is created table of length z holding amount of sounds in each syllable
     *   4. in a loop using function iterate_tab each viable syllable length combination is added to current row of the base
     *   5. then process is repeated for all k and z's
     * is free of dependencies on options class
     */
    void generate_word_base(int, int, int, int);

    //connected to generate_word_base
    //for iter_tab sets next proper syllable length combination which fills all conditions
    //conditions are listed below. All end with _check
    int iterate_tab(std::vector<int>&, int, int, int, int);

    //checked during tab iteration
    //checks if iterated tab fulfills length requirement
    bool length_check(std::vector<int>&, int, int);
    //eliminates words which have more than n_cons_vowels together
    bool vowel_check(std::vector<int>&, int, int);

    //displays whole word base

public:
    SyllableBase();
    ~SyllableBase();

    void display_base();

    Options options;
    Dictionary dictionary;

    void update();
    std::string new_w();        //generates new word
    void save_word(const std::string&);//saves new word in saved_words.txt
};
#endif //GENERATOR_SLOW_SYLLABLEBASE_H
