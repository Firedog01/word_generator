//
// Created by Firedog on 25.03.2021.
//

#include "../lib/Dictionary.h"

#define DICT_FILE "../res/dict.txt"
#define DICT_FILE_TEMP "../res/dict_temp.txt"

Dictionary::Dictionary() {
    std::fstream _dict(DICT_FILE, std::ios::in);
    if( ! _dict.good()) {
        is_dict_good = false;
        return;
    }
    std::string line;
    _dict.seekg(0);
    std::getline(_dict, line); // nic, pomijamy linię
    std::getline(_dict, line); // wczytanie samoglosek
    n_consonants = 1;
    for(int i = 0; i < line.length(); i++) {
        if(line[i] == ';') {
            n_consonants++;
        }
    } //zliczenie ilości samoglosek
    consonants = new std::string[n_consonants];
    for(int i = 0, j = 0; i < n_consonants && j < line.length(); i++, j++) { //j to pozycja względem początku, i to liczba komórki
        std::string tmp;
        while(line[j] != ';' && line[j] != 0) {
            tmp += line[j];
            j++;
        }
        consonants[i] = tmp;
    }
    std::getline(_dict, line); // nic, pomijamy linię
    std::getline(_dict, line); // wczytanie spolglosek
    n_vowels = 1;
    for(int i = 0; i < line.length(); i++) {
        if(line[i] == ';') {
            n_vowels++;
        }
    } //zliczenie ilości samoglosek
    vowels = new std::string[n_vowels];
    for(int i = 0, j = 0; i < n_vowels && j < line.length(); i++, j++) { //j to pozycja względem początku, i to liczba komórki
        std::string tmp;
        while(line[j] != ';' && line[j] != 0) {
            tmp += line[j];
            j++;
        }
        vowels[i] = tmp;
    }
    _dict.close();
    is_dict_good = true;
}

Dictionary::~Dictionary() {

}

void Dictionary::update_dict() {
    std::string line;
    std::fstream _dict_temp(DICT_FILE_TEMP, std::ios::out | std::ios::trunc | std::ios::in );
    if( ! _dict_temp.good()) {
        std::cout << "nie wprowadzono zmian. Nie utworzono dict_temp.txt\n";
    }
    _dict_temp << "spolgloski = " << n_consonants << '\n';
    _dict_temp << consonants[0];
    for(int i = 1; i < n_consonants; i++) {
        _dict_temp << ";" << consonants[i];
    }
    _dict_temp << "\nspolgloski = " << n_vowels << '\n';
    _dict_temp << vowels[0];
    for(int i = 1; i < n_vowels; i++) {
        _dict_temp << ";" << vowels[i];
    }
    _dict_temp.seekg(0);
    std::fstream _dict(DICT_FILE, std::ios::out|std::ios::trunc);
    if( ! _dict.good()) {
        std::cout << "nie wprowadzono zmian. Nie otwarto dict.txt\n";
    }
    for(int i = 0; i < 4; i++) {
        getline(_dict_temp, line);
        _dict << line << '\n';
    }
    _dict_temp.close();
}

//adds new vowel to vowel table
void Dictionary::add_vowel(std::string new_v) {
    int n_new_v = 1;
    for(int i = 0; i < new_v.length(); i++) {
        if(new_v[i] == ' ') {
            n_new_v++;
            while(new_v[i] == ' ') { i++; }
        }
    }
    auto* temp_new = new std::string[n_new_v];
    for(int i = 0, j = 0; i < n_new_v; i++) {
        std::string temp_sound;
        for(; new_v[j] != ' ' && new_v[j] != 0; j++)
            temp_sound+=new_v[j];
        j++;
        temp_new[i] = temp_sound;
    }
    n_vowels+=n_new_v;
    auto* temp = new std::string[n_vowels];
    for(int i = 0; i < n_vowels - n_new_v; i++) {
        temp[i] = vowels[i];
    }
    for(int i = 0, j = n_new_v; i < n_new_v; i++, j--) {
        temp[n_vowels-j] = temp_new[i];
    }
    delete [] temp_new;
    delete [] vowels;
    vowels = temp;
    string_sort(vowels, n_vowels);
    update_dict();
}

