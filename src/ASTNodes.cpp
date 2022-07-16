#include "ASTNodes.h"


namespace boop::AST {
ExprBinary::ExprBinary(ExprPtrVariant left, Token op, ExprPtrVariant right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

ExprGrouping::ExprGrouping(ExprPtrVariant expression)
    : expression(std::move(expression)) {}

ExprLiteral::ExprLiteral(OptionalLiteral value)
    : literalVal(std::move(value)) {}

ExprUnary::ExprUnary(Token op, ExprPtrVariant right)
    : op(std::move(op)), right(std::move(right)) {}

ExprConditional::ExprConditional(ExprPtrVariant condition,
                                 ExprPtrVariant then_branch,
                                 ExprPtrVariant else_branch)
    : condition(std::move(condition)), then_branch(std::move(then_branch)),
      else_branch(std::move(else_branch)) {}

ExprPostfix::ExprPostfix(ExprPtrVariant left, Token op)
    : left(std::move(left)), op(std::move(op)) {}

ExprVariable::ExprVariable(Token var_name) : var_name(std::move(var_name)) {}

ExprAssignment::ExprAssignment(Token var_name, ExprPtrVariant right)
    : var_name(std::move(var_name)), right(std::move(right)) {}

ExprLogical::ExprLogical(ExprPtrVariant left, Token op, ExprPtrVariant right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

ExprCall::ExprCall(ExprPtrVariant callee, Token paren,
                   std::vector<ExprPtrVariant> arguments)
    : callee(std::move(callee)), paren(std::move(paren)),
      arguments(std::move(arguments)) {}

ExprFunction::ExprFunction(std::vector<Token> parameters,
                   std::vector<StmtPtrVariant> body)
    : parameters(std::move(parameters)), body(std::move(body)) {}

ExprGet::ExprGet(ExprPtrVariant expr, Token name)
    : expr(std::move(expr)), name(std::move(name)) {}

ExprSet::ExprSet(ExprPtrVariant expr, Token name, ExprPtrVariant value)
    : expr(std::move(expr)), name(std::move(name)), value(std::move(value)) {}

ExprThis::ExprThis(Token keyword) : keyword(std::move(keyword)) {}

ExprSuper::ExprSuper(Token keyword, Token method)
    : keyword(std::move(keyword)), method(std::move(method)) {}


auto make_binary_expr(ExprPtrVariant left, Token op, ExprPtrVariant right)
    -> ExprPtrVariant {
  return std::make_unique<ExprBinary>(std::move(left), op, std::move(right));
}

auto make_unary_expr(Token op, ExprPtrVariant right) -> ExprPtrVariant {
  return std::make_unique<ExprUnary>(op, std::move(right));
}

auto make_grouping_expr(ExprPtrVariant right) -> ExprPtrVariant {
  return std::make_unique<ExprGrouping>(std::move(right));
}

auto make_literal_expr(OptionalLiteral literal) -> ExprPtrVariant {
  return std::make_unique<ExprLiteral>(std::move(literal));
}

auto make_conditional_expr(ExprPtrVariant condition, ExprPtrVariant then,
                          ExprPtrVariant else_branch) -> ExprPtrVariant {
  return std::make_unique<ExprConditional>(
      std::move(condition), std::move(then), std::move(else_branch));
}

auto make_postfix_expr(ExprPtrVariant left, Token op) -> ExprPtrVariant {
  return std::make_unique<ExprPostfix>(std::move(left), op);
}

auto make_variable_expr(Token var_name) -> ExprPtrVariant {
  return std::make_unique<ExprVariable>(var_name);
}

auto make_assignment_expr(Token var_name, ExprPtrVariant expr) -> ExprPtrVariant {
  return std::make_unique<ExprAssignment>(var_name, std::move(expr));
}

auto make_logical_expr(ExprPtrVariant left, Token op, ExprPtrVariant right)
    -> ExprPtrVariant {
  return std::make_unique<ExprLogical>(std::move(left), op, std::move(right));
}

auto make_call_expr(ExprPtrVariant callee, Token paren,
                   std::vector<ExprPtrVariant> arguments) -> ExprPtrVariant {
  return std::make_unique<ExprCall>(std::move(callee), std::move(paren),
                                    std::move(arguments));
}

auto make_function_expr(std::vector<Token> params,
                   std::vector<StmtPtrVariant> fnBody) -> ExprPtrVariant {
  return std::make_unique<ExprFunction>(std::move(params), std::move(fnBody));
}

auto make_get_expr(ExprPtrVariant expr, Token name) -> ExprPtrVariant {
  return std::make_unique<ExprGet>(std::move(expr), std::move(name));
}

auto make_set_expr(ExprPtrVariant expr, Token name, ExprPtrVariant value)
    -> ExprPtrVariant {
  return std::make_unique<ExprSet>(std::move(expr), std::move(name),
                                   std::move(value));
}

auto make_this_expr(Token keyword) -> ExprPtrVariant {
  return std::make_unique<ExprThis>(std::move(keyword));
}

auto make_super_expr(Token keyword, Token method) -> ExprPtrVariant {
  return std::make_unique<ExprSuper>(std::move(keyword), std::move(method));
}

StmtExpr::StmtExpr(ExprPtrVariant expr) : expression(std::move(expr)) {}

StmtPrint::StmtPrint(ExprPtrVariant expr) : expression(std::move(expr)) {}

StmtBlock::StmtBlock(std::vector<StmtPtrVariant> statements)
    : statements(std::move(statements)) {}

StmtVariable::StmtVariable(Token var_name, std::optional<ExprPtrVariant> initializer)
    : var_name(std::move(var_name)), initializer(std::move(initializer)) {}

StmtIf::StmtIf(ExprPtrVariant condition, StmtPtrVariant then_branch,
               std::optional<StmtPtrVariant> else_branch)
    : condition(std::move(condition)), then_branch(std::move(then_branch)),
      else_branch(std::move(else_branch)) {}

StmtWhile::StmtWhile(ExprPtrVariant condition, StmtPtrVariant loop_body)
    : condition(std::move(condition)), loop_body(std::move(loop_body)) {}

StmtFor::StmtFor(std::optional<StmtPtrVariant> initializer,
                 std::optional<ExprPtrVariant> condition,
                 std::optional<ExprPtrVariant> increment,
                 StmtPtrVariant loop_body)
    : initializer(std::move(initializer)), condition(std::move(condition)),
      increment(std::move(increment)), loop_body(std::move(loop_body)) {}

StmtFunction::StmtFunction(Token function_name, ExprFunctionPtr ExprFunction)
    : function_name(std::move(function_name)), ExprFunction(std::move(ExprFunction)) {}

StmtReturn::StmtReturn(Token ret, std::optional<ExprPtrVariant> value)
    : ret(std::move(ret)), value(std::move(value)) {}

StmtClass::StmtClass(Token class_name, std::optional<ExprPtrVariant> superClass,
                     std::vector<StmtPtrVariant> methods)
    : class_name(std::move(class_name)), superClass(std::move(superClass)),
      methods(std::move(methods)) {}


auto make_expr_stmt(ExprPtrVariant expr) -> StmtPtrVariant {
  return std::make_unique<StmtExpr>(std::move(expr));
}

auto make_print_stmt(ExprPtrVariant expr) -> StmtPtrVariant {
  return std::make_unique<StmtPrint>(std::move(expr));
}

auto make_block_stmt(std::vector<StmtPtrVariant> statements) -> StmtPtrVariant {
  return std::make_unique<StmtBlock>(std::move(statements));
}

auto make_var_stmt(Token var_name, std::optional<ExprPtrVariant> initializer)
    -> StmtPtrVariant {
  return std::make_unique<StmtVariable>(var_name, std::move(initializer));
}

auto make_if_stmt(ExprPtrVariant condition, StmtPtrVariant then_branch,
                 std::optional<StmtPtrVariant> else_branch) -> StmtPtrVariant {
  return std::make_unique<StmtIf>(std::move(condition), std::move(then_branch),
                                  std::move(else_branch));
}

auto make_while_stmt(ExprPtrVariant condition, StmtPtrVariant loop_body)
    -> StmtPtrVariant {
  return std::make_unique<StmtWhile>(std::move(condition), std::move(loop_body));
}

auto make_for_stmt(std::optional<StmtPtrVariant> initializer,
                  std::optional<ExprPtrVariant> condition,
                  std::optional<ExprPtrVariant> increment,
                  StmtPtrVariant loop_body) -> StmtPtrVariant {
  return std::make_unique<StmtFor>(std::move(initializer), std::move(condition),
                                   std::move(increment), std::move(loop_body));
}

auto make_function_stmt(Token fName, ExprFunctionPtr ExprFunction) -> StmtPtrVariant {
  return std::make_unique<StmtFunction>(std::move(fName), std::move(ExprFunction));
}

auto make_return_stmt(Token ret, std::optional<ExprPtrVariant> value)
    -> StmtPtrVariant {
  return std::make_unique<StmtReturn>(std::move(ret), std::move(value));
}

auto make_class_stmt(Token class_name, std::optional<ExprPtrVariant> superClass,
                    std::vector<StmtPtrVariant> methods) -> StmtPtrVariant {
  return std::make_unique<StmtClass>(std::move(class_name),
                                     std::move(superClass), std::move(methods));
}
}