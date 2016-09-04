LIB_ANTLR := lib/antlr.jar
ANTLR_SCRIPT := Micro.g4

all: group compiler

group:
	@echo "Jordan Huffaker, Eric Colter"
compiler: flex
	g++  -Isrc generated/*.cpp -o micro

flex: 
	rm -rf generated
	mkdir generated
	flex -+ -o generated/flex.yy.cpp src/tokens.lex

clean:
	rm -rf generated

.PHONY: all group compiler clean flex
