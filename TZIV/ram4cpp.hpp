/**
 * License notice:
 * 	Author: https://github.com/SimplyProgrammer/Ram4Cpp
 * 	2024 - All rights reserved
 * 	You are forbidden to redistribute this software by other means than link above, or resounding it as your own in any other way!
 * 
 * This allows you to use Random Access Machine instructions in C++ program.
 * Your RAM program must start with _BEGIN(countOfRegs) and end with _END.
 * 
 * Syntax:
 * 	program: (instruction | labelDeclaration)*

 * 	instruction: mnemonic ' '+ (int | reg | label)
 * 	mnemonic: <any valid RAM instruction name in lowercase>
 * 	int: <positive integer>
 * 	reg: r [0-255]
 * 	label: <valid declared label>
 * 
 * 	labelDeclaration: <standard C label declaration>
 * 
 * Mem addressing:
 * 	Constant:	i	|	add 1	| Will add 1 to acc, =1 in RAM
 * 	Direct:		ri	|	add r1	| Will add add value of register 1 to acc, 1 in RAM
 * 	Indirect:	*ri	|	add *r1	| Will add add value of register with index of value stored in r1, *1 in RAM
 * 
 * Note that ; are optional but in some cases are required before or after label declaration...
 * Also note that if you need more than 255 registers (that are always allocated by default) then you have declare _BEGIN with bigger number than 255 and subsequently use r[i] to get the register.
 * 
 * How it works:
 * 	stdin acts as input tape where each "read" instruction will require you to type the value in to the console each separated by next line.
 * 	stdout acts as output where each "write" operation will print the requested value separated by comma.
 * 
 * 	Remember that every "well behaved" RAM program should halt at the end, this library can't really enforce that but still 1 exit code will be returned if program wasn't properly halted before ending.
*/

#pragma once

#include <iostream>

using namespace std;

typedef long long reg;
struct Reg
{
	reg value;

	void operator =(reg val)
	{
		value = val;
	}

	void operator +=(reg other)
	{
		value += other;
	}

	void operator -=(reg other)
	{
		value -= other;
	}

	void operator *=(reg other)
	{
		value *= other;
	}

	void operator /=(reg other)
	{
		value /= other;
	}

	void operator +=(Reg& other)
	{
		value += other.value;
	}

	void operator -=(Reg& other)
	{
		value -= other.value;
	}

	void operator *=(Reg& other)
	{
		value *= other.value;
	}

	void operator /=(Reg& other)
	{
		value /= other.value;
	}

	void operator >>(Reg& other) 
	{
		other.value = value;
	}

	friend ostream& operator <<(ostream& os, Reg& reg) 
	{
		os << reg.value;
		return os;
	}

	friend istream& operator >>(istream& is, Reg& reg) 
	{
		is >> reg.value;
		return is;
	}
};
typedef struct Reg Reg;

Reg* _r;

Reg& operator *(Reg self) // Indirect addressing
{
	return _r[self.value];
}

#ifndef HALT_MESSAGE
	#define HALT_MESSAGE "Halted!"
#endif

#ifndef OUT_SEPARATOR
	#define OUT_SEPARATOR ", "
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(OS_Windows)
	#ifndef WAIT_AFTER_HALT
		#define WAIT_AFTER_HALT cout << endl; system("pause");
	#endif
#else
	#ifndef WAIT_AFTER_HALT
		#define WAIT_AFTER_HALT cin.get(); cin.get();
	#endif
#endif

#define read ;cin >> 
#define write ;\
		if (countOfPrints++)\
			cout << OUT_SEPARATOR;\
		cout <<

#define jz ;if (r0.value == 0) goto
#define jzero jz

#define jgz ;if (r0.value > 0) goto
#define jgzero jgz

#define add ;r0 += 
#define sub ;r0 -= 
#define mul ;r0 *= 
#define div ;r0 /= 

#define load ;r0 = 
#define store ;r0 >> 

#define jump ;goto
#define jmp jump
#define halt ;statusCode = 0; goto __END;

