#include "Expr.h"

namespace boop {

template <typename T>
auto Expr::Assign::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_assign_expr(*this);
}

template <typename T>
auto Expr::Binary::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_binary_expr(*this);
}

template <typename T>
auto Expr::Call::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_call_expr(*this);
}

template <typename T>
auto Expr::Get::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_get_expr(*this);
}

template <typename T>
auto Expr::Grouping::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_grouping_expr(*this);
}

template <typename T>
auto Expr::Literal::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_literal_expr(*this);
}

template <typename T>
auto Expr::Logical::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_logical_expr(*this);
}

template <typename T>
auto Expr::Set::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_set_expr(*this);
}

template <typename T>
auto Expr::Super::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_super_expr(*this);
}

template <typename T>
auto Expr::This::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_this_expr(*this);
}

template <typename T>
auto Expr::Unary::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_unary_expr(*this);
}

template <typename T>
auto Expr::Variable::accept(const Expr::Visitor<T> &visitor) -> T override {
  return visitor.visit_variable_expr(*this);
}

} // namespace boop