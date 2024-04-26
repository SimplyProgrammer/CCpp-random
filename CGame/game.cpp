#include <iostream>
#include <string>
#include <fstream>
#include <io.h> // _access and thats all

#include <windows.h> // for real time key input...

using namespace std;

// Ansi magic...
#define C_RGB(r, g, b) cout << "\x1b[38;2;" << (r) << ";" << (g) << ";" << (b) << "m"
#define C_RESET cout << "\x1B[0m"

#define U cout << "\033[4m"
#define U_RESET cout << "\033[0m\n"

#define renderAt(x, y, str) cout << "\033[" << (y)+1 << ";" << (x)+1 << "H" << (str)

#define isKeyDown(key) GetAsyncKeyState(key) & 0x8000

#define offsetAreaAsArgs(x, y, offset) (x) - (offset), (y) - (offset), (x) + (offset) + 1, (y) + (offset) + 1 //x- y- x+ y+

#define clamp(x, min, max) (x) < (min) ? (min) : (x) > (max) ? (max) : (x)

typedef struct
{
	int plyX, plyY, tick, width, height;
	short doRerender, hasKey, endState;
	char** map;
} Game;

void delete2D(void*** array, int rows) 
{
	for (int i = 0; i < rows; i++)
		delete[] (*array)[i];
	delete[](*array);
	*array = NULL;
}

void renderRect(int, int, int, int, string, string, string);
int openWindow(int, int, string menuOptions[], int, string);

void startGame(Game*, string);
void saveGame(Game*, string);
void renderMap(Game*, int, int, int, int);
void player(Game*);
void updateReavers(Game*);

int main() 
{
	Game gm = {0};
	printf("\e[?25l"); // Hide cursor

	mainMenu: string menuOptions[4] = {"New game", gm.map || _access("save.txt", 0) == 0 ? "Continue" : "\n" , "\n", "Quit"};
	switch (openWindow(0, 0, menuOptions, 4, "ONES AND ZEROS"))
	{
		case 0:
			startG: startGame(&gm, "map.txt"); 
			break;
		case 1:
			if (!gm.map)
			{
				startGame(&gm, "save.txt"); 
				break;
			}

			gm.doRerender = 1;
			break;

		default: 
			goto end;
	}
	
	gameLoop: while (!gm.endState) // Game loop
	{
		if (isKeyDown(VK_CONTROL) && isKeyDown('R') && gm.tick % 5 == 0)
			gm.doRerender = 1;

		if (isKeyDown(VK_ESCAPE))
			goto mainMenu;

		if (gm.doRerender) // Do hard refresh/rerender
		{
			system("cls");

			renderMap(&gm, 0, 0, -1, -1);
			gm.doRerender = 0;
		}

		if (gm.tick % 23 == 0)
			updateReavers(&gm);

		player(&gm);

		gm.tick++;
		Sleep(1);
	}

	Sleep(500);

	if (gm.endState == 1)
	{
		remove("save.txt");

		string menuOptions[2] = {"Retry", "Quit"};
		if (openWindow(0, 0, menuOptions, 2, "You have been NULLIFIED!") == 0)
			goto startG;
	}
	else if (gm.endState == 2)
	{
		renderAt(0, 0, "You have been realocated!\n");
	}

	end: Sleep(500);

	system("cls");

	if (!gm.endState && gm.map)
		saveGame(&gm, "save.txt");
	delete2D((void***) &gm.map, gm.height);
}

// UI

void renderRect(int x, int y, int w, int h, string edge, string vertWall, string horWall)
{
	for (int iy = 0; iy < h; iy++)
	{
		if (iy == 0 || iy == h - 1)
			for (int ix = 0; ix < w; ix++)
				renderAt(x + ix, y + iy, ix == 0 || ix == w - 1 ? edge : horWall);
		else
		{
			renderAt(x, y + iy, vertWall);
			renderAt(x + w - 1, y + iy, vertWall);
		}
	}
}

int openWindow(int x, int y, string menuOptions[], int optionsCount, string title)
{
	x++;
	y++;

	int w = title.length() + 1;
	int h = optionsCount + 3;

	system("cls");
	renderRect(x - 1, y - 1, w + 1, h + 1, "#", "|", "-"); // Windows border

	renderAt(x, y, title);

	y += 2;
	x++;

	for (int option = 0, wasRendered = 0;;)
	{
		int step = isKeyDown(VK_UP) ? -1 : (isKeyDown(VK_DOWN) ? 1 : 0);
		if (step == 0 && wasRendered)
		{
			if (isKeyDown(VK_ESCAPE))
				return optionsCount-1;
			if (isKeyDown(VK_RETURN) || isKeyDown(VK_RIGHT)) // Return selected option
				return option;
			goto standBy;
		}

		do
		{
			if ((option = (option + step) % optionsCount) < 0)
				option = optionsCount - 1;
		} while (menuOptions[option][0] < 32); // Jump over empty

		for (int i = 0; i < optionsCount; i++) // Render options
		{
			C_RGB(199, 21, 133);
			renderAt(x, y + i, i == option ? ">" : " ");
			C_RESET;

			renderAt(x + 2, y + i, menuOptions[i]);
		}

		wasRendered = 1;

		Sleep(200);

		standBy:
		Sleep(4);
	}
}

