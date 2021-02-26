#include "lexer.cpp"

class Node {
   public:
    Node(std::string tokenValue, TokenTypes tType)
        : tokenType(tType), value(tokenValue) {}

    virtual std::string toString() const { return value; }
    const TokenTypes tokenType;
    const std::string value;
};

class UnitaryNode : Node {
   public:
    UnitaryNode(std::string tokenValue, TokenTypes tType, const Node *child)
        : Node(tokenValue, tType), child(child) {}

    std::string toString() const override {
        return "(" + value + child->toString() + ")";
    }

   private:
    const Node *child;
};

class BinaryNode : public Node {
   public:
    BinaryNode(std::string tokenValue, TokenTypes tType, const Node *left, const Node *right)
        : Node(tokenValue, tType), left(left), right(right) {}

    std::string toString() const override {
        return "(" + left->toString() + value + right->toString() + ")";
    }
    const Node *left;
    const Node *right;
};

class Parser {
   public:
    static Node *parse(std::deque<Token *> *queue) { return expr(queue); }

   private:
    // <expr>::=<term><op2><term> | <term>
    static Node *expr(std::deque<Token *> *queue) {
        Node *ret = term(queue);
        if (queue->empty()) return ret;

        BinaryNode *op2 = (BinaryNode *)ret;
        while (!queue->empty() && queue->front()->getTokenType() == TokenTypes::OP2) {
            Token *tk = queue->front();
            queue->pop_front();
            Node *term2 = term(queue);
            op2 = new BinaryNode(tk->getValue(), tk->getTokenType(), op2, term2);
        }
        return op2;
    }

    // <term>::=<factor><op1><factor> | <factor>
    static Node *term(std::deque<Token *> *queue) {
        Node *ret = factor(queue);
        if (queue->empty()) return ret;

        BinaryNode *op1 = (BinaryNode *)ret;
        while (!queue->empty() && queue->front()->getTokenType() == TokenTypes::OP1) {
            Token *tk = queue->front();
            queue->pop_front();
            Node *factor2 = factor(queue);
            op1 = new BinaryNode(tk->getValue(), tk->getTokenType(), op1, factor2);
        }
        return op1;
    }

    // <factor>::=<numeral> | “(" <expr> “)"
    static Node *factor(std::deque<Token *> *queue) {
        if (!queue->empty()) {
            Token *tk = queue->front();
            TokenTypes tp = tk->getTokenType();
            if (tp == TokenTypes::INTEGER || tp == TokenTypes::DOUBLE) {
                Node *numeral = new Node(tk->getValue(), tp);
                queue->pop_front();
                return numeral;
            } else if (tp == TokenTypes::LPAR) {
                queue->pop_front();
                Node *expression = expr(queue);
                queue->pop_front();
                return expression;
            }
        }
        return nullptr;
    }
};
