LEXER=lexer.l
GRAMMAR=grammar.y


all: group compiler

group:
	@echo "Jordan Huffaker jhuffak, Eric Colter coltere"
compiler: flex
	rm -rf objects
	mkdir objects
	g++  -Isrc generated/*.cpp -c -o objects/tokens.o
	g++  objects/* -o micro


flex: 
	rm -rf generated
	mkdir generated
	flex -o generated/flex.yy.cpp src/lexer.l
	cat generated/flex.yy.cpp | grep -v "define yyFlexLexer" > generated/tmp
	mv generated/tmp generated/flex.yy.cpp

clean:
	rm -rf generated micro objects

.PHONY: all group compiler clean flex
