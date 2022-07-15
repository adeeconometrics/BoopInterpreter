#include "Expr.h"

namespace boop {

template <typename T>
auto Expr::Assign(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_assign_expr(*this);
}

template <typename T>
auto Expr::Binary(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_binary_expr(*this);
}

template <typename T>
auto Expr::Call(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_call_expr(*this);
}

template <typename T>
auto Expr::Get(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_get_expr(*this);
}

template <typename T>
auto Expr::Grouping(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_grouping_expr(*this);
}

template <typename T>
auto Expr::Literal(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_literal_expr(*this);
}

template <typename T>
auto Expr::Logical(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_logical_expr(*this);
}

template <typename T>
auto Expr::Set(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_set_expr(*this);
}

template <typename T>
auto Expr::Super(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_super_expr(*this);
}

template <typename T>
auto Expr::This(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_this_expr(*this);
}

template <typename T>
auto Expr::Unary(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_unary_expr(*this);
}

template <typename T>
auto Expr::Variable(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_variable_expr(*this);
}

} // namespace boop