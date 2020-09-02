#include <hythonLexer.h>
#include <hythonParser.h>
#include <AST.h>
#include <string>
#include <map>

class ExprTreeEvaluator {
public:
    ExprTreeEvaluator();
    ExprTreeEvaluator(ExprTreeEvaluator *next);
    int run(haizei::ASTNode);
    void set_param(std::string name, int val);
    void def_param(std::string name, int val);
    int get_param(std::string name);
    ExprTreeEvaluator *next;
private:
    std::map<std::string,int> memory;
    int block_cnt = 0;
};