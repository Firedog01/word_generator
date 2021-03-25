//
// Created by Firedog on 25.03.2021.
//

#ifndef GENERATOR_SLOW_DICTIONARY_H
#define GENERATOR_SLOW_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>

class Dictionary {
    std::string* vowels;        //table of vowels
    int n_vowels;               //number of vowels
    std::string* consonants;    //table of consonants
    int n_consonants;           //number of consonants

    void string_sort(std::string*, int);//sorts arrays of strings because for some reason std::sort doesnt work ://
    void update_dict();          //updates dictionary !!!file!!!
public:
    bool is_dict_good;          //set true if file

    void remove_sound(std::string);
    void add_conso(std::string);
    void add_vowel(std::string);
    int find_sound(bool, const std::string&);
    Dictionary();
    ~Dictionary();
};

#endif //GENERATOR_SLOW_DICTIONARY_H
