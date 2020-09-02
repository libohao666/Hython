#include <head.h>
#include <master.h>
#include <AST.h>
#include <ExprTreeEvaluator.h>

namespace haizei {

IMaster::IMaster(ASTNode tree) : tree(tree) {}
IMaster::~IMaster() {}

PrintMaster::PrintMaster(ASTNode tree) : IMaster(tree) {}
ExprMaster::ExprMaster(ASTNode tree) : IMaster(tree) {}
BlockMaster::BlockMaster(ASTNode tree) : IMaster(tree) {}
CondMaster::CondMaster(ASTNode tree) : IMaster(tree) {}
CtrlMaster::CtrlMaster(ASTNode tree) : IMaster(tree) {}


void IMaster::IFactory::destory(IMaster *master) {
    delete master;    
}

int PrintMaster::run() {
    if (tree.type() != PRINT) {
        throw std::runtime_error("tree type is not PRINT!");
    }
    for(int i = 0; i < tree.size(); i++) {
        if (i) std::cout << " ";
        std::cout << run(tree[i]);
    }
    std::cout << std::endl;
    return 1;
}

int ExprMaster::run() {
    switch(tree.type()) {
        case INT: {
            std::string s = tree.text();
            if(s[0] == '~') {
                return -atoi(s.c_str() + 1);
            }
            else {
                return atoi(s.c_str());
            }
        }
        case ID: {
            return this->get_param(tree.text());
        }
        case PLUS:
            return run(tree[0]) + run(tree[1]);
        case MINUS:
            return run(tree[0]) - run(tree[1]);
        case TIMES:
            return run(tree[0]) * run(tree[1]);
        case DIV:
            return run(tree[0]) / run(tree[1]);
        case MOD:
            return run(tree[0]) % run(tree[1]);
        case ASSIGN: {
            std::string var(tree[0].text());
            get_param(var);
            int val = run(tree[1]);
            this->set_param(var, val);
            return 1;
        }
        case DEF: {
            int init_val = 0;
            for(int i = 0; i < tree.size(); i++) {
                std::string var(tree[i].text());
                if (tree[i].size() == 1) {
                    init_val = run(tree[i][0]);
                }
                this->def_param(var, init_val);
            }
            return init_val;
        }
        default : {
            throw std::runtime_error("tree type is not EXPR!");
        }
    }
}

int BlockMaster::run() {
    if (tree.type() != BLOCK) {
        throw std::runtime_error("tree type is not BLOCK!");
    }
    ExprTreeEvaluator tmp(this);
    int r = 0;
    for(int i = 0; i < tree.size(); i++) {
        r = tmp.run(tree[i]);
    }
    return r;
}

int CondMaster::run() {
    switch (tree.type()) {
        case OR: {
            return run(tree[0]) || run(tree[1]);
        }
        case AND:{
            return run(tree[0]) && run(tree[1]);
        }
        case GT :{
            return run(tree[0]) > run(tree[1]);
        }
        case LITTLE: {
            return run(tree[0]) < run(tree[1]);
        }
        case EQ: {
            return run(tree[0]) == run(tree[1]);
        }
        case GE: {
            return run(tree[0]) >= run(tree[1]);
        }
        case LE: {
            return run(tree[0]) <= run(tree[1]);
        }
        case NE: {
            return run(tree[0]) != run(tree[1]);
        }
        default : {
            throw std::runtime_error("tree type is not COND!");
        }
    }
}

int CtrlMaster::run() {
    switch (tree.type()) {
        case FOR: {
            ExprTreeEvaluator tmp(this);
            for (tmp.run(tree[0]); tmp.run(tree[1]); tmp.run(tree[2])) tmp.run(tree[3]);
            return 0;
        }
        case WHILE: {
            ExprTreeEvaluator tmp(this);
            while (tmp.run(tree[0])) tmp.run(tree[1]);
            return 0;
        }
        case DOWHILE: {
            ExprTreeEvaluator tmp(this);
            do {
                tmp.run(tree[1]);
            } while(tmp.run(tree[0]));
            return 0;
        }
        default : {
            throw std::runtime_error("tree type is not CTRL!");
        }
    }
}

} // end of namespace haizei