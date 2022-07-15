#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

#include "ErrorHandler.h"
#include "FileReader.h"
#include "Scanner.h"
#include "Token.h"

using boop;

auto run(std::string_view source) {
  ErrorHandler error_handler{};
  Scanner scanner{source, error_handler};
  vector<Token> tokens = scanner.scan_and_get_tokens();

  for (const auto i : tokens) {
    cout << i.to_string() << '\n';
  }
}

auto run_file(std::string_view c_str) -> void {
  FileReader fr{c_str};
  run(fr.content());
}

auto run_prompt() -> void {}

int main(int argc, char **argv) {
  // if(argc > 1)
  //     exit(1);
  // else if (argc == 1) {
  //     run_file(argv[1]);
  // } else {
  //     run_prompt();
  // }

  run_file("Sample.txt");
}