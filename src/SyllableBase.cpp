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
}

int SyllableBase::Word::get_syl(int n) {
    if(n < n_syllable)
        return syllable[n];
    else
        return 0;
}

SyllableBase::Word::Word(std::vector<int> tab, int n) {
    n_syllable = n;
    syllable = tab;
}

SyllableBase::Word &SyllableBase::Word::operator=(const SyllableBase::Word & old_word) {
    Word new_word(old_word.syllable, old_word.n_syllable);
    return new_word;
}

void SyllableBase::generate_word_base(int length_min, int length_max, int max_syl_len, int n_cons_vow) {
    std::vector< std::vector<Word> > new_base(length_max - length_min + 1);
    for(int k = length_min; k <= length_max; k++) {
        int z_min, z_max; //dla danej długosci k ustalamy maksymalna i minimalna ilosc podzialow
        z_min = ceil((double)k / (double)max_syl_len);
        z_max = k - 1;     //pomijamy przypadek samych samogłosek

        //std::cout << "k: " << k << ", z_min: " << z_min << ", z_max: " << z_max << '\n';
        for(int z = z_min; z <= z_max; z++) {
            //std::cout << "------ z = " << z << " ------\n";
            std::vector<int> iter_tab;
            for(int i = 0; i < z; i++) {
                iter_tab.push_back(1);
            }                       //ustawianie wszystkich elementow na 1 poza ostatnim, bo nie umiem inaczej ustawic warunku w iterate tab
            iter_tab[z-1] = 0;

            int condition;
            while(true) {
                condition = iterate_tab(iter_tab, z, k, max_syl_len, n_cons_vow);
                if(condition == 0) {
                    break;
                }
                //std::cout << "Uzyskany rozklad: ";
                //display_tab(iter_tab, z);
                new_base[k - length_min].emplace_back(iter_tab, z);
            }
        }
    }
    word_base = new_base;
}

int SyllableBase::iterate_tab(std::vector<int>& tab, int n_tab, int k, int max_syl_len, int n_cons_vow) {
    bool is_the_last = true;
    for(int i = 0; i < n_tab - 1; i++) {
        if (tab[i] <= tab[i+1])
            is_the_last = false;
    }
    if(is_the_last && tab[n_tab - 1] != 0)
        return 0;
    int max_cell = std::min( std::min(max_syl_len, (k - n_tab + 1)), k);
    do {
        tab[n_tab-1] += 1;
        //ta petla sprawdza warunek czy pojawila sie taka sytuacja, ze jakies pole tab ma wartosc wieksza niz max_cell
        //petla dojdzie tylko do tab[1]
        for(int i = n_tab - 1; i > 0; i--) {
            if(tab[i] > max_cell) {
                tab[i] = 1;
                tab[i-1] += 1;
            }
        }
        if(tab[0] > max_cell) {
            return 0;
        }
    } while( !(length_check(tab, n_tab, k) && vowel_check(tab, n_tab, n_cons_vow)) ); //sprawdza wszystkie checki, wszystkie musza byc spelnione
    return 1;
}

void SyllableBase::display_base() {
    for(int k = 0; k < word_base.size(); k++) {
        std::cout << "----------" << k << "----------\n";
        for(int i = 0; i < word_base[k].size(); i++) {
            for(int j = 0; j < word_base[k][i].get_n(); j++) {
                std::cout << word_base[k][i].get_syl(j) << ' ';
            }
            std::cout << " n: " << word_base[k][i].get_n();
            std::cout << '\n';
        }
    }
}

//sprawdza czy slowo ma oczekiwana dlugosc
bool SyllableBase::length_check(std::vector<int>& tab, int n, int k) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += tab[i];
    }
    if(sum == k) {
        return true;
    } else {
        return false;
    }
}

//sprawdza warunek n consecutive vowels
bool SyllableBase::vowel_check(std::vector<int>& tab, int n, int n_cons_vow) {
    bool is_vowel_cons;
    int max_vow = n_cons_vow;
    for(int i = 0; i < n; i++) {
        if(tab[i] == 1) {
            max_vow -= 1;
            if(max_vow == 0)
                return false;
        } else {
            max_vow = n_cons_vow;
        }
    }
    return true;
}

std::string SyllableBase::new_w() {
    std::string new_word;
    std::uniform_int_distribution<int> word_length(0, word_base.size() - 1);
    int l = word_length(generator);

    std::uniform_int_distribution<int> syl_dist(0, word_base[l].size() - 1);

    int l2 = syl_dist(generator);
    Word word = word_base[l][l2];

    std::uniform_int_distribution<int> consos(0, dictionary.get_n_conso());
    std::uniform_int_distribution<int> vowels(0, dictionary.get_n_vowels());
    int last_conso = -1, last_vowel = -1;

    for(int i = 0; i < word.syllable.size(); i++) {
        std::cout << word.syllable[i] << ' ';
    }
    std::cout << '\n';
    for(int i = 0; i < word.get_n(); i++) {
        std::cout << "syl: " << i << ", ";
        std::cout << "syl len: " << word.get_syl(i) << ", ";
        std::uniform_int_distribution<int> vow_pos_dist(1, word.get_syl(i));
        int vow_pos = vow_pos_dist(generator);
        std::cout << "vow pos: " << vow_pos << ", ";
        for(int j = 1; j <= word.get_syl(i); j++) {
            if(j == vow_pos) { //vowel
                int cur_vowel;
                do {
                    cur_vowel = vowels(generator);
                } while (last_vowel == cur_vowel);
                new_word += dictionary.get_vowel(cur_vowel);
            } else { //consonant
                int cur_conso;
                do {
                    cur_conso = consos(generator);
                } while (last_conso == cur_conso && options.repeating_conso != 0);
                new_word += dictionary.get_conso(cur_conso);
            }
        }
        std::cout << '\n';
    }
    return new_word;
}



void SyllableBase::save_word(const std::string& word) {
    std::fstream _save(SAVED_WORDS, std::ios::app);
    _save << word << '\n';
    _save.close();
}

void SyllableBase::update() {
    generate_word_base(options.word_length_min, options.word_length_max, options.max_syllable_len, options.n_cons_vowels);
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}












