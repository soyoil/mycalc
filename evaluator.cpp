#include "parser.cpp"

namespace Evaluator {
    long double evaluate(const Node *tree) {
        switch (tree->tokenType) {
            case TokenTypes::INTEGER:
                return std::stoi(tree->value);
            case TokenTypes::DOUBLE:
                return std::stold(tree->value);
            case TokenTypes::OP1:
                if (tree->value == "*") {
                    return evaluate(((BinaryNode *)tree)->left) *
                        evaluate(((BinaryNode *)tree)->right);
                } else if (tree->value == "/") {
                    return evaluate(((BinaryNode *)tree)->left) /
                        evaluate(((BinaryNode *)tree)->right);
                }
            case TokenTypes::OP2:
                if (tree->value == "+") {
                    return evaluate(((BinaryNode *)tree)->left) +
                        evaluate(((BinaryNode *)tree)->right);
                } else if (tree->value == "-") {
                    return evaluate(((BinaryNode *)tree)->left) -
                        evaluate(((BinaryNode *)tree)->right);
                }
            default:
                return 0;
        }
    }
}
