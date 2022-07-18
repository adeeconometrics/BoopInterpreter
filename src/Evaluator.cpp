#include "../include/Evaluator.h"
#include "../include/ErrorHandler.h"
#include "../include/Types.h"

#include <chrono>

#define EXPECT_TRUE(x) __builtin_expect(static_cast<int64_t>(x), 1)
#define EXPECT_FALSE(x) __builtin_expect(static_cast<int64_t>(x), 0)

namespace boop {

// throws RuntimeError is not double
auto Evaluator::get_double(const Token &token, const BoopObject &right)
    -> double {
  if (EXPECT_FALSE(!std::holds_alternative<double>(right)))
    throw report_runtime_error(
        m_error_handler, token,
        "Attempted to perform arithmetic operation on non-numeric literal " +
            get_object_string(right));
  return std::get<double>(right);
}

auto Evaluator::bind_instance(const FunctionPtr &method,
                              BoopInstancePtr instance) -> FunctionPtr {
  auto env_to_restore = m_env_manager.get_current_env();
  // Set the current environment to the function's closure,
  m_env_manager.set_current_env(method->get_closure());
  // Create a new environment and define 'this' to point to the instance
  m_env_manager.create_new_env();
  auto method_closure = m_env_manager.get_current_env();
  m_env_manager.define("this", instance);
  // restore the environ.
  m_env_manager.set_current_env(env_to_restore);
  // create and return a new Functor that uses this new environ as its closure.
  return std::make_shared<Functor>(
      method->get_declaration(), method->get_name(), method_closure,
      method->is_method(), method->is_initializer());
}

// definitions of Evaluator methods
Evaluator::Evaluator(ErrorReporter &error_handler)
    : m_error_handler(error_handler), m_env_manager(error_handler) {
  m_env_manager.define(
      Token(TokenType::FUN, "clock"),
      static_cast<BuiltinFunctionPtr>(
          std::make_shared<ClockBuiltin>(m_env_manager.get_current_env())));
}

auto Evaluator::evaluate_binary_expr(const AST::ExprBinaryPtr &expr)
    -> BoopObject {
  auto left = evaluate_expr(expr->left);
  auto right = evaluate_expr(expr->right);
  switch (expr->op.get_type()) {
  case TokenType::COMMA:
    return right;
  case TokenType::BANG_EQUAL:
    return !are_equals(left, right);
  case TokenType::EQUAL_EQUAL:
    return are_equals(left, right);
  case TokenType::MINUS:
    return get_double(expr->op, left) - get_double(expr->op, right);
  case TokenType::SLASH: {
    double denominator = get_double(expr->op, right);
    if (EXPECT_FALSE(denominator == 0.0))
      throw report_runtime_error(m_error_handler, expr->op,
                                 "Division by zero is illegal");
    return get_double(expr->op, left) / denominator;
  }
  case TokenType::STAR:
    return get_double(expr->op, left) * get_double(expr->op, right);
  case TokenType::LESS:
    return get_double(expr->op, left) < get_double(expr->op, right);
  case TokenType::LESS_EQUAL:
    return get_double(expr->op, left) <= get_double(expr->op, right);
  case TokenType::GREATER:
    return get_double(expr->op, left) > get_double(expr->op, right);
  case TokenType::GREATER_EQUAL:
    return get_double(expr->op, left) >= get_double(expr->op, right);
  case TokenType::PLUS: {
    if (std::holds_alternative<double>(left) &&
        std::holds_alternative<double>(right)) {
      return std::get<double>(left) + std::get<double>(right);
    }
    if (std::holds_alternative<std::string>(left) ||
        std::holds_alternative<std::string>(right)) {
      return get_object_string(left) + get_object_string(right);
    }
    throw report_runtime_error(
        m_error_handler, expr->op,
        "Operands to 'plus' must be numbers or strings; This is invalid: " +
            get_object_string(left) + " + " + get_object_string(right));
  }
  default:
    throw report_runtime_error(
        m_error_handler, expr->op,
        "Attempted to apply invalid operator to binary expr: " +
            expr->op.get_type_string());
  }
}

auto Evaluator::evaluate_grouping_expr(const AST::ExprGroupingPtr &expr)
    -> BoopObject {
  return evaluate_expr(expr->expression);
}

namespace {
auto boop_object_from_string_literal(const Literal &str_literal) -> BoopObject {
  const auto &str = std::get<std::string>(str_literal);
  if (str == "true")
    return BoopObject(true);
  if (str == "false")
    return BoopObject(false);
  if (str == "nil")
    return BoopObject(nullptr);
  return BoopObject(str);
};
} // namespace

auto Evaluator::evaluate_literal_expr(const AST::ExprLiteralPtr &expr)
    -> BoopObject {
  return expr->literalVal.has_value()
             ? std::holds_alternative<std::string>(expr->literalVal.value())
                   ? boop_object_from_string_literal(expr->literalVal.value())
                   : BoopObject(std::get<double>(expr->literalVal.value()))
             : BoopObject(nullptr);
}

auto Evaluator::evaluate_unary_expr(const AST::ExprUnaryPtr &expr)
    -> BoopObject {
  BoopObject right = evaluate_expr(expr->right);
  switch (expr->op.get_type()) {
  case TokenType::BANG:
    return !is_true(right);
  case TokenType::MINUS:
    return -get_double(expr->op, right);
  case TokenType::PLUS_PLUS:
    return get_double(expr->op, right) + 1;
  case TokenType::MINUS_MINUS:
    return get_double(expr->op, right) - 1;
  default:
    throw report_runtime_error(
        m_error_handler, expr->op,
        "Illegal unary expression: " + expr->op.get_lexeme() +
            get_object_string(right));
  }
}

auto Evaluator::evaluate_conditional_expr(const AST::ExprConditionalPtr &expr)
    -> BoopObject {
  if (is_true(evaluate_expr(expr->condition)))
    return evaluate_expr(expr->then_branch);
  return evaluate_expr(expr->else_branch);
}

auto Evaluator::evaluate_variable_expr(const AST::ExprVariablePtr &expr)
    -> BoopObject {
  return m_env_manager.get(expr->var_name);
}

auto Evaluator::evaluate_assignment_expr(const AST::ExprAssignmentPtr &expr)
    -> BoopObject {
  m_env_manager.assign(expr->var_name, evaluate_expr(expr->right));
  return m_env_manager.get(expr->var_name);
}

namespace {
auto match(const Token &token, TokenType tType) -> bool {
  return token.get_type() == tType;
}

auto apply_post_fix_op(const Token &op, const BoopObject &val) -> BoopObject {
  if (EXPECT_TRUE(std::holds_alternative<double>(val))) {
    double dVal = std::get<double>(val);
    if (match(op, TokenType::PLUS_PLUS))
      return BoopObject(++dVal);
    if (match(op, TokenType::MINUS_MINUS))
      return BoopObject(--dVal);
  }
  throw RuntimeError();
}
} // namespace

auto Evaluator::evaluate_postfix_expr(const AST::ExprPostfixPtr &expr)
    -> BoopObject {
  BoopObject lhs = evaluate_expr(expr->left);
  if (EXPECT_TRUE(std::holds_alternative<AST::ExprVariablePtr>(expr->left))) {
    m_env_manager.assign((std::get<AST::ExprVariablePtr>(expr->left))->varName,
                         apply_post_fix_op(expr->op, lhs));
  }
  return lhs;
}

auto Evaluator::evaluate_logical_expr(const AST::ExprLogicalPtr &expr)
    -> BoopObject {
  BoopObject lhs = evaluate_expr(expr->left);
  if (expr->op.get_type() == TokenType::OR)
    return is_true(lhs) ? lhs : evaluate_expr(expr->right);
  if (expr->op.get_type() == TokenType::AND)
    return !is_true(lhs) ? lhs : evaluate_expr(expr->right);

  throw report_runtime_error(m_error_handler, expr->op,
                             "Illegal logical operator: " +
                                 expr->op.get_lexeme());
}

auto Evaluator::evaluate_call_expr(const AST::ExprCallPtr &expr) -> BoopObject {
  BoopObject callee = evaluate_expr(expr->callee);
  if (EXPECT_FALSE(std::holds_alternative<BuiltinFunctionPtr>(callee))) {
    return std::get<BuiltinFunctionPtr>(callee)->run();
  }

  BoopObject nullable_instance = ([&]() -> BoopObject {
    if (EXPECT_FALSE(std::holds_alternative<BoopClassPtr>(callee)))
      return BoopObject(
          std::make_shared<BoopInstance>(std::get<BoopClassPtr>(callee)));
    return BoopObject(nullptr);
  })();

  const FunctionPtr fun_obj = ([&]() -> FunctionPtr {
    if (std::holds_alternative<BoopClassPtr>(callee)) {
      auto instance = std::get<BoopInstancePtr>(nullable_instance);
      try {
        return bind_instance(std::get<FunctionPtr>(instance->get("init")),
                             instance);
      } catch (const RuntimeError &e) {
        return nullptr;
      }
    }

    if (EXPECT_TRUE(std::holds_alternative<FunctionPtr>(callee)))
      return std::get<FunctionPtr>(callee);

    throw report_runtime_error(m_error_handler, expr->paren,
                               "Attempted to invoke a non-function");
  })();

  if (fun_obj.get() == nullptr) {
    // exit early if there is no initializer
    return nullable_instance;
  }

  // Throw error if arity doesn't match the number of arguments supplied
  size_t arity = fun_obj->arity();
  size_t arg_size = expr->arguments.size();

  if (EXPECT_FALSE(arity != arg_size)) {
    throw report_runtime_error(m_error_handler, expr->paren,
                               "Expected " + std::to_string(arity) +
                                   " arguments. Got " +
                                   std::to_string(arg_size) + " arguments. ");
  }

  // Evaluate Arguments before switching to the next context as the arguments
  // may rely on values in this context
  std::vector<BoopObject> evaluated_args;
  for (const auto &arg : expr->arguments) {
    evaluated_args.push_back(evaluate_expr(arg));
  }

  // Save caller's environment so we can restore it later
  auto environToRestore = m_env_manager.get_current_env();
  // Set the m_current_env to the function's closure,
  m_env_manager.set_current_env(fun_obj->get_closure());
  // Create a new env for the function so it won't get cluttered with the
  // closure.
  m_env_manager.create_new_env();

  { // Define each parameter with evaluated argument
    const auto &params = fun_obj->get_params();
    auto param = params.begin();
    auto arg = evaluated_args.begin();
    for (; param != params.end() && arg != evaluated_args.end();
         ++param, ++arg) {
      m_env_manager.define(*param, *arg);
    }
  }

  // Evaluate the function
  std::optional<BoopObject> fnRet = evaluate_stmts(fun_obj->get_body_stmt());

  // Teardown any environments created by the function.
  if (!fun_obj->is_method())
    m_env_manager.discard_envs_till(fun_obj->get_closure());
  else
    m_env_manager.discard_envs_till(fun_obj->get_closure()->getParentEnv());
  // Restore caller's environment.
  m_env_manager.set_current_env(environToRestore);

  // return result or BoopObject(nullptr);
  if (fnRet.has_value()) {
    if (EXPECT_FALSE(fun_obj->is_initializer()))
      throw report_runtime_error(
          m_error_handler, expr->paren,
          "Initializer can't return a value other than 'this'");
    return fnRet.value();
  }
  return nullable_instance;
}

auto Evaluator::evaluate_function_expr(const AST::ExprFunctionPtr &expr)
    -> BoopObject {
  // The current Environment becomes the closure for the function.
  auto closure = m_env_manager.get_current_env();
  // We also create a new environment because we don't want any redefinitions of
  // variables that are later in the program lexical order to be visible to this
  // function (in case it's stored and passed around). This environment creation
  // isn't paired with a destruction in this function. The environment will be
  // discarded when exiting wrapping scope this function is defined in (and the
  // Functor goes out of scope.)
  m_env_manager.create_new_env();
  return std::make_shared<Functor>(expr, "BoopAnonFuncDoNotUseThisNameAADWAED",
                                   std::move(closure));
}

auto Evaluator::evaluate_get_expr(const AST::ExprGetPtr &expr) -> BoopObject {
  BoopObject inst_obj = evaluate_expr(expr->expr);
  if (EXPECT_FALSE(!std::holds_alternative<BoopInstancePtr>(inst_obj))) {
    throw report_runtime_error(m_error_handler, expr->name,
                               "Only instances have properties");
  }
  try {
    BoopObject property =
        std::get<BoopInstancePtr>(inst_obj)->get(expr->name.get_lexeme());
    if (std::holds_alternative<FunctionPtr>(property)) {
      // if it's a method that we just looked up, then we need to create a
      // binding for 'this'
      property = BoopObject(bind_instance(std::get<FunctionPtr>(property),
                                          std::get<BoopInstancePtr>(inst_obj)));
    }
    return property;
  } catch (const RuntimeError &e) {
    throw report_runtime_error(
        m_error_handler, expr->name,
        "Attempted to access undefined property: " + expr->name.get_lexeme() +
            " on " + std::get<BoopInstancePtr>(inst_obj)->toString());
  }
}

auto Evaluator::evaluate_set_expr(const AST::AST::ExprSetPtr &expr)
    -> BoopObject {
  BoopObject object = evaluate_expr(expr->expr);
  if (EXPECT_FALSE(!std::holds_alternative<BoopInstancePtr>(object)))
    throw report_runtime_error(m_error_handler, expr->name,
                               "Only instances have fields.");
  BoopObject value = evaluate_expr(expr->value);
  std::get<BoopInstancePtr>(object)->set(expr->name.get_lexeme(), value);
  return value;
}

auto Evaluator::evaluate_this_expr(const AST::ExprThisPtr &expr) -> BoopObject {
  return m_env_manager.get(expr->keyword);
}

auto Evaluator::evaluate_super_expr(const AST::ExprSuperPtr &expr)
    -> BoopObject {
  BoopClassPtr super_class =
      std::get<BoopClassPtr>(m_env_manager.get(expr->keyword));
  auto optionalMethod = super_class->findMethod(expr->method.get_lexeme());
  if (!optionalMethod.has_value())
    throw report_runtime_error(m_error_handler, expr->keyword,
                               "Attempted to access undefined property " +
                                   expr->keyword.get_lexeme() + " on super.");

  return bind_instance(std::get<FunctionPtr>(optionalMethod.value()),
                       std::get<BoopInstancePtr>(
                           m_env_manager.get(Token(TokenType::THIS, "this"))));
}

auto Evaluator::evaluate_expr(const ExprPtrVariant &expr) -> BoopObject {
  switch (expr.index()) {
  case 0: // AST::ExprBinaryPtr
    return evaluate_binary_expr(std::get<0>(expr));
  case 1: // AST::ExprGroupingPtr
    return evaluate_grouping_expr(std::get<1>(expr));
  case 2: // AST::ExprLiteralPtr
    return evaluate_literal_expr(std::get<2>(expr));
  case 3: // AST::ExprUnaryPtr
    return evaluate_unary_expr(std::get<3>(expr));
  case 4: // AST::ExprConditionalPtr
    return evaluate_conditional_expr(std::get<4>(expr));
  case 5: // AST::ExprPostfixPtr
    return evaluate_postfix_expr(std::get<5>(expr));
  case 6: // AST::ExprVariablePtr
    return evaluate_variable_expr(std::get<6>(expr));
  case 7: // AST::ExprAssignmentPtr
    return evaluate_assignment_expr(std::get<7>(expr));
  case 8: // AST::ExprLogicalPtr
    return evaluate_logical_expr(std::get<8>(expr));
  case 9: // AST::ExprCallPtr
    return evaluate_call_expr(std::get<9>(expr));
  case 10: // AST::ExprFunctionPtr
    return evaluate_function_expr(std::get<10>(expr));
  case 11: // AST::ExprGetPtr
    return evaluate_get_expr(std::get<11>(expr));
  case 12: // AST::ExprSetPtr
    return evaluate_set_expr(std::get<12>(expr));
  case 13: // AST::ExprThisPtr
    return evaluate_this_expr(std::get<13>(expr));
  case 14: // AST::ExprSuperPtr
    return evaluate_super_expr(std::get<14>(expr));
  default:
    static_assert(std::variant_size_v<ExprPtrVariant> == 15,
                  "Looks like you forgot to update the cases in "
                  "Evaluator::Evaluate(const ExptrVariant&)!");
    return "";
  }
}

//==============================//
// Statement Evaluation Methods //
//==============================//
auto Evaluator::evaluate_expr_stmt(const AST::ExprStmtPtr &stmt)
    -> std::optional<BoopObject> {
  BoopObject result = evaluate_expr(stmt->expression);

  return std::nullopt;
}

auto Evaluator::evaluate_print_stmt(const AST::PrintStmtPtr &stmt)
    -> std::optional<BoopObject> {
  BoopObject obj_to_print = evaluate_expr(stmt->expression);
  std::cout << "> " << get_object_string(obj_to_print) << '\n';

  return std::nullopt;
}

auto Evaluator::evaluate_block_stmt(const AST::BlockStmtPtr &stmt)
    -> std::optional<BoopObject> {

  auto current_env = m_env_manager.get_current_env();
  m_env_manager.create_new_env();
  
  std::optional<BoopObject> result = evaluate_stmts(stmt->statements);
  
  m_env_manager.discard_envs_till(current_env);
  return result;
}

auto Evaluator::evaluate_var_stmt(const AST::VarStmtPtr &stmt)
    -> std::optional<BoopObject> {
  if (stmt->initializer.has_value()) {
    m_env_manager.define(stmt->varName,
                         evaluate_expr(stmt->initializer.value()));
  } else {
    m_env_manager.define(stmt->varName, BoopObject(nullptr));
  }
  return std::nullopt;
}

auto Evaluator::evaluate_if_stmt(const AST::IfStmtPtr &stmt)
    -> std::optional<BoopObject> {
  if (is_true(evaluate_expr(stmt->condition)))
    return evaluate_stmt(stmt->then_branch);
  if (stmt->else_branch.has_value())
    return evaluate_stmt(stmt->else_branch.value());
  return std::nullopt;
}

auto Evaluator::evaluate_while_stmt(const AST::WhileStmtPtr &stmt)
    -> std::optional<BoopObject> {
  std::optional<BoopObject> result = std::nullopt;
  while (is_true(evaluate_expr(stmt->condition)) && !result.has_value()) {
    result = evaluate_stmt(stmt->loop_body);
  }
  return result;
}

auto Evaluator::evaluate_for_stmt(const AST::ForStmtPtr &stmt)
    -> std::optional<BoopObject> {
  std::optional<BoopObject> result = std::nullopt;
  if (stmt->initializer.has_value())
    evaluate_stmt(stmt->initializer.value());
  while (true) {
    if (stmt->condition.has_value() &&
        !is_true(evaluate_expr(stmt->condition.value())))
      break;
    result = evaluate_stmt(stmt->loop_body);
    if (result.has_value())
      break;
    if (stmt->increment.has_value())
      evaluate_expr(stmt->increment.value());
  }
  return result;
}

auto Evaluator::evaluate_function_stmt(const AST::FuncStmtPtr &stmt)
    -> std::optional<BoopObject> {
  // The current Environment becomes the closure for the function.
  std::shared_ptr<Environment> closure = m_env_manager.get_current_env();
  // Create a Functor for the function, and hand it off to environment to store
  m_env_manager.define(stmt->function_name,
                       std::make_shared<Functor>(stmt->funcExpr,
                                                 stmt->function_name.get_lexeme(),
                                                 std::move(closure)));
  // We also create a new environment because we don't want any redefinitions of
  // variables that are later in the program lexical order to be visible to this
  // function (in case it's stored and passed around). This environment creation
  // isn't paired with a destruction in this function. The environment will be
  // discarded when exiting wrapping scope this function is defined in (and the
  // Functor goes out of scope.)
  m_env_manager.create_new_env();
  return std::nullopt;
}

auto Evaluator::evaluate_return_stmt(const AST::RetStmtPtr &stmt)
    -> std::optional<BoopObject> {
  return stmt->value.has_value()
             ? std::make_optional(evaluate_expr(stmt->value.value()))
             : std::nullopt;
}

auto Evaluator::evaluate_class_stmt(const AST::ClassStmtPtr &stmt)
    -> std::optional<BoopObject> {
  // Determine if this class has a super class or not;
  auto superClass = [&]() -> std::optional<BoopClassPtr> {
    if (stmt->superClass.has_value()) {
      auto superclass_obj = evaluate_expr(stmt->superClass.value());
      if (!std::holds_alternative<BoopClassPtr>(superclass_obj))
        throw report_runtime_error(
            m_error_handler, stmt->class_name,
            "Superclass must be a class; Can't inherit from non-class");
      return std::get<BoopClassPtr>(superclass_obj);
    }
    return std::nullopt;
  }();

  // Define the class name in the current environment
  m_env_manager.define(stmt->class_name, BoopObject(nullptr));

  // If there is a super class, create a new environ and define 'super' there
  if (superClass.has_value()) {
    m_env_manager.create_new_env();
    m_env_manager.define("super", superClass.value());
  }

  std::vector<std::pair<std::string, BoopObject>> methods;
  std::shared_ptr<Environment> closure = m_env_manager.get_current_env();
  for (const auto &stmt : stmt->methods) {
    const auto &functionStmt = std::get<AST::FuncStmtPtr>(stmt);
    bool isInitializer = functionStmt->function_name.get_lexeme() == "init";
    BoopObject method = std::make_shared<Functor>(
        functionStmt->funcExpr, functionStmt->function_name.get_lexeme(), closure,
        true, isInitializer);
    methods.emplace_back(functionStmt->function_name.get_lexeme(), method);
  }

  // Discard the environment created for defining 'super'
  if (superClass.has_value()) {
    m_env_manager.set_current_env(
        m_env_manager.get_current_env()->getParentEnv());
  }

  // Declare the class
  m_env_manager.assign(stmt->class_name,
                       std::make_shared<BoopClass>(stmt->class_name.get_lexeme(),
                                                   superClass, methods));

  // Create a new environment so changes that occur afterwards in lexical order
  // aren't visible to the class defn.
  m_env_manager.create_new_env();

  return std::nullopt;
}

auto Evaluator::evaluate_stmt(const AST::StmtPtrVariant &stmt)
    -> std::optional<BoopObject> {
  switch (stmt.index()) {
  case 0: // AST::ExprStmtPtr
    return evaluate_expr_stmt(std::get<0>(stmt));
  case 1: // AST::PrintStmtPtr
    return evaluate_print_stmt(std::get<1>(stmt));
  case 2: // AST::BlockStmtPtr
    return evaluate_block_stmt(std::get<2>(stmt));
  case 3: // AST::VarStmtPtr
    return evaluate_var_stmt(std::get<3>(stmt));
  case 4: // AST::IfStmtPtr
    return evaluate_if_stmt(std::get<4>(stmt));
  case 5: // AST::WhileStmtPtr
    return evaluate_while_stmt(std::get<5>(stmt));
  case 6: // AST::ForStmtPtr
    return evaluate_for_stmt(std::get<6>(stmt));
  case 7: // AST::FuncStmtPtr
    return evaluate_function_stmt(std::get<7>(stmt));
  case 8: // AST::RetStmtPtr
    return evaluate_return_stmt(std::get<8>(stmt));
  case 9: // AST::ClassStmtPtr
    return evaluate_class_stmt(std::get<9>(stmt));
  default:
    static_assert(std::variant_size_v<StmtPtrVariant> == 10,
                  "Looks like you forgot to update the cases in "
                  "PrettyPrinter::toString(const StmtPtrVariant& statement)!");
    return std::nullopt;
  }
}

auto Evaluator::evaluate_stmts(const std::vector<AST::StmtPtrVariant> &stmts)
    -> std::optional<BoopObject> {
  std::optional<BoopObject> result = std::nullopt;
  for (const AST::StmtPtrVariant &stmt : stmts) {
    try {
      result = evaluate_stmt(stmt);
      if (result.has_value())
        break;
    } catch (const RuntimeError &e) {
      if (EXPECT_FALSE(++numRunTimeErr > MAX_RUNTIME_ERR)) {
        std::cerr << "Too many errors occurred. Exiting evaluation."
                  << std::endl;
        throw e;
      }
    }
  }
  return result;
}

class ClockBuiltin : public BuiltinFunction {
public:
  explicit ClockBuiltin(Environment::EnvironmentPtr closure)
      : BuiltinFunction("clock", std::move(closure)) {}
  auto arity() -> size_t override { return 0; }
  auto run() -> BoopObject override {
    return static_cast<double>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count());
  }
  auto get_name() -> std::string override { return "< builtin-fn_clock >"; }
};

} // namespace boop