// Zarivnoy Nikolay, home work #3

#include "pch.h"
#include "time.h"
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


struct timeval tv1, tv2, dtv;
struct timezone tz;

// Запоминаем в глобальных переменных текущее время
void time_start()
{
	gettimeofday(&tv1, &tz);
}
// Рассчитываем время прошедшее с момента запуска time_start()
long time_stop()
{
	gettimeofday(&tv2, &tz);
	dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
	dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
		if (dtv.tv_usec < 0)
		{
			dtv.tv_sec--;
			dtv.tv_usec += 1000000;
		}
	return dtv.tv_sec * 1000 + dtv.tv_usec / 1000;
}


// функция обмена позициями
void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// процедура печати массива
void print(int N, int *a)
{
	int i;
	for (i = 0; i < N; i++)
		printf("%d\n", a[i]);
	printf("\n");
}

/// <summary>
/// функция поиска (бинарный алгоритм)
/// </summary>
int Binary(int N,int *a,int trg)
{
	int min = 0;
	int max = N;
	int pos = 0;

	while (true)
	{
		pos = (min + max) / 2;
		if (a[pos] == trg) return pos;
		if (a[pos] > trg)
		{
			max = pos;
		} else if (a[pos] < trg)
		{
			min = pos;
		}
		if (min == max) return -1;

	}

}

/// <summary>
/// демонстрация бинарного поиска
/// </summary>
void Sol3()
{
	// массив заполним от 0 до N-1
	int a[MaxN];
	for (int i = 0; i < MaxN; i++)
	{
		a[i] = i;
	}

	printf("Введите число для поиска, массив заполнен числами от 0 до %d\n",MaxN);
	int variant = 0;
	scanf("%i", &variant);

	variant = Binary(MaxN,a,variant);
	if (variant == -1)
	{
		printf("\nЗначение не найдено!");
	}
	else {
		printf("\nЗначение найдено на позиции %d массива",variant);
	}
}

/// <summary>
/// шейкерная сортировка
/// </summary>
void Sol2()
{
	int a[MaxN]; // создаём массив максимального размера
	int i = 0;
	int min = 0;
	int max = 0;
	int counter = 0;
	// заполняем его произвольными значениями
	for (i=0; i < MaxN; i++)
	{
		a[i] = rand();
	}
	
	puts("Массив до сортировки");
	//print(MaxN, a);
	// сделаем копию, для более точной оценки результатов
	// for (i = 0; i < MaxN; i++) b[i] = a[i];
	
	time_start();

	// непосредствено алгоритм
	// проходим в одну сторону, сортируя все позиции
	// потом в обратную, уменьшая при этом правую и левую границу на -1
	// повторяем до отсутствия свапов в отсторитрованном массиве
	max = MaxN;
	min = 0;
	bool sorted = false;
	while (!sorted)
	{
		for (i = min; i < max - 1; i++)
		{
			sorted = true;
			if (a[i] > a[i + 1])
			{
				swap(&a[i], &a[i + 1]);
				sorted = false;
			}
			counter++;
		}
		max--;
		for (i = max; i > min; i--)
		{
			if (a[i] < a[i - 1])
			{
				swap(&a[i], &a[i - 1]);
			}
			counter++;
		}
		min++;
	}

	double time_elapsed = time_stop();
	puts("Массив после сортиорвки");
	//print(MaxN, a);
	puts("\nСортировка заняла: ");
	printf("%7.2lf\n", time_elapsed);
	puts("Количество операций совершено: ");
	printf("%d\n", counter);
}

/// <summary>
/// пузырьковая сортировка, сравнение не оптимизированной и оптимизированной
/// </summary>
void Sol1()
{
	int a[MaxN]; // создаём массив максимального размера
	int b[MaxN];
	int i = 0;
	int j = 0;
	int counter = 0;
	// заполняем его произвольными значениями
	for (i = 0; i < MaxN; i++)
	{
		a[i] = rand();
	}

	puts("Массив до сортировки");
	//print(MaxN, a);
	// сделаем копию, для более точной оценки результатов
	for (i = 0; i < MaxN; i++) b[i] = a[i];

	time_start();
	for (i = 0; i < MaxN; i++)
		for (j = 0; j < MaxN - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);

			}
			counter++;
		}

	double time_elapsed = time_stop();
	puts("Массив после сортиорвки");
	//print(MaxN, a);
	puts("\nСортировка заняла: ");
	printf("%7.2lf\n", time_elapsed);
	puts("Количество операций совершено: ");
	printf("%d\n", counter);
	// улучшенная сортиорвка

	// сделаем копию, для более точной оценки результатов
	for (i = 0; i < MaxN; i++) a[i] = b[i];
	int counter2 = 0;
	puts("Массив до сортировки");
	//print(MaxN, a);

	bool sorted = true;
	time_start();
	for (i = 0; i < MaxN; i++)
	{
		sorted = true;
		for (j = 0; j < MaxN - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
				sorted = false;
			}
			counter2++;
		}
		if (sorted) break;
	}

	double time_elapsed2 = time_stop();
	puts("Массив после сортиорвки");
	//print(MaxN, a);
	puts("\nСортировка заняла: ");
	printf("%7.2lf\n", time_elapsed2);
	puts("Количество операций совершено: ");
	printf("%d\n", counter2);
	printf("Эффективность оптимизации, : %7.2lf, сек. %d операций", time_elapsed - time_elapsed2, counter - counter2);
}

void Sol4()
{
	Sol1();
	Sol2();
	// результаты измерений
	//								100 эл		1000 эл		10 000 эл		100 000 эл			
	//	алг 1 (пузырьковая)			9900		999 000		99 990 000		1 409 965 408
	//	алг 2 (пузырьковая+)		8910		975 024		99 750 024		1 387 165 636
	//	алг 3 (шейкерная+)			2550		43 032		 1 705 208		29 356 782
	// асимптотическая	(п"2)		10 000		1 000 000	100 000 000		10 000 000 000
	// 		наблюдается достаточно сильное отклонение от асимптотической сложности для шейерной сортировки... где ошибка? :)
}

int main()
{
	setlocale(LC_ALL, "Rus");

	printf("Домашнее задание №3\n");
	printf("Выберите задачу: 1 - пузырьковая сортировка и пузырьковая сортировка с оптимизацией (сравнение)\n");
	printf("Выберите задачу: 2 - шейкерная сортировка с оптимизацией\n");
	printf("Выберите задачу: 3 - бинарный поиск\n");
	printf("Выберите задачу: 4 - измерение количества операций по п.1 и п.2 \n");
	int variant = 0;
	scanf("%i", &variant);
	switch (variant)
	{
	case 1:
		Sol1();
		break;
	case 2:
		Sol2();
		break;
	case 3:
		Sol3();
		break;
	case 4:
		Sol4();
		break;

	default:
		printf("Пока!");
		break;
	}


	return 0;
}
