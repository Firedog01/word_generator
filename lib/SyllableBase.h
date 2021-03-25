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

//#include "../lib/Dictionary.h"

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
    int which_one(int*, int, int);

    //-------------------
    //communicating with dict.txt file
    //-------------------
    bool is_dict_good;          //set true if file
    std::string* vowels;        //table of vowels
    int n_vowels;               //number of vowels
    std::string* consonants;    //table of consonants
    int n_consonants;           //number of consonants
    int handle_dict();          //creates above vars
    void string_sort(std::string*, int);//sorts arrays of strings because for some reason std::sort doesnt work ://
    void update_dict();          //updates dictionary !!!file!!!


    //-------------------
    //communicating with preset file and generating word base
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

    int max_syllable_len;       //maximal generated length of syllable, in sounds
    int n_cons_vowels;          //number of maximal consecutive vowels in a row
    int word_length_min;        //*
    int word_length_max;        //* interval of considered lengths (in sounds)

    //stores every available syllable length combination
    //may be big? Although im not sure
    Word* word_base;

    //generates every acceptable word as combination on syllables(above struct)
    //generation excludes:
    //      - words constructed of only vowels
    //      - row of more than n consecutive vowels
    //      - ???
    //      - profit
    void generate_word_base(int length_min, int length_man);

    //updates above vars
    //reads from preset file and sets variables right
    static int set_var(std::string&);
    int handle_preset();

    //-------------------
    //additional functions
    //-------------------
    //returns position of sound in table. If not found returns 0
    //first bool states if searching in consonants(0) or vowels(1)
    int find_sound(bool, const std::string&);
public:
    SyllableBase();
    ~SyllableBase();

    //Dictionary dictionary;

    void display_dict();
    void add_vowel(std::string);//*these add new sound to tables but do not update dict file
    void add_conso(std::string);//*
    void remove_sound(std::string);//removes sound from tables, but does not update dict file

    std::string new_w();        //generates new word
    void save_word(std::string);//saves new word in saved_words.txt
};
#endif //GENERATOR_SLOW_SYLLABLEBASE_H
