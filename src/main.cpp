#include <iostream>
#include "../lib/SyllableBase.h"

using namespace std;

void word_loop(SyllableBase&);
void display_help(char a);

/*
 * todo (features):
 *  * zapisywanie kilku presetów
 *  * mechanizm zapamiętywania dobrych połączeń sylab (?)
 *  * może tworzenie jakiś pregenerowanych struktur (?)
 *
 *
Kolejność głosek nie ma znaczenia.
Po ostatniej głosce nie ma średnika.
Nie może być mniej niż 2 litery w linii.
Głoski mogą zawierać się z kilku liter.
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
        cout << "menu>";
        getline(cin, line);
        int i = 0;
        while (line[i] == ' ') { i++; }
        switch (line[i]) {
            case 'b':   //zacznij generowac slowa
                ///////////////////////////////////////////////begin
                {
                    cout << "word creation>\n";
                    string word;
                while (line[i] != 'x') {
                    word = base.new_w();
                    cout << word << "\t\t:";
                    getline(cin, line);
                    switch(line[i]) {
                        case 'l':
                            //modify length
                            break;
                        case 's':
                            base.save_word(word);
                            break;
                    }
                }
                } //b
                //word_loop(base);
                break;
            case 'd':   //opcje slownika
                ///////////////////////////////////////////////dictionary
                {
                do { i++; } while (line[i] == ' ');
                switch (line[i]) {
                    case 0: {
                        while (line[i] != 'x') {
                            cout << "directory options>";
                            getline(cin, line);
                            i = 0;
                            while (line[i] == ' ') { i++; }
                            switch (line[i]) {
                                case 'c':
                                    do { i++; }
                                    while (line[i] == ' ');
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
                                    do { i++; }
                                    while (line[i] == ' ');
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
                                    do { i++; }
                                    while (line[i] == ' ');
                                    switch (line[i]) {
                                        case 0:
                                            cout << "Podaj co usunac:";
                                            getline(cin, line);
                                            base.remove_sound(line);
                                            break;
                                        default:
                                            base.remove_sound(&line[i]);
                                            break;
                                    }
                                    break;
                                case 'x':
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
                        do { i++; }
                        while (line[i] == ' ');
                        switch (line[i]) {
                            case 0:
                                cout << "podaj nowa spolgloske:";
                                getline(cin, line);
                                base.add_conso(line);
                                break;
                            default:
                                base.add_conso(&line[i]);
                        }
                        base.display_dict();
                        break;
                    case 'v':
                        do { i++; }
                        while (line[i] == ' ');
                        switch (line[i]) {
                            case 0:
                                cout << "podaj nowa samogloske:";
                                getline(cin, line);
                                base.add_vowel(line);
                                break;
                            default:
                                base.add_vowel(&line[i]);
                                break;
                        }
                        base.display_dict();
                        break;
                    case 'r':
                        do { i++; }
                        while (line[i] == ' ');
                        switch (line[i]) {
                            case 0:
                                cout << "Podaj co usunac:";
                                getline(cin, line);
                                base.remove_sound(line);
                                break;
                            default:
                                base.remove_sound(&line[i]);
                                break;
                        }
                        base.display_dict();
                        break;
                    case 'x':
                        cout << "Aby wyjsc z programu nacisnij \'q\'.\n";
                        break;
                    default:
                        cout << "Zla opcja. Wpisz \'h d\' by dowiedziec sie wiecej.\n";
                        break;
                }
                } //d
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
