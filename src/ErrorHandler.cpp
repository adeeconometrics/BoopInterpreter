#include "ErrorHandler.h"

#include <iostream>
#include <string>

namespace boop {

auto ErrorHandler::report() const -> void {
  for (const auto& error : error_list) {
    std::cerr << error << '\n';
  }
}

auto ErrorHandler::add(int line, const std::string &msg) -> void {
  error_list.emplace_back("[Line " + std::to_string(line) + "] Error: " + msg);
  has_found_error = true;
}

auto ErrorHandler::clear() -> void { error_list.clear(); }

auto report_runtime_error(ErrorHandler &reporter, const Token &token,
                          const std::string &msg) -> RuntimeError {
  reporter.add(token.get_line(), token.get_lexeme() + ": " + msg);
  return RuntimeError();
}

} // namespace boop