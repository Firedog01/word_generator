//
// Created by Firedog on 08.03.2021.
//


#define GEND_FILE "../res/saved_words.txt"
#define TREE_FILE "../src/tree_file"

#include "../lib/SyllableTree.h"

SyllableTree::SyllableTree(int l) {
    this->len = l;
    //TODO check if tree file exists
    TREE_FILE;

    make_tree();
    //TODO obsługa błędów
    /*
     * 4 - dict.txt nie istnieje
     * 5 - nie można utworzyć saved_words.txt
     */

}

int SyllableTree::make_tree() {
    std::fstream _gend(GEND_FILE, std::ios::out | std::ios::in);
    if ( ! _gend.good()) {
        std::fstream temp(GEND_FILE, std::ios::out);
        _gend = dynamic_cast<std::basic_fstream<char, std::char_traits<char>> &&>(temp);    //?? idk what dat is
        if ( ! _gend.good()) {
            return 5;
        }
    }


}


