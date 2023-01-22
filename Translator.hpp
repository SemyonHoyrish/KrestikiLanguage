#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "Lexer.hpp"
#include "Utils.hpp"

class Translator
{
private:
    std::vector<Token> tokens;

public:
    Translator(std::vector<Token> tokens)
    {
        this->tokens = tokens;
    }

    std::string GetCppCode()
    {
        std::string output = "";
        LogInfo(std::to_string(this->tokens.size()));
        
        bool tilda_opened = false;
        for(int i = 1; i < this->tokens.size() - 1; ++i)
        {
            LogInfo("TOKEN: " + this->tokens[i].text);
            switch (this->tokens[i].kind)
            {
                case TokenKind::Plus:
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <PLUS> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " + " + right.text;

                    break;

                case Minus:
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <MINUS> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " - " + right.text;
                    
                    break;

                case Multiplication:
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <MULTIPLICATION> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " * " + right.text;
    
                    break;
                
                case Division:
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <DIVISION> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " / " + right.text;
                    
                    break;

                case Remainder:
                    Token left = tokens[i - 1];
                    Token right = tokens[i + 1];
                    
                    if (left.kind != TokenKind::Symbols ||
                        right.kind != TokenKind::Symbols) {
                        
                        LogFatal("Unsupported operation <REMAINDER> beetwen '" + left.text + "' and '" + right.text + "'");
                    }

                    output += left.text + " % " + right.text;
                    
                    break;
                
                case Tilda:
                    if (!tilda_opened)
                    {
                        if (i + 3 >= tokens.size()) {
                            LogFatal("Not enough tokens to process if operation");
                        }
                        Token if_operation = tokens[i + 1];
                        Token value        = tokens[i + 2];
                        Token 

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

                case Less:
                    break;
                case Bigger:
                    break;
                case Equals:
                    break;
                case NotEquals:
                    break;
                case Label:
                    break;
                case GoTo:
                    break;
                case Variable:
                    break;
                case Function:
                    break;
                case Integer:
                    break;
                case String:
                    break;

                case Semicolon:
                    output += ";";
                    break;

                case OpenParenthesis:
                    break;
                case CloseParenthesis:
                    break;
            }
        }

        return "";
    }

};

#endif
