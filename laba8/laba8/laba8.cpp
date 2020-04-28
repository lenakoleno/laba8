#include "pch.h"
#pragma warning (disable:4786)
#include <string>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

void cls(void) {

	system("cls");

} // функция очистки экрана

void DrawLine(void) {

	cout << "\n--------------------------------------\n";

} // функция отрисовки пунктирной линии

void Continue(void) {

	cout << "\nДля продолжения нажмите любую клавишу... \n";
	_getch();

} // функция ожидания нажатия

struct Elem
{
	int data; // данные
	Elem * next, *prev;
};

class List
{
	// Голова, хвост
	Elem * Head, *Tail;
	// Количество элементов
	int Count;

public:

	// Конструктор
	List();
	// Конструктор копирования
	List(const List&);
	// Деструктор
	~List();

	// Получить количество
	int GetCount();
	// Получить элемент списка
	Elem* GetElem(int);

	// Удалить весь список
	void DelAll();
	// Удаление элемента, если параметр не указывается,
	// то функция его запрашивает
	void Del(int pos = 0);
	// Вставка элемента, если параметр не указывается,
	// то функция его запрашивает
	void Insert(int pos = 0);

	// Добавление в конец списка
	void AddTail(int n);

	// Добавление в начало списка
	void AddHead(int n);

	// Печать списка
	void Print();
	// Печать определенного элемента
	void Print(int pos);

	List& operator = (const List&);
	// сложение двух списков (дописывание)
	List operator + (const List&);

	// сравнение по элементам
	bool operator == (const List&);
	bool operator != (const List&);
	bool operator <= (const List&);
	bool operator >= (const List&);
	bool operator < (const List&);
	bool operator > (const List&);

	// переворачивание списка
	List operator - ();
};

List::List()
{
	// Изначально список пуст
	Head = Tail = NULL;
	Count = 0;
}

List::List(const List & L)
{
	Head = Tail = NULL;
	Count = 0;

	// Голова списка, из которого копируем
	Elem * temp = L.Head;
	// Пока не конец списка
	while (temp != 0)
	{
		// Передираем данные
		AddTail(temp->data);
		temp = temp->next;
	}
}

List::~List()
{
	// Удаляем все элементы
	DelAll();
}

void List::AddHead(int n)
{
	// новый элемент
	Elem * temp = new Elem;

	// Предыдущего нет
	temp->prev = 0;
	// Заполняем данные
	temp->data = n;
	// Следующий - бывшая голова
	temp->next = Head;

	// Если элементы есть?
	if (Head != 0)
		Head->prev = temp;

	// Если элемент первый, то он одновременно и голова и хвост
	if (Count == 0)
		Head = Tail = temp;
	else
		// иначе новый элемент - головной
		Head = temp;

	Count++;
}

void List::AddTail(int n)
{
	// Создаем новый элемент
	Elem * temp = new Elem;
	// Следующего нет
	temp->next = 0;
	// Заполняем данные
	temp->data = n;
	// Предыдущий - бывший хвост
	temp->prev = Tail;

	// Если элементы есть?
	if (Tail != 0)
		Tail->next = temp;

	// Если элемент первый, то он одновременно и голова и хвост
	if (Count == 0)
		Head = Tail = temp;
	else
		// иначе новый элемент - хвостовой
		Tail = temp;

	Count++;
}

void List::Insert(int pos)
{
	// если параметр отсутствует или равен 0, то запрашиваем его
	if (pos == 0)
	{
		cout << "Input position: ";
		cin >> pos;
	}

	// Позиция от 1 до Count?
	if (pos < 1 || pos > Count + 1)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return;
	}

	// Если вставка в конец списка
	if (pos == Count + 1)
	{
		// Вставляемые данные
		int data;
		cout << "Input new number: ";
		cin >> data;
		// Добавление в конец списка
		AddTail(data);
		return;
	}
	else if (pos == 1)
	{
		// Вставляемые данные
		int data;
		cout << "Input new number: ";
		cin >> data;
		// Добавление в начало списка
		AddHead(data);
		return;
	}

	// Счетчик
	int i = 1;

	// Отсчитываем от головы n - 1 элементов
	Elem * Ins = Head;

	while (i < pos)
	{
		// Доходим до элемента, 
		// перед которым вставляемся
		Ins = Ins->next;
		i++;
	}

	// Доходим до элемента, 
	// который предшествует
	Elem * PrevIns = Ins->prev;

	// Создаем новый элемент
	Elem * temp = new Elem;

	// Вводим данные
	cout << "Input new number: ";
	cin >> temp->data;

	// настройка связей
	if (PrevIns != 0 && Count != 1)
		PrevIns->next = temp;

	temp->next = Ins;
	temp->prev = PrevIns;
	Ins->prev = temp;

	Count++;
}