// Game

void saveGame(Game* gm, string mapPath)
{
	ofstream saveGame("save.txt", ios::trunc);
	if (saveGame.is_open())
	{
		saveGame << (gm->hasKey ? "~?" : "~") << endl;

		gm->map[gm->plyY][gm->plyX] = '0';
		for (int i = 0; i < gm->height; i++)
		{
			if (i > 0)
				saveGame << endl;
			saveGame << gm->map[i];
		}

		saveGame.close();
	}
}

void startGame(Game* gm, string mapPath) 
{
	delete2D((void***) &gm->map, gm->height);

	gm->map = new char*[127];
	gm->height = gm->width = gm->hasKey = gm->tick = gm->endState = 0;
	gm->doRerender = 1;

	ifstream mapFile(mapPath);
	if (mapFile.is_open())
	{
		for (string row; getline(mapFile, row);) 
		{
			if (row[0] == '~')
			{
				gm->hasKey = row[1] == '?';

				continue;
			}

			gm->map[gm->height] = new char[(gm->width = row.length())+1];
			strcpy(gm->map[gm->height], row.c_str());

			for (int px = 0; px < gm->width; px++) // Find and place player...
				if (gm->map[gm->height][px] == '0')
				{
					gm->map[gm->plyY = gm->height][gm->plyX = px] = ' ';
					break;
				}

			gm->height++;
		}

		mapFile.close();
	}
}

void renderMap(Game* gm, int fromX, int fromY, int toX, int toY)
{
	if (fromX == 0 && fromY == 0 && toX < 0 && toY < 0) // Just for optimization sake...
	{
		toX = gm->width-1;
		toY = gm->height-1;

		for (; toY >= 0; toY--)
			if (gm->map[toY][0] > 0)
				renderAt(0, toY, gm->map[toY]);

		return;
	}

	for (int mx = fromX; mx < toX; mx++)
		for (int my = fromY; my < toY; my++)
		{
			char obj = gm->map[my][mx];
			if (obj > 0)
			{
				// if (obj == '-' || obj == '=')
				// 	C_RGB(160, 160, 160);
				// else if (obj == '*')
				// 	C_RGB(255, 0, 0);
				// else if (obj == '?')
				// 	C_RGB(255, 215, 0);
				renderAt(mx, my, &(gm->map[my][mx]));

				// C_RESET;
			}
		}
}

void player(Game* gm) // Player render and logic
{
	char* obj;
	int oldX = gm->plyX, oldY = gm->plyY;

	if (isKeyDown('E')) // Handle doors
	{
		if (*(obj = &(gm->map[gm->plyY + 1][gm->plyX])) == '-' || (*obj == '=' && gm->hasKey) || // Down door open
			(*(obj = &(gm->map[gm->plyY - 1][gm->plyX])) == '-' || (*obj == '=' && gm->hasKey))) // Up door open
		{
			*obj = ' ';
			renderMap(gm, offsetAreaAsArgs(gm->plyX, gm->plyY, 1));
		}
	}
	else if (gm->tick % 5 == 0)
	{
		// Movement
		gm->plyX += isKeyDown('A') ? -1 : isKeyDown('D') ? 1 : 0;

		gm->plyY += isKeyDown('W') ? -1 : isKeyDown('S') ? 1 : 0;
		
		gm->plyX = clamp(gm->plyX, 0, gm->width-1);
		gm->plyY = clamp(gm->plyY, 0, gm->height-1);
	}

	if (*(obj = &(gm->map[gm->plyY][gm->plyX])) == '?') // Get key
	{
		gm->hasKey++;

		*obj = ' ';
	}
	else if (*obj == '1') // Finish / game over
		gm->endState = 2;
	else if (*obj == '*' || *obj == '<' || *obj == '>') // Dead...
		gm->endState = 1;
	else if (*obj != ' ') // Handle collisions, allow walk only into empty spaces
	{
		gm->plyX = oldX;
		gm->plyY = oldY;
		return;
	}

	renderAt(oldX, oldY, " "); // We are not making snake...
	if (gm->endState != 1)
		renderAt(gm->plyX, gm->plyY, gm->endState ? "1" : "0");
}

void updateReavers(Game* gm)
{
	// C_RGB(255, 0, 0);

	for (int my = 0; my < gm->height; my++)
		for (int mx = 0; mx < gm->width; mx++)
		{
			if (gm->map[my][mx] == '<')
			{
				if (gm->map[my][mx-1] == ' ')
				{
					gm->map[my][mx] = ' ';
					renderAt(mx, my, " ");

					gm->map[my][mx-1] = '<';
					renderAt(mx-1, my, "<");
				}
				else
				{
					gm->map[my][mx] = '>';
					renderAt(mx, my, ">");
				}

				break;
			}

			if (gm->map[my][mx] == '>')
			{
				if (gm->map[my][mx+1] == ' ')
				{
					gm->map[my][mx] = ' ';
					renderAt(mx, my, " ");

					gm->map[my][mx+1] = '>';
					renderAt(mx+1, my, ">");
				}
				else
				{
					gm->map[my][mx] = '<';
					renderAt(mx, my, "<");
				}

				break;
			}
		}

	// C_RESET;
}