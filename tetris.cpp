#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include<conio.h>
#include"mygraphics.h"
using namespace std;
int up_arrow = 72, down_arrow = 80, left_arrow = 75, right_arrow = 77; //ascii for arrow keys

const int d1 = 20, d2 = 25, d3 = 3, d4 = 2; //ranges 
int Xp = d1 / 2;
int Yp = 1;

const int Bheight = 25; //Board height
const int Bwidth = 25; //Board width
int Score; //Score calculation variable
int level; //Level increment variable
int lines; //No. of lines cleared purpose variable
bool Matrix[d1 - 2][d2 - 2]; //Check if shape is available or not


void clrscr() //function to clear the screen
{
	system("cls");
}
void Setposition(int i, int j) //sets position through coordinates x and y
{
	COORD position = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void HideCursor() //function to hide the cursor on console 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}
void shpaeprinting(char str, WORD color)  //function to set
										  // the colors for the shapes thorugh handling
{
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(handle, color);
	cout << str;
	SetConsoleTextAttribute(handle, colorOld);
}
void print(int x, int y, int ColorDisplay)  //function which uses positions of x and y and prints
											// shape accordingly and give colors to them
{
	gotoxy(x, y);
	if (ColorDisplay == 0)
		cout << " ";
	if (ColorDisplay == 1)
	{
		shpaeprinting('*', 60);
	}
	if (ColorDisplay == 2)
	{

		shpaeprinting(' ', 35);
	}
}
void p1(int x, int y, int ColorDisplay, int c1, int c2) //another function which uses positions of x and y and prints
											// shape accordingly and give colors to them
{
	gotoxy(x, y);
	if (ColorDisplay == 0)
		cout << " ";
	if (ColorDisplay == 1)
	{
		shpaeprinting('*', c1);
	}
	if (ColorDisplay == 2)
	{

		shpaeprinting(' ', c2);
	}
}
class Board //Board Class 
{
public:


	int random;
	bool Tboard[25][12];

	Board()   //constructor
	{

		Score = 0;
		level = 1;
		lines = 0;
	}
	void BoardFrame() //function to print board on screen
	{
		gotoxy(2, 1);
		cout << "-----------Tetris Board------------" << endl;
		for (int i = 0; i < d2; i++)
		{
			for (int j = 0; j < d1; j++)
			{
				if (j == 0 || j == d1 - 1)
				{

					
					p1(j + d3, i + d4, 2, 60, 32);

				}
				else if (i == 0 || i == d2 - 1)
				{
					
					p1(j + d3, i + d4, 2, 60, 32);
				}
			}
		}


	}
	void setscore(int earnscores)
	{
		Score = earnscores;
		Score = Score + Score;
		
	}
	int getscore()
	{
		return Score;
	}
	void SidemenuBoard() //function to print side menu alongwith printing of board
	{
		gotoxy(d2 + 10, d3 + 8);
		cout << "SCORE" << endl;
		gotoxy(d2 + 15, d3 + 8);

		cout << "|  " << getscore() << "  |" << endl;

		gotoxy(d2 + 15, d3 + 9);
		cout << " ------" << endl;
		gotoxy(d2 + 10, d3 + 10);
		cout << "LEVEL" << endl;
		gotoxy(d2 + 15, d3 + 10);
		cout << "|  " << level << "  |" << endl;
		gotoxy(d2 + 15, d3 + 11);
		cout << " ------" << endl;
		gotoxy(d2 + 10, d3 + 12);
		cout << "LINES" << endl;
		gotoxy(d2 + 15, d3 + 12);
		cout << "|  " << lines << "  |" << endl;
		gotoxy(d2 + 15, d3 + 13);
		cout << " ------" << endl;
		gotoxy(d2 + 15, d3 + 25);
		cout << "       " << endl;

	}
	void GameScreen()   //function which calls both the above functions and sets the whole screen
	{
		BoardFrame();
		SidemenuBoard();
	}
	

};
class Pieces : public Board  //Pieces Class inherited from Board Class
{
public:
	bool moving = true;
	Board b;
	char c;
	int currentSpeed;
	int Pieces_fallSpeed;
	int incre;
	Pieces() //constructor
	{
		c = 0;
		currentSpeed = 1000;
		Pieces_fallSpeed = 1000;
		incre = 0;
	}
	//.....................All these are virtual functions which are being used in every shape class............................
	virtual void Shape_print() //func to print
	{

	}
	virtual void rotate() //func to rotate
	{

	}
	virtual void dropshapesprint() //func to print shape again and again
	{

	}
	virtual void Game_Run() //func to run the whole game
	{

	}
};

//piece 1 --------Line shape-------------------------------------
class Shapeline :public Pieces
{
public:
	int Shape_Line[4][4] = { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} };
	Shapeline() :Pieces()
	{
		c = 0;
		
		incre = 0;
	}

	void Shape_print()//display the shape on game board
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (Shape_Line[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
				
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}

		}
	}
	void rotate()// function to perform the possible rotations of the shape
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp[i][j] = Shape_Line[3 - j][i];
				{
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++) {
							Shape_Line[i][j] = temp[i][j];

							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (Shape_Line[i][j] == 1)
									{


										p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
									}
									else
									{

										p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
									}

								}
								cout << endl;
							}
						}
					}
				}
			}
		}
	}
	void dropshapesprint(int ColorDisplay) //display the shape that is falling down during performing of each down ward movement
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Shape_Line[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline() //fucntion to check if the line is full them remove it
	{
		int i, j, k, checkA, checkB, checkC = 0;
		bool Temp1;
		for (j = d2 - 3; j >= 0; j--)
		{
			checkA = 0;
			checkB = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
				{
					checkA = 1;
				}
				if (Matrix[j][i] == false) {
					checkB = 1;
				}
			}
			if (checkB == 0)
			{
				Score = Score + 200;
				b.setscore(Score);
				checkC = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						Temp1 = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = Temp1;
					}
				}
				j++;
			}
			if (checkA == 0)
			{
				break;
			}
		}
		return checkC;
	}
	bool check_After_Oper(char key) //check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow)//on pressing uparrow ,it check  if the shape is within the boundry(left and right side of baord )
		{
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else {
				for (int i = 0; i < 3; i++)
				{

					rotate();

					return false;
				}
			}

		}
		if (int(key) == down_arrow)//on pressing downarrow ,it check  if the shape is within the boundry(bottom side of baord )
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)//on pressing left arrow ,shape move to left most corner .it check  if the shape is within the boundry(left side)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)//on pressing right arrow ,shape move to right  most corner .it check  if the shape is within the boundry(right side)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	bool move(char key) //perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;
				Score = Score + 4;
				b.setscore(Score);
			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false) //check if further downward movemnet possible ,(at  the boundry of board )
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (Shape_Line[i][j] == 1)
					{
						Matrix[Yp + i - 1][Xp + j - 1] = true;
					}
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	
	void reset() //Generate a new block
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;
			random = rand() % 7;

		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Shape_Line[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt)
	{
		if (clock() - t > tt)
		{
			t = clock();
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //Peform a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{
				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
					delay(10);
					
				}
			}
			else
			{
				c = 0;
				delay(4);
			}
		}
	}
	int level_rise() //increase the level w r t score
	{

		if (Score >= 100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}
	
	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}
	void Game_Run()
	{
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			reset();
			
			level_rise();
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					/*clrscr();
					cout << "------- GAME OVER--------" << endl;*/
				}
			}
			b.setscore(Score);
			
		}
		clrscr();
		b.setscore(Score);
		b.SidemenuBoard();
	}
};
//Pieces 2---------T SHAPE--------------------
class Shape_T :public Pieces
{
public:
	int ShapeT[4][4] = { {0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0} };
	Shape_T() :Pieces()
	{
		c = 0;
		incre = 0;
	}

