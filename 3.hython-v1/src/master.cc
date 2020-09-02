#include <master.h>
#include <single.h>
#include <memory>
#include <iostream>

namespace haizei {

int ExprMaster::run(ASTNode &tree, std::shared_ptr<Parameter> &p) {
    #define BOP(op) MasterChainRun::run(tree[0], p) op MasterChainRun::run(tree[1], p)
    switch (tree.type()) {
        case INT: {
            std::string s = tree.text();
            if(s[0] == '-') {
                return -atoi(s.c_str() + 1);
            }
            else {
                return atoi(s.c_str());
            }
        }
        case ID: {
            return p->get_param(tree.text());
        }
        case PLUS: return BOP(+);
        case MINUS: return BOP(-);
        case TIMES: return BOP(*);
        case DIV: return BOP(/);
        case MOD: return BOP(%);
        case OR: return BOP(||);
        case AND: return BOP(&&);
        case GT: return BOP(>);
        case LITTLE: return BOP(<);
        case EQ: return BOP(==);
        case GE: return BOP(>=);
        case LE: return BOP(<=);
        case NE: return BOP(!=);
        case ASSIGN: {
            std::string var(tree[0].text());
            p->get_param(var);
            int val = MasterChainRun::run(tree[1], p);
            p->set_param(var, val);
            return val;
        }
    }
    #undef BOP
    throw std::runtime_error(typeid(*this).name() + "Unhandled token: #" + tree.type());
    return 0;
}

int ControlBlockMaster::run(ASTNode &node, std::shared_ptr<Parameter> &p) {
    // TODO
    switch (node.type()) {
        case BLOCK: {
            int r = 0;
            for(int i = 0; i < node.size(); i++) {
                r = MasterChainRun::run(node[0], p)
            }
            return r;
        }
        case FOR: {
            for (MasterChainRun::run(node[0], p); MasterChainRun::run(node[1], p); MasterChainRun::run(node[2], p)) MasterChainRun::run(node[3], p);
            return 0;
        }
    }
    throw std::runtime_error(typeid(*this).name() + "Unhandled token: #" + node.type());
    return 0;
}

int ControlNoBlockExprMaster::run(ASTNode &node, std::shared_ptr<Parameter> &p) {
    // TODO
    switch (node.type()) {
        case IF: {
            if (MasterChainRun::run(node[0], p)) {
                MasterChainRun::run(node[1], p);
            } else if (node.size() == 3) {
                MasterChainRun::run(node[2], p);
            }
            return 0;
        }
        case WHILE: {
            while (MasterChainRun::run(node[0], p)) MasterChainRun::run(node[1], p);
            return 0;
        }
        case DOWHILE: {
            do {
                MasterChainRun::run(node[1], p);
            } while(MasterChainRun::run(node[0], p));
            return 0;
        }
    }
    throw std::runtime_error(typeid(*this).name() + "Unhandled token: #" + tree.type());
    return 0;
}

int PrintMaster::run(ASTNode &node, std::shared_ptr<Parameter> &p) {
    // TODO
    switch (node.type()) {
        case PRINT: {
            for(int i = 0; i < node.size(); i++) {
                if (i) std::cout << " ";
                std::cout << MasterChainRun::run(node[i], p);
            }
            std::cout << std::endl;
            return 1;
        }
    }
    throw std::runtime_error(typeid(*this).name() + "Unhandled token: #" + tree.type());
    return 0;
}

}