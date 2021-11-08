#include <iostream>
#include <conio.h>

using namespace std;


bool gameOver;       
const int width = 20;    //размеры карты
const int height = 20;
int x, y, fruitX, fruitY, score; //переменные для змеи, фрукта и счета
int tailX[100], tailY[100];	//переменные для хвоста
int nTail; 
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //управление
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;  //изначальная позиция 
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width; //случайные координаты фрукта
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls"); //очистка карты
	for (int i = 0; i < width; i++) //верхняя граница
		cout << "# ";
	cout << endl;
	
	for (int i = 0; i < height; i++) { //создание поля
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) 
				cout << "#";
			if (i == y && j == x) //отображение змейки
				cout << "$";
			else if (i == fruitY && j == fruitX) // отображение фруктов
				cout << "*";
			else {
				bool print = false; //отображение хвоста
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
			cout << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++) //нижняя граница
		cout << "# ";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Для управления используйте: W-вверх,A-влево,S-вправо,D-вниз" << endl;
	cout << "Для окончания игры нажмите (X)";
}

void Input() {
	if (_kbhit()) { //считывание нажатия клавиши
		switch (_getch()) { //получение какую именно клавишу нажали
		case 'a':	//управление англ раскладкой
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x': //окончание игры
			gameOver = true;
			break;
		case 'ф':	//управление ру раскладкой
			dir = LEFT;
			break;
		case 'ы':
			dir = DOWN;
			break;
		case 'в':
			dir = RIGHT;
			break;
		case 'ц':
			dir = UP;
			break;
		case 'ч': //окончание игры
			gameOver = true;
			break;
		}
	}
}

void Logic() { //логика управления
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) { //логика чтобы хвост повторял движения змеи
		prev2X = tailX[i];
		prev2Y = tailX[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) //логика направления движения
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (x > width || x < 0 || y > height || y < 0) //проверка на касание стен
		gameOver = true;

	for (int i = 0; i < nTail; i++) { //проверка на касание самого себя
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;	
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width; //пересоздание координат фрукта
		fruitY = rand() % height;
		nTail++;
	}
	
}

int main() {
	setlocale(LC_ALL, "rus");
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}