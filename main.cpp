#include "AFD.hpp"
using namespace std;
using namespace AFD_fx;

int main() {
    string input;
    printProtocol();
    string fileName;
    cin >> fileName;
    AFD afd(read(fileName));
    if(!afd.checkHealth())
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