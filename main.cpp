#include "AFD.hpp"
using namespace std;

int main() {
    string input;
    print_protocol();
    string fileName;
    cin >> fileName;
    AFD afd(read(fileName));
    if(!afd.mechanic()) 
        return 0;
    afd.print();
    string mot = "abba";
    afd.Try(mot);
    mot = "bbbabb";
    afd.Try(mot);
    mot = "bababa";
    afd.Try(mot);
    afd.Try("abbbbbbbbababbb");
    while (true) {
        cout << "Entrez un mot a tester : ";
        cin >> input;
        if(input == "exit")
            break;
        afd.Try(input);
    }
    getch();
    return 0;
}