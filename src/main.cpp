#include <iostream>
#include "../lib/SyllableBase.h"

using namespace std;

void word_loop(SyllableBase&);
void display_help(char a);
void menu_manager(string, string);


#define DICTIONARY_PATH "../res/dict.txt"

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
    base.update();
    base.display_base();
    for(int i = 0; i < 50; i++) {
        cout << base.new_w() << '\n';
    }

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
                word_loop(base);
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
                                            base.dictionary.add_conso(line);
                                            break;
                                        default:
                                            base.dictionary.add_conso(&line[i]);
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
                                            base.dictionary.add_vowel(line);
                                            break;
                                        default:
                                            base.dictionary.add_vowel(&line[i]);
                                            break;
                                    }
                                    break;
                                case 'd':
                                    base.dictionary.display();
                                    break;
                                case 'r':
                                    do { i++; }
                                    while (line[i] == ' ');
                                    switch (line[i]) {
                                        case 0:
                                            cout << "Podaj co usunac:";
                                            getline(cin, line);
                                            base.dictionary.remove_sound(line);
                                            break;
                                        default:
                                            base.dictionary.remove_sound(&line[i]);
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
                        base.dictionary.display();
                        break;
                    case 'c':
                        do { i++; }
                        while (line[i] == ' ');
                        switch (line[i]) {
                            case 0:
                                cout << "podaj nowa spolgloske:";
                                getline(cin, line);
                                base.dictionary.add_conso(line);
                                break;
                            default:
                                base.dictionary.add_conso(&line[i]);
                        }
                        base.dictionary.display();
                        break;
                    case 'v':
                        do { i++; }
                        while (line[i] == ' ');
                        switch (line[i]) {
                            case 0:
                                cout << "podaj nowa samogloske:";
                                getline(cin, line);
                                base.dictionary.add_vowel(line);
                                break;
                            default:
                                base.dictionary.add_vowel(&line[i]);
                                break;
                        }
                        base.dictionary.display();
                        break;
                    case 'r':
                        do { i++; }
                        while (line[i] == ' ');
                        switch (line[i]) {
                            case 0:
                                cout << "Podaj co usunac:";
                                getline(cin, line);
                                base.dictionary.remove_sound(line);
                                break;
                            default:
                                base.dictionary.remove_sound(&line[i]);
                                break;
                        }
                        base.dictionary.display();
                        break;
                    case 'x':
                        break;
                    default:
                        cout << "Zla opcja. Wpisz \'h d\' by dowiedziec sie wiecej.\n";
                        break;
                }
                } //d
                break;
            case 'h':   //pomoc
                ///////////////////////////////////////////////help
                do { i++; }
                while (line[i] == ' ');
                switch(line[i]) {
                    case 0:
                        display_help('a');
                    default:
                        display_help(line[i]);
                }
                break;
            case 'o':   //opcje
                ///////////////////////////////////////////////options
                {
                do { i++; } while(line[i] == ' ');
                switch(line[i]) {
                    case 0:
                        {

                        }//case 0
                        break;
                    case 'l':
                        do { i++; } while(line[i] == ' ');
                        switch(line[i]) {
                            case 0:
                                cout << "Podaj word length min: ";
                                getline(cin, line);
                                base.options.set_word_length_min(line, 1);
                                cout << "Podaj word length max: ";
                                getline(cin, line);
                                base.options.set_word_length_max(line);
                                break;
                            case 'a': //min
                                do { i++; } while (line[i] == ' ');
                                switch (line[i]) {
                                    case 0:
                                        cout << "Podaj word length min: ";
                                        getline(cin, line);
                                        base.options.set_word_length_min(line, 0);
                                        break;
                                    default:
                                        base.options.set_word_length_min(&line[i], 0);
                                }
                                break;
                            case 'b': //max
                                do { i++; } while (line[i] == ' ');
                                switch (line[i]) {
                                    case 0:
                                        cout << "Podaj word length max: ";
                                        getline(cin, line);
                                        base.options.set_word_length_max(line);
                                        break;
                                    default:
                                        base.options.set_word_length_max(&line[i]);
                                }
                                break;
                            case 'c': //both
                                do { i++; } while (line[i] == ' ');
                                switch (line[i]) {
                                    case 0:
                                        cout << "Podaj word length min: ";
                                        getline(cin, line);
                                        base.options.set_word_length_min(line, 1);
                                        cout << "Podaj word length max: ";
                                        getline(cin, line);
                                        base.options.set_word_length_max(line);
                                        break;
                                    default:
                                        base.options.set_word_lengths(&line[i]);
                                }
                                break;
                            default:
                                cout << "Zla opcja. Wpisz \'h o\' by dowiedziec sie wiecej.\n";
                                break;
                        }
                        break;
                    case 'd': //displays current options
                        base.options.display();
                        break;
                    case 'c': //repeating conso
                        do { i++; } while(line[i] == ' ');
                        switch(line[i]) {
                            case 0:
                                cout << "Podaj wartosc repeating consonant: ";
                                getline(cin, line);
                                base.options.set_repeating_conso(line);
                                break;
                            default:
                                base.options.set_repeating_conso(&line[i]);
                        }
                        break;
                    case 'm': //max syllable length
                        do { i++; } while(line[i] == ' ');
                        switch(line[i]) {
                            case 0:
                                cout << "Podaj max syllable length: ";
                                getline(cin, line);
                                base.options.set_max_syllable_len(line);
                                break;
                            default:
                                base.options.set_max_syllable_len(&line[i]);
                        }
                        break;
                    case 'n': //n cons vowels
                        do { i++; } while(line[i] == ' ');
                        switch(line[i]) {
                            case 0:
                                cout << "Podaj n consecutive vowels: ";
                                getline(cin, line);
                                base.options.set_n_cons_vowels(line);
                                break;
                            default:
                                base.options.set_n_cons_vowels(&line[i]);
                        }
                        break;
                }
                }
                break;
            case 'q':   //wyjście
                ///////////////////////////////////////////////quit
                exit = true;
                break;
            case 'x':
                cout << "Aby wyjsc z programu nacisnij \'q\'.\n";
                break;
            default:    //error
                ///////////////////////////////////////////////error
                break;
        }
    }
    return 0;
}

