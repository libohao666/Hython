#include <head.h>
#include <ExprTreeEvaluator.h>
#include <AST.h>
#include <runtimeenv.h>

int main(int argc, char* argv[]) {
    assert(argc > 1);
    haizei::ASTNode *tree = new haizei::ASTNode(argv[1]);
    haizei::RunTimeEnv env(tree);
    env.run();
    return 0;
}



