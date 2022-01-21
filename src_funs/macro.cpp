#include <iostream>

#pragma region macro

#define MAIN(argc, argv) \
    int main(int argc, char *argv[])

#define FUNCTION(reType, name, ...) \
    reType name(__VA_ARGS__)

#define FUNCTION_CALL(name, ...) \
    name(__VA_ARGS__)

#define TEMPLATE(...) \
    template <__VA_ARGS__>

#define RETURN(param) return param

template <typename Ostream>
Ostream &__ostream__helper(Ostream &os)
{
    return os;
}
template <typename Ostream, typename ArgvType>
Ostream &__ostream__helper(Ostream &os, const ArgvType &argv)
{
    os << argv;
    return os;
}
template <typename Ostream, typename ArgvType, typename... ElseArgvs>
Ostream &__ostream__helper(Ostream &os, const ArgvType &argv, const ElseArgvs &...argvs)
{
    os << argv;
    return __ostream__helper(os, argvs...);
}

#define COUT(...) \
    __ostream__helper(std::cout, __VA_ARGS__);

#define COUT_WITH_ENDL(...) \
    COUT(__VA_ARGS__)       \
    COUT('\n')

#define FOUT(ofs, ...) \
    __ostream__helper(ofs, __VA_ARGS__);

#define FOUT_WITH_ENDL(ofs, ...) \
    FOUT(ofs, __VA_ARGS__)       \
    FOUT('\n')

#define NAMESPACE(name) \
    namespace name

#define THIS(member) \
    this->member

#define CLASS(name) \
    class name

#define STRUCT(name) \
    struct name

#define ENUM(name) \
    enum class name

#define PUBLIC() public:
#define PROTECTED() protected:
#define PRIVATE() private:

#define VA_DECLARE(type, name) \
    type name
#define VA_DEFINE(type, name, ...) \
    type name = ARGV_LIST(__VA_ARGS__)
#define ARGV_LIST(...) \
    {                  \
        __VA_ARGS__    \
    }

#define FOR_LOOP(initExp, conditionExp, loopExp) \
    for (initExp; conditionExp; loopExp)

#define WHILE_LOOP(conditionExp) \
    while (conditionExp)

#define BREAK() break
#define CONTINUE() continue

#define IF(conditionExp) \
    if (conditionExp)
#define IF_NOT(conditionExp) \
    if (!(conditionExp))
#define ELSE_IF(conditionExp) \
    else if (conditionExp)
#define ELSE() else

#define TRY() try
#define CATCH(exp) catch (exp)

#define CONST() const

#pragma endregion

#pragma region test

STRUCT(Info)
{
    PRIVATE()
    VA_DECLARE(float, _id);
    VA_DECLARE(std::string, _str);

    PUBLIC()
    Info(VA_DECLARE(float, id), VA_DECLARE(const std::string &, str))
        : _id(id), _str(str) {}

    FUNCTION(void, print)
    {
        IF_NOT(THIS(_str).empty())
        {
            COUT_WITH_ENDL(THIS(_id), THIS(_str));
            THIS(_str).clear();
        }
        ELSE()
        {
            COUT_WITH_ENDL("NO INFO");
        }
        RETURN();
    }
};

MAIN(argc, argv)
{
    VA_DEFINE(Info, i, 12, "Hello, world.");
    FUNCTION_CALL(i.print);
    FUNCTION_CALL(i.print);
    RETURN(0);
}
#pragma endregion