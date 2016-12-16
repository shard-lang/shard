/* ************************************************************************* */
/* This file is part of Shard.                                               */
/*                                                                           */
/* Shard is free software: you can redistribute it and/or modify             */
/* it under the terms of the GNU Affero General Public License as            */
/* published by the Free Software Foundation.                                */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              */
/* GNU Affero General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Affero General Public License  */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.      */
/* ************************************************************************* */

// Declaration
#include "shard/interpreter/Interpreter.hpp"

// C++
#include <cstdio>

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Decl.hpp"
#include "shard/ast/Stmt.hpp"
#include "shard/ast/Expr.hpp"
#include "shard/ast/Module.hpp"
#include "shard/interpreter/Exception.hpp"
#include "shard/interpreter/Context.hpp"

/* ************************************************************************* */

#define PRINT_CALL // printf("%s\n", __PRETTY_FUNCTION__);

/* ************************************************************************* */

namespace shard {
inline namespace v1 {
namespace interpreter {

/* ************************************************************************* */

namespace {

/* ************************************************************************* */

void interpretExprStmt(ViewPtr<const ast::ExprStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

    interpret(stmt->getExpr(), ctx);
}

/* ************************************************************************* */

void interpretDeclStmt(ViewPtr<const ast::DeclStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

    // Get declaration
    const auto& decl = stmt->getDecl();
    SHARD_ASSERT(decl);

    // Only variable is supported
    if (!ast::VariableDecl::is(decl))
        throw Exception("Only variable can be declared in statement");

    auto varDecl = ast::VariableDecl::cast(decl);

    // Create variable
    auto var = ctx.createVariable(varDecl->getName(), varDecl->getType());

    if (varDecl->getInitExpr())
        var->setValue(interpret(varDecl->getInitExpr(), ctx));
}

/* ************************************************************************* */

void interpretCompoundStmt(ViewPtr<const ast::CompoundStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

    ctx.push();

    for (const auto& s : *stmt)
        interpret(makeView(s), ctx);

    ctx.pop();
}

/* ************************************************************************* */

void interpretIfStmt(ViewPtr<const ast::IfStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretWhileStmt(ViewPtr<const ast::WhileStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretDoWhileStmt(ViewPtr<const ast::DoWhileStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretForStmt(ViewPtr<const ast::ForStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretSwitchStmt(ViewPtr<const ast::SwitchStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretCaseStmt(ViewPtr<const ast::CaseStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretDefaultStmt(ViewPtr<const ast::DefaultStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretContinueStmt(ViewPtr<const ast::ContinueStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretBreakStmt(ViewPtr<const ast::BreakStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

void interpretReturnStmt(ViewPtr<const ast::ReturnStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

}

/* ************************************************************************* */

Value interpretNullLiteralExpr(ViewPtr<const ast::NullLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

Value interpretBoolLiteralExpr(ViewPtr<const ast::BoolLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return Value(expr->getValue());
}

/* ************************************************************************* */

Value interpretIntLiteralExpr(ViewPtr<const ast::IntLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return Value(expr->getValue());
}

/* ************************************************************************* */

Value interpretFloatLiteralExpr(ViewPtr<const ast::FloatLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

Value interpretCharLiteralExpr(ViewPtr<const ast::CharLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

Value interpretStringLiteralExpr(ViewPtr<const ast::StringLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

Value interpretBinaryExpr(ViewPtr<const ast::BinaryExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    // Evaluate operands
    auto lhs = interpret(expr->getLhs(), ctx);
    auto rhs = interpret(expr->getRhs(), ctx);

    switch (expr->getOpKind())
    {
    //  Equality operators
    case ast::BinaryExpr::OpKind::EQ: break;
    case ast::BinaryExpr::OpKind::NE: break;

    // Relational operators
    case ast::BinaryExpr::OpKind::LT: break;
    case ast::BinaryExpr::OpKind::LE: break;
    case ast::BinaryExpr::OpKind::GT: break;
    case ast::BinaryExpr::OpKind::GE: break;

    // Additive operators
    case ast::BinaryExpr::OpKind::Add:
        return Value(lhs.asInt() + rhs.asInt());

    case ast::BinaryExpr::OpKind::Sub: break;

    // Multiplicative operators
    case ast::BinaryExpr::OpKind::Mul: break;
    case ast::BinaryExpr::OpKind::Div: break;
    case ast::BinaryExpr::OpKind::Rem: break;

    // Assignment operators
    case ast::BinaryExpr::OpKind::Assign: break;
    case ast::BinaryExpr::OpKind::MulAssign: break;
    case ast::BinaryExpr::OpKind::DivAssign: break;
    case ast::BinaryExpr::OpKind::RemAssign: break;
    case ast::BinaryExpr::OpKind::AddAssign: break;
    case ast::BinaryExpr::OpKind::SubAssign: break;
    }

    return {};
}

/* ************************************************************************* */

Value interpretUnaryExpr(ViewPtr<const ast::UnaryExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    // Evaluate
    auto res = interpret(expr->getExpr(), ctx);

    switch (expr->getOpKind())
    {
    case ast::UnaryExpr::OpKind::PostInc: break;
    case ast::UnaryExpr::OpKind::PostDec: break;
    case ast::UnaryExpr::OpKind::PreInc: break;
    case ast::UnaryExpr::OpKind::PreDec: break;
    case ast::UnaryExpr::OpKind::Plus: break;
    case ast::UnaryExpr::OpKind::Minus: break;
    case ast::UnaryExpr::OpKind::Not: break;
    }

    return {};
}

/* ************************************************************************* */

Value interpretTernaryExpr(ViewPtr<const ast::TernaryExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

Value interpretParenExpr(ViewPtr<const ast::ParenExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return interpret(expr->getExpr(), ctx);
}

/* ************************************************************************* */

Value interpretIdentifierExpr(ViewPtr<const ast::IdentifierExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    auto var = ctx.findVariable(expr->getName());

    return var->getValue();
}

/* ************************************************************************* */

Value interpretFunctionCallExpr(ViewPtr<const ast::FunctionCallExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    // TODO: remove
    if (ast::IdentifierExpr::is(expr->getExpr()) && ast::IdentifierExpr::cast(expr->getExpr())->getName() == "print")
    {
        for (const auto& arg : expr->getArguments())
        {
            printf("%d\n", interpret(makeView(arg), ctx).asInt());
        }
    }

    return {};
}

/* ************************************************************************* */

Value interpretMemberAccessExpr(ViewPtr<const ast::MemberAccessExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

Value interpretSubscriptExpr(ViewPtr<const ast::SubscriptExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return {};
}

/* ************************************************************************* */

}

/* ************************************************************************* */

void interpret(ViewPtr<const ast::Module> unit, Context& ctx)
{
    SHARD_ASSERT(unit);
    PRINT_CALL;

    // Register variable declarations
    for (const auto& decl : unit->getDeclarations<ast::VariableDecl>())
    {
        SHARD_ASSERT(decl);
        auto var = ctx.createVariable(decl->getName(), decl->getType());
        SHARD_ASSERT(var);

        if (decl->getInitExpr())
            var->setValue(interpret(decl->getInitExpr(), ctx));
    }

    // Find function declaration
    ViewPtr<ast::Decl> decl = unit->findDeclaration("main");

    if (decl == nullptr || !ast::FunctionDecl::is(decl))
        throw Exception("No 'main' function in the compilation unit");

    // Parameters
    ctx.push();

    // Call function
    interpret(ast::FunctionDecl::cast(decl)->getBodyStmt(), ctx);
}

/* ************************************************************************* */

void interpret(ViewPtr<const ast::Module> unit)
{
    SHARD_ASSERT(unit);
    PRINT_CALL;

    Context ctx;

    interpret(unit, ctx);
}

/* ************************************************************************* */

void interpret(ViewPtr<const ast::Stmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

#define CASE(name) \
    case ast::StmtKind::name: interpret ## name ## Stmt(ast::name ## Stmt::cast(stmt), ctx); break;

    switch (stmt->getKind())
    {
    CASE(Expr)
    CASE(Decl)
    CASE(Compound)
    CASE(If)
    CASE(While)
    CASE(DoWhile)
    CASE(For)
    CASE(Switch)
    CASE(Case)
    CASE(Default)
    CASE(Continue)
    CASE(Break)
    CASE(Return)
    }

#undef CASE
}

/* ************************************************************************* */

Value interpret(ViewPtr<const ast::Expr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

#define CASE(name) \
    case ast::ExprKind::name: return interpret ## name ## Expr(ast::name ## Expr::cast(expr), ctx);

    switch (expr->getKind())
    {
    CASE(NullLiteral)
    CASE(BoolLiteral)
    CASE(IntLiteral)
    CASE(FloatLiteral)
    CASE(CharLiteral)
    CASE(StringLiteral)
    CASE(Binary)
    CASE(Unary)
    CASE(Ternary)
    CASE(Paren)
    CASE(Identifier)
    CASE(FunctionCall)
    CASE(MemberAccess)
    CASE(Subscript)
    }

#undef CASE

    return {};
}

/* ************************************************************************* */

}
}
}

/* ************************************************************************* */
