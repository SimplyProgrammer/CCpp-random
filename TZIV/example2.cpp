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
	sub 1 // r1 -= 1 | l(N-i) + l(1)
	store r1
	jz end
	mul r2 
	store r2 // r2 = (r1-1)*r2
	jmp loop;

end:
write r2

halt
_RAM_END

/*
#include "ram4cpp.hpp"
int main() _RAM_BEGIN(-1) // -1 will default to 255 registers

read r1 // N

read r2 // K
load r2
store r3; // r3 = r2 (input K)

loop:
	load r2
	sub 1 // r2 -= 1 | l(K-i) + l(1)
	store r2
	jz end
	mul r3
	store r3 // r3 = (r2-1)*r3
	jmp loop;

end:
load r1
mul r3
write r0

halt
_RAM_END
*/