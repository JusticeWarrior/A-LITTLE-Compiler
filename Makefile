LEXER=lexer.l
GRAMMAR=grammar.y
GEN_DIR=generated
SRC_DIR=src
OBJ_DIR=objects


all: group micro

group:
	@echo "Jordan Huffaker jhuffak, Eric Colter coltere"
micro: generated/flex.yy.cpp generated/grammar.tab.cpp objects
	@cd objects && g++  -g -I../src -I../generated ../generated/*.cpp ../src/*.cpp -c
	@g++ -g -Isrc -Igenerated generated/*.cpp src/*.cpp -o micro


generated/flex.yy.cpp: generated
	@flex -o generated/flex.yy.cpp src/lexer.l
	@cat generated/flex.yy.cpp | grep -v "define yyFlexLexer" > generated/tmp
	@mv generated/tmp generated/flex.yy.cpp


generated/grammar.tab.cpp: generated
	@bison -d src/grammar.ypp -o generated/grammar.tab.cpp

clean:
	@rm -rf generated micro objects

generated:
	@mkdir generated

objects:
	@mkdir objects

.PHONY: all group clean
