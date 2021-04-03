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

void Options::display() {
    std::cout << "max syllable length: " << max_syllable_len << '\n';
    std::cout << "n vowels alongside:  " << n_cons_vowels << '\n';
    std::cout << "repeating consonant: " << repeating_conso << '\n';
    std::cout << "word length min:     " << word_length_min << '\n';
    std::cout << "word length max:     " << word_length_max << '\n';
}


void Options::set_max_syllable_len(std::string line) {
    int i = 0, a;
    while(line[i] == ' ') { i++; }
    if(line[i] >= '0' && line[i] <= '9') {
        a = std::stoi(&line[i]);
        if(a > 1) {
            max_syllable_len = a;
        } else {
            std::cout << "Max syllable length nie moze byc mniejsze niz 2.\n";
        }
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
}
void Options::set_n_cons_vowels(std::string line) {
    int i = 0, a;
    while(line[i] == ' ') { i++; }
    if(line[i] >= '0' && line[i] <= '9') {
        a = std::stoi(&line[i]);
        if(a > 1) {
            n_cons_vowels = a;
        } else {
            std::cout << "N consecutive vowels nie moze byc mniejsze niz 2.\n";
        }
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
}
void Options::set_repeating_conso(std::string line) {
    int i = 0, a;
    while(line[i] == ' ') { i++; }
    if(line[i] >= '0' && line[i] <= '9') {
        a = std::stoi(&line[i]);
        if(a == 0 || a == 1 || a == 2) {
            repeating_conso = a;
        } else {
            std::cout << "Repeating consonant moze przybierac tylko wartosci 0, 1 lub 2.\n";
        }
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
}
void Options::set_word_length_min(std::string line, bool force) {
    int i = 0;
    while (line[i] == ' ') { i++; }
    if (line[i] >= '0' && line[i] <= '9') {
        int a = std::stoi(&line[i]);
        if (a > 1 && (a <= word_length_max || force)) {
            word_length_min = a;
        } else {
            std::cout << "Dlugosc slowa nie moze byc krotsza niz 1 ani wieksza niz word length max.\n";
        }
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
}
void Options::set_word_length_max(std::string line) {
    int i = 0;
    while (line[i] == ' ') { i++; }
    if (line[i] >= '0' && line[i] <= '9') {
        int a = std::stoi(&line[i]);
        if (a > 1 && a >= word_length_min) {
            word_length_max = a;
        } else {
            std::cout << "Dlugosc slowa nie moze byc krotsza niz 1 ani mniejsza niz word length min.\n";
        }
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
}
void Options::set_word_lengths(std::string line) {
    int i = 0, a, b;
    while (line[i] == ' ') { i++; }
    if(line[i] >= '0' && line[i] <= '9') {
        a = std::stoi(&line[i]);
        while (line[i] >= '0' && line[i] <= '9') { i++; }
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
    while (line[i] == ' ') { i++; }
    if(line[i] >= '0' && line[i] <= '9') {
        b = std::stoi(&line[i]);
        if(b >= a) {
            word_length_min = a;
            word_length_max = b;
        } else {
            word_length_min = b;
            word_length_max = a;
        }
    } else if(line[i] == 0) {
        word_length_min = a;
        word_length_max = a;
    } else {
        std::cout << "Prosze podac liczbe.\n";
    }
}
