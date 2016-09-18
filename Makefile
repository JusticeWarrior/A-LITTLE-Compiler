LEXER=lexer.l
GRAMMAR=grammar.y
GEN_DIR=generated
SRC_DIR=src
OBJ_DIR=objects


all: group compiler

group:
	@echo "Jordan Huffaker jhuffak, Eric Colter coltere"
compiler: bison flex
	rm -rf objects
	mkdir objects
	g++  -Isrc -Igenerated generated/*.cpp src/*.cpp -o micro


flex: 
	flex -o generated/flex.yy.cpp src/lexer.l
	cat generated/flex.yy.cpp | grep -v "define yyFlexLexer" > generated/tmp
	mv generated/tmp generated/flex.yy.cpp


bison:
	rm -rf generated
	mkdir generated
	bison -d src/grammar.ypp -o generated/grammar.tab.cpp

clean:
	rm -rf generated micro objects

.PHONY: all group compiler clean flex