	void Shape_print()//  display the shape on the baord
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (ShapeT[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
					
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}

		}
	}
	void rotate()//perform the possible rotations of the shape
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp[i][j] = ShapeT[3 - j][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ShapeT[i][j] = temp[i][j];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (ShapeT[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}
				else
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
			cout << endl;
		}
	}
	void dropshapesprint(int ColorDisplay)//display the  shapes moving downward in th baord
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (ShapeT[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline()  //fucntion to check if the line is full them remove it
	{
		int i, j, k, checkA, checkB, checkC = 0;
		bool Temp1;
		for (j = d2 - 3; j >= 0; j--)
		{
			checkA = 0;
			checkB = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
				{
					checkA = 1;
				}
				if (Matrix[j][i] == false)
				{
					checkB = 1;
				}
			}
			if (checkB == 0)
			{
				Score = Score + 200;
				b.setscore(Score);
				checkC = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						Temp1 = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = Temp1;
					}
				}
				j++;
			}
			if (checkA == 0)
				break;
		}
		return checkC;

	}
	bool move(char key) //perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;
				Score = Score + 4;
				b.setscore(Score);
			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false)//check if further downward movemnet possible ,(at  the boundry of board )
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (ShapeT[i][j] == 1)
					{
						Matrix[Yp + i - 1][Xp + j - 1] = true;
					}
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	bool check_After_Oper(char key)//check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow)//on pressing uparrow ,it check  if the shape is within the boundry(left and right side of baord )
		{
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else {
				for (int i = 0; i < 3; i++)
				{
					rotate();

					return false;
				}
			}

		}
		if (int(key) == down_arrow)//on pressing downarrow ,it check  if the shape is within the boundry(bottom side of baord )
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)//on pressing left arrow ,shape move to left most corner .it check  if the shape is within the boundry(left side)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)//on pressing right arrow ,shape move to right  most corner .it check  if the shape is within the boundry(right side)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void reset() //Generate a new shape
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;


		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (ShapeT[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt)
	{
		if (clock() - t > tt)
		{
			t = clock();
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //Perform a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{
				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
					Pieces_fallSpeed = currentSpeed;
				

				}
			}
			else
			{
				c = 0;
				Pieces_fallSpeed = currentSpeed;
			}
		}
	}
	int level_rise() //rise the level of game w r t to current score
	{
		if (Score >=100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}
	
	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}

	void Game_Run() 
	{
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			reset();
			
			level_rise();
			
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					clrscr();
					cout << "------- GAME OVER--------" << endl;
				}
			}
			b.setscore(Score);
			
		}
		clrscr();
		b.setscore(Score);
		b.SidemenuBoard();
		
	}
};
//Piece 3-----------Z1 shape-------------------