void List::Del(int pos)
{

	if (pos < 1 || pos > Count)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return;
	}

	// Счетчик
	int i = 1;

	Elem * Del = Head;

	while (i < pos)
	{
		// Доходим до элемента, 
		// который удаляется
		Del = Del->next;
		i++;
	}

	// Доходим до элемента, 
	// который предшествует удаляемому
	Elem * PrevDel = Del->prev;
	// Доходим до элемента, который следует за удаляемым
	Elem * AfterDel = Del->next;

	// Если удаляем не голову
	if (PrevDel != 0 && Count != 1)
		PrevDel->next = AfterDel;
	// Если удаляем не хвост
	if (AfterDel != 0 && Count != 1)
		AfterDel->prev = PrevDel;

	// Удаляются крайние?
	if (pos == 1)
		Head = AfterDel;
	if (pos == Count)
		Tail = PrevDel;

	// Удаление элемента
	delete Del;

	Count--;
}

void List::Print(int pos)
{
	// Позиция от 1 до Count?
	if (pos < 1 || pos > Count)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return;
	}

	Elem * temp;

	// Определяем с какой стороны 
	// быстрее двигаться
	if (pos <= Count / 2)
	{
		// Отсчет с головы
		temp = Head;
		int i = 1;

		while (i < pos)
		{
			// Двигаемся до нужного элемента
			temp = temp->next;
			i++;
		}
	}
	else
	{
		// Отсчет с хвоста
		temp = Tail;
		int i = 1;

		while (i <= Count - pos)
		{
			// Двигаемся до нужного элемента
			temp = temp->prev;
			i++;
		}
	}
	// Вывод элемента
	cout << pos << " element: ";
	cout << temp->data << endl;
}

void List::Print()
{
	// Если в списке присутствуют элементы, то пробегаем по нему
	// и печатаем элементы, начиная с головного
	if (Count != 0)
	{
		Elem * temp = Head;
		cout << "( ";
		while (temp->next != 0)
		{
			cout << temp->data << ", ";
			temp = temp->next;
		}

		cout << temp->data << " )\n";
	}
}

void List::DelAll()
{
	// Пока остаются элементы, удаляем по одному с головы
	while (Count != 0)
		Del(1);
}

int List::GetCount()
{
	return Count;
}

Elem * List::GetElem(int pos)
{
	Elem *temp = Head;

	// Позиция от 1 до Count?
	if (pos < 1 || pos > Count)
	{
		// Неверная позиция
		cout << "Incorrect position !!!\n";
		return 0;
	}

	int i = 1;
	// Ищем нужный нам элемент
	while (i < pos && temp != 0)
	{
		temp = temp->next;
		i++;
	}

	if (temp == 0)
		return 0;
	else
		return temp;
}

void Show_Array_Elements_And_Speed(int* Array, const int Size, DWORD Time) {

	cout << "\n\nЭлементы получившегося массива:\n\n";

	for (int i = 0; i < Size; i++)
		cout << Array[i] << " ";

	cout << "\n\nЗатраченное время на создание динамического массива: " << Time << " мс\n";

} // функция для отображения элементов массива и скорости на его создание

int Count_Elements_InFile(string FilePath) {

	int Count = 0; // счетчик
	int Number = 0;

	ifstream Read(FilePath.c_str());

	while (Read >> Number)
		Count++;

	Read.close();

	return Count;

} // функция подсчитывающая кол-во элементов в файле

void Show_List_And_Speed(List* list, DWORD Time) {

	cout << "\n\nЭлементы получившегося списка:\n\n";

	list->Print();

	cout << "\n\nЗатраченное время на создание списка: " << Time << " мс\n";

} // функция отображения элементов списка и скорости на его создание

void Show_Drob_Result(int* Array, const int Size) {

	cout << "\n\n";

	for (int i = 0; i < Size; i++)
		cout << "кол-во элементов, нацело делящихся на " << i + 1 << ": " << Array[i] << " шт.\n";

} // функция отображения кол-во цельных дробей на каждую цифру

