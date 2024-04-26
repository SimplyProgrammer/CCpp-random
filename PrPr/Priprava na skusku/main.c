#include <stdio.h>
#include <stdlib.h>

#define toUpperCase(c) c & '_' // Napíšte definíciu makra na_velke(c). 

int printMatrix(int matrix[][3], int w, int h) 
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
			printf("%i ", matrix[y][x]);
		printf("\n");
	}
	printf("\n");
}

// 4.	Napíšte procedúru strdelete(char *s, int i, int n), ktorá vymaže z reťazca s, od pozície i (počítaná od 0) n znakov. Predpokladajte, že reťazec je dlhší ako n+i znakov. Reťazec s sa nesmie prealokovávať t.j. výsledný reťazec sa nachádza na tej istej adrese ako s.
#include <string.h>

void strdel(char* s, int i, int n) 
{
	for (; s[i + n]; i++)
		s[i] = s[i + n];
	s[i] = '\0';
}

// 2.	Napíšte funkciu minimum(), ktorá vráti minimálny prvok z prvkov, ktoré sa nachádzajú na oboch diagonálach štvorcovej matice NxN (premenná N je definovaná ako #define N 10).
#define N 3

int minimum(int matrix[][3]) 
{
	int min = matrix[0][0];
	for (int i = 1; i < N; i++)
		if (matrix[i][i] < min)
			min = matrix[i][i];

	for (int x = N-1, y = 0; x >= 0; x--, y++)
		if (matrix[y][x] < min)
			min = matrix[y][x];

	return min;
}

/*
	5.	Vysvetlite koncept štruktúr = Structura (struct) je nastroj na vytvaranie vlastnych zlozitych specifickych datovych typov. Jedna sa v podstate o "class" ktory ale sluzi len na ukladanie dat, zjadne construktory, ziadne metody ani ziadna logika...
		a.	(2b) ukážka definície štruktúry a vysvetlenie jednotlivých častí k čomu slúžia = Nizsie...
		b.	(2b) vysvetlenie na aký typ problémov sú vhodné štruktúry = Struktury nam ulahcuju pracu s velkymi datami, najme ich premiestnvanie. Predstav me si ze mame pracovat s informaciami o uzivateloch kde kazdy ma meno, prizvysko, vek, zaluby a dalsich 10 udajov,
		V takomto pripade je jednoduchsie si declarovat raz na zaciatku programu strukturu uzivatel a nasledne s datami o uzivateloch pracovat pomocou tejto struktury. Napr pri posielani uzivatelov do funkci nam postaci 1 argment zo struktrov co bude lahsie a rehladnejsie ako tucet jednotlivych attributov.
		Struktury su teda urcene na riesenie problemov kde sa pracuje s mnozstvom zlozitych ale rovnakych/podobnych dat...
*/

typedef // Definuje struc ako vlastny datovy typ, toto je dobre na to ze pri vytvarani premennych typu tejto struktury nemusime pred declaraciu premennej davat keyword struct ako modificator
struct // Keyword struct hovori ze sa jedna o structuru
Person // Nazov struktury
{
	// Member premenne struktury
	char* name;
	int age;
	double height;
} 
Person; // Nazov pod akym sa struktura bude pouzivat v kode...

typedef struct RecordNode {
	char ch;

	struct RecordNode* next;
} RecordNode;

/*
	7.	Vysvetli rozdiel statickej a dynamickej alokácie pamäte, uveď výhody a nevýhody, príklady a okomentuje ich.

	Staticka 									Dynamicka

1.	Je rychlejsia								Je pomalsia
2.	Stacke  									Heap
3.	Velkost udajov vopred znama					Velkost udajov nemusi byt vopred nutne znama
	je nutne ju hardcodenut
4.	Velkost udajov nemozno menit				Velkost udajov mozno menit za pochodu
	za pochodu (maju velkost aka bola zadana...)
5.	Udaje su ukladane v rade za sebou			Udaje su ukladane do nahodnych pametovych miest
6.	Velkost statickej pameti (stack)			Velkost dynamickej pameti (heap) sa moze podla potreby zvacsovat a zmensovat
	je fixne dana, nemenna
7.	Alokuje sa pomocou operatora = a hodnoty	Alokuje sa pomocou malloc(size), calloc(count, size) alebo realloc(pointer, newSize) a prisupuje sa k nej cez pointre
8.	Program ju dokaze po zbehnuti sam uvolnit	Je nutne manualne uvolnenie free

Pr: int nums[5];//Pocet prvkov vopred znamy		int count;//Pocet prvkov zadany z klavesnice...
	printf("Zadaj 5 cisel: ");					printf("Zadaj pocet prvkov: ");
	for (int i = 0; i < 5; i++)					scanf("%i", &count);
		scanf("%i", &nums[i]);					
												printf("Zadaj prvky:\n");
												int* nums = calloc(count, sizeof(int)); // Dynamicka alokácie pameti pre pole
												for (i = 0; i < count; i++)
													scanf("%i", &nums[i]);
												...
												free(nums); // Manualne uvolnenie pameti na konci programu
*/

