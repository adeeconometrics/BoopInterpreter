#include "ErrorHandler.h"

#include <iostream>
#include <string>

namespace boop {

auto ErrorHandler::report() const -> void {
  for (const auto error : error_list) {
    std::cout << "[line " + std::to_string(error.line) + "]Error " +
                     error.where + ": " + error.message
              << '\n';
  }
}

auto ErrorHandler::add(int line, const std::string &msg) -> void {
  error_list.emplace_back("[Line " + std::to_string(line) + "] Error: " + msg);
  has_found_error = true;
}

auto ErrorHandler::clear() -> void { error_list.clear(); }

} // namespace boop