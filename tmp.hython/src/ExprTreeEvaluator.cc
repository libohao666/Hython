#include <head.h>
#include <ExprTreeEvaluator.h>
#include <master.h>
#include <AST.h>

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
        haizei::IMaster *m = tree.factory->create(tree);
        int ret = m->run();
        tree.factory->destroy(tree);
        return ret;
    }
    else {
        int r = 0;
        for(int i = 0; i < tree.size(); i++) {
            r = run(tree[i]);
        }
        return r;
    }
}