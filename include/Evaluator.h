#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

#include "ASTNodes.h"
#include "ErrorHandler.h"
#include "Environment.h"
#include "Types.h"
#include "Token.h"

#include <exception>
#include <memory>
#include <string>
#include <vector>

namespace boop {

class Evaluator {
private: 
    static const int MAX_RUNTIME_ERR = 20;
    int m_runtime_err_count {};
    ErrorHandler& m_error_handler;
    EnvironmentManager m_env_manager; 

public: 
    explicit Evaluator(ErrorHandler& error_handler);

    auto evaluate_expr(const AST::ExprPtrVariant& expr) -> BoopObject;
    auto evaluate_stmt(const AST::StmtPtrVariant& stmt) -> std::optional<BoopObject>;
    auto evaluate_stmts(const std::vector<AST::StmtPtrVariant> &stmt)
        -> std::optional<BoopObject>;

  private:
    // methods for evaluating Expr types
    auto evaluate_binary_expr(const AST::ExprBinaryPtr &expr) -> BoopObject;
    auto evaluate_grouping_expr(const AST::ExprGroupingPtr &expr) -> BoopObject;
    static auto evaluate_literal_expr(const AST::ExprLiteralPtr &expr) -> BoopObject;
    auto evaluate_unary_expr(const AST::ExprUnaryPtr &expr) -> BoopObject;
    auto evaluate_conditional_expr(const AST::ExprConditionalPtr &expr) -> BoopObject;
    auto evaluate_postfix_expr(const AST::ExprPostfixPtr &expr) -> BoopObject;
    auto evaluate_variable_expr(const AST::ExprVariablePtr &expr) -> BoopObject;
    auto evaluate_assignment_expr(const AST::ExprAssignmentPtr &expr) -> BoopObject;
    auto evaluate_logical_expr(const AST::ExprLogicalPtr &expr) -> BoopObject;
    auto evaluate_call_expr(const AST::ExprCallPtr &expr) -> BoopObject;
    auto evaluate_function_expr(const AST::ExprFunctionPtr &expr) -> BoopObject;
    auto evaluate_get_expr(const AST::ExprGetPtr &expr) -> BoopObject;
    auto evaluate_set_expr(const AST::ExprSetPtr &expr) -> BoopObject;
    auto evaluate_this_expr(const AST::ExprThisPtr &expr) -> BoopObject;
    auto evaluate_super_expr(const AST::ExprSuperPtr &expr) -> BoopObject;

    // methods for evaluating Stmt types
    auto evaluate_expr_stmt(const AST::ExprStmtPtr &stmt)
        -> std::optional<BoopObject>;
    auto evaluate_print_stmt(const AST::PrintStmtPtr &stmt)
        -> std::optional<BoopObject>;
    auto evaluate_block_stmt(const AST::BlockStmtPtr &stmt)
        -> std::optional<BoopObject>;
    auto evaluate_var_stmt(const AST::VarStmtPtr &stmt) -> std::optional<BoopObject>;
    auto evaluate_if_stmt(const AST::IfStmtPtr &stmt) -> std::optional<BoopObject>;
    auto evaluate_while_stmt(const AST::WhileStmtPtr &stmt)
        -> std::optional<BoopObject>;
    auto evaluate_for_stmt(const AST::ForStmtPtr &stmt) -> std::optional<BoopObject>;
    auto evaluate_function_stmt(const AST::FuncStmtPtr &stmt) -> std::optional<BoopObject>;
    auto evaluate_return_stmt(const AST::RetStmtPtr &stmt) -> std::optional<BoopObject>;
    auto evaluate_class_stmt(const AST::ClassStmtPtr &stmt)
        -> std::optional<BoopObject>;

    // throws RuntimeError if right isn't a double
    auto get_double(const Token &token, const BoopObject &right) -> double;
    auto bind_instance(const FuncShrdPtr &method, LoxInstanceShrdPtr instance)
        -> FuncShrdPtr;
};

}

#endif // __EVALUATOR_H__