#include "AFD.hpp"
using namespace std;

int main() {
    string input;
    cout << "Dans le fichier txt. Vous devez saisir en respectant ce protocol : \n" << "Etat Initial => I,\n" <<"transition => t,\n" << "liste d'etats => E,\n" << "liste d'etats finaux => F,\n" << "l'alphabet => A,\n";
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Veuillez entrer le nom du fichier a utiliser : ";
    string fileName;
    cin >> fileName;
    AFD afd(read(fileName));
    if(!afd.mechanic()) 
        return 0;
    afd.print();
    string mot = "abba";
    cout << "Le mot " << mot << " : \n" << (afd.accept(mot) ? "accepte" : "refuse") << endl;
    mot = "bbbabb";
    cout << "Le mot bbbabb : \n" << (afd.accept(mot) ? "accepte" : "refuse") << endl;
    mot = "bababa";
    cout << "Le mot bababa : \n" << (afd.accept(mot) ? "accepte" : "refuse") << endl;
    while (true) {
        cout << "Entrez un mot a tester : ";
        cin >> input;
        if(input == "exit")
            break;
        cout << "Le mot " << input << " : \n" << (afd.accept(input) ? "accepte" : "refuse") << endl;
    }
    getch();
    return 0;
}