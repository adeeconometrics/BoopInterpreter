#ifndef __TYPES_H__
#define __TYPES_H__

/**
 * @file Types.h
 * @author ddamiana
 * @brief contains core types of the language
 * @version 0.1
 * @date 2022-07-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ASTNodes.h"
#include "Token.h"

#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <utility>
#include <map>

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

auto get_literal_string(const LiteralType &value) -> std::string;
auto make_optional_literal(double value) -> OptionalLiteral;
auto make_optional_literal(const std::string &lexeme) -> OptionalLiteral;

// forward declaration of types
struct Functor;
struct BuiltinFunction;
struct BoopClass;
struct BoopInstance;

using FunctionPtr = std::shared_ptr<Functor>;
using BuiltinFunctionPtr = std::shared_ptr<BuiltinFunction>;
using BoopClassPtr = std::shared_ptr<BoopClass>;
using BoopInstancePtr = std::shared_ptr<BoopInstance>;

using BoopObject = std::variant<std::string, double, bool, std::nullptr_t,
                                FunctionPtr, BuiltinFunctionPtr, BoopClassPtr,
                                BoopClassPtr, BoopInstancePtr>;

// external functions
auto are_equals(const BoopObject& left, const BoopObject& right) -> bool;
auto get_object_string(const BoopObject& object) -> std::string;
auto is_true(const BoopObject& object) -> bool;

// type declarations
struct Functor : public Uncopyable {
private:
  const AST::ExprFunctionPtr &m_declaration;
  const std::string m_name{};
  std::shared_ptr<Environment> m_closure;
  bool m_is_method{false};
  bool m_is_initializer{false};

public:
  explicit Functor(const AST::ExprFunctionPtr &declaration, std::string name,
                   std::shared_ptr<Environment> closure);

  auto arity() const noexcept -> size_t;
  auto get_closure() const noexcept -> std::shared_ptr<Environment>;
  const auto get_declaration() const noexcept -> AST::ExprFunctionPtr&;
  const auto get_name() const noexcept -> std::string&; // see if this can be optimized using std::string_view 
  const auto get_body_stmt() const -> std::vector<AST::StmtPtrVariant>&; 
  
  auto is_method() const noexcept -> bool;
  auto is_initializer() const noexcept -> bool;
  
  auto get_params() const noexcept -> std::vector<Token>&;
};

struct BuiltinFunction: public Uncopyable {
private: 
  std::string m_name{};
  std::shared_ptr<Environment> m_closure;

public:
  explicit BuiltinFunction(std::string name, std::shared_ptr<Environment> closure);

  // abstract methods for communicating with built-in functions
  virtual auto arity() -> size_t = 0;
  virtual auto run() -> BoopObject = 0;
  virtual auto get_name() -> std::string = 0;
};

struct BoopClass: public Uncopyable {
private:
  const std::string m_name;
  std::optional<BoopClassPtr> m_super_class;
  std::hash<std::string> m_hasher;
  std::map<size_t, BoopObject> m_methods;

public:
  explicit BoopClass(
      std::string name, std::optional<BoopClassPtr> super,
      const std::vector<std::pair<std::string, BoopObject>> &method_pairs);

  auto get_name() -> std::string;
  auto get_super_class() -> std::optional<BoopClassPtr>;

  auto find_methods(const std::string &name) -> std::optional<BoopObject>;
};

struct BoopInstance: public Uncopyable {
private: 
  const BoopClassPtr m_class;
  std::hash<std::string> m_hasher;
  std::map<size_t, BoopObject> m_fields;

public:
  explicit BoopInstance(BoopClassPtr _class);

  auto to_string() -> std::string;
  auto get(const std::string& name) -> BoopObject;
  auto set(const std::string& name, BoopObject value) -> void;
};

} // namespace boop

#endif // __TYPES_H__