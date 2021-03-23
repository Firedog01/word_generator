//
// Created by Firedog on 08.03.2021.
//

/*
 * tworzenie drzewa:
 *      wygenerowanie tablicy wszystkich kombinacji
 *      potasowanie jej (?)
 *      utworzenie drzewa
 *      zapisanie do pliku
 */

#ifndef GENERATOR_SLOW_SYLLABLETREE_H
#define GENERATOR_SLOW_SYLLABLETREE_H

#include <iostream>
#include <string>
#include <fstream>

class SyllableTree{
    friend class SyllableBase;

    class Leaf {
        Leaf* r_leaf;
        Leaf* l_leaf;
        std::string c;
    public:
        Leaf() : r_leaf(nullptr), l_leaf(nullptr), c("")
            {}
    };

    int len;            //length of one syllable
    std::string* tab;   //dynamic table of all syllables
    Leaf root;

    int make_tree();
    std::string* gen_tab(int);
public:
    SyllableTree(int);
};

#endif //GENERATOR_SLOW_SYLLABLETREE_H
