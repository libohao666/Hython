#include <single.h>
#include <memory>

namespace haizei {

int MasterChainSingle::run(ASTNode &node, std::shared_ptr<Parameter> &p) {
    const IHandle *h = get();
    int ret = 0;
    while (h != nullptr) {
        if (!(h->Test(node))) {
            h = h->next();
            continue; 
        }
        // 执行对应的 master 的 run 方法
        break;
    }
    return ret;
}

const IHandle *MasterChainSingle::get() {
    if (object == nullptr) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (object == nullptr) {
            object = SingleInit();
        }
    }
    return object;
}

const IHandle *MasterChainSingle::SingleInit() {
    PrintHandle *node4 = new PrintHandle(nullptr);
    ControlNoBlockHandle  *node3 = new ControlNoBlockHandle(node4);
    ControlBlockHandle *node2 = new ControlBlockHandle(node3);
    ExprHandle *node1 = new ExprHandle(node2);
    return node1;
}

} // end of namespace haizei