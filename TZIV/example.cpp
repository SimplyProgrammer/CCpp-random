/**
 * This example will load specified amount of numbers from input and then output the sum and integer avg of these numbers!
*/

#include "ram4cpp.hpp"
_BEGIN(-1) // -1 will default to 255 registers

read r101 // Count of numbers to load
load r101
jz end

load 1
store r100; // Iteration index

loadNext:
	read *r100
	load r100
	add 1 // r100++
	store r100

	sub r101
	jgz calcSum
	jmp loadNext;

calcSum:
	load 1
	store r100;

	sumLoop:
		load r102
		add *r100
		store r102

		load r100
		add 1
		store r100

		sub r101
		jgz end
		jmp sumLoop;

end:
write r102 // The result (sum)
load r102
div r101
write r0 // Avg...

halt

_END