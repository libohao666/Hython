namespace haizei {

class IMaster {
public :
    IMaster(ASTNode);
    class IFactory {
    public :
        virtual IMaster *create(ASTNode) = 0;
        virtual void destory(IMaster *);
    };
    virtual int run() = 0;
    virtual ~IMaster();

    haizei::ASTNode tree;
};

class PrintMaster : public IMaster {
public :
    PrintMaster(ASTNode);
    virtual int run();
};

class ExprMaster : public IMaster {
public :
    ExprMaster(ASTNode);
    virtual int run();
};

class CondMaster : public IMaster {
public :
    CondMaster(ASTNode);
    virtual int run();
};

class BlockMaster : public IMaster {
public :
    BlockMaster(ASTNode);
    virtual int run();
};

class CtrlMaster : public IMaster {
public :
    CtrlMaster(ASTNode);
    virtual int run();
};

}