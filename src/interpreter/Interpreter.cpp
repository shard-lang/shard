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
#include <utility>
#include <cstdio>

// Shard
#include "shard/Assert.hpp"
#include "shard/ast/Decls.hpp"
#include "shard/ast/Stmts.hpp"
#include "shard/ast/Exprs.hpp"
#include "shard/ast/Unit.hpp"
#include "shard/interpreter/Exception.hpp"
#include "shard/interpreter/Context.hpp"

/* ************************************************************************* */

//#define PRINT_CALL printf("%s\n", __PRETTY_FUNCTION__);
#define PRINT_CALL

/* ************************************************************************* */

namespace shard::interpreter {

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
    if (!decl->is<ast::VariableDecl>())
        throw Exception("Only variable can be declared in statement");

    auto& varDecl = decl->cast<ast::VariableDecl>();

    // Create variable
    auto var = ctx.addSymbol(varDecl.getName(), SymbolKind::Variable);

    if (varDecl.getInitExpr())
        var->setValue(interpret(varDecl.getInitExpr(), ctx));
}

/* ************************************************************************* */

void interpretCompoundStmt(ViewPtr<const ast::CompoundStmt> stmt, Context& ctx)
{
    SHARD_ASSERT(stmt);
    PRINT_CALL;

    ctx.push();

    for (const auto& s : stmt->getStmts())
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

    // Evaluate return expr
    auto ret = interpret(stmt->getResExpr(), ctx);

    auto retSym = ctx.findSymbol("return");
    SHARD_ASSERT(retSym);
    retSym->setValue(std::move(ret));
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

    return Value(expr->getValue());
}

/* ************************************************************************* */

Value interpretCharLiteralExpr(ViewPtr<const ast::CharLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return Value(expr->getValue());
}

/* ************************************************************************* */

Value interpretStringLiteralExpr(ViewPtr<const ast::StringLiteralExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    return Value(expr->getValue());
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
    case ast::BinaryExpr::OpKind::EQ: return Value(lhs == rhs);
    case ast::BinaryExpr::OpKind::NE: return Value(lhs != rhs);

    // Relational operators
    case ast::BinaryExpr::OpKind::LT: return Value(lhs < rhs);
    case ast::BinaryExpr::OpKind::LE: return Value(lhs <= rhs);
    case ast::BinaryExpr::OpKind::GT: return Value(lhs > rhs);
    case ast::BinaryExpr::OpKind::GE: return Value(lhs >= rhs);

    // Additive operators
    case ast::BinaryExpr::OpKind::Add: return lhs + rhs;
    case ast::BinaryExpr::OpKind::Sub: return lhs - rhs;

    // Multiplicative operators
    case ast::BinaryExpr::OpKind::Mul: return lhs * rhs;
    case ast::BinaryExpr::OpKind::Div: return lhs / rhs;
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

    // Try to find required symbol
    auto sym = ctx.findSymbol(expr->getName());

    if (sym == nullptr)
        throw Exception("Symbol '" + expr->getName() + "' not defined in within current scope");

    return sym->getValue();
}

/* ************************************************************************* */

Value interpretFunctionCallExpr(ViewPtr<const ast::FunctionCallExpr> expr, Context& ctx)
{
    SHARD_ASSERT(expr);
    PRINT_CALL;

    // Evaluate expr before arguments
    auto res = interpret(expr->getExpr(), ctx);

    if (res.getKind() != ValueKind::Function)
        throw Exception("Not a function");

    // Get function info
    auto fn = res.asFunction();

    // Builtin function
    if (fn.getName() == "print")
    {
        for (auto& arg : expr->getArguments())
        {
            // Evaluate argument
            auto val = interpret(makeView(arg), ctx);

            switch (val.getKind())
            {
            case ValueKind::Null:       printf("null"); break;
            case ValueKind::Bool:       printf("%s", val.asBool() ? "true" : "false"); break;
            case ValueKind::Int:        printf("%d", val.asInt()); break;
            case ValueKind::Float:      printf("%f", val.asFloat()); break;
            case ValueKind::Char:       printf("%c", static_cast<char>(val.asChar())); break;
            case ValueKind::String:     printf("%s", val.asString().c_str()); break;
            case ValueKind::Function:   printf("<callable>"); break;
            }
        }

        printf("\n");

        return {};
    }

    if (fn.getDecl() == nullptr)
        throw Exception("Missing function declaration");

    // FIXME: Function context

    // Arguments context
    ctx.push();

    // Return value
    auto retSym = ctx.addSymbol("return", SymbolKind::Variable);

    // Parameters & Arguments
    const auto& params = fn.getDecl()->getParameters();
    const auto& args = expr->getArguments();

    if (args.size() != params.size())
        throw Exception("Function call argument count mismatch");

    // Register arguments
    for (int i = 0; i < params.size(); ++i)
    {
        auto param = ctx.addSymbol(params[i]->getName(), SymbolKind::Variable);
        SHARD_ASSERT(param);

        param->setValue(interpret(makeView(args[i]), ctx));
    }

    // Intepret function body
    interpretCompoundStmt(fn.getDecl()->getBodyStmt(), ctx);

    // Get return value
    auto ret = retSym->getValue();

    ctx.pop();

    return ret;
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

void interpret(ViewPtr<const ast::Unit> unit, Context& ctx)
{
    SHARD_ASSERT(unit);
    PRINT_CALL;

    // Register declarations
    for (const auto& decl : unit->getDeclarations())
    {
        SHARD_ASSERT(decl);

        // Is variable
        if (decl->is<ast::VariableDecl>())
        {
            const auto& varDecl = decl->cast<ast::VariableDecl>();

            // Register symbol as variable
            auto var = ctx.addSymbol(varDecl.getName(), SymbolKind::Variable);
            SHARD_ASSERT(var);

            // Define variable initial value
            if (varDecl.getInitExpr())
                var->setValue(interpret(varDecl.getInitExpr(), ctx));
        }
        else if (decl->is<ast::FunctionDecl>())
        {
            const auto& fnDecl = decl->cast<ast::FunctionDecl>();

            // Register symbol as function
            auto fn = ctx.addSymbol(fnDecl.getName(), SymbolKind::Function);
            SHARD_ASSERT(fn);

            // Store function definition
            fn->setValue(Function(fnDecl.getName(), &fnDecl));
        }
        else
        {
            throw Exception("Unknown declaration type");
        }
    }

    // Find main function
    auto main = ctx.findSymbol("main");

    if (main == nullptr || main->getValue().getKind() != ValueKind::Function)
        throw Exception("No 'main' function in the compilation unit");

    // Parameters
    ctx.push();

    // Main function info
    auto mainFn = main->getValue().asFunction();
    SHARD_ASSERT(mainFn.getDecl());

    // Call function
    interpret(mainFn.getDecl()->getBodyStmt(), ctx);
}

/* ************************************************************************* */

void interpret(ViewPtr<const ast::Unit> unit)
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
    case ast::StmtKind::name: interpret ## name ## Stmt(&stmt->cast<ast::name ## Stmt>(), ctx); break;

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
    case ast::ExprKind::name: return interpret ## name ## Expr(&expr->cast<ast::name ## Expr>(), ctx);

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

/* ************************************************************************* */