#define _RAM_BEGIN(countOfRegs) {\
			unsigned int countOfPrints = 0, statusCode = 1;\
			Reg r[countOfRegs > 256 ? countOfRegs : 256] = {0};\
			_r = r;\
			Reg &r0 = r[0], &r1 = r[1], &r2 = r[2], &r3 = r[3], &r4 = r[4], &r5 = r[5], &r6 = r[6], &r7 = r[7], &r8 = r[8], &r9 = r[9], &r10 = r[10], &r11 = r[11], &r12 = r[12], &r13 = r[13], &r14 = r[14], &r15 = r[15], &r16 = r[16], &r17 = r[17], &r18 = r[18], &r19 = r[19], &r20 = r[20], &r21 = r[21], &r22 = r[22], &r23 = r[23], &r24 = r[24], &r25 = r[25], &r26 = r[26], &r27 = r[27], &r28 = r[28], &r29 = r[29], &r30 = r[30], &r31 = r[31], &r32 = r[32], &r33 = r[33], &r34 = r[34], &r35 = r[35], &r36 = r[36], &r37 = r[37], &r38 = r[38], &r39 = r[39], &r40 = r[40], &r41 = r[41], &r42 = r[42], &r43 = r[43], &r44 = r[44], &r45 = r[45], &r46 = r[46], &r47 = r[47], &r48 = r[48], &r49 = r[49], \
			&r50 = r[50], &r51 = r[51], &r52 = r[52], &r53 = r[53], &r54 = r[54], &r55 = r[55], &r56 = r[56], &r57 = r[57], &r58 = r[58], &r59 = r[59], &r60 = r[60], &r61 = r[61], &r62 = r[62], &r63 = r[63], &r64 = r[64], &r65 = r[65], &r66 = r[66], &r67 = r[67], &r68 = r[68], &r69 = r[69], &r70 = r[70], &r71 = r[71], &r72 = r[72], &r73 = r[73], &r74 = r[74], &r75 = r[75], &r76 = r[76], &r77 = r[77], &r78 = r[78], &r79 = r[79], &r80 = r[80], &r81 = r[81], &r82 = r[82], &r83 = r[83], &r84 = r[84], &r85 = r[85], &r86 = r[86], &r87 = r[87], &r88 = r[88], &r89 = r[89], &r90 = r[90], &r91 = r[91], &r92 = r[92], &r93 = r[93], &r94 = r[94], &r95 = r[95], &r96 = r[96], &r97 = r[97], &r98 = r[98], &r99 = r[99], \
			&r100 = r[100], &r101 = r[101], &r102 = r[102], &r103 = r[103], &r104 = r[104], &r105 = r[105], &r106 = r[106], &r107 = r[107], &r108 = r[108], &r109 = r[109], &r110 = r[110], &r111 = r[111], &r112 = r[112], &r113 = r[113], &r114 = r[114], &r115 = r[115], &r116 = r[116], &r117 = r[117], &r118 = r[118], &r119 = r[119], &r120 = r[120], &r121 = r[121], &r122 = r[122], &r123 = r[123], &r124 = r[124], &r125 = r[125], &r126 = r[126], &r127 = r[127], &r128 = r[128], &r129 = r[129], &r130 = r[130], &r131 = r[131], &r132 = r[132], &r133 = r[133], &r134 = r[134], &r135 = r[135], &r136 = r[136], &r137 = r[137], &r138 = r[138], &r139 = r[139], &r140 = r[140], &r141 = r[141], &r142 = r[142], &r143 = r[143], &r144 = r[144], &r145 = r[145], &r146 = r[146], &r147 = r[147], &r148 = r[148], &r149 = r[149], \
			&r150 = r[150], &r151 = r[151], &r152 = r[152], &r153 = r[153], &r154 = r[154], &r155 = r[155], &r156 = r[156], &r157 = r[157], &r158 = r[158], &r159 = r[159], &r160 = r[160], &r161 = r[161], &r162 = r[162], &r163 = r[163], &r164 = r[164], &r165 = r[165], &r166 = r[166], &r167 = r[167], &r168 = r[168], &r169 = r[169], &r170 = r[170], &r171 = r[171], &r172 = r[172], &r173 = r[173], &r174 = r[174], &r175 = r[175], &r176 = r[176], &r177 = r[177], &r178 = r[178], &r179 = r[179], &r180 = r[180], &r181 = r[181], &r182 = r[182], &r183 = r[183], &r184 = r[184], &r185 = r[185], &r186 = r[186], &r187 = r[187], &r188 = r[188], &r189 = r[189], &r190 = r[190], &r191 = r[191], &r192 = r[192], &r193 = r[193], &r194 = r[194], &r195 = r[195], &r196 = r[196], &r197 = r[197], &r198 = r[198], &r199 = r[199], \
			&r200 = r[200], &r201 = r[201], &r202 = r[202], &r203 = r[203], &r204 = r[204], &r205 = r[205], &r206 = r[206], &r207 = r[207], &r208 = r[208], &r209 = r[209], &r210 = r[210], &r211 = r[211], &r212 = r[212], &r213 = r[213], &r214 = r[214], &r215 = r[215], &r216 = r[216], &r217 = r[217], &r218 = r[218], &r219 = r[219], &r220 = r[220], &r221 = r[221], &r222 = r[222], &r223 = r[223], &r224 = r[224], &r225 = r[225], &r226 = r[226], &r227 = r[227], &r228 = r[228], &r229 = r[229], &r230 = r[230], &r231 = r[231], &r232 = r[232], &r233 = r[233], &r234 = r[234], &r235 = r[235], &r236 = r[236], &r237 = r[237], &r238 = r[238], &r239 = r[239], &r240 = r[240], &r241 = r[241], &r242 = r[242], &r243 = r[243], &r244 = r[244], &r245 = r[245], &r246 = r[246], &r247 = r[247], &r248 = r[248], &r249 = r[249], \
			&r250 = r[250], &r251 = r[251], &r252 = r[252], &r253 = r[253], &r254 = r[254], &r255 = r[255];\

#define _RAM_END ;\
			__END:\
			if (statusCode == 0) {\
				if (countOfPrints++)\
					cout << endl;\
				cout << HALT_MESSAGE;\
			}\
			WAIT_AFTER_HALT\
			return statusCode;}

/* #include <iostream>

using namespace std;

int main() {
	cout << "Reg ";
	for (int i = 0; i <= 1000; i++)
	{
		if (i && i % 50 == 0)
			cout << "\\" << endl;
		cout << "&r" << i << " = " << "r[" << i << "], ";
	}
}
*/