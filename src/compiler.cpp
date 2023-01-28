#include <iostream>
#include <fstream>
#include <map>

#include "Utils.hpp"
#include "Lexer.hpp"
#include "Translator.hpp"


using namespace std;

int main(int argc, char** argv)
{

    if (argc < 2) {
        LogFatal("Not enough arguments");
    }


    if (std::string(argv[1]) == "help") {
        
        cout << "Krestiki Language Compiler\n\n"
            << "Usage: \n"
            << "krestiki[.exe] <source>.krst [OPTIONS]\n\n"
            << "Available options: \n"
            << "--target windows | linux | macos  - specify OS\n"
            << "--compile                         - skip compilation confirmation\n"
            << "--keep-cpp                        - do not remove generated c++ code\n"
            ;

        return 0;
    }

    map<std::string, std::string> options;
    for (int i = 2; i < argc; ++i) {
        std::string option_name = argv[i];
        if (option_name.substr(0, 2) == "--") {
            std::string option_value = "1";
            if (i < argc - 1 && std::string(argv[i + 1]).substr(0, 2) != "--") {
                option_value = argv[i + 1];
            }
            options[option_name.substr(2, option_name.length() - 2)] = option_value;
        }
    }

    if (options["target"] != "windows" &&
        options["target"] != "linux"   &&
        options["target"] != "macos") {
        LogFatal("Target OS not specified");
    }

    for (const auto &[key, value] : options) {
        LogInfo("Option '" + key + "' == '" + value + "'");
    }

    string rawfilename = argv[1];
    string extension = rawfilename.substr(rawfilename.length() - 5, 5);
    if (extension != ".krst") {
        LogFatal("Unsupported file extension '" + extension + "'");
    }
    std::string filename = rawfilename.substr(0, rawfilename.length() - 5);


    ifstream infile(rawfilename);
    string input;
    string tmp;
    while (infile) {
        std::getline(infile, tmp);
        if (tmp.substr(0, 2) != "//") 
            input += tmp + "\n";
        tmp = "";
    }
    infile.close();

    Lexer *lexer = new Lexer(input);
    vector<Token> tokens = lexer->Parse();

    Translator *translator = new Translator(tokens);

    string code = translator->GetCppCode();

    std::string cpp_filename = "_krestikilang_" + filename + ".cpp";
    ofstream file(cpp_filename);

    file << "/*\nCode generated by Krestiki Language Compiler\n*/\n";
    file << code;

    file.close();


    std::string answer;
    if (options["compile"] == "1") {
        answer = "y";
        cout << "Compiling..." << endl;
    }
    else {
        cout << "Compile? [y/n] ";
        cin >> answer;
    }

    std::string output_filename = "";
    if (options["output"] != "") {
        output_filename = options["output"];
    }
    else {
        if (options["target"] == "windows")
            output_filename = filename + ".exe";
        else if (options["target"] == "linux" || options["target"] == "macos")
            output_filename;
    }
    
    if (answer == "y") {
        if (options["target"] == "windows")
            system(("g++ " + cpp_filename + " -o " + output_filename).c_str());
        else if (options["target"] == "linux" || options["target"] == "macos")
            system(("g++ " + cpp_filename + " -o " + output_filename).c_str());
    }
  
    if (options["keep-cpp"] == "") {
         if (options["target"] == "windows")
            system(("del " + cpp_filename).c_str());
        else if (options["target"] == "linux" || options["target"] == "macos")
            system(("rm " + cpp_filename).c_str());
    }

    return 0;
}
