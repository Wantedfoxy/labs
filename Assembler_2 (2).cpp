#include <cstdio>

#define N 4

int main()
{
	unsigned matrix[N] =
	{
		0b0100,
		0b0100,
		0b0111,
		0b1001
	};

	printf("Matrix:\n");
	for (int i = 0; i < N; i++) {
		for (unsigned j = unsigned(1) << (N - 1); j != 0; j >>= 1) {
			printf("%c", (matrix[i] & j) ? '1' : '0');
		}
		printf("\n");
	}

	__asm {
		mov ecx, N - 2; Регистром ecx проходим по строкам булевой матрицы от N - 2 до 0 включительно(цикл L1).
		L1:     mov edx, ecx; В каждой строке проходим по элементам от ecx + 1 до N - 1 включительно(цикл L2)
				add edx, 1; и для каждого такого элемента Aij меняем его местами с противоположным элементом Aji.
				mov esi, N - 1; Ввиду того, что числа, к сожалению, в этом мире мы почему - то пишем задом наперед, приходится использовать два регистра
				sub esi, ecx; esi: = N - 1 - ecx, edi : = N - 1 - edx, которые проходят промежуток[ecx / edx, N - 1] задом наперед.
				mov edi, N - 1; Они нужны для индексации бита строки в инструкциях bt, btc.
				sub edi, edx
				L2 : bt[matrix + 4 * ecx], edi; В L2 проверяем какое значение{ 0, 1 } находится в Аij, Aji.Случаи 0 0, 1 1 (E)пропускаем.
					 jc A; Для случаев 0 1, 1 0 (B)инвертируем элементы.Таким образом производится обмен местами битовых элементов Aij, Aji
					 bt[matrix + 4 * edx], esi; 0 .
					 jc B; 0 1
					 jmp E; 0 0
					 A:      bt[matrix + 4 * edx], esi; 1 .
							 jc E; 1 1
							 B:      btc[matrix + 4 * edx], esi; 1 0, 0 1
									 btc[matrix + 4 * ecx], edi;
	E:      inc edx; 0 0, 1 1
		dec edi
		cmp edx, N
		jnz L2
		dec ecx
		jge L1
	}

	printf("\n\nTransposed matrix:\n");
	for (int i = 0; i < N; i++) {
		for (unsigned j = unsigned(1) << (N - 1); j != 0; j >>= 1) {
			printf("%c", (matrix[i] & j) ? '1' : '0');
		}
		printf("\n");
	}

	return 0;
}