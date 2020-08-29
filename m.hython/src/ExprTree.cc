#include <head.h>
#include <ExprTree.h>
using std::cout;
using std::endl;

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
        case FLOAT: {
            
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
                cout << "var : " << var << " = " << init_val << endl;
                this->def_param(var, init_val);
            }
            return init_val;
        }
        case BLOCK: {
            ExprTreeEvaluator tmp(this);
            int r = 0;
            for(int i = 0; i < tree.size(); i++) {
                r = tmp.run(tree[i]);
                //cout << "Block value : " << r << endl;
            }
            return r;
        }
        case PRINT: {
            int r = 0;
            for(int i = 0; i < tree.size(); i++) {
                r = run(tree[i]);
                cout << r;
            }
            cout << endl;
            return 1;
        }
        case EQ: {
            return 999;
        }
        default:
            cout << "Unhandled token: #" << tree.type() << '\n';
            return -1;
        }
    }
    else {
        int r = 0;
        for(int i = 0; i < tree.size(); i++) {
            r = run(tree[i]);
            cout << "lbh result----" << r << endl;
        }
        return r;
    }
}

