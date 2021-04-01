//
// Created by Firedog on 01.04.2021.
//
#include "../lib/Options.h"

int Options::set_var(std::string& line) {
    int i = 0;
    while(line[i] != '=') { i++; }
    return std::stoi(&line[++i]);
}

void Options::init(std::string _path) {
    path = _path;
    std::fstream _preset(_path, std::ios::in | std::ios::out);
    if( ! _preset.good()) {
        good = false;
        return;
    }
    std::string line;
    _preset.seekg(0);                 //setting cursor to beginning
    std::getline(_preset, line);    //max syllable length
    max_syllable_len = set_var(line);
    std::getline(_preset, line);    //min word length
    word_length_min = set_var(line);
    std::getline(_preset, line);    //max word length
    word_length_max = set_var(line);
    std::getline(_preset, line);    //number of consecutive vowels
    n_cons_vowels = set_var(line);
    std::getline(_preset, line);    //can consonants repeat
    repeating_conso = set_var(line);
    _preset.close();
    good = true;
}