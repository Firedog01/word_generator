//
// Created by Firedog on 01.04.2021.
//

#ifndef GENERATOR_SLOW_OPTIONS_H
#define GENERATOR_SLOW_OPTIONS_H

#include <iostream>
#include <string>
#include <fstream>

class Options {
    std::string path;

    static int set_var(std::string&);
public:
    int max_syllable_len;       //maximal generated length of syllable, in sounds
    int n_cons_vowels;          //number of maximal consecutive vowels in a row
    int repeating_conso;        //can consonants repeat
    int word_length_min;        //*
    int word_length_max;        //* interval of considered lengths (in sounds)

    bool good;

    void set_max_syllable_len(std::string);
    void set_n_cons_vowels(std::string);
    void set_repeating_conso(std::string);
    void set_word_length_min(std::string, bool);
    void set_word_length_max(std::string);
    void set_word_lengths(std::string);
    void init(std::string);
    void display();
};
#endif //GENERATOR_SLOW_OPTIONS_H
