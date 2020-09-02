namespace haizei {

class ASTNode;

class RunTimeEnv {
public:
    RunTimeEnv(ASTNode *tree);
    void run();
private:
    ASTNode *tree;
};

} // end of namespace haizei