int main(void) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); // кириллица в консоли
	system("title Лабораторная работа № 8, вариант 7");
	srand((unsigned int)time(NULL));

	int ButtonNumber = 0; // переменная для работа с функцией getch
	int* Array = new int[1]; // объявление массива
	int N = 0; // размерность массива
	DWORD t1; // стартовое время
	DWORD t2; // конечное время

	List list;

	while (true) { // начало жизненного цикла программы

		ButtonNumber = 0;
		cls();

		cout << "		Меню программы\n\n";
		cout << "1. Формирование целочисленного одномерного массива с замером скорости\n";
		cout << "2. Вставка, удаление и получение элемента массива с замером скорости\n";
		cout << "3. Формирование двусвязного списка с замером скорости\n";
		cout << "4. Вставка, удаление и получение элемента двусвязного списка с замером скорости\n";
		cout << "5. Вариант 7 по таблице - сравнение скорости работы массива и списка\n";
		cout << "0. Выйти из программы\n";

		while (true) { // защита от дурака по нажатию

			cout << "\nВвод: ";
			cin >> ButtonNumber;

			if (ButtonNumber == 0) {

				delete[] Array;
				return 0; // завершение программы

			}

			else if (ButtonNumber > 0 && ButtonNumber < 6) {

				cls();
				break;

			}

		}

		if (ButtonNumber == 1) {

			int Choise = 0;
			cout << "      Формирование целочисленного одномерного массива с замером скорости\n\n";
			cout << "Выберите способ заполнения массива:\n";
			cout << "1. Генерация элементов случайным образом\n2. Ввод элементов вручную\n3. Элементы считываются из файла Array.txt\n0. Вернуться в главное меню\n\n";

			while (true) {

				cout << "\nВвод: ";
				cin >> Choise;

				if (Choise == 0)
					break;

				else {

					DrawLine();
					delete[] Array;

					string FileName = "numbers.txt";

					if (Choise == 1) {

						cout << "Введите размерность массива: ";
						cin >> N;

						t1 = GetTickCount(); // засекаем старт

						Array = new int[N];

						for (int i = 0; i < N; i++)
							Array[i] = 0 + rand() % 99;

						t2 = GetTickCount(); // засекаем финиш

						Show_Array_Elements_And_Speed(Array, N, t2 - t1);

					} // генерация элементов случ. образом

					else if (Choise == 2) {

						string Str = "\0";

						cout << "Введите элементы массива через пробел - нажатие на Enter останавливает ввод:\n";
						cin.get();
						getline(cin, Str); // считываем всю строку

						t1 = GetTickCount(); // засекаем старт											

						ofstream Write(FileName.c_str());
						Write << Str; // закидываем строку в файл
						Write.close();

						const int N = Count_Elements_InFile(FileName);
						Array = new int[N];

						ifstream Read(FileName.c_str());

						for (int i = 0; i < N; i++)
							Read >> Array[i]; // считывание элементов из файла

						Read.close();

						t2 = GetTickCount(); // засекаем финиш

						Show_Array_Elements_And_Speed(Array, N, t2 - t1);

					} // ручной ввод элементов

					else if (Choise == 3) {

						t1 = GetTickCount();

						const int N = Count_Elements_InFile(FileName);
						Array = new int[N];

						ifstream Read(FileName.c_str());

						for (int i = 0; i < N; i++)
							Read >> Array[i]; // считывание элементов из файла

						Read.close();

						t2 = GetTickCount(); // засекаем финиш

						Show_Array_Elements_And_Speed(Array, N, t2 - t1);

					} // считывание элементорв из файла


				}

			}

		} // Формирование целочисленного одномерного массива с замером скорости

		else if (ButtonNumber == 2) {

			cout << "      Вставка, удаление и получение элемента массива с замером скорости\n\n";

			int Choise = -1;

			while (true) {

				cout << "Выберите способ взаимодействия:\n";
				cout << "1. Вставка нового элемента\n2. Удаление элемента\n3. Получение элемента\n0. Вернуться в главное меню\n\n";

				while (true) {

					cout << "Ввод: ";
					cin >> Choise;

					if (Choise == 0 || Choise == 1 || Choise == 2 || Choise == 3)
						break;

				}

				if (Choise == 0)
					break;

				DrawLine();
				int Number = 0;
				int Vibor = 0;

				if (Choise == 1) {

					cout << "\nВведите значение нового элемента: ";
					cin >> Number;

					t1 = GetTickCount();

					int* Temp = new int[N];

					for (int i = 0; i < N; i++)
						Temp[i] = Array[i];

					delete[] Array;

					N++;
					Array = new int[N];

					for (int i = 0; i < N; i++)
						Array[i] = Temp[i];

					Array[N - 1] = Number;

					delete[] Temp;

					t2 = GetTickCount();

					Show_Array_Elements_And_Speed(Array, N, t2 - t1);

				} // вставка элемента

				else if (Choise == 2 || Choise == 3) {

					cout << "\nВыберите реализацию:\n1. По индексу элемента\n2. По значению элемента\n\n";
					cout << "Ввод: ";
					cin >> Vibor;

				}

				if (Choise == 2) {

					if (Vibor == 1) {

						int Index = 0;
						cout << "\nВведите номер индекса: ";
						cin >> Index;

						t1 = GetTickCount();

						int* Temp = new int[N];

						for (int i = 0; i < N; i++)
							Temp[i] = Array[i];

						N--;
						int c = 0;

						for (int i = 0; i < N + 1; i++) {

							if (Index != i) {

								Array[c] = Temp[i];
								c++;

							}

						}

						t2 = GetTickCount();

					}

					else if (Vibor == 2) {

						int Value = 0;
						cout << "\nВведите значение элемента: ";
						cin >> Value;

						t1 = GetTickCount();

						int* Temp = new int[N];

						for (int i = 0; i < N; i++)
							Temp[i] = Array[i];

						N--;
						int c = 0;
						bool Flag = false;

						for (int i = 0; i < N + 1; i++) {

							if (Temp[i] == Value && Flag == false)
								Flag = true;

							else if (Flag == true && Temp[i] == Value) {

								Array[c] = Temp[i];
								c++;

							}

							else {

								Array[c] = Temp[i];
								c++;

							}

						}

						t2 = GetTickCount();

					}

					Show_Array_Elements_And_Speed(Array, N, t2 - t1);

				}

				if (Choise == 3) {

					if (Vibor == 1) {

						int Index = 0;
						cout << "\nВведите номер индекса: ";
						cin >> Index;

						t1 = GetTickCount();

						for (int i = 0; i < N; i++) {

							if (Index == i) {

								cout << "\nЗначение элемента по индексу " << Index << " : " << Array[i] << "\n";
								break;

							}

						}

						t2 = GetTickCount();

					}

					else if (Vibor == 2) {

						int Value = 0;
						cout << "\nВведите значение элемента: ";
						cin >> Value;

						t1 = GetTickCount();

						for (int i = 0; i < N; i++) {

							if (Value == Array[i]) {

								cout << "\nИндекс элемента по элементу: " << Value << " : " << i << "\n";
								break;

							}

						}

						t2 = GetTickCount();

					}

					Show_Array_Elements_And_Speed(Array, N, t2 - t1);

				} // получение элемента

			}

		} // Вставка, удаление и получение элемента массива с замером скорости

		else if (ButtonNumber == 3) {

			cout << "      Формирование двусвязного списка с замером скорости\n\n";

			int Choise = 0;
			cout << "Выберите способ заполнения массива:\n";
			cout << "1. Генерация элементов случайным образом\n2. Ввод элементов вручную\n3. Элементы считываются из файла Array.txt\n0. Вернуться в главное меню\n\n";

			while (true) {


				cout << "\nВвод: ";
				cin >> Choise;

				if (Choise == 0)
					break;

				else {

					DrawLine();
					list.DelAll();

					string FileName = "numbers.txt";

					if (Choise == 1) {

						cout << "Введите размерность массива: ";
						cin >> N;

						t1 = GetTickCount(); // засекаем старт

						int Num = 0;

						for (int i = 0; i < N; i++) {

							Num = 0 + rand() % 99;
							list.AddTail(Num);

						}

						t2 = GetTickCount(); // засекаем финиш

						Show_List_And_Speed(&list, t2 - t1);

					} // генерация элементов случ. образом

					else if (Choise == 2) {

						string Str = "\0";

						cout << "Введите элементы массива через пробел - нажатие на Enter останавливает ввод:\n";
						cin.get();
						getline(cin, Str); // считываем всю строку

						t1 = GetTickCount(); // засекаем старт											

						ofstream Write(FileName.c_str());
						Write << Str; // закидываем строку в файл
						Write.close();

						const int N = Count_Elements_InFile(FileName);
						int Num = 0;

						ifstream Read(FileName.c_str());

						for (int i = 0; i < N; i++) {

							Read >> Num; // считывание элементов из файла
							list.AddTail(Num);

						}

						Read.close();

						t2 = GetTickCount(); // засекаем финиш

						Show_List_And_Speed(&list, t2 - t1);

					} // ручной ввод элементов

					else if (Choise == 3) {

						t1 = GetTickCount();

						const int N = Count_Elements_InFile(FileName);
						int Num = 0;

						ifstream Read(FileName.c_str());

						for (int i = 0; i < N; i++) {

							Read >> Num; // считывание элементов из файла
							list.AddTail(Num);

						}

						Read.close();

						t2 = GetTickCount(); // засекаем финиш

						Show_List_And_Speed(&list, t2 - t1);

					} // считывание элементорв из файла


				}

			}

		} // Формирование двусвязного списка с замером скорости

		else if (ButtonNumber == 4) {

			cout << "      Вставка, удаление и получение элемента двусвязного списка с замером скорости\n\n";

			int Choise = -1;

			while (true) {

				cout << "\nВыберите способ взаимодействия:\n";
				cout << "1. Вставка нового элемента\n2. Удаление элемента\n3. Получение элемента\n0. Вернуться в главное меню\n\n";

				while (true) {

					cout << "Ввод: ";
					cin >> Choise;

					if (Choise == 0 || Choise == 1 || Choise == 2 || Choise == 3)
						break;

				}

				if (Choise == 0)
					break;

				DrawLine();
				int Number = 0;
				int Vibor = 0;
				int Index = 0;

				if (Choise == 1) {

					cout << "\nВведите значение нового элемента: ";
					cin >> Number;

					t1 = GetTickCount();

					list.AddTail(Number);

					t2 = GetTickCount();

					Show_List_And_Speed(&list, t2 - t1);

				} // вставка элемента

				else if (Choise == 2 || Choise == 3) {

					cout << "\nВыберите реализацию:\n1. По индексу элемента\n2. По значению элемента\n\n";
					cout << "Ввод: ";
					cin >> Vibor;

				}

				if (Choise == 2) {

					if (Vibor == 1) {

						cout << "\nВведите номер индекса: ";
						cin >> Index;

						t1 = GetTickCount();

						list.Del(Index);

						t2 = GetTickCount();

					}

					else if (Vibor == 2) {

						int Value = 0;
						cout << "\nВведите значение элемента: ";
						cin >> Value;

						t1 = GetTickCount();

						for (int i = 1; i <= list.GetCount(); i++) {

							if (Value == list.GetElem(i)->data) {

								Index = i;
								break;

							}

						}


						list.Del(Index);

						t2 = GetTickCount();

					}

					Show_List_And_Speed(&list, t2 - t1);

				} // удаление элемента

				if (Choise == 3) {

					if (Vibor == 1) {

						int Index = 0;
						cout << "\nВведите номер индекса: ";
						cin >> Index;

						t1 = GetTickCount();

						list.Print(Index);

						t2 = GetTickCount();

					}

					else if (Vibor == 2) {

						int Value = 0;
						cout << "\nВведите значение элемента: ";
						cin >> Value;

						t1 = GetTickCount();

						for (int i = 1; i <= list.GetCount(); i++) {

							if (Value == list.GetElem(i)->data) {

								Index = i;
								break;

							}

						}


						list.Print(Index);

						t2 = GetTickCount();


					}

					Show_List_And_Speed(&list, t2 - t1);

				} // получение элемента

			}

			Continue();

		} // Вставка, удаление и получение элемента двусвязного списка с замером скорости

		else if (ButtonNumber == 5) {

			DWORD Array_Result;
			DWORD List_Result;

			const int CountSize = 10;
			int* Array_Count = new int[CountSize];
			int* List_Count = new int[CountSize];

			for (int i = 0; i < CountSize; i++) {

				Array_Count[i] = 0;
				List_Count[i] = 0;

			} // очистка массива

			cout << "Вывод кол-ва элементов, которые нацело делятся на 1, 2, 3, 4, 5, 6, 7, 8, 9\n\n";

			cout << "Элементы массива:\n\n";

			for (int i = 0; i < N; i++)
				cout << Array[i] << " ";

			cout << "\nКол-во таких элементов в массиве: \n";

			t1 = GetTickCount();

			for (int i = 0; i < CountSize; i++) {

				for (int c = 0; c < N; c++) {

					if (Array[c] % (i + 1) == 0)
						Array_Count[i]++;

				}

			}

			t2 = GetTickCount();

			Array_Result = t2 - t1;

			Show_Drob_Result(Array_Count, CountSize);
			cout << "\nСкорость выполнения: " << Array_Result << " мс\n";

			DrawLine();

			cout << "\nЭлементы списка:\n\n";
			list.Print();
			cout << "\nКол-во таких элементов в списке: \n";

			t1 = GetTickCount();

			for (int i = 0; i < CountSize; i++) {

				for (int c = 1; c <= list.GetCount(); c++) {

					if (list.GetElem(c)->data % (i + 1) == 0)
						List_Count[i]++;

				}

			}

			t2 = GetTickCount();

			List_Result = t2 - t1;

			Show_Drob_Result(List_Count, CountSize);
			cout << "\nСкорость выполнения: " << List_Result << " мс\n";

			delete[] Array_Count;
			delete[] List_Count;

			Continue();

		} // сравнение скорости работы списка и массива

	} // конец жизненного цикла программы

}