class Shapez1 :public Pieces
{
public:

	int shapeZ1[4][4] = { {0,0,0,0},{1,1,0,0},{0,1,1,0} ,{0,0,0,0} };

	Shapez1() :Pieces()
	{
		c = 0;
		
		incre = 0;
	}

	void Shape_print()//display the shape on game board
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (shapeZ1[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
					print(d3 + j + 1, d4 + i + 1, 0);
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}

		}
	}
	void rotate()//display the shape that is falling down during performing of each down ward movement
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp[i][j] = shapeZ1[3 - j][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				shapeZ1[i][j] = temp[i][j];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapeZ1[i][j] == 1)
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}
				else
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
			cout << endl;
		}
	}
	void dropshapesprint(int ColorDisplay) //display the shape that is falling down during performing of each down ward movement
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapeZ1[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline() //fucntion to check if the line is full them remove it
	{
		int i, j, k, flag1, flag2, flag3 = 0;
		bool temp1;
		for (j = d2 - 3; j >= 0; j--)
		{
			flag1 = 0;
			flag2 = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
					flag1 = 1;
				if (Matrix[j][i] == false)
					flag2 = 1;
			}
			if (flag2 == 0)
			{
				Score += 1;
				flag3 = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						temp1 = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = temp1;
					}
				}
				j++;
			}
			if (flag1 == 0)
				break;
		}
		return flag3;
	}
	bool move(char key)//perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;
				Score = Score + 4;
				b.setscore(Score);
			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false) //If it detects that the downward movement is not possible, then the end of the drop
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (shapeZ1[i][j] == 1)
						Matrix[Yp + i - 1][Xp + j - 1] = true;
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	bool check_After_Oper(char key) //check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow)//on pressing uparrow ,it check  if the shape is within the boundry(left and right side of baord )
		{
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else {
				for (int i = 0; i < 3; i++)
				{
					rotate();
					return false;
				}
			}

		}
		if (int(key) == down_arrow)//on pressing downarrow ,it check  if the shape is within the boundry(bottom side of baord )
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)//on pressing left arrow ,shape move to left most corner .it check  if the shape is within the boundry(left side)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)//on pressing right arrow ,shape move to right  most corner .it check  if the shape is within the boundry(right side)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void reset() //Generate a new shape
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;
			random = rand() % 7;

		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapeZ1[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt) 
	{
		if (clock() - t > tt)
		{
			t = clock();
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //Peform a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{

				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
					delay(5);
					Pieces_fallSpeed = currentSpeed;
				}
			}
			else
			{
				c = 0;
				delay(5);
				Pieces_fallSpeed = currentSpeed;
			}
		}
	}
	int level_rise() //increase the level w r t score
	{

		if (Score >= 100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}
	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}
	void Game_Run() 
	{
		bool check1;
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			
			level_rise();
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					/*clrscr();
					cout << "------- GAME OVER--------" << endl;*/
				}
			}
			b.setscore(Score);
			
		}
		clrscr();

		b.setscore(Score);
		b.SidemenuBoard();
	}
};
// Pieces 4--------Z2 SHape------------------------------
class Shapez2 :public Pieces
{
public:
	int shapeZ2[4][4] = { {0,0,0,0},{0,1,1,0},{1,1,0,0} ,{0,0,0,0} };


