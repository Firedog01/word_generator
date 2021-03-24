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

class SyllableBase {
    unsigned seed;
    std::mt19937_64 generator;

    std::string get_syllable(int,
                             std::uniform_int_distribution<int>&,
                             std::uniform_int_distribution<int>&,
                             int&,
                             int&);
                                //generates new syllable
                                // implemented:
                                // * differentiates sounds between syllables.
                                //      prevents from double vowels or consonants back to back
                                //      (negative) will not create structures as such: v_1c_1 v_2c_1
    int which_one(int*, int, int);

    const int max_syllable_len = 3;

    std::string* vowels;        //table of vowels
    int n_vowels;               //number of vowels
    std::string* consonants;    //table of consonants
    int n_consonants;           //number of consonants
    int handle_dict();          //creates above vars
    void string_sort(std::string*, int);//sorts arrays of strings because for some reason std::sort doesnt work ://
    void update_dict();          //updates dictionary !!!file!!!

    int* syllable_stress;       //preferred length of one syllable
    int* length_stress;         //preferred length of word (in syllables)
    int  max_length;            //max number of syllables
    bool is_dict_good;          //
    bool is_stress_modified_s;  //how long syllables will be used
    bool is_stress_modified_l;  //how long will be generated word
    int handle_preset();        //updates above vars
                                //reads from preset file and sets variables right

    int find_sound(bool, const std::string&);   //returns position of sound in table. If not found returns 0
                                                //first bool states if searching in consonants(0) or vowels(1)

public:
    SyllableBase();
    ~SyllableBase();

    void display_dict();
    void add_vowel(std::string);//*these add new sound to tables but do not update dict file
    void add_conso(std::string);//*
    void remove_sound(std::string);//removes sound from tables, but does not update dict file

    std::string new_w();        //generates new word
    void save_word(std::string);//saves new word in saved_words.txt
};
#endif //GENERATOR_SLOW_SYLLABLEBASE_H
