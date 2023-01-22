#ifndef LEXER_HPP
#define LEXER_HPP

#include <cassert>
#include <vector>

#include "Utils.hpp"

#define INT32_MAX 2147483647

enum TokenKind
{
    Symbols,
    Plus,
    Minus,
    Multiplication,
    Division,
    Remainder,
    Tilda,
    Less,
    Bigger,
    Equals,
    NotEquals,
    Label,
    GoTo,
    Variable,
    Function,
    Integer,
    String,
    Read,
    Write,
    Update,
    Throw,

    Comma,
    Semicolon,

    OpenParenthesis,
    CloseParenthesis,
    //OpenArrow, // Less
    //CloseArrow, // Bigger
    
    TOKENS_START,
    TOKENS_END

};

struct Token
{
    TokenKind kind;
    std::string text;
};


class Lexer
{
private:
    std::string text = "";

public:
    Lexer(std::string text)
    {
        assert(text.size() <= INT32_MAX);
        this->text = text;
    }

    std::vector<Token> Parse()
    {
        std::vector<Token> tokens;
        tokens.push_back({TokenKind::TOKENS_START, "<TOKENS_START>"});
        std::string symbols = "";
        int symbols_tokens_ind  = -1;
        int symbols_last_i  = -1;
        for(int i = 0; i < text.size(); i++)
        {
            switch(this->text[i])
            {
                case ' ':
                case '\n':
                case '\r':
                    break;

                case 'A':
                    tokens.push_back({TokenKind::Plus, "A"});
                    break;
                case 'B':
                    tokens.push_back({TokenKind::Minus, "B"});
                    break;
                case 'C':
                    tokens.push_back({TokenKind::Multiplication, "C"});
                    break;
                case 'D':
                    tokens.push_back({TokenKind::Division, "D"});
                    break;
                case 'E':
                    tokens.push_back({TokenKind::Remainder, "E"});
                    break;
                case 'V':
                    tokens.push_back({TokenKind::Variable, "V"});
                    break;
                case 'F':
                    tokens.push_back({TokenKind::Function, "F"});
                    break;
                case '~':
                    tokens.push_back({TokenKind::Tilda, "~"});
                    break;
                case '<':
                    tokens.push_back({TokenKind::Less, "<"});
                    break;
                case '>':
                    tokens.push_back({TokenKind::Bigger, ">"});
                    break;
                case '=':
                    tokens.push_back({TokenKind::Equals, "="});
                    break;
                case '!':
                    tokens.push_back({TokenKind::NotEquals, "!"});
                    break;
                case ':':
                    tokens.push_back({TokenKind::Label, ":"});
                    break;
                case ';':
                    tokens.push_back({TokenKind::Semicolon, ";"});
                    break;
                case 'G':
                    tokens.push_back({TokenKind::GoTo, "G"});
                    break;
                case 'I':
                    tokens.push_back({TokenKind::Integer, "I"});
                    break;
                case 'S':
                    tokens.push_back({TokenKind::String, "S"});
                    break;
                case '(':
                    tokens.push_back({TokenKind::OpenParenthesis, "("});
                    break;
                case ')':
                    tokens.push_back({TokenKind::CloseParenthesis, ")"});
                    break;
                case 'R':
                    tokens.push_back({TokenKind::Read, "R"});
                    break;
                case 'W':
                    tokens.push_back({TokenKind::Write, "W"});
                    break;
                case 'U':
                    tokens.push_back({TokenKind::Update, "U"});
                    break;
                case 'T':
                    tokens.push_back({TokenKind::Throw, "T"});
                    break;
                case ',':
                    tokens.push_back({TokenKind::Comma, ","});
                    break;

                default:
                    //char cur = text[i];
                    //std::cout << "CUR '" << cur << "'\n";

                    if (symbols_last_i == -1)
                    {
                        tokens.push_back({TokenKind::Symbols, ""});
                        symbols_tokens_ind = tokens.size() - 1;
                    }
                    //else if (symbols_last_i != i - 1 || cur == ' ' || cur == '\n' || cur == '\r')
                    else if (symbols_last_i != i - 1)
                    {
                        tokens[symbols_tokens_ind].text = symbols;
                        symbols = "";

                        tokens.push_back({TokenKind::Symbols, ""});
                        symbols_tokens_ind = tokens.size() - 1;
                    }
                    symbols += this->text[i];
                    symbols_last_i = i;
                    /*
                    std::string msg = "Unexpected symbol: '"; 
                                msg += this->text[i];
                                msg += "'";
                    LogWarning(msg);
                    */

                    break;
            }

        }

        if (symbols != "")
        {
            tokens[symbols_tokens_ind].text = symbols;
        }

        tokens.push_back({TokenKind::TOKENS_END, "<TOKENS_END>"});
        return tokens;
    }


};


#endif
