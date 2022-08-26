using namespace std;
#include "./src/AFD.hpp" //! inclusion must be after the use of std namespace
using namespace AFD_fx;

int main() {
    printProtocol();
    string fileName;
    std::cout << "Veuillez entrer le nom du fichier a utiliser : ";
    std::cin >> fileName;
    const AFD afd(read(fileName));
    const AFD test_afd(read("test_automate.afd"));
    /* try {
     AFD *__afd = new AFD(read("automate_EX5.afd"));
        __afd->print();
        delete __afd;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    } */
    cout << test_afd;
    if(!afd.isHealthy()) 
        return 0;
    afd.print("AFD EX5");
    const std::string mot = "abba";
    const AFD _AFD = afd;
    afd.Try(mot);
    afd.Try("bbbabb");
    afd.Try("bababa");
    afd.Try("abbbbbbbbababbb");
    std::cout << mirror("test") << std::endl;
    std::cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << std::endl;
    afd.consoleInput();
    std::cout << afd;
    afd.isAccessibleState(1) ? std::cout << "accessible" << std::endl : std::cout << "not accessible" << endl;
    return 0;
}