	Shapez2() :Pieces()
	{
		c = 0;
		incre = 0;
	}

	void Shape_print()
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (shapeZ2[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
					print(d3 + j + 1, d4 + i + 1, 0);
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}

		}
	}
	void rotate()
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp[i][j] = shapeZ2[3 - j][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				shapeZ2[i][j] = temp[i][j];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapeZ2[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}
				else
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
			cout << endl;
		}
	}
	void dropshapesprint(int ColorDisplay) // display the shape that is falling down during performing of each down ward movement
	
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapeZ2[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline() //Check if a line is filled, if it is filled, remove it
	{
		int i, j, k, flag1, flag2, flag3 = 0;
		bool temp1;
		for (j = d2 - 3; j >= 0; j--)
		{
			flag1 = 0;
			flag2 = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
					flag1 = 1;
				if (Matrix[j][i] == false)
					flag2 = 1;
			}
			if (flag2 == 0)
			{
				Score += 1;
				flag3 = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						temp1 = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = temp1;
					}
				}
				j++;
			}
			if (flag1 == 0)
				break;
		}
		return flag3;
	}
	bool move(char key) //perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;
				Score = Score + 4;
				b.setscore(Score);
			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false) //If it detects that the downward movement is not possible, then the end of the drop
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (shapeZ2[i][j] == 1)
						Matrix[Yp + i - 1][Xp + j - 1] = true;
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	bool check_After_Oper(char key)  //check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow) {
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else {
				for (int i = 0; i < 3; ++i)
					rotate();
				return false;
			}

		}
		if (int(key) == down_arrow)
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void reset() //Generate a new shape
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;
			random = rand() % 7;

		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapeZ2[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt) 
	{
		if (clock() - t > tt)
		{
			t = clock();
			
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //perform a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{

				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
					delay(5);
					Pieces_fallSpeed = currentSpeed;
				}
			}
			else
			{
				c = 0;
				delay(5);
				Pieces_fallSpeed = currentSpeed;
			}
		}
	}
	int level_rise() //increase the level w r t score
	{

		if (Score >= 100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}

	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}
	void Game_Run() // is equivalent to the main function
	{
		bool check1;
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			reset();
			
			level_rise();
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					/*clrscr();
					cout << "------- GAME OVER--------" << endl;*/
				}
			}
			b.setscore(Score);
			
		}
		clrscr();

		b.setscore(Score);
		b.SidemenuBoard();
	}
};
//Pieces 5--------------Sqaure Shape=------------------
class Shapesq :public Pieces
{
public:
	int shapesq[4][4] = { {0,0,0,0},{0,1,1,0},{0,1,1,0} ,{0,0,0,0} };


