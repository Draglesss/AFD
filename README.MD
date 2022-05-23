<h1>AFD READER</h1>

<h2>What is this project?</h2>
This project is a simple implementation of a Finite Automate using Finite-state Machine Model.

<h2>What is the purpose of this project?</h2>
This project is to learn how to use the C++ language by building a simple console application relying on a static library wich includes a full AFD implementation.

<h2>How to use this project?</h2>
You can use this library to implement your own Finite Automate by including the header file and reading from a text file respecting the FA defining protocol. <br>
The header file is located in the AFD_cpp\AFD\AFD.hpp file.<br>
The main file is an example of how to use the library.

~~~cpp
#include "AFD.hpp"
using namespace std;
using namespace AFD_fx;

int main() {
    printProtocol(); //* Prints the protocol of the FA defining protocol to the console.
    string fileName; //* The name of the file to be read.	
    cin >> fileName; //* Reads the name of the file to be read.
    const AFD afd(read(fileName)); //* Creates an AFD object using the read function.
    AFD AFd(read("automate_EX5.txt"));
    cout << ((AFd == afd) ? "similar" : "not similar" ) << endl; //* Prints if the AFD is similar to the AFD created by the read function.
    AFd = afd; //* Assigns the AFD created by the read function to the AFD created by the AFD object.
    const AFD afdd = read("automate.txt"); 
    if(!afd.isHealthy()) { //* Checks if the AFD is healthy.
        return 0;
    afd.print("AFD EX5"); //* Prints the AFD to the console.
    AFd.print("test AFD");
    const string mot = "abba";
    afd.Try(mot); //* Prints the Finite Automate's path and result for the given word.
    afd.Try("bbbabb");
    afd.Try("bababa");
    afd.Try("abbbbbbbbababbb");
    cout << mirror(mot) << endl; //* Prints the mirror of the given word.
    printSize(mot);
    cout << "Le mot " << mot << " est " << (AFD_fx::isPalindrome(mot) ? "" : "pas ") << "un palindrome" << endl;
    afd.inputFromUser(); //* Reads a word from the console and prints the Finite Automate's path and result for the given word during runtime.
    getch();
    return 0;
}
~~~	

<h2>What's the future of this project?</h2>
This project is a work in progress.<br>
Soon i might add a GUI that shows the input analyzer doing its magic, and also AFD to AFD manilpulation.<br>

<h3>Credits</h3>
<ul>
<li>Otmane Fatteh aka Draglesss</li>
</ul>
