#include "AFD.hpp"
using namespace std;
using namespace AFD_fx;

int main() {
    printProtocol();
    string fileName;
    cin >> fileName;
    const AFD afd(read(fileName));
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
    cout << mirror(mot) << endl;
    printSize(mot);
    mot = "abba";
    cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << endl;
    afd.inputFromUser();
    getch();
    return 0;
}