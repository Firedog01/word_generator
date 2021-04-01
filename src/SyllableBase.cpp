//
// Created by Firedog on 08.03.2021.
//

#define DICT_FILE "../res/dict.txt"
#define PRESET_FILE "../res/preset.txt"
#define SAVED_WORDS "../saved_words.txt"

#include "../lib/SyllableBase.h"

SyllableBase::SyllableBase() {
    dictionary.init(DICT_FILE);
    if(!dictionary.good) {
        std::cout << "blad przy otwieraniu pliku dict.txt\n";
    }
    options.init(PRESET_FILE);
    if(!options.good) {
        std::cout << "blad przy otwieraniu pliku preset.txt\n";
    }
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

SyllableBase::~SyllableBase() {
    //delete [] word_base;
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

void SyllableBase::generate_word_base(int length_min, int length_max) {
    //todo
    //trzeba najpierw policzyć sumę wielokrotną wszystkich elementów o długości pomiędzy min i max
    //długość sylaby wacha się od 1 do max_syllable_len

    //najpierw policzmy sumę wszystkich elementów, żeby zainicjalizować tablicę?
    //albo nie.. możę ztobić tablicę tablic a potem ją zmergować

    //zliczenie i zainicjowanie wartościami powinno przebiegać równocześnie

    //mając już rozważaną długość słowa, oznaczmy ją jako l
    //potrzebujemy wyznaczyć ilość z podziałów na sylaby. Np, dla l=5 podział 4+1 z=1
    //trzeba wyznaczyć z_min i z_max
    //czyli przeiterować przez wszystkie interesujące nas kombinacje

    //może funkcja która potem przechodzi przez tablicę dla danego k i danego z
    //wyeliminuje niechciane kombinacje np same sylaby

    //funkcja do iteracji po tablicy liczb
    //np dla max_syl_len = 4 i z = 2
    //2|1|4 -> 2|2|1 -> 2|2|2 itp
    for(int k = length_min; k <= length_max; k++) {
        int z_min = 0, z_max = 0;
        //wyznaczenie z_min i z_max;
        for(int z = z_min; z <= z_max; z++) {
            int* iter_tab = new int[z];
            for(int i = 0; i < z; i++) {
                iter_tab[i] = 1;
            }
            //syl_pos_base[k - length_min] = generate_syl_pos(k, z, iter_tab);
        }
    }
    /*
     * Syllable inter_tab(int* tab, int n_tab, ); //
     * Word* generate_syl_pos(int k, int z, int* iter_tab, int n);
     *
     *  Word** syl_pos_base;
     *  for(int k = length_min; k <= length_max; k++) {
     *      //wyznaczenie z_min i z_max;
     *      for(int z = z_min; z <= z_max; z++) {
     *          int* iter_tab = new int[z];
     *          for(int i = 0; i < z; i++) {
     *              iter_tab[i] = 1;
     *          }
     *          syl_pos_base[k - length_min] = generate_syl_pos(k, z, iter_tab);
     *
     *      }
     *  }
     *
     *
     *  Word* generate_syl_pos(int k, int z, int* iter_tab, int n) {
     *      Word* tab;
     *      while( // wszystkie komórki w iter_tab są równe max_syl_pos) {
     *
     *      }
     *
     *  }
     */

}


std::string SyllableBase::new_w() {
    std::string word;
    /*
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
     */
    return word;
}

std::string SyllableBase::get_syllable(int generated_length, std::uniform_int_distribution<int>& vowel,std::uniform_int_distribution<int>& conso, int& last_vowel, int& last_conso) {
    std::string syl;
    int letter;
    std::uniform_int_distribution<int> vow_pos(1, generated_length);
    /*
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
     */
    return syl;
}

int SyllableBase::which_one(const int* table, int len, int generated) {
    for(int i = 0; i < len; i++) {
        generated -= table[i];
        if(generated <= 0) {
            return ++i;
        }
    }
    return 0;
}



void SyllableBase::save_word(const std::string& word) {
    std::fstream _save(SAVED_WORDS, std::ios::app);
    _save << word << '\n';
    _save.close();
}

SyllableBase::Syllable SyllableBase::iterate_Tab(int *, int) {

    return SyllableBase::Syllable();
}







