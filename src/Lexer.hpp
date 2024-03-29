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
    FunctionCall,
    Integer,
    String,
    Pointer,
    Load,
    Read,
    Write,
    Update,
    Throw,
    Array,

    Comma,
    Semicolon,

    Percent,

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
        bool is_string = false;
        std::string string_content = "";
        for(int i = 0; i < text.size(); i++)
        {
            if (text[i] == '|') {
                if (!is_string) {
                    is_string = true;
                }
                else if (is_string) {
                    is_string = false;
                    tokens.push_back({TokenKind::Symbols, "\"" + string_content + "\""});
                    string_content = "";
                }
            }
            else if (is_string) {
                string_content += text[i];
                continue;
            }
            else {
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
                    case '@':
                        tokens.push_back({TokenKind::FunctionCall, "@"});
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
                    case '%':
                        tokens.push_back({TokenKind::Percent, "%"});
                        break;
                    case 'G':
                        tokens.push_back({TokenKind::GoTo, "G"});
                        break;
                    case 'P':
                        tokens.push_back({TokenKind::Pointer, "P"});
                        break;
                    case 'L':
                        tokens.push_back({TokenKind::Load, "L"});
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
                    case 'M':
                        tokens.push_back({TokenKind::Array, "M"});
                        break;
                    case ',':
                        tokens.push_back({TokenKind::Comma, ","});
                        break;

                    default:
                        if (symbols_last_i == -1)
                        {
                            tokens.push_back({TokenKind::Symbols, ""});
                            symbols_tokens_ind = tokens.size() - 1;
                        }
                        else if (symbols_last_i != i - 1)
                        {
                            tokens[symbols_tokens_ind].text = symbols;
                            symbols = "";

                            tokens.push_back({TokenKind::Symbols, ""});
                            symbols_tokens_ind = tokens.size() - 1;
                        }
                        symbols += this->text[i];
                        symbols_last_i = i;
                        break;
                }
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
