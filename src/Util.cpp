#include <Util.hpp>

#include <iostream>
#include <fstream>

#include <string>

std::string Util::LoadAsString (const char* path)
{
  std::ifstream file;
  file.open(path, std::ios::in);

  if (!file.is_open()) {
    return std::string("");
  }

  std::string content("");
  std::string line;

  while (std::getline(file, line)) {
    content += line + '\n';
  }

  file.close();

  return content;
}
