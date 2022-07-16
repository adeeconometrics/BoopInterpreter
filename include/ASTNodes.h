#ifndef __ASTNODES_H__
#define __ASTNODES_H__

#include "Token.h"
#include "Types.h"

#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

/**
 * @brief Alternative implementation of Stmt.h and Expr.h that does not rely on
 * VTables and gets rid of performance overhead vtables incurr
 *
 */
namespace boop::AST {

// forward declaration of expression node types
struct ExprBinary;
struct ExprGrouping;
struct ExprLiteral;
struct ExprUnary;
struct ExprConditional;
struct ExprPostfix;
struct ExprVariable;
struct ExprAssignment;
struct ExprLogical;
struct ExprCall;
struct ExprFunction;
struct ExprGet;
struct ExprSet;
struct ExprThis;
struct ExprSuper;

// reference manager assigned to smart pointer 
using ExprBinaryPtr = std::unique_ptr<ExprBinary>;
using ExprGroupingPtr = std::unique_ptr<ExprGrouping>;
using ExprLiteralPtr = std::unique_ptr<ExprLiteral>;
using ExprUnaryPtr = std::unique_ptr<ExprUnary>;
using ExprConditionalPtr = std::unique_ptr<ExprConditional>;
using ExprPostfixPtr = std::unique_ptr<ExprPostfix>;
using ExprVariablePtr = std::unique_ptr<ExprVariable>;
using ExprAssignmentPtr = std::unique_ptr<ExprAssignment>;
using ExprLogicalPtr = std::unique_ptr<ExprLogical>;
using ExprCallPtr = std::unique_ptr<ExprCall>;
using ExprFunctionPtr = std::unique_ptr<ExprFunction>;
using ExprGetPtr = std::unique_ptr<ExprGet>;
using ExprSetPtr = std::unique_ptr<ExprSet>;
using ExprThisPtr = std::unique_ptr<ExprThis>;
using ExprSuperPtr = std::unique_ptr<ExprSuper>;

// union type for reference manager to handle statement nodes
using ExprPtrVariant =
    std::variant<ExprBinaryPtr, ExprGroupingPtr, ExprLiteralPtr, ExprUnaryPtr,
                 ExprConditionalPtr, ExprPostfixPtr, ExprVariablePtr,
                 ExprAssignmentPtr, ExprLogicalPtr, ExprCallPtr, ExprFunctionPtr,
                 ExprGetPtr, ExprSetPtr, ExprThisPtr, ExprSuperPtr>;
                 
// forward declaration of statement node types
struct StmtExpr;
struct StmtPrint;
struct StmtBlock;
struct StmtVariable;
struct StmtIf;
struct StmtWhile;
struct StmtFor;
struct StmtFunction;
struct StmtReturn;
struct StmtClass;

// alias for automatic reference managers on each statement node types
using ExprStmtPtr = std::unique_ptr<StmtExpr>;
using PrintStmtPtr = std::unique_ptr<StmtPrint>;
using BlockStmtPtr = std::unique_ptr<StmtBlock>;
using VarStmtPtr = std::unique_ptr<StmtVariable>;
using IfStmtPtr = std::unique_ptr<StmtIf>;
using WhileStmtPtr = std::unique_ptr<StmtWhile>;
using ForStmtPtr = std::unique_ptr<StmtFor>;
using FuncStmtPtr = std::unique_ptr<StmtFunction>;
using RetStmtPtr = std::unique_ptr<StmtReturn>;
using ClassStmtPtr = std::unique_ptr<StmtClass>;

// union type for reference manager to handle statement nodes
using StmtPtrVariant =
    std::variant<ExprStmtPtr, PrintStmtPtr, BlockStmtPtr, VarStmtPtr, IfStmtPtr,
                 WhileStmtPtr, ForStmtPtr, FuncStmtPtr, RetStmtPtr,
                 ClassStmtPtr>;

// methods that creates expression nodes 
auto make_binary_expr(ExprPtrVariant left, Token op, ExprPtrVariant right)
    -> ExprPtrVariant;
auto make_unary_expr(Token op, ExprPtrVariant right) -> ExprPtrVariant;
auto make_grouping_expr(ExprPtrVariant right) -> ExprPtrVariant;
auto make_literal_expr(OptionalLiteral literal) -> ExprPtrVariant;
auto make_conditional_expr(ExprPtrVariant condition, ExprPtrVariant then,
                          ExprPtrVariant elseBranch) -> ExprPtrVariant;
auto make_postfix_expr(ExprPtrVariant left, Token op) -> ExprPtrVariant;
auto make_variable_expr(Token varName) -> ExprPtrVariant;
auto make_assignment_expr(Token varName, ExprPtrVariant expr) -> ExprPtrVariant;
auto make_logical_expr(ExprPtrVariant left, Token op, ExprPtrVariant right)
    -> ExprPtrVariant;
auto make_call_expr(ExprPtrVariant callee, Token paren,
                   std::vector<ExprPtrVariant> arguments) -> ExprPtrVariant;
auto make_function_expr(std::vector<Token> params,
                   std::vector<StmtPtrVariant> fnBody) -> ExprPtrVariant;
auto make_get_expr(ExprPtrVariant expr, Token name) -> ExprPtrVariant;
auto make_set_expr(ExprPtrVariant expr, Token name, ExprPtrVariant value)
    -> ExprPtrVariant;
auto make_this_expr(Token keyword) -> ExprPtrVariant;
auto make_super_expr(Token keyword, Token method) -> ExprPtrVariant;



// methods that creates statement nodes
auto make_expr_stmt(ExprPtrVariant expr) -> StmtPtrVariant;
auto make_print_stmt(ExprPtrVariant expr) -> StmtPtrVariant;
auto make_block_stmt(std::vector<StmtPtrVariant> statements) -> StmtPtrVariant;
auto make_var_stmt(Token varName, std::optional<ExprPtrVariant> initializer)
    -> StmtPtrVariant;
auto make_if_stmt(ExprPtrVariant condition, StmtPtrVariant thenBranch,
                 std::optional<StmtPtrVariant> elseBranch) -> StmtPtrVariant;
auto make_while_stmt(ExprPtrVariant condition, StmtPtrVariant loopBody)
    -> StmtPtrVariant;
auto make_for_stmt(std::optional<StmtPtrVariant> initializer,
                  std::optional<ExprPtrVariant> condition,
                  std::optional<ExprPtrVariant> increment,
                  StmtPtrVariant loopBody) -> StmtPtrVariant;
auto make_function_stmt(Token fName, ExprFunctionPtr ExprFunction) -> StmtPtrVariant;
auto make_return_stmt(Token ret, std::optional<ExprPtrVariant> value)
    -> StmtPtrVariant;
auto make_class_stmt(Token className, std::optional<ExprPtrVariant> superClass,
                    std::vector<StmtPtrVariant> methods) -> StmtPtrVariant;


// Expression AST Types member declaration:
struct ExprBinary final : public Uncopyable {
  ExprPtrVariant left;
  Token op;
  ExprPtrVariant right;
  ExprBinary(ExprPtrVariant left, Token op, ExprPtrVariant right);
};

struct ExprGrouping final : public Uncopyable {
  ExprPtrVariant expression;
  explicit ExprGrouping(ExprPtrVariant expression);
};

struct ExprLiteral final : public Uncopyable {
  OptionalLiteral literalVal;
  explicit ExprLiteral(OptionalLiteral value);
};

struct ExprUnary final : public Uncopyable {
  Token op;
  ExprPtrVariant right;
  ExprUnary(Token op, ExprPtrVariant right);
};

struct ExprConditional final : public Uncopyable {
  ExprPtrVariant condition;
  ExprPtrVariant thenBranch;
  ExprPtrVariant elseBranch;
  ExprConditional(ExprPtrVariant condition, ExprPtrVariant thenBranch,
                  ExprPtrVariant elseBranch);
};

struct ExprPostfix final : public Uncopyable {
  ExprPtrVariant left;
  Token op;
  ExprPostfix(ExprPtrVariant left, Token op);
};

struct ExprVariable final : public Uncopyable {
  Token varName;
  explicit ExprVariable(Token varName);
};

struct ExprAssignment final : public Uncopyable {
  Token varName;
  ExprPtrVariant right;
  ExprAssignment(Token varName, ExprPtrVariant right);
};

struct ExprLogical final : public Uncopyable {
  ExprPtrVariant left;
  Token op;
  ExprPtrVariant right;
  ExprLogical(ExprPtrVariant left, Token op, ExprPtrVariant right);
};

struct ExprCall final : public Uncopyable {
  ExprPtrVariant callee;
  Token paren;
  std::vector<ExprPtrVariant> arguments;
  ExprCall(ExprPtrVariant callee, Token paren,
           std::vector<ExprPtrVariant> arguments);
};

struct ExprFunction final : public Uncopyable {
  std::vector<Token> parameters;
  std::vector<StmtPtrVariant> body;
  ExprFunction(std::vector<Token> parameters, std::vector<StmtPtrVariant> body);
};

struct ExprGet final : public Uncopyable {
  ExprPtrVariant expr;
  Token name;
  ExprGet(ExprPtrVariant expr, Token name);
};

struct ExprSet final : public Uncopyable {
  ExprPtrVariant expr;
  Token name;
  ExprPtrVariant value;
  ExprSet(ExprPtrVariant expr, Token name, ExprPtrVariant value);
};

struct ExprThis final : public Uncopyable {
  Token keyword;
  explicit ExprThis(Token keyword);
};

struct ExprSuper final : public Uncopyable {
  Token keyword;
  Token method;
  explicit ExprSuper(Token keyword, Token method);
};

// Statment AST types declaration
struct StmtExpr final : public Uncopyable {
  ExprPtrVariant expression;
  explicit StmtExpr(ExprPtrVariant expr);
};

struct StmtPrint final : public Uncopyable {
  ExprPtrVariant expression;
  explicit StmtPrint(ExprPtrVariant expression);
};

struct StmtBlock final : public Uncopyable {
  std::vector<StmtPtrVariant> statements;
  explicit StmtBlock(std::vector<StmtPtrVariant> statements);
};

struct StmtVariable final : public Uncopyable {
  Token varName;
  std::optional<ExprPtrVariant> initializer;
  explicit StmtVariable(Token varName, std::optional<ExprPtrVariant> initializer);
};

struct StmtIf final : public Uncopyable {
  ExprPtrVariant condition;
  StmtPtrVariant thenBranch;
  std::optional<StmtPtrVariant> elseBranch;
  explicit StmtIf(ExprPtrVariant condition, StmtPtrVariant thenBranch,
                  std::optional<StmtPtrVariant> elseBranch);
};

struct StmtWhile final : public Uncopyable {
  ExprPtrVariant condition;
  StmtPtrVariant loopBody;
  explicit StmtWhile(ExprPtrVariant condition, StmtPtrVariant loopBody);
};

struct StmtFor final : public Uncopyable {
  std::optional<StmtPtrVariant> initializer;
  std::optional<ExprPtrVariant> condition;
  std::optional<ExprPtrVariant> increment;
  StmtPtrVariant loopBody;
  explicit StmtFor(std::optional<StmtPtrVariant> initializer,
                   std::optional<ExprPtrVariant> condition,
                   std::optional<ExprPtrVariant> increment,
                   StmtPtrVariant loopBody);
};

struct StmtFunction : public Uncopyable {
  Token funcName;
  ExprFunctionPtr ExprFunction;
  StmtFunction(Token funcName, ExprFunctionPtr ExprFunction);
};

struct StmtReturn : public Uncopyable {
  Token ret;
  std::optional<ExprPtrVariant> value;
  StmtReturn(Token ret, std::optional<ExprPtrVariant> value);
};

struct StmtClass : public Uncopyable {
  Token className;
  std::optional<ExprPtrVariant> superClass;
  std::vector<StmtPtrVariant> methods;
  StmtClass(Token className, std::optional<ExprPtrVariant> superClass,
            std::vector<StmtPtrVariant> methods);
};

} // namespace cpplox::AST

#endif // __ASTNODES_H__