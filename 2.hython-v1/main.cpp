#include <head.h>
#include <ExprTreeEvaluator.h>
 
int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode tree(argv[1]);

    ExprTreeEvaluator eval;
    int rr = eval.run(tree);
    std::cout << "Evaluator result: " << rr << '\n';

    tree.destroy();
    return 0;
}



