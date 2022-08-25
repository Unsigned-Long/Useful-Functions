#define FORMAT_VECTOR
#include "artwork/logger/logger.h"
#include <algorithm>

using Byte = unsigned char;
using ByteArray = std::vector<Byte>;

// cast for normal variable
template <typename Ty>
ByteArray cast(const Ty &val) {
  auto buffer = (Byte *)(&val);
  ByteArray bufferVec(sizeof(Ty));
  std::copy_n(buffer, sizeof(Ty), bufferVec.begin());
  return bufferVec;
}

// cast for variable array
template <typename Ty>
ByteArray cast(Ty *val) {
  int len = sizeof(val) / sizeof(Ty);
  ByteArray bufferVec(sizeof(val));
  for (int i = 0; i != len; ++i) {
    ByteArray buffer = cast(val[i]);
    std::copy_n(buffer.begin(), buffer.size(), bufferVec.begin() + i * sizeof(Ty));
  }
  return bufferVec;
}

template <typename Ty>
ByteArray cast(const Ty *val) {
  int len = sizeof(val) / sizeof(Ty);
  ByteArray bufferVec(sizeof(val));
  for (int i = 0; i != len; ++i) {
    ByteArray buffer = cast(val[i]);
    std::copy_n(buffer.begin(), buffer.size(), bufferVec.begin() + i * sizeof(Ty));
  }
  return bufferVec;
}

// cast for char array
ByteArray cast(const char *val, std::size_t len) {
  ByteArray bufferVec(len);
  for (int i = 0; i != len; ++i) {
    ByteArray buffer = cast(val[i]);
    std::copy_n(buffer.begin(), buffer.size(), bufferVec.begin() + i * sizeof(char));
  }
  return bufferVec;
}

// cast for std::string
ByteArray cast(const std::string &val) {
  return cast(val.c_str(), val.size());
}

// recovery for variable array
template <typename Ty>
std::vector<Ty> recovery(const ByteArray &buffer, std::size_t itemSize) {
  std::size_t typeSize = sizeof(Ty);
  Byte *bufferPtr = new Byte[typeSize];
  std::vector<Ty> result(itemSize);
  for (int i = 0; i != itemSize; ++i) {
    std::copy_n(buffer.cbegin() + i * typeSize, typeSize, bufferPtr);
    result[i] = *((Ty *)(bufferPtr));
  }
  delete[] bufferPtr;
  return result;
}

// recovery for variable
template <typename Ty>
Ty recovery(const ByteArray &buffer) {
  std::size_t typeSize = sizeof(Ty);
  Byte *bufferPtr = new Byte[typeSize];
  std::copy_n(buffer.cbegin(), typeSize, bufferPtr);
  Ty val = *((Ty *)(bufferPtr));
  delete[] bufferPtr;
  return val;
}

// recovery for std::string
template <>
std::string recovery(const ByteArray &buffer) {
  std::vector<char> str = recovery<char>(buffer, buffer.size());
  return std::string(str.cbegin(), str.cend());
}

int main(int argc, char **argv) {
  {
    std::string pi = "Hello, world!";
    auto buffer = cast(pi);
    LOG_VAR(recovery<std::string>(buffer));
  }

  {
    double e = 2.71;
    auto buffer = cast(e);
    LOG_VAR(recovery<double>(buffer));
  }

  {
    int ary[2] = {12, 45};
    auto buffer = cast(ary);
    LOG_VAR(recovery<int>(buffer, 2));
  }
  return 0;
}
