#pragma once
#include <iostream>
#include "TParserBaseListener.h"
#include "TParser.h"
#include "TLexer.h"
#include "polinom.h"
#include <stack> 
#include <map>

using namespace std;

namespace antlrcpptest {
	class Calculator: public TParserBaseListener
	{
        stack<Polynom> polynom_stack;
        map<string, Polynom> parameters;
        stack<string> var_stack;
        stack<int> integ;

        int x_deg;
        int y_deg;
        int z_deg;

        stack<string> mon_var;

    public:
        Calculator() : x_deg(0), y_deg(0), z_deg(0) {}

        void exitPlusOp(TParser::PlusOpContext* ctx) override {
            if (polynom_stack.size() < 2) return;
            Polynom r = move(polynom_stack.top()); polynom_stack.pop();
            Polynom l = move(polynom_stack.top()); polynom_stack.pop();
            polynom_stack.push(move(l + r));
        }

        void exitBinaryMinusOp(TParser::BinaryMinusOpContext* ctx) override {
            if (polynom_stack.size() < 2) return;
            Polynom r = move(polynom_stack.top()); polynom_stack.pop();
            Polynom l = move(polynom_stack.top()); polynom_stack.pop();
            polynomial_stack.push(move(l - r));
        }

        void exitUnaryMinusOp(TParser::UnaryMinusOpContext* ctx) override {
            if (polynom_stack.empty()) return;
            polynom_stack.top() = move(polynom_stack.top() * (-1));
        }

        void exitMultOp(TParser::MultOpContext* ctx) override {
            if (polynom_stack.size() < 2) return;
            Polynom r = move(polynom_stack.top()); polynom_stack.pop();
            Polynom l = move(polynom_stack.top()); polynom_stack.pop();
            polynom_stack.push(move(l * r));
        }

        void exitSetValue(TParser::SetValueContext* ctx) override {
            if (polynom_stack.empty() || var_stack.empty()) return;
            Polynom cur = move(polynom_stack.top());
            string var_name = move(var_stack.top());
            parameters[var_name] = move(cur);
            polynom_stack.pop();
            var_stack.pop();
        }

        void exitGetValue(TParser::GetValueContext* ctx) override {
            if (var_stack.empty()) return;
            string var_name = move(var_stack.top());
            var_stack.pop();
            try {
                Polynom cur = parameters.at(var_name);
                polynom_stack.push(move(cur));
            }
            catch (const out_of_range&) {
                string message = var_name + " not found";
                throw out_of_range(message);
            }
        }

        void exitConvertToInt(TParser::ConvertToIntContext* ctx) override {
            integ.push(atoi(ctx->getText()));
        }

        void exitReadUserVar(TParser::ReadUserVarContext* ctx) override {
            var_stack.push(ctx->getText());
        }

        void exitPrint(TParser::PrintContext* ctx) override {
            if (polynom_stack.empty()) return;
            polynom_stack.top().Print();
            cout << endl;
            polynom_stack.pop();
        }

        void exitReadVar(TParser::ReadVarContext* ctx) override {
            mon_var.push(ctx->getText());
        }

        void exitPow(TParser::PowContext* ctx) override {
            if (integ.empty() || mon_var.empty()) return;
            int pow = integ.top();
            string var = mon_var.top();
            if (var == "x") {
                x_deg += pow;
            }
            else if (var == "y") {
                y_deg += pow;
            }
            else if (var == "z") {
                z_deg += pow;
            }
            integ.pop();
            mon_var.pop();
        }

        void enterMonom(TParser::MonomContext* ctx) override {
            x_deg = y_deg = z_deg = 0;
        }

        void exitFullMonom(TParser::FullMonomContext* ctx) override {
            if (integ.empty()) return;
            int coeff = integ.top(); integ.pop();
            Polynom polynom;
            polynom.AddMonom(coeff, 100 * x_deg + 10 * y_deg + z_deg);
            polynom_stack.push(move(polynom));
        }

        void exitMonomZeroPower(TParser::MonomZeroPowerContext* ctx) override {
            if (integ.empty()) return;
            int coeff = integ.top(); integ.pop();
            Polynom polynom;
            polynom.AddMonom(coeff, 0);
            polynom_stack.push(move(polynom));
        }

        void enterMonomWithouCoefficient(TParser::MonomWithouCoefficientContext* ctx) override {
            Polynom polynom;
            polynom.AddMonom(1, 100 * x_deg + 10 * y_deg + z_deg);
            polynom_stack.push(move(polynom));
        }

        void exitCalculate(TParser::CalculateContext* ctx) override {
            if (integ.size() < 3 || polynom_stack.empty()) return;
            int x = integ.top(); integ.pop();
            int y = integ.top(); integ.pop();
            int z = integ.top(); integ.pop();
            Polynom cur = move(polynom_stack.top()); polynom_stack.pop();
            int result = cur.value_pol(x, y, z);
            cout << "Value in (" << x << ", " << y << ", " << z << ") = " << result << endl;
	};
}


