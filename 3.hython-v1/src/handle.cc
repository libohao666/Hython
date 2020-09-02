#include <handle.h>

namespace haizei {

IHandle::IHandle(IHandle *next) : __next(next) {}
IHandle* IHandle::next() {
    return __next;
}

ExprHandle::ExprHandle(IHandle *next) : IHandle(next) {}

ControlBlockHandle::ControlBlockHandle(IHandle *next) : IHandle(next) {}

ControlNoBlockHandle::ControlNoBlockHandle(IHandle *next) : IHandle(next) {}

PrintHandle::PrintHandle(IHandle *next) : IHandle(next) {}

bool ExprHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case INT:
        case ID:
        case PLUS:
        case MINUS:
        case TIMES:
        case DIV:
        case MOD:
        case ASSIGN:
        case OR:
        case AND:
        case GT :
        case LITTLE:
        case EQ:
        case GE:
        case LE:
        case NE:
            return true;
    }
    return false;
}

bool ControlBlockHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case BLOCK:
        case FOR:
            return true;
    }
    return false;
}

bool ControlNoBlockHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case IF:
        case WHILE:
        case DOWHILE:
            return true;
    }
    return false;
}

bool PrintHandle::Test(const ASTNode &n) const {
    switch (n.type()) {
        case PRINT:
            return true;
    }
    return false;
}

} // end of namespace haizei