#include <iostream>

#include "Lexer.hpp"
#include "Translator.hpp"


using namespace std;

int main(int argc, char** argv)
{

    cout << sizeof(Token) << endl;

    cout << 1 << endl;

    Lexer *lexer = new Lexer("a A 7");
    //Lexer *lexer = new Lexer("~ A )");
    vector<Token> tokens = lexer->Parse();

    Translator *translator = new Translator(tokens);

    translator->GetCppCode();

    cout << 1 << endl;
    
    return 0;
}

