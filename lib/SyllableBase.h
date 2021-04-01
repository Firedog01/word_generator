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

#include "../lib/Options.h"
#include "../lib/Dictionary.h"

class SyllableBase {
    //-------------------
    //everything connected to rng
    //-------------------
    unsigned seed;              //plant this seed well, it will bloom into beautiful, ugh, word
    std::mt19937_64 generator;  //one rng to rule them all

    //generates new syllable
    // implemented:
    // * differentiates sounds between syllables.
    //      prevents from double vowels or consonants back to back
    //      (negative) will not create structures as such: v_1c_1 v_2c_1
    std::string get_syllable(int,
                             std::uniform_int_distribution<int>&,
                             std::uniform_int_distribution<int>&,
                             int&, int&);

    // gets table of layout
    // returns which in order is drawn
    // eg. for 1/2/3 drawn 2 returns 2
    // is required by get_syllable
    int which_one(const int*, int, int);

    //-------------------
    //generating word base
    //-------------------
    struct Syllable {
        int length;
        int vowel_pos;
    };
    class Word {
        int n_syllable = 0;
        Syllable* syllable = nullptr;
    public:
        void set_properties(int, Syllable*);
        Syllable get_syllable(int syl_pos);
        int get_n() const;
    };

    //stores every available syllable length combination
    //may be big? Although im not sure
    std::vector<Word> word_base;

    //generates every acceptable word as combination on syllables
    //but only their lengths. Vowel position will be generated later
    void generate_word_base(int length_min, int length_man);

    Syllable iterate_Tab(int*, int);


public:
    SyllableBase();
    ~SyllableBase();

    Options options;
    Dictionary dictionary;

    std::string new_w();        //generates new word
    static void save_word(const std::string&);//saves new word in saved_words.txt
};
#endif //GENERATOR_SLOW_SYLLABLEBASE_H
