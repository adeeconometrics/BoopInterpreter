#include "Stmt.h"

namespace boop {

template <typename T>
auto Stmt::Block(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_block_stmt(*this);
}

template <typename T>
auto Stmt::Class(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_class_stmt(*this);
}

template <typename T>
auto Stmt::Expr(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_expr_stmt(*this);
}

template <typename T>
auto Stmt::Function(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_function_stmt(*this);
}

template <typename T>
auto Stmt::If(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_if_stmt(*this);
}

template <typename T>
auto Stmt::Print(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_print_stmt(*this);
}

template <typename T>
auto Stmt::Return(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_return_stmt(*this);
}

template <typename T>
auto Stmt::Var(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_var_stmt(*this);
}

template <typename T>
auto Stmt::While(const Stmt::Visitor<T> &visitor) -> T override {
  return visitor.visit_while_stmt(*this);
}

}