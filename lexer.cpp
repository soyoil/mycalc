#include <deque>
#include <iostream>

enum TokenTypes {
    INTEGER,
    DOUBLE,
    LPAR,
    RPAR,
    EXPR,
    TERM
};

class Token {
   public:
    Token(std::string source, TokenTypes tType) : value(source), tokenType(tType) {}

    std::string toString() const {
        std::string str;
        switch (tokenType) {
            case TokenTypes::INTEGER:
                str = "INTEGER";
                break;
            case TokenTypes::DOUBLE:
                str = "DOUBLE";
                break;
            case TokenTypes::LPAR:
                str = "LPAR";
                break;
            case TokenTypes::RPAR:
                str = "RPAR";
                break;
            case TokenTypes::EXPR:
                str = "EXPR";
                break;
            case TokenTypes::TERM:
                str = "TERM";
                break;
            default:
                break;
        }
        return value + ": " + str;
    }

   private:
    const std::string value;
    const TokenTypes tokenType;
};

class Lexer {
   public:
    Lexer(std::string program) {
        tokenQueue = new std::deque<Token *>();
        std::string str = "";
        for (int i = 0; i < program.length(); i++) {
            if ('0' <= program[i] && program[i] <= '9') {
                while ('0' <= program[i] && program[i] <= '9') {
                    str += program[i++];
                }
                if (program[i] == '.') {
                    str += program[i];
                    i++;
                    while ('0' <= program[i] && program[i] <= '9') {
                        str += program[i++];
                    }
                    tokenQueue->push_back(new Token(str, TokenTypes::DOUBLE));
                } else {
                    tokenQueue->push_back(new Token(str, TokenTypes::INTEGER));
                }
                str = "";
                i--;
                continue;
            }
            switch (program[i]) {
                case '+':
                    tokenQueue->push_back(new Token("+", TokenTypes::EXPR));
                    break;
                case '-':
                    tokenQueue->push_back(new Token("-", TokenTypes::EXPR));
                    break;
                case '*':
                    tokenQueue->push_back(new Token("*", TokenTypes::TERM));
                    break;
                case '/':
                    tokenQueue->push_back(new Token("/", TokenTypes::TERM));
                    break;
                case '(':
                    tokenQueue->push_back(new Token("(", TokenTypes::LPAR));
                    break;
                case ')':
                    tokenQueue->push_back(new Token(")", TokenTypes::RPAR));
                    break;
                case ' ':
                    break;
                default:
                    std::cerr << "Unexpected token: " << program[i] << std::endl;
                    break;
            }
        }
    }

    std::deque<Token *> *getQueue() {
        return tokenQueue;
    }

    std::string toString() const {
        std::string str = "";
        for (Token *token : *tokenQueue) {
            str += token->toString() + "\n";
        }
        return str;
    }

   private:
    std::deque<Token *> *tokenQueue;
};
