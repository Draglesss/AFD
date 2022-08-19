#include "./src/AFD.hpp"
using namespace std;
using namespace AFD_fx;

int main() {
    printProtocol();
    string fileName;
    cout << "Veuillez entrer le nom du fichier a utiliser : ";
    cin >> fileName;
    const AFD afd(read(fileName));
    AFD yAFD(read("automate_EX5.afd"));
    cout << ((yAFD == afd) ? "similar" : "not similar" ) << endl;
    yAFD = afd;
    if(!afd.isHealthy())
        return 0;
    afd.print("AFD EX5");
    yAFD.print("test AFD");
    const string mot = "abba";
    afd.Try(mot);
    afd.Try("bbbabb");
    afd.Try("bababa");
    afd.Try("abbbbbbbbababbb");
    cout << mirror("test") << endl;
    cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << endl;
    afd.consoleInput();
    cout << afd;
    afd.isAccessibleState(1) ? cout << "accessible" << endl : cout << "not accessible" << endl;
    getch();
    return 0;
}