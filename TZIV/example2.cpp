/**
 * Example 2
 * N Factorial
*/

#include "ram4cpp.hpp"
int main() _RAM_BEGIN(-1) // -1 will default to 255 registers

read r1 // N
load r1

store r2; // r2 = r1 (input N)

loop:
	load r1
	sub 1 // r1 -= 1
	store r1
	jz end
	mul r2 
	store r2 // r2 = (r1-1)*r2
	jmp loop;

end:
write r2

halt
_RAM_END