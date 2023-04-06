# Makefile
# Author: Laura Carolina Triana Martínez

# This rule "program" indicates that the file "program.cpp" should be compiled to generate the executable file "program".
program: program.cpp
	g++ program.cpp -o program -lm

# This rule allows you to compile and run just by doing "make run".
run: program
	./program

# This phony rule removes the executable file "program" from the folder.
clean: 
	rm -f program





