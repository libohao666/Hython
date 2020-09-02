#include <handle.h>
#include <mutex>

namespace haizei {

class Singleton {
public :
protected:
    Singleton() = default;
    static std::mutex m_mutex;
};

class MasterChainSingle : public Singleton {
public :
    static int run(ASTNode &, std::shared_ptr<Parameter> &);
private:
    static const IHandle *get();
    MasterChainSingle() = delete;
    static const IHandle *SingleInit();
    static const IHandle *object;
};

}