/**
 * Author: https://github.com/SimplyProgrammer
 * 2024 - All rights reserved
 * 
 * Allow you to use Random Access Machine instructions in C++ program.
 * Your RAM program must start with _BEGIN and end with _END.
 * 
 * Syntax:
 * 	program: (instruction | labelDeclaration)*

 * 	instruction: mnemonic ' '+ (int | reg | label)
 * 	mnemonic: <any valid RAM instruction name in lowercase>
 * 	int: <positive integer>
 * 	reg: r [0-999]
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

	friend std::ostream& operator <<(std::ostream& os, Reg& reg) 
	{
		os << reg.value;
		return os;
	}

	friend std::istream& operator >>(std::istream& is, Reg& reg) 
	{
		is >> reg.value;
		return is;
	}
};
typedef struct Reg Reg;

Reg r0; // acc

Reg& operator *(Reg self) // Indirect addressing
{
	return (&r0)[self.value];
}

#if !defined(HALT_MESSAGE)
	#define HALT_MESSAGE "Halted!"
#endif

#define read ;cin >> 
#define write ;\
		if (countOfPrints++)\
			cout << ", ";\
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

#define _BEGIN int main() {\
			unsigned int countOfPrints = 0, statusCode = 1;\
			r0 = {0};\
			Reg r1 = {0}, r2 = {0}, r3 = {0}, r4 = {0}, r5 = {0}, r6 = {0}, r7 = {0}, r8 = {0}, r9 = {0}, r10 = {0}, r11 = {0}, r12 = {0}, r13 = {0}, r14 = {0}, r15 = {0}, r16 = {0}, r17 = {0}, r18 = {0}, r19 = {0}, r20 = {0}, r21 = {0}, r22 = {0}, r23 = {0}, r24 = {0}, r25 = {0}, r26 = {0}, r27 = {0}, r28 = {0}, r29 = {0}, r30 = {0}, r31 = {0}, r32 = {0}, r33 = {0},\
			r34 = {0}, r35 = {0}, r36 = {0}, r37 = {0}, r38 = {0}, r39 = {0}, r40 = {0}, r41 = {0}, r42 = {0}, r43 = {0}, r44 = {0}, r45 = {0}, r46 = {0}, r47 = {0}, r48 = {0}, r49 = {0},\
			r50 = {0}, r51 = {0}, r52 = {0}, r53 = {0}, r54 = {0}, r55 = {0}, r56 = {0}, r57 = {0}, r58 = {0}, r59 = {0}, r60 = {0}, r61 = {0}, r62 = {0}, r63 = {0}, r64 = {0}, r65 = {0}, r66 = {0}, r67 = {0}, r68 = {0}, r69 = {0}, r70 = {0}, r71 = {0}, r72 = {0}, r73 = {0}, r74 = {0}, r75 = {0}, r76 = {0}, r77 = {0}, r78 = {0}, r79 = {0}, r80 = {0}, r81 = {0}, r82 = {0}, r83 = {0}, r84 = {0}, r85 = {0}, r86 = {0}, r87 = {0}, r88 = {0}, r89 = {0}, r90 = {0}, r91 = {0}, r92 = {0}, r93 = {0}, r94 = {0}, r95 = {0}, r96 = {0}, r97 = {0}, r98 = {0}, r99 = {0},\
			r100 = {0}, r101 = {0}, r102 = {0}, r103 = {0}, r104 = {0}, r105 = {0}, r106 = {0}, r107 = {0}, r108 = {0}, r109 = {0}, r110 = {0}, r111 = {0}, r112 = {0}, r113 = {0}, r114 = {0}, r115 = {0}, r116 = {0}, r117 = {0}, r118 = {0}, r119 = {0}, r120 = {0}, r121 = {0}, r122 = {0}, r123 = {0}, r124 = {0}, r125 = {0}, r126 = {0}, r127 = {0}, r128 = {0}, r129 = {0}, r130 = {0}, r131 = {0}, r132 = {0}, r133 = {0}, r134 = {0}, r135 = {0}, r136 = {0}, r137 = {0}, r138 = {0}, r139 = {0}, r140 = {0}, r141 = {0}, r142 = {0}, r143 = {0}, r144 = {0}, r145 = {0}, r146 = {0}, r147 = {0}, r148 = {0}, r149 = {0},\
			r150 = {0}, r151 = {0}, r152 = {0}, r153 = {0}, r154 = {0}, r155 = {0}, r156 = {0}, r157 = {0}, r158 = {0}, r159 = {0}, r160 = {0}, r161 = {0}, r162 = {0}, r163 = {0}, r164 = {0}, r165 = {0}, r166 = {0}, r167 = {0}, r168 = {0}, r169 = {0}, r170 = {0}, r171 = {0}, r172 = {0}, r173 = {0}, r174 = {0}, r175 = {0}, r176 = {0}, r177 = {0}, r178 = {0}, r179 = {0}, r180 = {0}, r181 = {0}, r182 = {0}, r183 = {0}, r184 = {0}, r185 = {0}, r186 = {0}, r187 = {0}, r188 = {0}, r189 = {0}, r190 = {0}, r191 = {0}, r192 = {0}, r193 = {0}, r194 = {0}, r195 = {0}, r196 = {0}, r197 = {0}, r198 = {0}, r199 = {0},\
			r200 = {0}, r201 = {0}, r202 = {0}, r203 = {0}, r204 = {0}, r205 = {0}, r206 = {0}, r207 = {0}, r208 = {0}, r209 = {0}, r210 = {0}, r211 = {0}, r212 = {0}, r213 = {0}, r214 = {0}, r215 = {0}, r216 = {0}, r217 = {0}, r218 = {0}, r219 = {0}, r220 = {0}, r221 = {0}, r222 = {0}, r223 = {0}, r224 = {0}, r225 = {0}, r226 = {0}, r227 = {0}, r228 = {0}, r229 = {0}, r230 = {0}, r231 = {0}, r232 = {0}, r233 = {0}, r234 = {0}, r235 = {0}, r236 = {0}, r237 = {0}, r238 = {0}, r239 = {0}, r240 = {0}, r241 = {0}, r242 = {0}, r243 = {0}, r244 = {0}, r245 = {0}, r246 = {0}, r247 = {0}, r248 = {0}, r249 = {0},\
			r250 = {0}, r251 = {0}, r252 = {0}, r253 = {0}, r254 = {0}, r255 = {0}, r256 = {0}, r257 = {0}, r258 = {0}, r259 = {0}, r260 = {0}, r261 = {0}, r262 = {0}, r263 = {0}, r264 = {0}, r265 = {0}, r266 = {0}, r267 = {0}, r268 = {0}, r269 = {0}, r270 = {0}, r271 = {0}, r272 = {0}, r273 = {0}, r274 = {0}, r275 = {0}, r276 = {0}, r277 = {0}, r278 = {0}, r279 = {0}, r280 = {0}, r281 = {0}, r282 = {0}, r283 = {0}, r284 = {0}, r285 = {0}, r286 = {0}, r287 = {0}, r288 = {0}, r289 = {0}, r290 = {0}, r291 = {0}, r292 = {0}, r293 = {0}, r294 = {0}, r295 = {0}, r296 = {0}, r297 = {0}, r298 = {0}, r299 = {0},\
			r300 = {0}, r301 = {0}, r302 = {0}, r303 = {0}, r304 = {0}, r305 = {0}, r306 = {0}, r307 = {0}, r308 = {0}, r309 = {0}, r310 = {0}, r311 = {0}, r312 = {0}, r313 = {0}, r314 = {0}, r315 = {0}, r316 = {0}, r317 = {0}, r318 = {0}, r319 = {0}, r320 = {0}, r321 = {0}, r322 = {0}, r323 = {0}, r324 = {0}, r325 = {0}, r326 = {0}, r327 = {0}, r328 = {0}, r329 = {0}, r330 = {0}, r331 = {0}, r332 = {0}, r333 = {0}, r334 = {0}, r335 = {0}, r336 = {0}, r337 = {0}, r338 = {0}, r339 = {0}, r340 = {0}, r341 = {0}, r342 = {0}, r343 = {0}, r344 = {0}, r345 = {0}, r346 = {0}, r347 = {0}, r348 = {0}, r349 = {0},\
			r350 = {0}, r351 = {0}, r352 = {0}, r353 = {0}, r354 = {0}, r355 = {0}, r356 = {0}, r357 = {0}, r358 = {0}, r359 = {0}, r360 = {0}, r361 = {0}, r362 = {0}, r363 = {0}, r364 = {0}, r365 = {0}, r366 = {0}, r367 = {0}, r368 = {0}, r369 = {0}, r370 = {0}, r371 = {0}, r372 = {0}, r373 = {0}, r374 = {0}, r375 = {0}, r376 = {0}, r377 = {0}, r378 = {0}, r379 = {0}, r380 = {0}, r381 = {0}, r382 = {0}, r383 = {0}, r384 = {0}, r385 = {0}, r386 = {0}, r387 = {0}, r388 = {0}, r389 = {0}, r390 = {0}, r391 = {0}, r392 = {0}, r393 = {0}, r394 = {0}, r395 = {0}, r396 = {0}, r397 = {0}, r398 = {0}, r399 = {0},\
			r400 = {0}, r401 = {0}, r402 = {0}, r403 = {0}, r404 = {0}, r405 = {0}, r406 = {0}, r407 = {0}, r408 = {0}, r409 = {0}, r410 = {0}, r411 = {0}, r412 = {0}, r413 = {0}, r414 = {0}, r415 = {0}, r416 = {0}, r417 = {0}, r418 = {0}, r419 = {0}, r420 = {0}, r421 = {0}, r422 = {0}, r423 = {0}, r424 = {0}, r425 = {0}, r426 = {0}, r427 = {0}, r428 = {0}, r429 = {0}, r430 = {0}, r431 = {0}, r432 = {0}, r433 = {0}, r434 = {0}, r435 = {0}, r436 = {0}, r437 = {0}, r438 = {0}, r439 = {0}, r440 = {0}, r441 = {0}, r442 = {0}, r443 = {0}, r444 = {0}, r445 = {0}, r446 = {0}, r447 = {0}, r448 = {0}, r449 = {0},\
			r450 = {0}, r451 = {0}, r452 = {0}, r453 = {0}, r454 = {0}, r455 = {0}, r456 = {0}, r457 = {0}, r458 = {0}, r459 = {0}, r460 = {0}, r461 = {0}, r462 = {0}, r463 = {0}, r464 = {0}, r465 = {0}, r466 = {0}, r467 = {0}, r468 = {0}, r469 = {0}, r470 = {0}, r471 = {0}, r472 = {0}, r473 = {0}, r474 = {0}, r475 = {0}, r476 = {0}, r477 = {0}, r478 = {0}, r479 = {0}, r480 = {0}, r481 = {0}, r482 = {0}, r483 = {0}, r484 = {0}, r485 = {0}, r486 = {0}, r487 = {0}, r488 = {0}, r489 = {0}, r490 = {0}, r491 = {0}, r492 = {0}, r493 = {0}, r494 = {0}, r495 = {0}, r496 = {0}, r497 = {0}, r498 = {0}, r499 = {0},\
			r500 = {0}, r501 = {0}, r502 = {0}, r503 = {0}, r504 = {0}, r505 = {0}, r506 = {0}, r507 = {0}, r508 = {0}, r509 = {0}, r510 = {0}, r511 = {0}, r512 = {0}, r513 = {0}, r514 = {0}, r515 = {0}, r516 = {0}, r517 = {0}, r518 = {0}, r519 = {0}, r520 = {0}, r521 = {0}, r522 = {0}, r523 = {0}, r524 = {0}, r525 = {0}, r526 = {0}, r527 = {0}, r528 = {0}, r529 = {0}, r530 = {0}, r531 = {0}, r532 = {0}, r533 = {0}, r534 = {0}, r535 = {0}, r536 = {0}, r537 = {0}, r538 = {0}, r539 = {0}, r540 = {0}, r541 = {0}, r542 = {0}, r543 = {0}, r544 = {0}, r545 = {0}, r546 = {0}, r547 = {0}, r548 = {0}, r549 = {0},\
			r550 = {0}, r551 = {0}, r552 = {0}, r553 = {0}, r554 = {0}, r555 = {0}, r556 = {0}, r557 = {0}, r558 = {0}, r559 = {0}, r560 = {0}, r561 = {0}, r562 = {0}, r563 = {0}, r564 = {0}, r565 = {0}, r566 = {0}, r567 = {0}, r568 = {0}, r569 = {0}, r570 = {0}, r571 = {0}, r572 = {0}, r573 = {0}, r574 = {0}, r575 = {0}, r576 = {0}, r577 = {0}, r578 = {0}, r579 = {0}, r580 = {0}, r581 = {0}, r582 = {0}, r583 = {0}, r584 = {0}, r585 = {0}, r586 = {0}, r587 = {0}, r588 = {0}, r589 = {0}, r590 = {0}, r591 = {0}, r592 = {0}, r593 = {0}, r594 = {0}, r595 = {0}, r596 = {0}, r597 = {0}, r598 = {0}, r599 = {0},\
			r600 = {0}, r601 = {0}, r602 = {0}, r603 = {0}, r604 = {0}, r605 = {0}, r606 = {0}, r607 = {0}, r608 = {0}, r609 = {0}, r610 = {0}, r611 = {0}, r612 = {0}, r613 = {0}, r614 = {0}, r615 = {0}, r616 = {0}, r617 = {0}, r618 = {0}, r619 = {0}, r620 = {0}, r621 = {0}, r622 = {0}, r623 = {0}, r624 = {0}, r625 = {0}, r626 = {0}, r627 = {0}, r628 = {0}, r629 = {0}, r630 = {0}, r631 = {0}, r632 = {0}, r633 = {0}, r634 = {0}, r635 = {0}, r636 = {0}, r637 = {0}, r638 = {0}, r639 = {0}, r640 = {0}, r641 = {0}, r642 = {0}, r643 = {0}, r644 = {0}, r645 = {0}, r646 = {0}, r647 = {0}, r648 = {0}, r649 = {0},\
			r650 = {0}, r651 = {0}, r652 = {0}, r653 = {0}, r654 = {0}, r655 = {0}, r656 = {0}, r657 = {0}, r658 = {0}, r659 = {0}, r660 = {0}, r661 = {0}, r662 = {0}, r663 = {0}, r664 = {0}, r665 = {0}, r666 = {0}, r667 = {0}, r668 = {0}, r669 = {0}, r670 = {0}, r671 = {0}, r672 = {0}, r673 = {0}, r674 = {0}, r675 = {0}, r676 = {0}, r677 = {0}, r678 = {0}, r679 = {0}, r680 = {0}, r681 = {0}, r682 = {0}, r683 = {0}, r684 = {0}, r685 = {0}, r686 = {0}, r687 = {0}, r688 = {0}, r689 = {0}, r690 = {0}, r691 = {0}, r692 = {0}, r693 = {0}, r694 = {0}, r695 = {0}, r696 = {0}, r697 = {0}, r698 = {0}, r699 = {0},\
			r700 = {0}, r701 = {0}, r702 = {0}, r703 = {0}, r704 = {0}, r705 = {0}, r706 = {0}, r707 = {0}, r708 = {0}, r709 = {0}, r710 = {0}, r711 = {0}, r712 = {0}, r713 = {0}, r714 = {0}, r715 = {0}, r716 = {0}, r717 = {0}, r718 = {0}, r719 = {0}, r720 = {0}, r721 = {0}, r722 = {0}, r723 = {0}, r724 = {0}, r725 = {0}, r726 = {0}, r727 = {0}, r728 = {0}, r729 = {0}, r730 = {0}, r731 = {0}, r732 = {0}, r733 = {0}, r734 = {0}, r735 = {0}, r736 = {0}, r737 = {0}, r738 = {0}, r739 = {0}, r740 = {0}, r741 = {0}, r742 = {0}, r743 = {0}, r744 = {0}, r745 = {0}, r746 = {0}, r747 = {0}, r748 = {0}, r749 = {0},\
			r750 = {0}, r751 = {0}, r752 = {0}, r753 = {0}, r754 = {0}, r755 = {0}, r756 = {0}, r757 = {0}, r758 = {0}, r759 = {0}, r760 = {0}, r761 = {0}, r762 = {0}, r763 = {0}, r764 = {0}, r765 = {0}, r766 = {0}, r767 = {0}, r768 = {0}, r769 = {0}, r770 = {0}, r771 = {0}, r772 = {0}, r773 = {0}, r774 = {0}, r775 = {0}, r776 = {0}, r777 = {0}, r778 = {0}, r779 = {0}, r780 = {0}, r781 = {0}, r782 = {0}, r783 = {0}, r784 = {0}, r785 = {0}, r786 = {0}, r787 = {0}, r788 = {0}, r789 = {0}, r790 = {0}, r791 = {0}, r792 = {0}, r793 = {0}, r794 = {0}, r795 = {0}, r796 = {0}, r797 = {0}, r798 = {0}, r799 = {0},\
			r800 = {0}, r801 = {0}, r802 = {0}, r803 = {0}, r804 = {0}, r805 = {0}, r806 = {0}, r807 = {0}, r808 = {0}, r809 = {0}, r810 = {0}, r811 = {0}, r812 = {0}, r813 = {0}, r814 = {0}, r815 = {0}, r816 = {0}, r817 = {0}, r818 = {0}, r819 = {0}, r820 = {0}, r821 = {0}, r822 = {0}, r823 = {0}, r824 = {0}, r825 = {0}, r826 = {0}, r827 = {0}, r828 = {0}, r829 = {0}, r830 = {0}, r831 = {0}, r832 = {0}, r833 = {0}, r834 = {0}, r835 = {0}, r836 = {0}, r837 = {0}, r838 = {0}, r839 = {0}, r840 = {0}, r841 = {0}, r842 = {0}, r843 = {0}, r844 = {0}, r845 = {0}, r846 = {0}, r847 = {0}, r848 = {0}, r849 = {0},\
			r850 = {0}, r851 = {0}, r852 = {0}, r853 = {0}, r854 = {0}, r855 = {0}, r856 = {0}, r857 = {0}, r858 = {0}, r859 = {0}, r860 = {0}, r861 = {0}, r862 = {0}, r863 = {0}, r864 = {0}, r865 = {0}, r866 = {0}, r867 = {0}, r868 = {0}, r869 = {0}, r870 = {0}, r871 = {0}, r872 = {0}, r873 = {0}, r874 = {0}, r875 = {0}, r876 = {0}, r877 = {0}, r878 = {0}, r879 = {0}, r880 = {0}, r881 = {0}, r882 = {0}, r883 = {0}, r884 = {0}, r885 = {0}, r886 = {0}, r887 = {0}, r888 = {0}, r889 = {0}, r890 = {0}, r891 = {0}, r892 = {0}, r893 = {0}, r894 = {0}, r895 = {0}, r896 = {0}, r897 = {0}, r898 = {0}, r899 = {0},\
			r900 = {0}, r901 = {0}, r902 = {0}, r903 = {0}, r904 = {0}, r905 = {0}, r906 = {0}, r907 = {0}, r908 = {0}, r909 = {0}, r910 = {0}, r911 = {0}, r912 = {0}, r913 = {0}, r914 = {0}, r915 = {0}, r916 = {0}, r917 = {0}, r918 = {0}, r919 = {0}, r920 = {0}, r921 = {0}, r922 = {0}, r923 = {0}, r924 = {0}, r925 = {0}, r926 = {0}, r927 = {0}, r928 = {0}, r929 = {0}, r930 = {0}, r931 = {0}, r932 = {0}, r933 = {0}, r934 = {0}, r935 = {0}, r936 = {0}, r937 = {0}, r938 = {0}, r939 = {0}, r940 = {0}, r941 = {0}, r942 = {0}, r943 = {0}, r944 = {0}, r945 = {0}, r946 = {0}, r947 = {0}, r948 = {0}, r949 = {0},\
			r950 = {0}, r951 = {0}, r952 = {0}, r953 = {0}, r954 = {0}, r955 = {0}, r956 = {0}, r957 = {0}, r958 = {0}, r959 = {0}, r960 = {0}, r961 = {0}, r962 = {0}, r963 = {0}, r964 = {0}, r965 = {0}, r966 = {0}, r967 = {0}, r968 = {0}, r969 = {0}, r970 = {0}, r971 = {0}, r972 = {0}, r973 = {0}, r974 = {0}, r975 = {0}, r976 = {0}, r977 = {0}, r978 = {0}, r979 = {0}, r980 = {0}, r981 = {0}, r982 = {0}, r983 = {0}, r984 = {0}, r985 = {0}, r986 = {0}, r987 = {0}, r988 = {0}, r989 = {0}, r990 = {0}, r991 = {0}, r992 = {0}, r993 = {0}, r994 = {0}, r995 = {0}, r996 = {0}, r997 = {0}, r998 = {0};

#define _END ;\
			__END:\
			if (statusCode == 0) {\
				if (countOfPrints++)\
					cout << endl;\
				cout << HALT_MESSAGE;\
			}\
			cin.get();\
			cin.get();\
			return statusCode;}