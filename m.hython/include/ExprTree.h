#include <AST.h>
class ExprTreeEvaluator {
    std::map<std::string,int> memory;
    int block_cnt = 0;
public:
    ExprTreeEvaluator() : next(NULL){}
    ExprTreeEvaluator(ExprTreeEvaluator *next) : next(next) {}
    int run(haizei::ASTNode);
    void set_param(std::string name, int val);
    void def_param(std::string name, int val);
    int get_param(std::string name);
    ExprTreeEvaluator *next;
};