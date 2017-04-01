#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <bitset>
#include "base64/base64_functions.h"

namespace cuhksz {
static const std::string codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

std::string base64Encode(std::string str, int length) {
  if (length < -1) {
    return "";
  }
  std::ostringstream encoded;
  std::string binaryStr = "";
  for (char &c: str) {
    binaryStr += std::bitset<8>(c).to_string();
  }
  if (binaryStr.length() % 6) {
    binaryStr += std::string(6 - binaryStr.length() % 6, '0');
  }
  auto size = binaryStr.length();
  for (int i = 0; i < size; i += 6) {
    int index = (int) std::bitset<8>(binaryStr.substr((unsigned long) i, 6)).to_ulong();

    encoded << codes[index];
  }
  std::string encodedStr = encoded.str();
  if (length != -1) {
    if (length < encodedStr.length()) {
      return (std::string) "";
    }
    encodedStr += std::string(length - encodedStr.length(), '=');
  } else {
    unsigned long remainder = encodedStr.length() % 4;
    switch (remainder) {
      case 0:
        break;
      case 2:
        encodedStr += "==";
        break;
      case 3:
        encodedStr += "=";
        break;
    }

  }
  return encodedStr;
};
}