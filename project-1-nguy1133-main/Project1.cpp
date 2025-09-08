// -- Some header files that are likely to be useful --
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// @Instructor note: Uncomment the line below once you have setup your lexer!
#include "lexer.hpp"

// @Instructor note: You may want to build a StringStack class to manage the translation process.
using emplex::Lexer;
using emplex::Token;

class StringStack {
private:
  std::string filename;
  Lexer lexer;

  void ProcessPrint() {
    lexer.Use(Lexer::ID_PRINT, "Internal Compiler Error!");
    Token token = lexer.Use();
    if (token == Lexer::ID_STRING) {
      std::cout << "string found" << std::endl;
      std::cout << token << std::endl;
    }
    else {
      std::cerr << "Unexpected token '" << token.lexeme << '\n';
    }
  }

  void ProcessLine() {
    auto token = lexer.Peek();
    switch (token) {
      case Lexer::ID_PRINT: 
        std::cout << "Going to print string." << std::endl;
        ProcessPrint(); 
        break;
      default: lexer.Error("Unknown token '", token.lexeme, "'.");
    }
  }

public:
  StringStack(std::string filename) : filename(filename) { }

  void Run() {
    std::ifstream fs(filename);
    lexer.Tokenize(fs);

    while (lexer.Any()) {
      std::cout << "Going to process line." << std::endl;
      ProcessLine();
    }
  }
};


int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cout << "Format: " << argv[0] << " [filename]" << std::endl;
    exit(1);
  }

  const std::string filename = argv[1];

  std::cout << "Replace me with a StringStack interpreter!!" << std::endl;
  StringStack lang(filename);
  lang.Run();
}