void menu_manager(string option, string param) {
    int i = 0;
    switch(option[i]) {
        ;
    }
}

void word_loop(SyllableBase& base) {
    string line, word;
    base.update();
    int i;
    while(true) {
        word = base.new_w();
        cout << word;

        i = 0;
        getline(cin, line);
        if(line.empty()) { continue; }
        while (line[i] == ' ') { i++; }
        switch(line[i]) {
            case 'X':
            case 'x':
                return;
            case 's':
                base.save_word(word);
                break;
            default:
                break;
        }
    }
}

void display_help(char a) {
    switch(a) {
        case 'a':
            cout << "Dostepne opcje:\n";
            cout << "b              - (begin) zacznij generowanie nowych slow\n";
            cout << "d              - (dictionary) edytuj slownik glosek\n";
            cout << "h              - (help) wyswietl pomoc\n";
            cout << "o              - (options) modyfikuj opcje generowania slow\n";
            cout << "q              - (quit) wyjscie z programu\n";
            cout << "\n";
            cout << "By dowiedziec sie o poszczegolnych funkcjach wcisnij \'h [opcja]\'\n";
            cout << "By dowiedzien sie wiecej o dzialaniu programu i korzystaniu z niego wpisz \'h h\'.\n";
            break;
        case 'b':
            cout << "Instrukcja korzystania z opcji b\n";
            break;
        case 'd':
            cout << "Instrukcja korzystania z opcji d\n";
            cout << "By wejsc w tryb edytowania slownika wybierz w menu opcje \'d\'\n";
            cout << "Alternatywnie mozna korzystac z formy d [opcja] [argumenty] w jednym poleceniu\n";
            cout << "c [argument/y] - (consonant) dodaj nowa samogloske\n";
            cout << "v [argument/y] - (vowel) dodaj nowa spolgloske\n";
            cout << "r [argument/y] - (remove) usun podane gloski\n";
            cout << "d              - (display) wyswietl aktualny slownik\n";
            cout << "x              - (exit) wyjdz z trybu edytowania slownika\n";
            break;
        case 'h':
            cout << "Korzystanie z programu i dodatkowe informacje\n";
            cout << "work in progress\n";
            break;
        default:
            cout << "Nieprawidlowa opcja. Wpisz \'h\' by dowiedziec sie wiecej.\n";
    }
}

