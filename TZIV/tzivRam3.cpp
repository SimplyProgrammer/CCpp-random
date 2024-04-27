// xhupkap

#include "ram4cpp.hpp"
_BEGIN

read r1
load r1

jz end // Check 0 and end

load 1 // Init r2,r3 to =1
store r2
store r3;

mainLoop:
	load r2
	sub r3 // Sub r3 to bring it down for compare
	jgz pow6 // if r2 > r3 goto pow6 else pow3
	jmp pow3;

	pow6:
		load r3
		sub 1
		jz noPrintPow6 // Dont print if r3 == 1

		write r3;

		noPrintPow6:
		load r3
		mul 6 // r3 *= 6
		store r3;

	pow3:
		write r2

		load r2
		mul 3 // r2 *= 3
		store r2;

	condition:
	load r2
	sub r1 // Sub input to bring it down for compare
	jgz end // End if r2 > input (r1)

	load r3
	sub r1 // Sub input to bring it down for compare
	jgz end // End if r3 > input (r1)

jmp mainLoop;

end:
halt

_END

/*
// C++ representation...
int main() 
{
	int r1; // Input
	cin >> r1;

	int r2 = 1, r3 = 1; // pow3 , pow6

	mainLoop:
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

		condition:
		if (r2 > r1)
			goto end;
		if (r3 > r1)
			goto end;

	goto mainLoop;

	end:
	cout << endl;
}
*/