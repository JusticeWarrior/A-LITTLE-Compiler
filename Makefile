
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
	flex -+ -o generated/flex.yy.cpp src/tokens.l

clean:
	rm -rf generated micro objects

.PHONY: all group compiler clean flex
