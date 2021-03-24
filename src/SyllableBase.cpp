//
// Created by Firedog on 08.03.2021.
//

#define DICT_FILE "../res/dict.txt"
#define DICT_FILE_TEMP "../res/dict_temp.txt"
#define PRESET_FILE "../res/preset.txt"
#define SAVED_WORDS "../saved_words.txt"

#include "../lib/SyllableBase.h"

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
}

///
/// functions connected to dict
///
//called in constructor, updates table with consonants and vowels and sets
//value of their number
int SyllableBase::handle_dict() {
    std::fstream _dict(DICT_FILE, std::ios::in);
    if( ! _dict.good()) {
        is_dict_good = false;
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
    return 0;
}

//updates only dict.txt file
void SyllableBase::update_dict() {
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

//uses cout to display contents of sounds tables
void SyllableBase::display_dict() {
    std::cout << "Spolgloski (" << n_consonants << "):\n";
    for(int i = 0; i < n_consonants; i++)
        std::cout << consonants[i] << ' ';
    std::cout << "\nSamogloski (" << n_vowels <<  "):\n";
    for(int i = 0; i < n_vowels; i++)
        std::cout << vowels[i] << ' ';
    std::cout << '\n';
}

//adds new vowel to vowel table
void SyllableBase::add_vowel(std::string new_v) {
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
void SyllableBase::add_conso(std::string new_c) {
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
void SyllableBase::remove_sound(std::string rem) {
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

int SyllableBase::find_sound(bool b, const std::string& sound) {//0 if conso
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

void SyllableBase::string_sort(std::string* table, int length) {
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


void SyllableBase::Word::set_properties(int n, Syllable* ptr) {
    n_syllable = n;
    syllable = ptr;
}

SyllableBase::Syllable SyllableBase::Word::get_syllable(int syl_pos) {
    if(syl_pos < n_syllable)
        return syllable[syl_pos];
    return SyllableBase::Syllable();
}

int SyllableBase::Word::get_n() const {
    return n_syllable;
}

void SyllableBase::generate_word_base(int length_min, int length_man) {
    //todo
    //trzeba najpierw policzyć sumę wielokrotną wszystkich elementów o długości pomiędzy min i max
    //długość sylaby wacha się od 1 do max_syllable_len
    
}

int SyllableBase::set_var(std::string& line) {
    int i = 0;
    while(line[i] != '=') { i++;}
    return std::stoi(&line[++i]);
}

int SyllableBase::handle_preset() {
    std::fstream _preset(PRESET_FILE, std::ios::in | std::ios::out);
    if( ! _preset.good()) {
        return 1;
    }
    std::string line;
    _preset.seekg(0);                 //setting cursor to beginning
    std::getline(_preset, line);    //max syllable length
    max_syllable_len = set_var(line);
    std::getline(_preset, line);    //min word length
    word_length_min = set_var(line);
    std::getline(_preset, line);    //max word length
    word_length_min = set_var(line);
    return 0;
}



std::string SyllableBase::new_w() {
    std::string word;
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

int SyllableBase::which_one(int* table, int len, int generated) {
    for(int i = 0; i < len; i++) {
        generated -= table[i];
        if(generated <= 0) {
            return ++i;
        }
    }
    return 0;
}



void SyllableBase::save_word(std::string word) {
    std::fstream _save(SAVED_WORDS, std::ios::app);
    _save << word << '\n';
    _save.close();
}






