#include <iostream>
#include "../lib/SyllableBase.h"

using namespace std;

void word_loop(SyllableBase&);
void mod_dictionary(SyllableBase&);
void display_help(char a);

/*
 * todo (features):
 *  * zapisywanie kilku presetów
 *  * mechanizm zapamiętywania dobrych połączeń sylab (?)
 *  * może tworzenie jakiś pregenerowanych struktur (?)
 */

int main() {
    SyllableBase base;
    string line;
    bool exit = false;

    cout << "+-------------------------------------------------+\n";
    cout << "|            Program do tworzenia slow            |\n";
    cout << "|          Wcisnij \'h\' by uzyskac pomoc.          |\n";
    cout << "+-------------------------------------------------+\n";

    //main program loop
    while(!exit) {
        getline(cin, line);
        int i = 0;
        while (line[i] == ' ') { i++; }
        switch (line[i]) {
            case 'b':   //zacznij generowac slowa
                word_loop(base);
                break;
            case 'd':   //opcje slownika
                mod_dictionary(base);
                break;
            case 'h':   //pomoc
                display_help('a');
                break;
            case 'o':   //opcje
                break;
            case 'q':   //wyjście
                exit = true;
                break;
            default:    //error
                break;
        }
    }
    return 0;
}
void word_loop(SyllableBase& base) {
    string line;
    int i;
    while(true) {
        cout << base.new_w();
        getline(cin, line);
        i = 0;
        if(line.empty()) { continue; }
        while (line[i] == ' ') { i++; }
        switch(line[i]) {
            case 'X':
            case 'x':
                return;
            case 's':
                //todo save
                break;
            default:
                break;
        }
    }
}

void mod_dictionary(SyllableBase& base) {
    char a;
    string sound;
    while (true) {
        switch(a = getchar()) {
            cout << a << '\n';
            case 'd':
                base.display_dict();
                break;
            case 'c': //spolgloska
                getline(cin, sound);
                base.add_conso(sound);
                break;
            case 'v':
                getline(cin, sound);
                base.add_vowel(sound);
                break;
            case 'x':
                base.update_dict();
                return;
        }
    }
}

void display_help(char a) {
    switch(a) {
        case 'a':
            cout << "Dostepne instrukcje:\n";
            cout << "b    - (begin) zacznij generowanie nowych slow\n";
            cout << "d    - (dictionary) edytuj opcje slownika sylab\n";
            cout << "h    - (help) wyswietl pomoc\n";
            cout << "o    - (options) modyfikuj opcje generowania slow\n";
            cout << "q    - (quit) wyjscie z programu\n";
            cout << "\n";
            cout << "By dowiedziec sie o poszczegolnych funkcjach wcisnij \'h [opcja]\'\n";
            break;
        case 'b':
            cout << "Instrukcja korzystania z b\n";
            break;
    }

}