/*
	8.	Napíšte procedúru nasledovnik(), ktorá pre každý prvok vstupného poľa vypíše prvý väčší prvok (písmeno), ktorý sa nachádza vpravo od neho (abecedne). Ak takýto prvok neexistuje, procedúra vypíše 'NaN'.
*/
void nasledovnik(char* str) //WTF toto zadanie...
{
	for (int i = 0; str[i]; i++)
		if (str[i] >= 'a' && str[i] < 'z')
			printf("%c", (char) (str[i]+1));
		else
			printf("%s", "NaN");
}

/*
	9.	Pomocou bitových operácií zistite počet jednotkových bitov v premennej x. Premenná x je typu unsigned int, funkcia jednotky ju dostane ako parameter.
*/
int countOf1(unsigned int x)
{
	int count = x & 1;
	for (int i = 1; i < sizeof(unsigned int)*8; i++)
		count += (x >> i) & 1;
	return count;
}

// Test pointer to stack return
int* pointerToStack()
{
	int val = 4;
	return &val;
}

/*
	10.	Vymenujte pamäťové triedy jazyka C

	Stack = Staticka pamet, fixna velkost, udaje za sebou, ich velkost (pocet bitov ktore zaberaju) nemozno menit...
	Heap = Dynamicka pamet, premenliva velkost, udaje nahodne, ich velkost mozno menit (realocovat), je nutne manualne uvolnenie...
	Static/Global = Pamet uchovavajuca staticke a globalne premenne...
	Prazdna pamet = pamet ktora je allocovane nasmu programu systemom no zatial nebola vyuzita...
	Pamet programu...
*/

/*
	11.	Definujte ukazovateľ na funkciu, ktorá nemá žiadny argument a vracia celé číslo.

	Rulo of thumb: return_type (*name_of_func_p)(type arg1, type arg2, ...args)

	int (*pointerToFunction)()
*/

/*
	12.	Definujte prototyp funkcie, ktorá dostane na vstupe ukazovateľ na pole celých čísel a vráti znak.

	char funkcia(int*);
*/

/*
	13.	Napíšte funkciu otoc_skupinu(Node *zaciatok,int k), ktorá v spájanom zozname otočí každých k prvkov. Funkcia vráti adresu počiatočného prvku otočeného spájaného zoznamu.
*/
RecordNode* reverseList(RecordNode* head, int k) 
{
	RecordNode* current = head, *prev = NULL, *next = NULL;
	for (int i = 0; current; i++)
	{
		next = current->next;
		if (i % k == 0)
			current->next = prev;

		prev = current;
		current = next;
	}

	return prev;
}

/*
	14.	Vysvetlite oddelený preklad
		a.	(2b) ukážka na príklade
		b.	(2b) vysvetlenie na aký typ úloh sa používa oddelený preklad a jeho porovnanie s obyčajným vkladaním súborov
		Odedelenny preklad je nastrojom modularizacie. Pri vacsich programoch nam umoznuje rozdelenie programu do viacerych podcasti (suborov) ktore sa nasledne pred kompilaciou nalinkuju na seba.
		Standardom je mat deklarovane header suboru ktore obsahuju iba strukturu kodu, teda veci ako protoypy funkcii, definicie datovych typov alebo macra. No nie logiku (zdrojovy kod), ta by mala byt separovana do zvlast C suborov.
		Alternativne tato logika moze byt definovana v uz skompilvanych externych kniziciach tj. .dll suboroch pricom header subor nam ju umozni pouzit...

*/

#include "utils.h"

int main() {
	// 1.	Napíšte a vysvetlite rôzne spôsoby definovania viacrozmerného poľa.
	int nums[2][3]; // Staticka declaracia s rozmermi

	int numsInit[2][3] = { // Staticka declaracia s rozmermi a inicializacio hodnoty prvkov
		{1, 2, 3},
		{4, 5, 6},
	};

	int numsMatrix[3][3] = { // Matrix-like staticka declaracia s rozmermi a inicializaciou, niesu tu nutne {} vnotrenych poly
		6, 2, 3,
		4, 5, 6,
		2, 1, 2
	};

	int** dynamicMatrix = calloc(2, sizeof(int*)); // Dynamicka deklaracia cez pointer a allocovanie pameti cez calloc
	for (int i = 0; i < 2; i++)
		dynamicMatrix[i] = calloc(3, sizeof(int));

	printMatrix(nums, 3, 2);
	printMatrix(numsInit, 3, 2);
	printMatrix(numsMatrix, 3, 2);

	printf("%i\n", minimum(numsMatrix));

	int* pole[5]; // 3.	Definujte premennú pole ako pole 5-tich ukazovateľov na typ int.

	char str[] = "hellowwww";

	int i = 2, n = 2;

	printf("%s\n", str);

	strdel(str, i, n);

	printf("%s\n", str);

	Person person; // 5. Declaracia
	person.name = "Ludmila";
	person.age = 20;
	person.height = 195.5;

	printf("Person[%s, %i, %g]\n", person.name, person.age, person.height);

	nasledovnik("abcdefgz");
	printf("\n");

	printf("Count of 1 bits: %i\n", countOf1(0b000111000)); //3

	//printf("Val of pointer from different scope: %i\n", *pointerToStack()); // Nope, nefunguje...

	printf("Min: %i\n", min(numsMatrix[0], 3));
}