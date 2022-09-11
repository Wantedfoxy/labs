﻿#include <iostream>

using namespace std;

//Задание 2: "Упорядочить столбцы булевой матрицы в порядке убывания весов"

int main()
{
	cout << "Boolean matrix:" << endl;
	cout << "0 1 1 1" << endl;
	cout << "0 0 1 1" << endl;
	cout << "1 1 1 0" << endl;
	cout << "0 0 1 1" << endl;

	const int n = 4;

	int a[n] =
	{
		0b1110,
		0b1100,
		0b0111,
		0b1100
	};

	int w[n] = { 0 }; // Массив весов столбцов

	int l = n - 1;

	int i, j;

	_asm
	{
		mov	eax, [n];		Записываем n
		dec	eax;			Уменьшаем на единицу
		mov[l], eax;		Количество сравнений
		lea	esi, [w];		Вес текущего столбца
		mov[i], 1;			Маска
		mov	ecx, [n];		Записываем в счетчик количество столбцов
		
		L1 : 
		lea ebx, [a];		Текущая строка
		push ecx;			Запоминаем счетчик в стек
		mov ecx, [n];		Записываем в счетчик количество строк
		
		L2 : 
		mov	eax, [ebx];		Записываем текущую строку
		and	eax, [i];		Накладываем маску
		je L3;				Если текущий элемент равен нулю, переходим к L3
		inc[esi];			Увеличиваем вес
		
		L3 : 
		add	ebx, 4;			Переходим к следующей строке
		loop L2;			Цикл, перебирающий строки
		pop	ecx;			Возвращаем значение счетчика из стека
		add	esi, 4;			Переходим к следующему столбцу
		shl[i], 1;			Сдвигаем маску на текущий столбец
		loop L1;			Цикл, перебирающий столбцы
		mov	ecx, [l];		Записываем в счетчик количество сравнений
		
		L4 : lea esi, [w];	Вес текущего столбца
		mov	edi, esi;		Записываем вес текущего столбца
		add	edi, 4;			Вес следующего столбца
		mov[i], 1;			Маска текущего столбца
		mov[j], 2;			Маска следующего столбца
		push ecx;			Записываем счетчик в стек
		mov	ecx, [l];		Записываем в счетчик количество сравнений

		L5 :
		mov	eax, [esi];		Записываем вес текущего элемента
		cmp	eax, [edi];		Записываем вес следующего элемента
		jge	L8;				Если текущий больше следующего, переходим к L8
		mov	eax, [esi];		Записываем вес текущего
		mov	edx, [edi];		Записываем вес следующего
		mov[esi], edx;		Записываем вес текущего
		mov[edi], eax;		Записываем вес следующего
		lea	ebx, [a];		Текущая строка
		push ecx;			Записываем счетчик в стек
		mov	ecx, [n];		Записываем в счетчик количество строк

		L6 : mov eax, [ebx];Записываем текущую строку
		and	eax, [i];		Получаем текущий элемент
		mov	edx, [ebx];		Записываем текущую строку
		and	edx, [j];		Получаем следующий элемент
		shr	edx, 1;			Выравниваем следующий элемент по текущему
		cmp	eax, edx;		Сравниваем текущий и слудующий
		je L7;				Если текущий равен следующему, переходим к L7
		mov	eax, [i];		Записываем маску текущего элемента
		xor[ebx], eax;		Инвертируем текущий элемент
		mov	eax, [j];		Записываем маску следующего элемента
		xor[ebx], eax;		Инвертируем следующий элемент

		L7 : add ebx, 4;	Переходим к следующей строке
		loop L6;			Цикл, перебирающий строки
		pop	ecx;			Возвращаем значение счетчика из стека

		L8 : 
		add	esi, 4;			Берем следующий текущий элемент
		add	edi, 4;			Берем следующий следующий элемент
		shl[i], 1;			Сдвигаем маску текущего элемента
		shl[j], 1;			Сдвигаем маску следующего элемента
		loop L5;			Цикл, перебирающий столбцы
		pop	ecx;			Возвращаем значение счетчика из стека
		loop L4;			Цикл, перебирающий столбцы
	}

	cout << "Boolean matrix with columns ordered in descending order of weights:" << endl;

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			cout << (a[j] >> i & 1) << " ";
		}

		cout << endl;
	}

	return 0;
}