	Shapesq() :Pieces()
	{
		c = 0;
		currentSpeed = 1000;
		Pieces_fallSpeed = 1000;
		incre = 0;
	}

	void Shape_print()
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (shapesq[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
					print(d3 + j + 1, d4 + i + 1, 0);
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
		}
	}
	void rotate()// function to perform the possible rotations of the shape
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp[i][j] = shapesq[3 - j][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				shapesq[i][j] = temp[i][j];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapesq[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}
				else
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
			cout << endl;
		}
	}
	void dropshapesprint(int ColorDisplay) //Print out the falling cube
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapesq[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline() //fucntion to check if the line is full them remove it
	{
		int i, j, k, cehckA, checkB, checkC = 0;
		bool temp;
		for (j = d2 - 3; j >= 0; j--)
		{
			cehckA = 0;
			checkB = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
				{
					cehckA = 1;
				}
				if (Matrix[j][i] == false)
				{
					checkB = 1;
				}
			}
			if (checkB == 0)
			{
				Score = Score + 200;
				b.setscore(Score);
				checkC = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						temp = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = temp;
					}
				}
				j++;
			}
			if (cehckA == 0)
				break;
		}
		return checkC;
	}
	bool move(char key) //perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;

				Score = Score + 4;
				b.setscore(Score);
			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false) //If it detects that the downward movement is not possible, then the end of the drop
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (shapesq[i][j] == 1)
						Matrix[Yp + i - 1][Xp + j - 1] = true;
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	bool check_After_Oper(char key)  //check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow)//on pressing uparrow ,it check  if the shape is within the boundry(left and right side of baord )
		{
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else {
				for (int i = 0; i < 3; i++)
				{
					rotate();
					return false;
				}
			}

		}
		if (int(key) == down_arrow)//on pressing downarrow ,it check  if the shape is within the boundry(bottom side of baord )
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)//on pressing left arrow ,shape move to left most corner .it check  if the shape is within the boundry(left side)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void reset() //Generate a new shape
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;
			random = rand() % 7;

		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapesq[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt) //corresponding keyboard
	{
		if (clock() - t > tt)
		{
			t = clock();
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //Make a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{

				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
					delay(5);
					Pieces_fallSpeed = currentSpeed;
				}
			}
			else
			{
				c = 0;
				delay(5);
				Pieces_fallSpeed = currentSpeed;
			}
		}
	}
	int level_rise() //increase the level w r t score
	{

		if (Score >= 100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}

	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}
	void Game_Run() 
	{
		bool check1;
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			reset();
			
			level_rise();
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					/*clrscr();
					cout << "------- GAME OVER--------" << endl;*/
				}
			}
			b.setscore(Score);
			
		}
		clrscr();

		b.setscore(Score);
		b.SidemenuBoard();
	}
};
//Pieces 6--------------l2 Shape=------------------
class Shapel2 :public Pieces
{
public:
	int shapel2[4][4] = { {0,0,0,0},{0,0,1,0},{1,1,1,0} ,{0,0,0,0} };


