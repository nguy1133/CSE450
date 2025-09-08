// -- Some header files that are likely to be useful --
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// @Instructor note: Uncomment the line below once you have setup your lexer!
// #include "lexer.hpp"

// @Instructor note: You may want to build a StringStack class to manage the translation process.

int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cout << "Format: " << argv[0] << " [filename]" << std::endl;
    exit(1);
  }

  const std::string filename = argv[1];

  std::cout << "Replace me with a StringStack interpreter!!" << std::endl;
}
