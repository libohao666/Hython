/*
* @Author: lbh
* @Date: 2020-08-27 13:39:39 
 * @Last Modified by: mikey.zhaopeng
 * @Last Modified time: 2020-08-27 14:05:14
*/
#include <head.h>
#include <hythonLexer.h>
#include <hythonParser.h>
#include <AST.h>
using std::map;
using std::string;
using std::cout;
using std::endl;
 
class ExprTreeEvaluator {
    map<string,int> memory;
    int block_cnt = 0;
public:
    ExprTreeEvaluator() : next(NULL){}
    ExprTreeEvaluator(ExprTreeEvaluator *next) : next(next) {}
    int run(haizei::ASTNode);
    void set_param(string name, int val);
    void def_param(string name, int val);
    int get_param(string name);
    ExprTreeEvaluator *next;
};

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);
const char* getText(pANTLR3_BASE_TREE tree);
 
int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode tree(argv[1]);

    ExprTreeEvaluator eval;
    int rr = eval.run(tree);
    cout << "Evaluator result: " << rr << '\n';

    tree.destroy();

    return 0;
}

void ExprTreeEvaluator::def_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
        throw std::runtime_error("!!![Error] param redefined : " + name);
    }
    memory[name] = val;
    return ;
}

void ExprTreeEvaluator::set_param(string name, int val) {
    if (memory.find(name) != memory.end()) {
        memory[name] = val;
        return ;
    }
    if (this->next) {
        this->next->set_param(name, val);
        return ;
    }
}

int ExprTreeEvaluator::get_param(string name) {
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
            string var(tree[0].text());
            get_param(var);
            int val = run(tree[1]);
            this->set_param(var, val);
            return 1;
        }
        case DEF: {
            int init_val = 0;
            for(int i = 0; i < tree.size(); i++) {
                string var(tree[i].text());
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

