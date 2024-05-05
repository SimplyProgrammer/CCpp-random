// xhupkap

#include "ram4cpp.hpp"
#include <math.h>
int main() _RAM_BEGIN(4) // We need 4 registers (including acc)
int r2count = 0, r3count = 0, r3multCount = 0, r2condCount = 0, r3condCountLoop = 0, r3condCountEnd = 0, loopCount = 0, guess = 1;

read r1
load r1

jgz program // End if input is 0 or less else proceed to program
jmp end;

program:
load 1 // Init r2,r3 to =1
store r2
store r3;

loop:
	guess &= r2.value == pow(3, r2count);
	guess &= r3.value == pow(6, r3multCount);
	load r2
	sub r3; // Sub r3 to bring it down for compare
	loopCount++;
	jgz pow6; // if r2 > r3 goto pow6 else pow3
	jmp pow3;

	pow6:
		load r3
		sub 1
		jz noPrintPow6 // Dont print (mult only) if r3 == 1

		write r3;
		r3count++;

		noPrintPow6:
		load r3
		mul 6 // r3 *= 6
		store r3;
		r3multCount++;

		jmp condition;

	pow3:
		write r2;
		r2count++

		load r2
		mul 3 // r2 *= 3p
		store r2;

	condition: // if (r2 > r1 && r3 > r1) goto end else loop
		load r2
		sub r1; // Sub input to bring it down for compare
		r2condCount++;
		jgz secondCheck;
		jmp loop;

		secondCheck:
		load r3
		sub r1; // Sub input to bring it down for compare
		r3condCountEnd++;
		jgz end; // End if r3 > input (r1)
		r3condCountLoop++;
		jmp loop;

end:
printf("\n\t%i: %i %i %i | %i %i %i | %i", loopCount, r2count, r3count, r3multCount, /**/ r2condCount, r3condCountEnd, r3condCountLoop /**/, guess);
halt

_RAM_END


// C++ pseudocode representation...
/*
int main() 
{
	int r1; // Input
	cin >> r1;

	if (r1 > 0)
		goto program;
	goto end;

	program:
	int r2 = 1, r3 = 1; // pow3 , pow6

	loop:
		if (r2 > r3)
			goto pow6;
		goto pow3;

		pow6:
			if (r3 == 1)
				goto noPrintPow6;
			cout << r3 << " ";
			noPrintPow6:
			r3 *= 6;
			goto condition;

		pow3:
			cout << r2 << " ";
			r2 *= 3;

		condition: // r2 > r1 && r3 >r1
		if (r2 > r1)
			goto secondCheck;
		goto loop;

		secondCheck: 
		if (r3 > r1)
			goto end;

	goto loop;

	end:
	cout << endl;
}
*/