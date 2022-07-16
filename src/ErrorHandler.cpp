#include "ErrorHandler.h"

#include <iostream>
using std::cout;

namespace boop {
auto ErrorHandler::report() const -> void {
  for (const auto error : error_list) {
    cout << "[line " + std::to_string(error.line) + "]Error " + error.where +
                ": " + error.message
         << '\n';
  }
}

auto ErrorHandler::add(int line, const string &where, const string &msg)
    -> void {
  error_list.push_back({line, where, msg});
  has_found_error = true;
}

auto ErrorHandler::clear() -> void { error_list.clear(); }
} // namespace boop