//adds new consonant to conso table
void Dictionary::add_conso(std::string new_c) {
    int n_new_c = 1;
    for(int i = 0; i < new_c.length(); i++) {
        if(new_c[i] == ' ') {
            n_new_c++;
            while(new_c[i] == ' ') { i++; }
        }
    }
    auto* temp_new = new std::string[n_new_c];
    for(int i = 0, j = 0; i < n_new_c; i++) {
        std::string temp_sound;
        for(; new_c[j] != ' ' && new_c[j] != 0; j++)
            temp_sound += new_c[j];
        j++;
        temp_new[i] = temp_sound;
    }
    n_consonants += n_new_c;
    auto* temp = new std::string[n_consonants];
    for(int i = 0; i < n_consonants - n_new_c; i++) {
        temp[i] = consonants[i];
    }
    for(int i = 0, j = n_new_c; i < n_new_c; i++, j--) {
        temp[n_consonants-j] = temp_new[i];
    }
    delete [] temp_new;
    delete [] consonants;
    consonants = temp;
    string_sort(consonants, n_consonants);
    update_dict();
}

//removes sound from tables
void Dictionary::remove_sound(std::string rem) {
    int n_rem = 1;
    for(int i = 0; i < rem.length(); i++) {
        if(rem[i] == ' ') {
            n_rem++;
            while(rem[i] == ' ') { i++; }
        }
    }
    auto* rem_table = new std::string[n_rem];
    for(int i = 0, j = 0; i < n_rem; i++) {
        std::string temp_sound;
        for(; rem[j] != ' ' && rem[j] != 0; j++)
            temp_sound += rem[j];
        j++;
        rem_table[i] = temp_sound;
    }
    for(int i = 0; i < n_rem; i++) {
        int a = find_sound(0, rem_table[i]); //spolgloski
        if(a == 0) {
            a = find_sound(1, rem_table[i]); //samogloski
            if(a == 0) {
                std::cout << "nie znaleziono gloski " << rem_table[i] << '\n';
                continue;
            }
            vowels[a-1] = "";
            n_vowels -= 1;
            auto* temp = new std::string[n_vowels];
            for(int j = 0, k = 0; j < n_vowels + 1; j++) {
                if(!vowels[j].empty()) {
                    temp[k] = vowels[j];
                    k++;
                }
            }
            delete [] vowels;
            vowels = temp;
        }
        consonants[a-1] = "";
        n_consonants -= 1;
        auto* temp = new std::string[n_consonants];
        for(int j = 0, k = 0; j < n_consonants + 1; j++) {
            if(!consonants[j].empty()) {
                temp[k] = consonants[j];
                k++;
            }
        }
        delete [] consonants;
        consonants = temp;
    }
    update_dict();
}

int Dictionary::find_sound(bool b, const std::string& sound) {//0 if conso
    int length;
    std::string* table;
    if(b) {
        length = n_vowels;
        table = vowels;
    } else {
        length = n_consonants;
        table = consonants;
    }
    for(int i = 0; i < length; i++) {
        if(table[i] == sound) {
            return i + 1;
        }
    }
    return 0;
}

void Dictionary::string_sort(std::string* table, int length) {
    //because table is already almost sorted will be used insertion sort
    //todo i was lazy and wrote bubble. Correct to insertion. [low priority]
    bool sorted = false;
    while(!sorted) {
        sorted = true;
        for (int i = 0; i < length - 1; i++) {
            if (table[i].compare(table[i + 1]) > 0) { // next is smaller
                std::swap(table[i], table[i + 1]);
                sorted = false;
            }
        }
    }
}


