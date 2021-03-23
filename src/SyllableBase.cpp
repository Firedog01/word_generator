//
// Created by Firedog on 08.03.2021.
//

#define DICT_FILE "../res/dict.txt"
#define PRESET_FILE "../res/preset.txt"

#include "../lib/SyllableBase.h"

unsigned int SyllableBase::display_length_stress(unsigned int &) {
    return 0;
}

unsigned int SyllableBase::display_syllable_stress(unsigned int &) {
    return 0;
}

SyllableBase::SyllableBase() {
    switch(handle_dict()) {
        case 0:
            break;
        case 1:
            std::cout << "dict nie istnieje";
    }
    switch(handle_preset()) {
        case 0:
            break;
        case 1:
            std::cout << "preset nie istnieje";
    }
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

SyllableBase::~SyllableBase() {
    delete [] vowels;
    delete [] consonants;
    delete [] syllable_stress;
    delete [] length_stress;
}

///
/// functions connected to dict
///
//called in constructor, updates table with consonants and vowels and sets
//value of their number
int SyllableBase::handle_dict() {
    std::fstream _dict(DICT_FILE, std::ios::in);
    if( ! _dict.good()) {
        return 1;
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
    for(int i = 0, j = 0; i < n_consonants && j < line.length(); i++, j++) { //j to pozycja względem początku, i to liczba komórki
        std::string tmp;
        while(line[j] != ';' && line[j] != 0) {
            tmp += line[j];
            j++;
        }
        vowels[i] = tmp;
    }
    _dict.close();
    is_dict_modified = false;
    is_dict_handled = true;
    return 0;
}

//updates only dict.txt file
void SyllableBase::update_dict() {
    std::string line;
    std::fstream _dict(DICT_FILE);
    if( ! _dict.good()) {
        std::cout << "nie wprowadzono zmian \n";
    }
    _dict.seekg(13);
    _dict << n_consonants << '\n';

    std::getline(_dict, line); // wczytanie samoglosek
    _dict.close();
    is_dict_modified = false;
    return;
}

//uses cout to display contents of sounds tables
void SyllableBase::display_dict() {
    std::cout << "Spolgloski:\n";
    for(int i = 0; i < n_consonants; i++)
        std::cout << consonants[i] << ' ';
    std::cout << "\nSamogloski:\n";
    for(int i = 0; i < n_vowels; i++)
        std::cout << vowels[i] << ' ';
    std::cout << '\n';

}

//adds new vowel to vowel table
void SyllableBase::add_vowel(std::string new_vowel) {
    n_vowels-=-1;
    std::string* temp = new std::string[n_vowels];
    for(int i = 0; i < n_vowels - 1; i++) {
        temp[i] = vowels[i];
    }
    temp[n_vowels-1] = new_vowel;
    delete [] vowels;
    vowels = temp;
    is_dict_modified = true;
}

//adds new consonant to conso table
void SyllableBase::add_conso(std::string new_conso) {
    n_consonants-=-1;
    std::string* temp = new std::string[n_consonants];
    for(int i = 0; i < n_consonants - 1; i++) {
        temp[i] = consonants[i];
    }
    temp[n_consonants-1] = new_conso;
    delete [] consonants;
    consonants = temp;
    is_dict_modified = true;
}

//reads from preset file and sets variables right
int SyllableBase::handle_preset() {
    std::fstream _preset(PRESET_FILE, std::ios::in | std::ios::out);
    if( ! _preset.good()) {
        return 1;
    }
    std::string line;
    _preset.seekg(0);                 //setting cursor to beginning
    std::getline(_preset, line);    //NO TOUCHY:

    std::getline(_preset, line);    //is dict modified
    int i = 0;
    while(line[i] != '=') { i++;}
    is_dict_modified = !!( std::stoi(&line[++i]) );

    std::getline(_preset, line);    //max length
    i = 0;
    while(line[i] != '=') { i++;}
    max_length = std::stoi(&line[++i]);

    std::getline(_preset, line);    //length stress
    length_stress = new int[max_length];
    i = 0;
    while(line[i] != '=') { i++;}
    for(int j = 0; j < max_length; j++) {
        i++;
        length_stress[j] = std::stoi(&line[i]);
        while(line[i] >= '0' && line[i] <= '9') { i++; }
    }

    std::getline(_preset, line);    //length stress
    syllable_stress = new int[max_syllable_len];
    i = 0;
    while(line[i] != '=') { i++;}
    for(int j = 0; j < max_syllable_len; j++) {
        i++;
        syllable_stress[j] = std::stoi(&line[i]);
        while(line[i] >= '0' && line[i] <= '9') { i++; }
    }
    is_stress_modified_l = false;
    is_stress_modified_s = false;
    return 0;
}


//generates new word
std::string SyllableBase::new_w() {
    std::string word;
    //this is bit complicated, but each 6 bits represents one syllable
    int total_word_length = 0;
    for(int i = 0; i < max_length; i++) {
        total_word_length += length_stress[i];
    }
    int total_syllable_length = 0;
    for(int i = 0; i < max_syllable_len; i++) {
        total_syllable_length += syllable_stress[i];
    }
    std::uniform_int_distribution<int> word_length(1, total_word_length);
    std::uniform_int_distribution<int> syllable_length(1, total_syllable_length);
    std::uniform_int_distribution<int> vowel(0, n_vowels - 1);
    std::uniform_int_distribution<int> conso(0, n_consonants - 1);

    int length = which_one(length_stress, max_length, word_length(generator));
    int last_vowel = 1024;
    int last_conso = 1024;
    for(int i = 0; i < length; i++) {
        word += get_syllable(which_one(syllable_stress, max_syllable_len, syllable_length(generator)),
                                vowel, conso, last_vowel, last_conso);
    }
    return word;
}

//generates new syllable
// implemented:
// * differentiates sounds between syllables.
//      prevents from double vowels or consonants back to back
//      (negative) will not create structures as such: v_1c_1 v_2c_1
std::string SyllableBase::get_syllable(int generated_length, std::uniform_int_distribution<int>& vowel,std::uniform_int_distribution<int>& conso, int& last_vowel, int& last_conso) {
    std::string syl;
    int letter;
    std::uniform_int_distribution<int> vow_pos(1, generated_length);
    int vow_pos_n = vow_pos(generator);
    for(int i = 1; i <= generated_length; i++) {
        if(i == vow_pos_n) {
            do {
                letter = vowel(generator);
            } while (letter == last_vowel);
            last_vowel = letter;
            syl += vowels[letter];
        } else {
            do {
                letter = conso(generator);
            } while (letter == last_conso);
            last_conso = letter;
            syl += consonants[letter];
        }
    }
    return syl;
}

// gets table of layout
// returns which in order is drawn
// eg. for 1/2/3 drawn 2 returns 2
// is required by get_syllable
int SyllableBase::which_one(int* table, int len, int generated) {
    for(int i = 0; i < len; i++) {
        generated -= table[i];
        if(generated <= 0) {
            return ++i;
        }
    }
    return 0;
}