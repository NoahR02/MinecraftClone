#include "ReadFile.h"
#include <fstream>

std::string readFile(const std::string& path) {
  std::ifstream file {path, std::ios::in | std::ios::binary};
  if(file) return std::string(std::istreambuf_iterator<char>(file), {});
  return "";
}