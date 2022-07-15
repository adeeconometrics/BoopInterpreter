#include "Expr.h"

namespace boop {
    template <typename T> auto Expr::Assign(const Expr::Visitor<T>& visitor) -> T override {
        return visitor.visit_assign_expr(*this);
    }
}