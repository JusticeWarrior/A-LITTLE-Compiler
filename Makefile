LEXER=lexer.l
GRAMMAR=grammar.ypp
GEN_DIR=generated
SRC_DIR=src
OBJ_DIR=objects

LEXER_CPP=$(GEN_DIR)/flex.yy.cpp
GRAMMAR_CPP=$(GEN_DIR)/grammar.tab.cpp
GRAMMAR_HPP=$(GEN_DIR)/grammar.tab.hpp

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(LEXER_CPP) $(GRAMMAR_CPP)

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SRCS)))))

CXX=g++
CPPFLAGS = 

all: group micro

group:
	 @ echo "Jordan Huffaker jhuffak, Eric Colter coltere"
micro: $(OBJS)
	 @ g++ -g -std=c++0x $(OBJS) -o micro

$(OBJ_DIR)/flex.yy.o: $(LEXER_CPP) $(GRAMMAR_HPP) | $(OBJ_DIR)
	 @ g++ -g -std=c++0x -I$(GEN_DIR) -I$(SRC_DIR) $< -c -o $@

$(OBJ_DIR)/grammar.tab.o: $(GRAMMAR_CPP) | $(OBJ_DIR)
	 @ g++ -g -std=c++0x -I$(GEN_DIR) -I$(SRC_DIR) $< -c -o $@



$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp | $(OBJ_DIR)
	 @ g++ -g -std=c++0x -I$(SRC_DIR) -I$(GEN_DIR) $< -c -o $@

$(LEXER_CPP): $(SRC_DIR)/$(LEXER) | $(GEN_DIR)
	 @ flex -o $(LEXER_CPP) $(SRC_DIR)/$(LEXER)
	 @ cat generated/flex.yy.cpp | grep -v "define yyFlexLexer" > generated/tmp
	 @ mv generated/tmp generated/flex.yy.cpp


$(GRAMMAR_CPP) $(GRAMMAR_HPP) : $(SRC_DIR)/$(GRAMMAR) | $(GEN_DIR)
	 @ bison -d $(SRC_DIR)/$(GRAMMAR) -o $(GRAMMAR_CPP)


$(GEN_DIR):
	 @ mkdir generated

$(OBJ_DIR):
	 @ mkdir objects

clean:
	 @ rm -rf generated micro objects

.PHONY: all group clean
.SECONDARY:
.SUFFIXES:
