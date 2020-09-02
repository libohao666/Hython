#include <memory>

namespace haizei {

class ASTree;
class Parameter;
class IValue;
class IntValue;
class FloatValue;
class StringValue;
class FunctionValue;
class ListValue;
class DFA;
class IDFANode;

using SIValue = std::shared_ptr<IValue>;
using SIntValue = std::shared_ptr<IntValue>;
using SFloatValue = std::shared_ptr<FloatValue>;
using SStringValue = std::shared_ptr<StringValue>;
using SFunctionValue = std::shared_ptr<FunctionValue>;
using SListValue = std::shared_ptr<ListValue>;
using SParameter = std::shared_ptr<Parameter>;

} // end of namespace haizei