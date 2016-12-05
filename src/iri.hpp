#ifndef _IRI_H_
#define _IRI_H_

#include "operand.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>

class Function;

class IRI{
	public:
		enum Types {
			STOREI, WRITEI, ADDI, MULTI, SUBI,
			DIVI, STOREF, WRITEF, ADDF, MULTF,
			SUBF, DIVF, READF, READI, GT, GE,
			LT, LE, NE, EQ, JUMP, LABEL, JSR,
			PUSH, POP, RET, LINK, WRITES, DUMP
		};

		IRI(Types type, Operand op1);
		IRI(Types type, Operand op1, Operand op2);
		IRI(Types type, Operand op1, Operand op2, Operand op3);

		static IRI* create(Types type, Operand op1) {
			return new IRI(type, op1);
		}
		static IRI* create(Types type, Operand op1, Operand op2) {
			return new IRI(type, op1, op2);
		}
		static IRI* create(Types type, Operand op1, Operand op2, Operand op3) {
			return new IRI(type, op1, op2, op3);
		}

		void PrintIRI(std::stringstream* stream);
		void PrintAssembly(std::stringstream* stream);
		std::string get_comparison();

		std::vector<Operand> Operands;
		Types Type;

		// Liveness analysis
		std::unordered_set<std::string> live_set;
		std::unordered_set<std::string> in_set;
		std::unordered_set<std::string> gen_set;
		std::unordered_set<std::string> kill_set;

		std::unordered_set<IRI*> predecessor_set;
		std::unordered_set<IRI*> successor_set;
		bool dump;

		void populate_gen_kill();

		Function* _Function;

		// Update the liveness set, return true if it has changed
		bool update_liveness_set();
};

#endif
