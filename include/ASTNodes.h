#ifndef __ASTNODES_H__
#define __ASTNODES_H__

#include "Token.h"
#include "Types.h"
#include "Uncopyable.h"

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
struct ExprAssign;
struct ExprCall;
struct ExprGet;
struct ExprGrouping;
struct ExprLiteral;
struct ExprLogical;
struct ExprSet;
struct ExprSuper;
struct ExprThis;
struct ExprUnary;
struct ExprVariable;
struct ExprPostfix;

// reference manager assign to smart pointer
using ExprBinaryPtr = std::unique_ptr<ExprBinary>;
using ExprAssignPtr = std::unique_ptr<ExprAssign>;
using ExprCallPtr = std::unique_ptr<ExprCall>;
using ExprGetPtr = std::unique_ptr<ExprGet>;
using ExprGroupingPtr = std::unique_ptr<ExprGrouping>;
using ExprLiteralPtr = std::unique_ptr<ExprLiteral>;
using ExprLogicalPtr = std::unique_ptr<ExprLogical>;
using ExprSetPtr = std::unique_ptr<ExprSet>;
using ExprSuperPtr = std::unique_ptr<ExprSuper>;
using ExprThisPtr = std::unique_ptr<ExprThis>;
using ExprUnaryPtr = std::unique_ptr<ExprUnary>;
using ExprVariablePtr = std::unique_ptr<ExprVariable>;
using ExprPostfixPtr = std::unique_ptr<ExprPostfix>;


// union type for reference manager to handle statement nodes
using ExprPtrVariant =
    std::variant<ExprAssign, ExprBinary, ExprCall, ExprGet, ExprGrouping,
                 ExprLiteral, ExprLogical, ExprSet, ExprSuper, ExprThis,
                 ExprUnary, ExprVariable, ExprPostfix>;

    // methods to visit expression types in AST

    auto make_binary_expr(ExprPtrVariant lhs, Token op, ExprPtrVariant rhs)
        -> ExprPtrVariant;
auto make_unary_expr(Token op, ExprPtrVariant rhs) -> ExprPtrVariant;
auto make_call_expr(ExprPtrVariant callee, Token parent,
                    std::vector<ExprPtrVariant> args) -> ExprPtrVariant;
auto make_get_expr(ExprPtrVariant expr, Token name) -> ExprPtrVariant;
auto make_group_expr() -> ExprPtrVariant;
auto make_literal_expr() -> ExprPtrVariant;
auto make_set_expr() -> ExprPtrVariant;
auto make_super_expr() -> ExprPtrVariant;
auto make_this_expr() -> ExprPtrVariant;
auto make_assign_expr(Token var_name, ExprPtrVariant expr) -> ExprPtrVariant;
auto make_variable_expr() -> ExprPtrVariant;

// forward declaration of statement node types
struct StmtExpr;
struct StmtPrint;
struct StmtBlock;
struct StmtVar;
struct StmtIf;
struct StmtWhile;
struct StmtFor;
struct StmtFunction;
struct StmtReturn;
struct StmtClass;

// reference manager assigned to handle node types
using StmtExprPtr = std::unique_ptr<StmtExpr>;
using StmtPrintPtr = std::unique_ptr<StmtPrint>;
using StmtBlockPtr = std::unique_ptr<StmtBlock>;
using StmtVarPtr = std::unique_ptr<StmtVar>;
using StmtIfPtr = std::unique_ptr<StmtIf>;
using StmtWhilePtr = std::unique_ptr<StmtWhile>;
using StmtForPtr = std::unique_ptr<StmtFor>;
using StmtFunctionPtr = std::unique_ptr<StmtFunction>;
using StmtReturnPtr = std::unique_ptr<StmtReturn>;
using StmtClassPtr = std::unique_ptr<StmtClass>;

// union type for reference manager to handle statement nodes
using StmtPtrVariant =
    std::variant<StmtExpr, StmtPrint, StmtBlock, StmtVar, StmtIf, StmtWhile,
                 StmtFor, StmtFunction, StmtReturn, StmtClass>

} // namespace boop::AST

#endif // __ASTNODES_H__