/*27(7) вариант
7.Пусть задано N прямоугольников, каждый из них задан
с помощью координат его левого верхнего угла и правого нижнего
угла.Определить прямоугольник наибольшей площади, вывести его
номер и площадь.*/
#include <iostream>      
#include <ctime>
#define M 1000
#define MY_ERROR_FILE 1

struct coord
{
	int x1, y1, x2, y2;
};

void fillArray(coord* mas, int& N, FILE* input, FILE* arrayBinary);
void printArray(coord* mas, int N);
void fillArrayCoordByHand(coord* mas, int& N, FILE* input, FILE* arrayBinary);
void fillArrayCoordByRandom(coord* mas, int& N, FILE* input, FILE* arrayBinary);
int calculatingMostArea(coord* mas, int N);
float getArea(coord A);
int fillArrayByFile(coord* mas, int& N, FILE* input);
int saveArray(coord* mas, int N, FILE* input);
int fillArrayByBinary(FILE* arrayBinary, coord* mas, int &N);
int saveArrayInBinary(FILE* arrayBinary, coord* mas, int N);

int main()
{
	system("chcp 1251");
	srand(time(0));

	coord mas[M];
	int N, index;
	float S;
	FILE* input = NULL;
	FILE* arrayBinary = NULL;

	fillArray(mas, N, input, arrayBinary);
	printArray(mas, N);

	index = calculatingMostArea(mas, N);
	S = getArea(mas[index]);
	printf("%i-й прямоугольник имеет наибольшую площадь = %lf\n", index, S);

	system("pause");
	return 0;
}

//Вывод массива
void printArray(coord* mas, int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("Координаты точек левого верхнего и правого нижнего угла %i-го прямоугольника:\n", i + 1);
		printf("x1 = %i ", mas[i].x1);
		printf("x2 = %i\n", mas[i].x2);
		printf("y1 = %i ", mas[i].y1);
		printf("y2 = %i ", mas[i].y2);
		printf("\n");
	}
	printf("\n");
}
//Выбор способа заполнения массива и его непосредственное заполнение.
void fillArray(coord* mas, int& N, FILE* input, FILE* arrayBinary)
{
	int choice;
	printf("Выберете способ заполнения массива:\n1)Рандомными числами.\n2)Ввод с клавиатуры.\n3)Из файла.\n4)Из бинарного файла.\n");
	do
	{
		scanf_s("%i", &choice);
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
			printf("Неверное число. Введите \"1\", \"2\", \"3\" или \"4\": ");
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
	switch (choice)
	{
	case 1: fillArrayCoordByRandom(mas, N, input, arrayBinary); break;
	case 2: fillArrayCoordByHand(mas, N, input, arrayBinary); break;
	case 3: fillArrayByFile(mas, N, input); break;
	case 4: fillArrayByBinary(arrayBinary, mas, N); break;
	}
}
//Ввод массива рандомом.
void fillArrayCoordByRandom(coord* mas, int& N, FILE* input, FILE* arrayBinary)
{
	printf("Введите количество прямоугольников N: ");
	do
	{
		scanf_s("%i", &N);
		if (N <= 0)
			printf("Введите натуральное целое число: ");
	} while (N <= 0);
	int A, B;
	printf("Введите границы используемых чисел A и В:\n");
	printf("A = "); scanf_s("%i", &A);
	printf("B = "); scanf_s("%i", &B);
	for (int i = 0; i < N; i++)
	{
		mas[i].x1 = rand() % (B - A + 1) + A;
		mas[i].y1 = rand() % (B - A + 1) + A;
		do
			mas[i].x2 = rand() % (B - A + 1) + A;
		while (mas[i].x2 < mas[i].x1);
		do
			mas[i].y2 = rand() % (B - A + 1) + A;
		while (mas[i].y2 > mas[i].y1);
	}
	saveArray(mas, N, input);
	saveArrayInBinary(arrayBinary, mas, N);
}
//Ввод массива с клавиатуры.
void fillArrayCoordByHand(coord* mas, int& N, FILE* input, FILE* arrayBinary)
{
	printf("Введите количество прямоугольников N: ");
	do
	{
		scanf_s("%i", &N);
		if (N <= 0)
			printf("Введите натуральное целое число: ");
	} while (N <= 0);
	for (int i = 0; i < N; i++)
	{
		printf("Введите координаты точек левого верхнего и правого нижнего угла %i-го прямоугольника: \n", i + 1);
		printf("x1: "); scanf_s("%i", &mas[i].x1);
		printf("y1: "); scanf_s("%i", &mas[i].y1);
		do
		{
			printf("x2: ");
			scanf_s("%i", &mas[i].x2);
		} while (mas[i].x2 <= mas[i].x1);
		do
		{
			printf("y2: ");
			scanf_s("%i", &mas[i].y2);
		} while (mas[i].y2 >= mas[i].y1);
	}
	saveArray(mas, N, input);
	saveArrayInBinary(arrayBinary, mas, N);
}
//Вычисление наибольшей площади.
int calculatingMostArea(coord* mas, int N)
{
	int index = 0;
	float S;
	double t = 0;
	for (int i = 0; i < N; i++)
	{
		S = getArea(mas[i]);
		if (S > t)
		{
			t = S;
			index = i + 1;
		}
	}
	return index;
}
float getArea(coord A)
{
	int S;
	S = (A.x2 - A.x1) * (A.y1 - A.y2);
	return S;
}
int fillArrayByFile(coord* mas, int& N, FILE* input)
{
	if (fopen_s(&input, "input.txt", "r") != 0)
	{
		printf("File error!\n");
		return MY_ERROR_FILE;
	}

	fscanf_s(input, "%i", &N);

	for (int i = 0; i < N; i++)
	{
		fscanf_s(input, "%i", &mas[i].x1);
		fscanf_s(input, "%i", &mas[i].y1);
		fscanf_s(input, "%i", &mas[i].x2);
		fscanf_s(input, "%i", &mas[i].y2);
	}
	fclose(input);
}
int saveArray(coord* mas, int N, FILE* input)
{
	if (fopen_s(&input, "input.txt", "w") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fprintf(input, "%i\n", N);
	for (int i = 0; i < N; i++)
	{
		fprintf(input, "%i\n", mas[i].x1);
		fprintf(input, "%i\n", mas[i].y1);
		fprintf(input, "%i\n", mas[i].x2);
		fprintf(input, "%i\n", mas[i].y2);
	}
	fclose(input);
	return 0;
}
int saveArrayInBinary(FILE* arrayBinary, coord* mas, int N)
{
	if (fopen_s(&arrayBinary, "arrayBinary.bin", "w") != 0)
	{
		printf("File error!\n");
		return MY_ERROR_FILE;
	}
		fwrite(&N, sizeof(int), 1, arrayBinary);
		fwrite(mas, sizeof(coord), N, arrayBinary);
	fclose(arrayBinary);
	return 0;
}
int fillArrayByBinary(FILE* arrayBinary, coord* mas, int &N)
{
	if (fopen_s(&arrayBinary, "arrayBinary.bin", "r") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fread(&N, sizeof(int), 1, arrayBinary);
	fread(mas, sizeof(coord), N, arrayBinary);
	fclose(arrayBinary);
	return 0;
}