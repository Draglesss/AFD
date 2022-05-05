#include "AFD.hpp"
using namespace std;
using namespace AFD_fx;

int main() {
    printProtocol();
    string fileName;
    cin >> fileName;
    const AFD afd(read(fileName));
    const AFD AFD;
    if(!afd.checkHealth())
        return 0;
    afd.print("AFD EX5");
    AFD.print("test AFD");
    string mot = "abba";
    afd.Try(mot);
    mot = "bbbabb";
    afd.Try(mot);
    mot = "bababa";
    afd.Try(mot);
    afd.Try("abbbbbbbbababbb");
    cout << mirror(mot) << endl;
    printSize(mot);
    afd.print("AFD EX5");
    cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << endl;
    afd.inputFromUser();
    getch();
    return 0;
}