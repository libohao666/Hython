#include <ExprTreeEvaluator.h>
#include <iostream>

ExprTreeEvaluator::ExprTreeEvaluator() : next(NULL){}

ExprTreeEvaluator::ExprTreeEvaluator(ExprTreeEvaluator *next) : next(next) {}

void ExprTreeEvaluator::def_param(std::string name, int val) {
    if (memory.find(name) != memory.end()) {
        throw std::runtime_error("!!![Error] param redefined : " + name);
    }
    memory[name] = val;
    return ;
}

void ExprTreeEvaluator::set_param(std::string name, int val) {
    if (memory.find(name) != memory.end()) {
        memory[name] = val;
        return ;
    }
    if (this->next) {
        this->next->set_param(name, val);
        return ;
    }
}

int ExprTreeEvaluator::get_param(std::string name) {
    if (this->memory.find(name) == this->memory.end() && !this->next) {
        throw std::runtime_error("!!![Error] param unknown : " + name);
    } 
    if (this->memory.find(name) != this->memory.end()) {
        return this->memory[name];
    }
    if (this->next) return this->next->get_param(name);
    return 0;
}

int ExprTreeEvaluator::run(haizei::ASTNode tree)
{
    if(tree.hasToken()) {
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
        case BLOCK: {
            ExprTreeEvaluator tmp(this);
            int r = 0;
            for(int i = 0; i < tree.size(); i++) {
                r = tmp.run(tree[i]);
            }
            return r;
        }
        case PRINT: {
            for(int i = 0; i < tree.size(); i++) {
                if (i) std::cout << " ";
                std::cout << run(tree[i]);
            }
            std::cout << std::endl;
            return 1;
        }
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
        case IF: {
            if (run(tree[0])) {
                run(tree[1]);
            } else if (tree.size() == 3) {
                run(tree[2]);
            }
            return 0;
        }
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
        default:
            std::cout << "Unhandled token: #" << tree.type() << std::endl;
            return -1;
        }
    }
    else {
        int r = 0;
        for(int i = 0; i < tree.size(); i++) {
            r = run(tree[i]);
        }
        return r;
    }
}