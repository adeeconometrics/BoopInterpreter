#ifndef __ERRORHANDLER_H__
#define __ERRORHANDLER_H__

#include <string>
#include <vector>

namespace boop {
  
struct ErrorHandler {
  ErrorHandler() = default;

  /**
   * @brief reports the error encountered.
   *
   */
  auto report() const -> void;

  /**
   * @brief add information about an error encountered which will be included in
   * the `error_list`
   *
   * @param line
   * @param msg
   */
  auto add(int line, const std::string &msg) -> void;

  /**
   * @brief clears the data of `error_list`
   *
   */
  auto clear() -> void;

  /**
   * @brief helper function that tells whether an error has occurred
   *
   */
  bool has_found_error{};

private:
  std::vector<std::string> error_list;
};

// auto debug_print(const std::string& str) -> void;

}

#endif // __ERRORHANDLER_H__