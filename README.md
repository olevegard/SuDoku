============================== SuDoku ==============================

A ( for now ) simple SuDoku solver that uses human logics instead of brue force.
It will only be able to solve SuDoku boards that have only one solution. 
The current version is able to solve most SuDokus withinn 1 ms  if running with optimization.

Solving SuDokus

	The solver works by adding possibilities into the struct cell. The board itself is held by
	a 2D array of shorts ( 0 = unsolved. ) Whenever you insert a digit to a cell, the validity
	of the move is checked. If the move is valid, the digit is added, the Cell structs are
	updated ( set as solved ) and that digit is remove from any cells in that 

	NOTE: There is a conflict between the 2d array of shorts and the 2D array of Cells:
	The 2D array of shorts range from 1-9, whereas the Cells from 0-9. The plan is to change
	the 2D array of shorts to 0-9 or remove it completely ( all information is stored in the
	Cells anyway. ) Both solutions will require work, but they are necesseary.

	Techniques ( see http://www.sudokuwiki.org/sudoku.htm for info and a similar, working solver ) 
		-Checks for cells with only 1 possiblily ( some work needed )
		-Checks for rows/columns/3*3-swuare with only one possiblity( work needed, should use Cells ) 
		-Checks for naked pairs ( not sure if implemented for all three ways ) 
		-Checks for naked triples ( not for 3*3 square ) 
		-Checks for naked quads ( to be done ) 
		-Checks for hidden pairs ( not sure if implemented for all three ways ) 
		-Checks for hidden triples ( to be done ) 
		-Checks for hidden quads ( to be done ) 
		-Checks for pointing pairs ( square->row and square->column)
		-Checks for XWing ( row only )


Compilation:
I personally use g++ with the following flags
-Werror
-Wall
-Weffc
-Wextra
-pedantic
	This flags all adds warnings ( -Werror turns warnings into errors. ) 
	This helps detecting logical errors and it tells you about unused/uninitialized variables.
	The Werror flag "forces" you to fix any warnings
-lrt
-std=c++0x
	Needed for some features

Full compiler string
	g++ main.cpp Board.cpp -Wall -Werror -Wextra -Weffc++ -pedantic -lrt -o SuDoku -std=c++0x 
