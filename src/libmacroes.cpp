#include <exception>
#include <iostream>

// the current function name
#define MC_FUNCTION_DESC __PRETTY_FUNCTION__

// the library name
#define MC_LIB_NAME "libmacro"

// the prefix used when print variables
#define MC_PREFIX "-- "

// the suffix used when print variables
#define MC_SUFFIX ""

// throw some information about current error [detail version]
#define MC_THROW_M(what)                                                   \
  throw std::runtime_error(                                                \
      std::string("[ ERROR | '") + MC_LIB_NAME + "':'" +                   \
      std::string(__FILE__).substr(std::string(__FILE__).rfind('/') + 1) + \
      "':'" + std::to_string(__LINE__) + "':'" + MC_FUNCTION_DESC +        \
      "' ] " + what);

// throw some information about current error [simple version]
#define MC_THROW(what)                                   \
  throw std::runtime_error(                              \
      std::string("[ ERROR | '") + MC_LIB_NAME + "':'" + \
      MC_FUNCTION_DESC +                                 \
      "' ] " + what);

// a macro launcher
#define MACRO_VAR_ARGS_IMPL_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_MACRO_VAR_ARGS(...) MACRO_VAR_ARGS_IMPL_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define MACRO_COMBINE_2(MACRO, ARGS_COUNT) MACRO##ARGS_COUNT
#define MACRO_COMBINE_1(MACRO, ARGS_COUNT) MACRO_COMBINE_2(MACRO, ARGS_COUNT)
#define MACRO_COMBINE(MACRO, ARGS_COUNT) MACRO_COMBINE_1(MACRO, ARGS_COUNT)

#define MACRO_LAUNCHER(MACRO, ...)                        \
  MACRO_COMBINE(MACRO, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
  (__VA_ARGS__)

// a helper
#define _MC_VAR_PACK_(var) \
#var << ": " << var << ", "

#define _MC_VAR_1(var) #var << ": " << var
#define _MC_VAR_2(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_1(__VA_ARGS__)
#define _MC_VAR_3(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_2(__VA_ARGS__)
#define _MC_VAR_4(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_3(__VA_ARGS__)
#define _MC_VAR_5(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_4(__VA_ARGS__)
#define _MC_VAR_6(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_5(__VA_ARGS__)
#define _MC_VAR_7(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_6(__VA_ARGS__)
#define _MC_VAR_8(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_7(__VA_ARGS__)
#define _MC_VAR_9(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_8(__VA_ARGS__)
#define _MC_VAR_10(var, ...) _MC_VAR_PACK_(var) << _MC_VAR_9(__VA_ARGS__)

// print variables for debug or something else
#define MC_VAR(...)                                               \
  std::cout << MC_PREFIX << MACRO_LAUNCHER(_MC_VAR_, __VA_ARGS__) \
            << MC_SUFFIX << std::endl;

int main(int argc, char const *argv[]) {
  try {
    const float pi = 3.14f;
    const int count = 10;
    const std::string author{"shlchen"};
    const std::string email{"3079625093@qq.com"};

    MC_VAR(pi, count);
    MC_VAR(author, email);

    MC_THROW("this is an exception with \"simple output\"");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    try {
      MC_THROW_M("this is an exception with \"detail output\"");
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }

  return 0;
}
