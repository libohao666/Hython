#include <head.h>
#include <handler.h>
#include <factory.h>
#include <AST.h>

namespace haizei {

void FactoryHandler::init_factory(ASTNode *tree) {
    auto p = FactoryHandler::get();
    for (; p != nullptr; p = p->next) {
        if (!p->is_valid(tree)) continue;
        p->do_factory(tree);
        break;
    }
    if (p == nullptr) {
        throw std::runtime_error(std::string("[Error] : No handler with " + tree.type()));
    }
    for (int i = 0; i < tree->size(); i++) {
        FactoryHandler::init_factory(tree->operator[](i));
    }
    return ;
}

FactoryHandler* FactoryHandler::get() {
    if (head == nullptr) {
        head = new PrintFactoryHandler();
        head->next = new ExprFactoryHandler();
        head->next = new BlockFactoryHandler();
        head->next = new CondFactoryHandler();
        head->next = new CtrlFactoryHandler();
    }
    return head;
}

bool PrintFactoryHandler::is_valid(ASTNode tree) {
    switch (tree.type()) {
        case PRINT: return true;
        default : return false;
    }
    return false;
}

bool ExprFactoryHandler::is_valid(ASTNode tree) {
    switch (tree.type()) {
        case INT: return true;
        case ID: return true;
        case PLUS: return true;
        case MINUS: return true;
        case TIMES: return true;
        case DIV: return true;
        case MOD: return true;
        case ASSIGN: return true;
        case DEF: return true;
        default: return false;
    }
    return false;
}

bool BlockFactoryHandler::is_valid(ASTNode tree) {
    switch (tree.type()) {
        case BLOCK: return true;
        default : return false;
    }
    return false;
}

bool CondFactoryHandler::is_valid(ASTNode tree) {
    switch (tree.type()) {
        case OR: return true;
        case AND: return true;
        case GT : return true;
        case LITTLE: return true;
        case EQ: return true;
        case GE: return true;
        case LE: return true;
        case NE: return true;
        default: return false;
    }
    return false;
}

bool CtrlFactoryHandler::is_valid(ASTNode tree) {
    switch (tree.type()) {
        case IF: return true;
        case FOR: return true;
        case WHILE: return true;
        case DOWHILE: return true;
        default: return false;
    }
    return false;
}

BlockFactory *BlockFactoryHandler::factory = new BlockFactory();
ExprFactory *ExprFactoryHandler::factory = new ExprFactory();
PrintFactory *PrintFactoryHandler::factory = new PrintFactory();
CondFactory *CondFactoryHandler::factory = new CondFactory();
CtrlFactory *CtrlFactoryHandler::factory = new CtrlFactory();
FactoryHandler *FactoryHandler::head = nullptr;

} // end of namespace haizei