	Shapel2() :Pieces()
	{
		c = 0;
		incre = 0;
	}

	void Shape_print()//display the shape on game board
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (shapel2[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
					print(d3 + j + 1, d4 + i + 1, 0);
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
		}
	}
	void rotate()//f unction to perform the rotations
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp[i][j] = shapel2[3 - j][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				shapel2[i][j] = temp[i][j];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapel2[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}
				else
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
			cout << endl;
		}
	}
	void dropshapesprint(int ColorDisplay)//display the  shapes moving downward in th baord
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapel2[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline()  //perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{
		int i, j, k, checkA, checkB, checkC = 0;
		bool Temp1;
		for (j = d2 - 3; j >= 0; j--)
		{
			checkA = 0;
			checkB = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
				{
					checkA = 1;

				}
				if (Matrix[j][i] == false)
				{
					checkB = 1;
				}
			}
			if (checkB == 0)
			{
				Score = Score + 200;
				b.setscore(Score);
				checkC = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						Temp1 = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = Temp1;
					}
				}
				j++;
			}
			if (checkA == 0)
				break;
		}
		return checkC;
	}
	bool move(char key) //perform the operation on the basis of the key press include left ,right ,down movement and rotation
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;
				Score = Score + 4;
				b.setscore(Score);
			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false) //If it detects that the downward movement is not possible, then the end of the drop
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (shapel2[i][j] == 1)
						Matrix[Yp + i - 1][Xp + j - 1] = true;
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	bool check_After_Oper(char key) //check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow)//on pressing uparrow ,it check  if the shape is within the boundry(left and right side of baord )
		{
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else {
				for (int i = 0; i < 3; i++)
				{
				
				rotate();
				return false;
			}
			}

		}
		if (int(key) == down_arrow)//on pressing downarrow ,it check  if the shape is within the boundry(bottom side of baord )
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)//on pressing left arrow ,shape move to left most corner .it check  if the shape is within the boundry(left side)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void reset() //Generate a new shape
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;
			random = rand() % 7;

		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapel2[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt) //corresponding keyboard
	{
		if (clock() - t > tt)
		{
			t = clock();
			//if (GetAsyncKeyState(VK_ESCAPE)) exit(0);
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //Make a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{

				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
					delay(5);
					Pieces_fallSpeed = currentSpeed;
				}
			}
			else
			{
				c = 0;
				delay(5);
				Pieces_fallSpeed = currentSpeed;
			}
		}
	}
	int level_rise() //rise the level of game w r t to current score
	{
		if (Score >= 100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}

	
	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}
	void Game_Run() 
	{
		bool check1;
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			reset();
			
			level_rise();
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					/*clrscr();
					cout << "------- GAME OVER--------" << endl;*/
				}
			}
			b.setscore(Score);
			b.SidemenuBoard();
		}
		clrscr();
		b.setscore(Score);
		b.SidemenuBoard();
	}
};
//Piece 7---------------L1 shpae--------------------------
class Shapel1 :public Pieces
{
public:
	int shapel1[4][4] = { {0,0,0,0},{1,0,0,0},{1,1,1,0} ,{0,0,0,0} };


	Shapel1() :Pieces()
	{
		c = 0;
		incre = 0;
	}

