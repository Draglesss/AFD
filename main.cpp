using namespace std;
#include "./src/AFD.hpp"
using namespace AFD_fx;

int main() {
    printProtocol();
    string fileName;
    std::cout << "Veuillez entrer le nom du fichier a utiliser : ";
    std::cin >> fileName;
    const AFD afd(read(fileName));
    // const AFD test_afd(read("test.test.afd"));
    /* try {
     AFD *__afd = new AFD(read("automate_EX5.afd"));
        __afd->print();
        delete __afd;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    } */
    if(!afd.isHealthy())
        return 0;
    afd.print("AFD EX5");
    const std::string mot = "abba";
    afd.Try(mot);
    afd.Try("bbbabb");
    afd.Try("bababa");
    afd.Try("abbbbbbbbababbb");
    std::cout << mirror("test") << std::endl;
    std::cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << std::endl;
    afd.consoleInput();
    afd << "afd";
    afd.isAccessibleState(1) ? std::cout << "accessible" << std::endl : std::cout << "not accessible" << endl;
    return 0;
}