#include "Types.h"

namespace boop {

auto makee_optional_lliteral(double value) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, value);
}
auto makee_optional_lliteral(const std::string &lexeme) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, lexeme);
}

} // namespace boop