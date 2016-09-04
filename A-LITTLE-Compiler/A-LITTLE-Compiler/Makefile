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
	flex -+ -o generated/flex.yy.cpp src/tokens.l

clean:
	rm -rf generated micro

.PHONY: all group compiler clean flex