	void Shape_print()
	{

		gotoxy(4, 4);
		for (int i = 0; i < d3 - 2; i++)
		{
			for (int j = 0; j < d4 - 1; j++)
			{
				if (shapel1[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 1, 45, 33);
				}
				else
				{
					print(d3 + j + 1, d4 + i + 1, 0);
					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}

		}
	}
	void rotate()//fuction to perform the possible rotation
	{



		int temp[4][4];

		for (int i = 0; i < 4; i++)

			for (int j = 0; j < 4; j++)
				temp[i][j] = shapel1[3 - j][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				shapel1[i][j] = temp[i][j];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapel1[i][j] == 1)
				{


					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}
				else
				{

					p1(d3 + j + 1, d4 + i + 1, 0, 45, 33);
				}

			}
			cout << endl;
		}
	}
	void dropshapesprint(int ColorDisplay) //display the  shapes moving downward in th baord
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapel1[i][j] == 1)
				{
					print(d3 + Xp + j, d4 + Yp - 1 + i, ColorDisplay);

				}
			}
		}

	}
	int Clearline()  //perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{
		int i, j, k, checkA, checkB, checkC = 0;
		bool Temp1;
		for (j = d2 - 3; j >= 0; j--)
		{
			checkA = 0;
			checkB = 0;
			for (i = 0; i <= d1 - 3; i++)
			{
				if (Matrix[j][i] == true)
				{
					checkA = 1;
				}
				if (Matrix[j][i] == false)
				{
					checkB = 1;
				}
			}
			if (checkB == 0)
			{
				Score = Score + 200;
				b.setscore(Score);
				checkC = 1;
				for (i = 0; i <= d1 - 3; i++)
					Matrix[j][i] = false;
				for (k = j; k > 0; k--)
				{
					for (i = 0; i <= d1 - 3; ++i)
					{
						Temp1 = Matrix[k][i];
						Matrix[k][i] = Matrix[k - 1][i];
						Matrix[k - 1][i] = Temp1;
					}
				}
				j++;
			}
			if (checkA == 0)
				break;
		}
		return checkC;
	}
	bool move(char key)//perform the operation on the basis of the key press include left ,right ,down movement and rotation 
	{

		if (moving)
		{
			if (int(key) == up_arrow && check_After_Oper(up_arrow))
			{
				key = up_arrow;
			}
			if ((int(key) == down_arrow || key == 0) && check_After_Oper(down_arrow))
			{
				Yp = Yp + 1;
				Score = Score + 4;
				b.setscore(Score);

			}
			if (int(key) == left_arrow && check_After_Oper(left_arrow))
			{
				Xp = Xp - 1;
			}
			if (int(key) == right_arrow && check_After_Oper(right_arrow))
			{
				Xp = Xp + 1;
			}
		}
		if (check_After_Oper(down_arrow) == false) //If it detects that the downward movement is not possible, then the end of the drop
		{
			moving = false;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (shapel1[i][j] == 1)
						Matrix[Yp + i - 1][Xp + j - 1] = true;
				}
			}
			Clearline();
			Shape_print();
			return false;
		}
		return true;
	}

	bool check_After_Oper(char key)//check  if it is out of boundry of baord after performing a certain movement
	{

		if (int(key) == up_arrow) //on pressing uparrow ,it check  if the shape is within the boundry(left and right side of baord )
		{
			rotate();
			if (check_wallscollision(Xp, Yp))
			{
				return true;
			}
			else 
			{
				for (int i = 0; i < 3; i++)
				{
					rotate();
					return false;
				}
			}

		}
		if (int(key) == down_arrow)//on pressing downarrow ,it check  if the shape is within the boundry(bottom side of baord )
		{

			if (check_wallscollision(Xp, Yp + 1))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
		if (int(key) == left_arrow)//on pressing left arrow ,shape move to left most corner .it check  if the shape is within the boundry(left side)
		{
			if (check_wallscollision(Xp - 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (int(key) == right_arrow)//on pressing right arrow ,shape move to right most corner .it check  if the shape is within the boundry(right side)
		{
			if (check_wallscollision(Xp + 1, Yp))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	void reset() //Generate a new shape
	{
		if (moving == false)
		{
			Xp = d1 / 2;
			Yp = 1;
			moving = true;
			random = rand() % 7;

		}
	}
	bool check_wallscollision(int x, int y)// just check to make sure the shape is within the boundry
	{
		x = x - 1;
		y = y - 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shapel1[i][j] == 1)
				{
					if (y + i >= d2 - 1 || x + j >= d1 - 2 || y + i < d3 - 2 || x + j < 0)
					{
						return false;
					}
					else if (Matrix[y + i][x + j] == true)
					{
						return false;
					}
				}
				else continue;
			}
		}
		return true;
	}
	void Game_keys(clock_t& t, int tt) //corresponding keyboard
	{
		if (clock() - t > tt)
		{
			t = clock();
			if (GetAsyncKeyState(VK_LEFT))c = left_arrow;
			if (GetAsyncKeyState(VK_RIGHT))c = right_arrow;
			if (GetAsyncKeyState(VK_UP))c = up_arrow;
			if (GetAsyncKeyState(VK_DOWN))c = down_arrow;

		}
	}
	void Pieces_Movement(clock_t& t) //perform a move
	{

		if (clock() - t > Pieces_fallSpeed)
		{
			dropshapesprint(0);
			move(c);
			dropshapesprint(1);
			t = clock();
			if (c == down_arrow)
			{

				Pieces_fallSpeed = 10;
				incre++;
				if (incre == 5)
				{
					incre = 0;
					c = 0;
				
					Pieces_fallSpeed = currentSpeed;
				}
			}
			else
			{
				c = 0;
				
				Pieces_fallSpeed = currentSpeed;
			}
		}
	}
	int level_rise() //rise the level of game w r t to current score
	{
		if (Score >= 100)
		{
			level = level + 1;
			currentSpeed = 200;
		}
		else if (Score >= 500)
		{
			level = level + 1;
			currentSpeed = 140;
		}
		else if (Score >= 650)
		{
			level = level + 1;
			currentSpeed = 100;
		}
		else if (Score >= 800)
		{
			level = level + 1;
			currentSpeed = 75;
		}
		return level;
	}
	
	bool is_gameover() //Check if the game is over
	{
		if (Yp == 1 && check_wallscollision(Xp, Yp) == false)
		{
			return true;
		}
		return false;
	}
	void Game_Run()
	{
		bool check1;
		clock_t t1, t2;
		t1 = clock();
		t2 = clock();
		int tt1 = 60;
		b.GameScreen();
		while (true)
		{
			HideCursor();
			Game_keys(t1, tt1);
			Pieces_Movement(t2);
			reset();
			
			level_rise();
			if (is_gameover())
			{
				bool check1;
				check1 = true;
				if (check1)
				{
					/*clrscr();
					cout << "------- GAME OVER--------" << endl;*/
				}
			}
			b.setscore(Score);
			b.SidemenuBoard();
		}
		clrscr();
		b.setscore(Score);
		b.SidemenuBoard();
	}
};
int main()
{
	system("color 5A");
	int random = 1 + (rand() % 7);
	Pieces** obj = new Pieces * [7];
	obj[0] = new Shapez1();
	obj[1] = new Shapez2();
	obj[2] = new Shapesq();
	obj[3] = new Shapeline();
	obj[4] = new Shapel2();
	obj[5] = new Shapel1();
	obj[6] = new Shape_T();
	if (random == 1)
	{
		obj[0]->Game_Run();
	}
	else if (random == 2)
	{
		obj[1]->Game_Run();
		//random = 1 + (rand() % 7);
	}
	else if (random == 3)
	{
		obj[2]->Game_Run();
		//random = 1 + (rand() % 7);
	}
	else if (random == 4)
	{
		obj[3]->Game_Run();
		//random = 1 + (rand() % 7);
	}
	else if (random == 5)
	{
		obj[4]->Game_Run();
		//random = 1 + (rand() % 7);
	}
	else if (random == 6)
	{
		obj[5]->Game_Run();
		//random = 1 + (rand() % 7);
	}
	else if (random == 7)
	{
		obj[6]->Game_Run();
		//random = 1 + (rand() % 7);
	}



	system("pause");
	return 0;


}