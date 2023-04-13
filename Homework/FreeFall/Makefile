# Makefile
# Author: Laura Carolina Triana Martínez

# This Makefile is used to compile and run the program of the freefall motion.

# The .SILENT: command prevents make from displaying the executed commands during compilation.
.SILENT:

# The first rule "program" specifies that the file "freefall.cpp" should be compiled using the g++ compiler.
# The resulting executable file should be named "program".
program: freefall.cpp
	g++ freefall.cpp -o program

# The "run" rule compiles and executes the program in one step by typing make run, moves the output files to the "output" directory and removes the "plot.gp" and "program" files from the current directory.
run: program
	./program
	mkdir -p output
	mv table.* output/ 
	mv position.png output/ 
	mv velocity.png output/
	rm plot.gp program

# The "clean" rule is used to remove the output directory and its contents, it is used to ensure that the output directory is deleted before running the program again.
clean: 
	rm -rf  output
