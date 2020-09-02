namespace haizei {

class ASTNode;

class FactoryHandler{
public:
    static void init_factory(ASTNode*);
    static FactoryHandler *get();
    virtual bool is_valid(ASTNode*) = 0;
    virtual void do_factory(ASTNode*) = 0;
protected:
    static FactoryHandler *head;
    FactoryHandler *next;
private:

};

class PrintFactoryHandler : public FactoryHandler {
public:
    virtual bool is_valid(ASTNode*);
    virtual void do_factory(ASTNode*);
private:
    static PrintFactory *factory;
};

class ExprFactoryHandler : public FactoryHandler {
public:
    virtual bool is_valid(ASTNode*);
    virtual void do_factory(ASTNode*);
private:
    static ExprFactory *factory;
};

class BlockFactoryHandler : public FactoryHandler {
public:
    virtual bool is_valid(ASTNode*);
    virtual void do_factory(ASTNode*);
private:
    static BlockFactory *factory;
};

class CondFactoryHandler : public FactoryHandler {
public:
    virtual bool is_valid(ASTNode*);
    virtual void do_factory(ASTNode*);
private:
    static CondFactory *factory;
};

class CtrlFactoryHandler : public FactoryHandler {
public:
    virtual bool is_valid(ASTNode*);
    virtual void do_factory(ASTNode*);
private:
    static CtrlFactory *factory;
};

} // end of namespace haizei