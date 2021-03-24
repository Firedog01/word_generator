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
    base.update_dict();
    //main program loop
    //string s1 = "z", s2 = "hg"; s1 > s2
    //cout << s1.compare(s2) << '\n';
    //cout << s2.compare(s1) << '\n';
    while(!exit) {
        cout << "menu>";
        getline(cin, line);
        int i = 0;
        while (line[i] == ' ') { i++; }
        switch (line[i]) {
            case 'b':   //zacznij generowac slowa
                ///////////////////////////////////////////////begin
                word_loop(base);
                break;
            case 'd':   //opcje slownika
                ///////////////////////////////////////////////dictionary
                do { i++; } while (line[i] == ' ');
                switch(line[i]) {
                    case 0: {
                        while (line[i] != 'x') {
                            cout << "directory options>";
                            getline(cin, line);
                            i = 0;
                            while (line[i] == ' ') { i++; }
                            switch (line[i]) {
                                case 'c':
                                    do { i++; } while (line[i] == ' ');
                                    switch (line[i]) {
                                        case 0:
                                            cout << "Podaj spolgloske:";
                                            getline(cin, line);
                                            base.add_conso(line);
                                            break;
                                        default:
                                            base.add_conso(&line[i]);
                                            break;
                                    }
                                    break;
                                case 'v':
                                    do { i++; } while (line[i] == ' ');
                                    switch (line[i]) {
                                        case 0:
                                            cout << "Podaj samogloske:";
                                            getline(cin, line);
                                            base.add_vowel(line);
                                            break;
                                        default:
                                            base.add_vowel(&line[i]);
                                            break;
                                    }
                                    break;
                                case 'd':
                                    base.display_dict();
                                    break;
                                case 'r':
                                    do { i++; } while (line[i] == ' ');
                                    switch (line[i]) {
                                        case 0:
                                            cout << "Podaj co usunac:";
                                            getline(cin, line);
                                            //base.remove_sound(line);
                                    }
                                    break;
                                case 'x':
                                    base.update_dict();
                                    break;
                                default:
                                    cout << "Zla opcja. Wpisz \'h d\' by dowiedziec sie wiecej.\n";
                            }
                        }
                        } //case 0
                        break;
                    case 'd':
                        base.display_dict();
                        break;
                    case 'c':
                        do { i++; } while (line[i] == ' ');
                        switch(line[i]) {
                            case 0:
                                cout << "podaj nowa spolgloske:";
                                getline(cin, line);
                                base.add_conso(line);
                                break;
                            default:
                                base.add_conso(&line[i]);
                        }
                        base.update_dict();
                        base.display_dict();
                        break;
                    case 'v':
                        do { i++; } while (line[i] == ' ');
                        switch(line[i]) {
                            case 0:
                                cout << "podaj nowa samogloske:";
                                getline(cin, line);
                                base.add_vowel(line);
                                break;
                            default:
                                base.add_vowel(&line[i]);
                                break;
                        }
                        base.update_dict();
                        base.display_dict();
                        break;
                    case 'r':
                        break;
                    case 's':
                        base.sort_tables();
                        break;
                    default:
                        cout << "Zla opcja. Wpisz \'h d\' by dowiedziec sie wiecej.\n";
                        break;
                }
                break;
            case 'h':   //pomoc
                ///////////////////////////////////////////////help
                display_help('a');
                break;
            case 'o':   //opcje
                ///////////////////////////////////////////////options
                break;
            case 'q':   //wyjście
                ///////////////////////////////////////////////quit
                exit = true;
                break;
            default:    //error
                ///////////////////////////////////////////////error
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
                cout << "podaj spółgłoskę: ";
                getline(cin, sound);
                base.add_conso(sound);
                break;
            case 'v':
                cout << "podaj samogłoskę: ";
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
