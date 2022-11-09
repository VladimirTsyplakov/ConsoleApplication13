#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include <windows.h>
#include<cmath>

using namespace std;

enum st{ red, blue, yel, block, gap };//структура для хранения статуса клетки красная=0, синяя=1, жёлтая=2, блок=3, пустая=4
struct Co { int x = 0; int y = 0; };//координаты клетки

const int shir = 5;//размеры массива
const int dlin = 5;

class kletka
{
public:
	st status;//статус клетки
	Co pos;//координаты клетки
	kletka() {};

};
class square
{
private:
	kletka arr[shir][dlin];//создаём массив
	kletka coursor;

public:
	square()
	{

		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)//наполняем по вертикали
			{
				arr[x][y].pos.x = x;
				arr[x][y].pos.y = y;
				switch (y)
				{
				case 0: arr[x][y].status = red; break;
				case 1: if (x == 0 || x == 2 || x == 4) { arr[x][y].status = gap; }
					  else { arr[x][y].status = block; } break;
				case 2: arr[x][y].status = blue; break;
				case 3: if (x == 0 || x == 2 || x == 4) { arr[x][y].status = gap; }
					  else arr[x][y].status = block; break;
				case 4: arr[x][y].status = yel; break;
				}
			}

			//задаём координаты и статус курсора
			coursor.pos.x = 0;
			coursor.pos.y = 0;
			coursor.status = arr[0][0].status;
		}
	}
		void mix()//мешалка, чтобы цифры были не на своих изначальных местах
		{
			srand(time(NULL));
			for (int v = 0; v < 30; v++)
			{
				int yran = rand() % 4;
				int yran2 = rand() % 3;
				switch (yran2)
				{
				case 0: yran2 = 0; break;
				case 1: yran2 = 2; break;
				case 2: yran2 = 4; break;

				}
				kletka temp;
				temp = arr[yran][yran2];
				arr[yran][yran2] = arr[yran][2];
				arr[yran][2] = temp;
			}
		}
		void set_c()//шаг 1-устанавливаем клетку, которую хотим двигать, шаг 2-выбираем клетку, которую хоим заменить на выбранную ранее
		{
			kletka* t = new kletka;

			char per = 'y';
			int x = coursor.pos.x;
			int y = coursor.pos.y;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD position{ coursor.pos.x, coursor.pos.y };
			int x1 = x;
			int y1 = y;
			SetConsoleCursorPosition(hConsole, position);//выбираем первый блок
			while (per != 'n')
			{
				per = _getch();
				switch (per)
				{
				case 72://при значении 72 проверяем на выход из границы нарисованного массива
					if (y - 1 < 0 || y - 1 > 4) { position = { static_cast<short>(x) ,static_cast<short>(y) };  SetConsoleCursorPosition(hConsole, position); break; } //вверх
					else { y--;   position = { static_cast<short>(x) ,static_cast<short>(y) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 80:
					if (y + 1 < 0 || y + 1 > 4) { position = { static_cast<short>(x),static_cast<short>(y) }; SetConsoleCursorPosition(hConsole, position); break; } //вниз
					{y++;   position = { static_cast<short>(x) ,static_cast<short>(y) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 75:
					if (x - 1 < 0 || x - 1 > 4) { position = { static_cast<short>(x),static_cast<short>(y) }; SetConsoleCursorPosition(hConsole, position); break; } //влево
					else { x--;   position = { static_cast<short>(x) ,static_cast<short>(y) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 77:
					if (x + 1 < 0 || x + 1 > 4) { position = { static_cast<short>(x),static_cast<short>(y) }; SetConsoleCursorPosition(hConsole, position);  break; } //вправо
					else { x++;   position = { static_cast<short>(x) ,static_cast<short>(y) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 13: per = 'n';	if (arr[y][x].status != gap && arr[y][x].status != block)//если выбрана клетка и нажат ентер, проверяем на легитимность выбранной клетки-не блок и не клетка
				{
					coursor.status = arr[y][x].status;
					coursor.pos.x = x;
					coursor.pos.y = y;
					break;
				}
					   else { per = 'y'; continue; } break;//если не прошла проверку, то заново
				}
			}




			int x2 = coursor.pos.x;//сохраняем выбранную клетку на курсор
			int y2 = coursor.pos.y;
			x1 = x2;
			y1 = y2;
			per = 'y';


			SetConsoleCursorPosition(hConsole, position);

			while (per != 'n')//выбираем клетку для обмена с сохранённым курсором
			{
				per = _getch();
				switch (per)
				{
				case 72:
					if (y2 - 1 < 0 || y2 - 1 > 4) { position = { static_cast<short>(x2) ,static_cast<short>(y2) };  SetConsoleCursorPosition(hConsole, position); break; } //вверх
					else { y2--;   position = { static_cast<short>(x2) ,static_cast<short>(y2) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 80:
					if (y2 + 1 < 0 || y2 + 1 > 4) { position = { static_cast<short>(x2),static_cast<short>(y2) }; SetConsoleCursorPosition(hConsole, position); break; } //вниз
					{y2++;   position = { static_cast<short>(x2) ,static_cast<short>(y2) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 75:
					if (x2 - 1 < 0 || x2 - 1 > 4) { position = { static_cast<short>(x2),static_cast<short>(y2) }; SetConsoleCursorPosition(hConsole, position); break; } //влево
					else { x2--;   position = { static_cast<short>(x2) ,static_cast<short>(y2) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 77:
					if (x2 + 1 < 0 || x + 1 > 4) { position = { static_cast<short>(x),static_cast<short>(y) }; SetConsoleCursorPosition(hConsole, position);  break; } //вправо
					else { x2++;   position = { static_cast<short>(x2) ,static_cast<short>(y2) };  SetConsoleCursorPosition(hConsole, position); break; }
				case 13:  per = 'n';	if (arr[y2][x2].status == gap && abs(abs(x2) - abs(x1)) < 2 && abs(abs(y2) - abs(y1)) < 2 && !(abs(abs(x2) - abs(x1)) >= 1 && abs(abs(y2) - abs(y1)) >= 1))
				{
					t = &(arr[y2][x2]);
					t->pos.y = y2;
					t->pos.x = x2;
					change(t);//запускаем функцию обмена курсора с выбранной клеткой
					arr[y][x].status = coursor.status;
				}
					   else break;
				default: break;
				}
			}
		}
		void change(kletka * arg)//меняем местами вызывает курсор с новой выбранной клеткой, за аргумент берет координаты новой клетки
		{
			kletka temp;
			temp.status = arg->status;
			temp.pos.x = arg->pos.x;
			temp.pos.y = arg->pos.y;

			switch (coursor.status)
			{
			case red: arg->status = red; break;
			case blue: arg->status = blue; break;
			case yel: arg->status = yel; break;
			}
			coursor.status = temp.status;

		}
		void show()//показываем массив
		{

			for (int x = 0; x < 5; x++)
			{
				for (int y = 0; y < 5; y++)
				{
					switch (arr[x][y].status)
					{
					case red: cout << "1"; break;
					case blue: cout << "2"; break;
					case yel: cout << "3"; break;
					case block: cout << "X"; break;
					case gap: cout << "."; break;
					}
					if (y == 4) { cout << endl; }
				}
			}
		}
		int chek() //проверка на выигрыш (все три колонки содержат одинаковые по колонке символы)
		{
			int x = 1;
			for (int r = 1; r < 5; r++)
			{
				if (arr[0][0].status == arr[r][0].status) { continue; }
				else { x = 0; break; }

			}
			if (x == 1)
			{
				for (int r1 = 1; r1 < 5; r1++)
				{
					if (arr[0][2].status == arr[r1][2].status) { continue; }
					else { x = 0; break; }
				}
			}

			if (x == 1)
			{
				for (int r2 = 1; r2 < 5; r2++)
				{
					if (arr[0][4].status == arr[r2][4].status) { continue; }
					else { x = 0; break; }
				}
			}
			return x;
		}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	square s;

	s.mix();


	while (s.chek()==0)
	{
		s.show();
		s.set_c();
		system("cls");
	}
	s.show();
	cout << "Победа. Цыплаков идёт учиться!!!" << endl;
	system("pause");
}
