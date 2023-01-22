#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "Lexer.hpp"
#include "Utils.hpp"

class Translator
{
private:
    std::vector<Token> tokens;

    std::string TypeByTokenKind(TokenKind kind)
    {
        switch (kind)
        {
            case Integer:
                return "long long int";
            case String:
                return "std::string";
            default:
                LogFatal("Does not a type!");
                break;
        }
    }

public:
    Translator(std::vector<Token> tokens)
    {
        this->tokens = tokens;
    }

    std::string GetCppCode(bool only_output=false)
    {
        std::string prefix = "\nint main(){\n";
        std::string postfix = "\n}\n";
        std::string functions = "#include <iostream>\n";
        std::string output = "";
        LogInfo(std::to_string(this->tokens.size()));
        
        bool tilda_opened = false;
        for(int i = 1; i < this->tokens.size() - 1; ++i)
        {
            LogInfo("TOKEN: " + this->tokens[i].text);
            switch (this->tokens[i].kind)
            {
                case TokenKind::Plus:
                {
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <PLUS> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " + " + right.text;

                    break;
                }
                case TokenKind::Minus:
                {
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <MINUS> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " - " + right.text;
                    
                    break;
                }
                case Multiplication:
                {
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <MULTIPLICATION> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " * " + right.text;
    
                    break;
                }
                case Division:
                {
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <DIVISION> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " / " + right.text;
                    
                    break;
                }
                case Remainder:
                {
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <REMAINDER> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " % " + right.text;
                    
                    break;
                }
                case Tilda:
                {
                    if (!tilda_opened)
                    {
                        if (i + 2 >= tokens.size()) {
                            LogFatal("Not enough tokens to process if operation");
                        }
                        Token if_operation = tokens[i + 1];
                        Token value        = tokens[i + 2];
                        //Token 

                        if (value.kind != Symbols) {
                            LogFatal("Cannot do if operation on '" + value.text + "'");
                        }

                        switch(if_operation.kind)
                        {
                        case Less:
                            output += "if (" + value.text + " < 0) {";
                            break;
                        case Bigger:
                            output += "if (" + value.text + " > 0) {";
                            break;
                        case Equals:
                            output += "if (" + value.text + " == 0) {";
                            break;
                        case NotEquals:
                            output += "if (" + value.text + " != 0) {";
                            break;
                        }

                        tilda_opened = true;
                    }
                    else
                    {
                        output += " } ";
                        tilda_opened = false;    
                    }

                    break;
                }
                /*case Less:
                    break;
                case Bigger:
                    break;
                case Equals:
                    break;
                case NotEquals:
                    break;
                    */
                case Label:
                {
                    Token right = tokens[i + 1];
                    if (right.kind != TokenKind::Symbols) {
                        LogFatal("Unexpected definition of label: '" + right.text + "'");
                    }

                    output += "\n" + right.text + ":\n";
                    break;
                }
                case GoTo: 
                {
                    Token right = tokens[i + 1];
                    if (right.kind != TokenKind::Symbols) {
                        LogFatal("Unexpected target of goto: '" + right.text + "'");
                    }

                    output += "goto " + right.text + ";";
                    break;
                }
                case Variable:
                {
                    if (i + 3 >= tokens.size()) {
                        LogFatal("Not enough arguments for variable definition");
                    }
                    Token name = tokens[i + 1];
                    Token type = tokens[i + 2];
                    // TODO: string value assignment
                    Token value = tokens[i + 3];

                    switch (type.kind)
                    {
                    case TokenKind::Integer:
                        output += "long long int";
                        break;
                    case TokenKind::String:
                        output += "std::string";
                        break;
                    default:
                        LogFatal("Unexpected type '" + type.text + "'");
                        break;
                    }

                    output += " " + name.text + " = " + value.text + ";";

                    break;
                }
                case Function:
                {
                    // TODO: check token kinds
                    
                    Token name = tokens[i + 1];
                    Token type = tokens[i + 2];
                    Token openpar = tokens[i + 3];

                    if (openpar.kind != TokenKind::OpenParenthesis) {
                        LogFatal("");
                    }
                    functions += TypeByTokenKind(type.kind) + " " + name.text + "(";

                    i += 4;
                    std::string argname = "";
                    while(tokens[i].kind != TokenKind::CloseParenthesis) {
                        switch (tokens[i].kind)
                        {
                            case Comma:
                                functions += ",";
                                break;
                            
                            case Symbols:
                                argname = tokens[i].text;
                                break;

                            case Integer:
                            case String:
                                functions += TypeByTokenKind(tokens[i].kind) + " " + argname;
                                argname = "";
                                break;
                        }
                        i++;
                    }
                    i++;
                    functions += ") {";
                    std::vector<Token> func_inner;
                    while(tokens[i].kind != TokenKind::Bigger) {
                        func_inner.push_back(tokens[i]);
                        i++;
                    }
                    Translator *tr = new Translator(func_inner);
                    functions += tr->GetCppCode(true);
                    functions += "}";

                    break;
                }
                case Semicolon:
                    output += ";";
                    break;

                case Read:
                {
                    Token name = tokens[i + 1];
                    if (name.kind != TokenKind::Symbols) {
                        LogFatal("Not a variable name: '" + name.text + "'");
                    }
                    output += "std::cin >> " + name.text + ";";
                    break;
                }
                case Write:
                {
                    Token name = tokens[i + 1];
                    if (name.kind != TokenKind::Symbols) {
                        LogFatal("Not a variable name: '" + name.text + "'");
                    }
                    output += "std::cout << " + name.text + ";";
                    
                    break;
                }
                case Update:
                {
                    if (i + 1 >= tokens.size()) {
                        LogFatal("Not enough arguments for <UPDATE>");
                    }
                    
                    Token name = tokens[i + 1];
                    if (name.kind != TokenKind::Symbols) {
                        LogFatal("Not a variable name: '" + name.text + "'");
                    }
                    output += name.text + " = ";
                    
                    break;
                }
                case Throw:
                {
                    Token name = tokens[i + 1];
                    if (name.kind != TokenKind::Symbols) {
                        LogFatal("Not a variable name: '" + name.text + "'");
                    }
                    output += "return " + name.text + ";";
                           
                    break;
                }

                /*case OpenParenthesis:
                    break;
                case CloseParenthesis:
                    break;*/
            }
        }

        //std::cout << "!@@!" << functions << "!AA" << std::endl;

        if (only_output) return output;

        return functions + prefix + output + postfix;
    }

};

#endif
