#include <iostream>

#define MACRO_VAR_ARGS_IMPL_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_MACRO_VAR_ARGS(...) MACRO_VAR_ARGS_IMPL_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define MACRO_COMBINE_2(MACRO, ARGS_COUNT) MACRO##ARGS_COUNT
#define MACRO_COMBINE_1(MACRO, ARGS_COUNT) MACRO_COMBINE_2(MACRO, ARGS_COUNT)
#define MACRO_COMBINE(MACRO, ARGS_COUNT) MACRO_COMBINE_1(MACRO, ARGS_COUNT)

#define MACRO_LAUNCHER(MACRO, ...)                          \
    MACRO_COMBINE(MACRO, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
    (__VA_ARGS__)

#define MACRO_1(...) "hello, world."
#define MACRO_2(...) MACRO_1(__VA_ARGS__)
#define MACRO_3(...) MACRO_2(__VA_ARGS__)
#define MACRO_4(...) MACRO_3(__VA_ARGS__)
#define MACRO_5(...) MACRO_4(__VA_ARGS__)

int main(int argc, char const *argv[])
{
    auto str = MACRO_LAUNCHER(MACRO_, 123, "12", 123.f);
    std::cout << str << std::endl;
    return 0;
}
