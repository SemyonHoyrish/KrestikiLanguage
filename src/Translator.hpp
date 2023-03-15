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

        return "";
    }

public:
    Translator(std::vector<Token> tokens)
    {
        this->tokens = tokens;
    }

    std::string GetCppCode(bool only_output=false)
    {
        std::string prefix = "\nint main(){\n";
        std::string postfix = "\nreturn 0;\n}\n";
        std::string functions = (std::string)"#include <iostream>\n"
            + "#define I_type long long int\n"
            + "const std::string _X1 = \"\\n\";\n"
            + "const std::string _X5 = \"|\";\n"
            + "std::string _X2(std::string s, I_type index) {"
            + "return ((std::string)\"\" + s[index]);"
            + "}\n"
            + "void _X3(I_type arr[], I_type index, I_type value) {"
            + "arr[index] = value; }\n"
            + "void _X3(std::string arr[], I_type index, std::string value) {"
            + "arr[index] = value; }\n"
            + "void _X4(I_type arr[], I_type index, I_type &value) {"
            + "value = arr[index]; }\n"
            + "void _X4(std::string arr[], I_type index, std::string &value) {"
            + "value = arr[index]; }\n"
            ;

        std::string output = "";
        
        bool tilda_opened = false;
        for(int i = 1; i < this->tokens.size() - 1; ++i)
        {

            // TODO: Check if there are enough tokens to translate operation
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
                    bool is_ptr = false;
                    while(tokens[i].kind != TokenKind::CloseParenthesis) {
                        switch (tokens[i].kind)
                        {
                            case Comma:
                                functions += ",";
                                break;
                            
                            case Symbols:
                                argname = tokens[i].text;
                                break;

                            case Pointer:
                                is_ptr = true;
                                break;

                            case Integer:
                            case String:
                                functions += TypeByTokenKind(tokens[i].kind) + (is_ptr ? "*" : "") + " " + argname;
                                argname = "";
                                is_ptr = false;
                                break;
                        }
                        i++;
                    }
                    //i++;
                    functions += ") {";
                    std::vector<Token> func_inner;
                    while(tokens[i].kind != TokenKind::Percent) {
                        func_inner.push_back(tokens[i]);
                        i++;
                    }
                    Translator *tr = new Translator(func_inner);
                    functions += tr->GetCppCode(true);
                    functions += "}";

                    break;
                }
                case FunctionCall:
                {
                    Token name = tokens[i + 1];
                    i++;
                    i++;
                    i++;
                    output += name.text + "(";
                    while (tokens[i].kind != TokenKind::CloseParenthesis) {
                        if (tokens[i].kind == TokenKind::Comma) {
                            output += ", ";
                        }
                        else if (tokens[i].kind == TokenKind::Pointer) {
                            output += "&";
                        }
                        else {
                            output += tokens[i].text;
                        }
                        i++;
                    }

                    output += ")";

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
                case Array:
                {
                    Token name = tokens[i + 1];
                    Token type = tokens[i + 2];
                    Token size = tokens[i + 3];

                    output += TypeByTokenKind(type.kind) + " " + name.text + "[" + size.text + "];";

                    break;
                }

                /*case OpenParenthesis:
                    break;
                case CloseParenthesis:
                    break;*/

                default:
                    //LogWarning("Unexpected token '" + tokens[i].text + "'");
                    break;
            }
        }

        if (only_output) return output;

        return functions + prefix + output + postfix;
    }

};

#endif
