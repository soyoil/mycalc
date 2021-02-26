#include <string>

#include "evaluator.cpp"

int main(void) {
    std::string program;
    Lexer *lexer;
    Node *tree;
    long double result;

    while (std::getline(std::cin, program)) {
        if (std::cin.eof()) break;
        lexer = new Lexer(program);
        tree = Parser::parse(lexer->getQueue());
        result = Evaluator::evaluate(tree);
        std::cout << "Result: " << std::fixed << result << std::endl;
        delete lexer;
    }
    return 0;
}
