//
// Created by Firedog on 25.03.2021.
//

#ifndef GENERATOR_SLOW_DICTIONARY_H
#define GENERATOR_SLOW_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>

class Dictionary {
    std::string path;                   //path of dictonary file
    std::string dict_temp_path;         //path of dict_temp file

    std::string* vowels = nullptr;      //table of vowels
    int n_vowels = 0;                   //number of vowels
    std::string* consonants = nullptr;  //table of consonants
    int n_consonants = 0;               //number of consonants

    //sorts arrays of strings because for some reason std::sort doesnt work ://
    static void string_sort(std::string*, int);
    //updates dictionary !!!file!!! Writes current contents of string tables to the file
    void update_dict();

    //returns position of a sound. first bool decides which table
    //0 if consonants, 1 if vowels
    int find_sound(bool, const std::string&);
public:
    Dictionary() {}
    ~Dictionary();
    void init(std::string);

    bool good;                  //set true if file is properly handled

    std::string get_vowel(int n);
    std::string get_conso(int n);
    int get_n_vowels();
    int get_n_conso();

    void display();
    void remove_sound(std::string);
    void add_conso(std::string);
    void add_vowel(std::string);
};

#endif //GENERATOR_SLOW_DICTIONARY_H
