#ifndef __ERRORHANDLER_H__
#define __ERRORHANDLER_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace boop {

class ErrorHandler {

public:
  struct ErrorInfo {
    int line{};
    string where;
    string message;
  };

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
   * @param where
   * @param msg
   */
  auto add(int line, const string &where, const string &msg) -> void;

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
  vector<ErrorInfo> error_list;
};
}

#endif // __ERRORHANDLER_H__