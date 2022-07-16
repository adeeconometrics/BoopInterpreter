#ifndef __TYPES_H__
#define __TYPES_H__

#include <optional>
#include <string>
#include <variant>


namespace boop {
struct Uncopyable {
  explicit Uncopyable() = default;
  Uncopyable(const Uncopyable &) = delete;
  Uncopyable(Uncopyable &&) = delete;

  virtual ~Uncopyable() = default;

  auto operator=(const Uncopyable &) noexcept -> Uncopyable & = delete;
  auto operator=(Uncopyable &&) noexcept -> Uncopyable & = delete;
};

using LiteralType = std::variant<std::string, double, float, int>;
using OptionalLiteral = std::optional<LiteralType>;

auto make_optional_literal(double value) -> OptionalLiteral;

auto make_optional_literal(const std::string &lexeme) -> OptionalLiteral;

} // namespace boop

#endif // __TYPES_H__