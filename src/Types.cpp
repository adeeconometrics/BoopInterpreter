#include "../include/Types.h"
#include "../include/Token.h"
#include "../include/ErrorHandler.h"

#include <cstddef>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

namespace boop {

auto get_literal_string(const LiteralType &value) -> std::string {
  switch (value.index()) {
  case 0: // string
    return std::get<0>(value);
  case 1: { // double
    std::string result = std::to_string(std::get<1>(value));
    auto pos = result.find(".000000");
    if (pos != std::string::npos)
      result.erase(pos, std::string::npos);
    else
      result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    return result;
  }
  default:
    static_assert(
        std::variant_size_v<LiteralType> == 2,
        "Looks like you forgot to update the cases in get_literal_string()!");
    return "";
  }
}

auto makee_optional_lliteral(double value) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, value);
}
auto makee_optional_lliteral(const std::string &lexeme) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, lexeme);
}

// type definitions

// Functor definitions
Functor::Functor(const AST::ExprFunctionPtr &declaration, std::string name,
                 std::shared_ptr<Environment> closure)
    : m_declaration(declaration), m_name(name), m_closure(closure) {}

auto Functor::arity() const noexcept -> size_t {
  return m_declaration->parameters.size();
}

auto Functor::get_closure() const noexcept -> std::shared_ptr<Environment> {
  return m_closure;
}

const auto Functor::get_declaration() const noexcept -> AST::ExprFunctionPtr & {
  return m_declaration;
}

const auto Functor::get_name() const noexcept -> std::string & {
  return m_name;
}

const auto get_body_stmt() const -> std::vector<AST::StmtPtrVariant> & {
  return m_declaration->body;
}

auto Functor::is_method() const noexcept -> bool { return m_is_method; }

auto Functor::is_initializer() const noexcept -> bool {
  return m_is_initializer;
}

auto Functor::get_params() const noexcept -> std::vector<Token> & {
  return m_declaration->parameters;
}

// BuiltinFunction definitions
BuiltinFunction::BuiltinFunction(std::string name,
                                 std::shared_ptr<Environment> closure)
    : m_name(name), m_closure(closure) {}

// BoopClass definitions
BoopClass::Booplass(
    std::string name, std::optional<BoopClassPtr> super,
    const std::vector<std::pair<std::string, BoopObject>> &method_pairs)
    : m_name(name), m_super_class(super), m_methods(method_pairs) {

  for (const auto &[a, b] : method_pairs) {
    m_methods.insert_or_assign(m_hasher(a), b); // check if this works
  }
}

auto BoopClass::get_name() -> std::string { return m_name; }

auto BoopClass::get_super_class() -> std::optional<BoopClassPtr> {
  return m_super_class;
}

auto BoopClass::find_methods(const std::string &name)
    -> std::optional<BoopObject> {

  auto iter = m_methods.find(m_hasher(name));
  if (iter != m_methods.end()) {
    return iter->second;
  }

  if (m_super_class.has_value()) {
    return m_super_class.value()->find_methods(name);
  }

  return std::nullopt;
}

// BoopInstance definitions
BoopInstance::BoopInstance(BoopClassPtr _class):
  m_class(_class){}

auto BoopInstance::to_string() -> std::string {
  return "Instance of " + m_class->get_name();
}

auto BoopInstance::get(const std::string &name) -> BoopObject {
  auto iter = m_fields.find(hasher(name));
  if (iter != m_fields.end()) {
    return iter->second;
  }
  std::optional<BoopObject> method = m_class->find_methods(name);
  if (method.has_value()){
    return method.value();
  }

  throw RuntimeError();
}

auto BoopInstance::set(const std::string &name, BoopObject value) -> void {
  m_fields[hasher(name)] = std::move(value);
}

// external functions definitions
auto are_equals(const BoopObject &left, const BoopObject &right) -> bool {
  if (left.index() == right.index()) {
    switch (left.index()) {
    case 0: // string
      return std::get<std::string>(left) == std::get<std::string>(right);
    case 1: // double
      return std::get<double>(left) == std::get<double>(right);
    case 2: // bool
      return std::get<bool>(left) == std::get<bool>(right);
    case 3: // std::nullptr_t
      // The case where one is null and the other isn't is handled by the
      // outer condition;
      return true;
    case 4: // FunctionPtr
      return std::get<FunctionPtr>(left)->getFnName() ==
             std::get<FunctionPtr>(right)->getFnName();
    case 5: // BoopFunctionPtr
      return std::get<BoopFunctionPtr>(left)->getFnName() ==
             std::get<BoopFunctionPtr>(right)->getFnName();
    case 6: // BoopClassPtr
      return std::get<BoopClassPtr>(left)->getClassName() ==
             std::get<BoopClassPtr>(right)->getClassName();
    case 7: // BoopInstancePtr
      return std::get<BoopInstancePtr>(left).get() ==
             std::get<BoopInstancePtr>(right).get();
    default:
      static_assert(std::variant_size_v<BoopObject> == 8,
                    "Looks like you forgot to update the cases in "
                    "ExprEvaluator::are_equal(const BoopObject&, const "
                    "BoopObject&)!");
    }
  }
  return false;
}

auto get_object_string(const BoopObject &object) -> std::string{
  switch (object.index()) {
  case 0: // string
    return std::get<0>(object);
  case 1: { // double
    std::string result = std::to_string(std::get<1>(object));
    auto pos = result.find(".000000");
    if (pos != std::string::npos)
      result.erase(pos, std::string::npos);
    else
      result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    return result;
  }
  case 2: // bool
    return std::get<2>(object) == true ? "true" : "false";
  case 3: // nullptr
    return "nil";
  case 4: // FunctionPtr
    return std::get<FunctionPtr>(object)->getFnName();
  case 5: // BuiltinFunctionPtr
    return std::get<BuiltinFunctionPtr>(object)->getFnName();
  case 6: // BoopClassPtr
    return std::get<BoopClassPtr>(object)->getClassName();
  case 7: // BoopInstancePtr
    return std::get<BoopInstancePtr>(object)->toString();
  default:
    static_assert(std::variant_size_v<LoxObject> == 8,
                  "Looks like you forgot to update the cases in "
                  "get_literal_string()!");
    return "";
  }
}

auto is_true(const BoopObject &object) -> bool{
  if (std::holds_alternative<std::nullptr_t>(object))
    return false;
  if (std::holds_alternative<bool>(object))
    return std::get<bool>(object);
  if (std::holds_alternative<FunctionPtr>(object))
    return (std::get<FunctionPtr>(object) == nullptr);
  if (std::holds_alternative<BuiltinFunctionPtr>(object))
    return (std::get<BuiltinFunctionPtr>(object) == nullptr);
  if (std::holds_alternative<BoopClassPtr>(object))
    return (std::get<BoopClassPtr>(object) == nullptr);
  if (std::holds_alternative<BoopInstancePtr>(object))
    return (std::get<BoopInstancePtr>(object) == nullptr);
  return true;
}

} // namespace boop