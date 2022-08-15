#include "./src/AFD.hpp"
using namespace std;
using namespace AFD_fx;

int main() {
    printProtocol();
    string fileName;
    cin >> fileName;
    const AFD afd(read(fileName));
    AFD AFd(read("automate_EX5.txt"));
    cout << ((AFd == afd) ? "similar" : "not similar" ) << endl;
    AFd = afd;
    const AFD afdd = read("automate.txt");
    if(!afd.isHealthy())
        return 0;
    afd.print("AFD EX5");
    AFd.print("test AFD");
    const string mot = "abba";
    afd.Try(mot);
    afd.Try("bbbabb");
    afd.Try("bababa");
    afd.Try("abbbbbbbbababbb");
    cout << mirror(mot) << endl;
    printSize(mot);
    cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << endl;
    afd.consoleInput();
    cout << afd;
    getch();
    afd.isAccessibleState(1) ? cout << "accessible" << endl : cout << "not accessible" << endl;
    return 0;
}