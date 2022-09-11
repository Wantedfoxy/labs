#include <iostream>
#include <string.h>

using namespace std;
typedef unsigned char UC;

class BoolVector
{
	UC *bv;
	int n, m;    	//n -длина булева вектора,
					   //m - количество элементов в массиве bv
					   //связь n и m: m=n/8 если n%8=0;
					   //         	  m=n/8+1, если n%8!=0
	int Input(const char *, int, int, int);		//формирование элемента массива bv
	void Output(int, int);                   		 //вывод элемента массива bv

public:

	// конструкторы, деструктор, перегрузка оператора присвоения
	BoolVector(int n1 = 1);          			// n1 - длина булева вектора
	BoolVector(const char *s);
	BoolVector(const char *s, int n);			// strlen(s) != n
	BoolVector(const BoolVector &);
	BoolVector operator= (const BoolVector &);
	~BoolVector() { delete[]bv; }

	//ввод, вывод, вес, определение k-й компоненты
	void Scan(int);
	void Print();
	int Weight();
	UC operator[] (int);

	//сравнение
	bool operator== (BoolVector &);
	bool operator!= (BoolVector &);
	bool operator< (BoolVector &y);   	//x<y если x[i]<=y[i]
	bool operator> (BoolVector &y);		 //x>y если x[i]>=y[i]

   //побитовые операции
	BoolVector operator & (BoolVector &x);		//создается новый вектор
	BoolVector & operator &=(BoolVector &x);		//изменяется *this
	BoolVector operator |(BoolVector &x);			//создается новый вектор
	BoolVector & operator |=(BoolVector &x);		//изменяется *this
	BoolVector operator ^(BoolVector &x);			//создается новый вектор
	BoolVector & operator ^=(BoolVector &x);		//изменяется *this
	BoolVector operator ~();						//изменяется *this
	BoolVector operator <<(int);					//создается новый вектор
	BoolVector  & operator <<=(int);				//изменяется *this
	BoolVector operator >>(int);					//создается новый вектор
	BoolVector operator >>=(int);				//изменяется *this


	//Изменение одной компоненты вектора
	BoolVector SetUp1(int pos);        	//установить в 1 компоненту pos
	BoolVector SetUp0(int pos);        	//сбросить в 0 компоненту pos
	BoolVector Invert(int pos);           	//инвертировать компоненту pos

	//Изменение нескольких компонент вектора
	BoolVector SetUp1(int kol, int pos);
	//установить в 1 kol компонент начиная с позиции pos, изменяется *this
	BoolVector SetUp0(int kol, int pos);
	//сбросить в 0 kol компонент начиная с позиции pos, изменяется *this
	BoolVector Invert(int kol, int pos);
	//инвертировать kol компонент начиная с позиции pos, изменяется *this

	friend ostream & operator<< (ostream &r, BoolVector &V);
	friend istream & operator>> (istream &r, BoolVector &V);

};

int BoolVector::Input(const char* s, int bvPos, int sPos, int k)
{
	UC mask = 1;
	bv[bvPos] = 0;
	for (int i = 0; i < k; i++, sPos++)
	{
		bv[bvPos] <<= 1; // Сдвиг влево на 1 бит
		if (s[sPos] == '1') bv[bvPos] |= mask;// Устанавливаем 1 в правый бит
	}
	return sPos;
}

void BoolVector::Output(int bvPos, int k)
{
	UC mask = 1;
	mask <<= k - 1;
	for (int i = 0; i < k; i++)
	{
		if (bv[bvPos] & mask)// Проверка bvPos бита путем сравнения с маской
		{
			cout << " " << '1';
		}
		else cout << " " << '0';
		mask >>= 1;// Сдвиг вправо на 1 бит
	}
}

BoolVector::BoolVector(int n1)
{
	m = n1 / 8;
	int k = n1 % 8;
	if (k)
		m++;
	bv = new UC[m];
	n = n1;
	for (int i = 0; i < m; i++)
		bv[i] = 0;
}

BoolVector::BoolVector(const BoolVector& x)
{
	n = x.n;
	m = x.m;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
		bv[i] = x.bv[i];
}

BoolVector::BoolVector(const char* s)
{
	n = strlen(s);
	m = n / 8; int k = n % 8;
	if (k) m++;
	bv = new UC[m];

	int sPos = 0, bvPos = 0;
	if (k) {// В случае, когда n%8 не равен 0, заполняем n%8 бит
		sPos = Input(s, bvPos, sPos, k);
		bvPos++;
	}
	for (; bvPos < m; bvPos++)// Заполняем полностью
		sPos = Input(s, bvPos, sPos, 8);
}

BoolVector::BoolVector(const char* s, int kol)
{
	int d = strlen(s);
	n = kol;
	m = n / 8; int k = n % 8;
	if (k) m++;
	bv = new UC[m];

	int bvPos, sPos;
	if (d >= n)
	{
		bvPos = 0; sPos = d - n;// Откидываем d-n символов в строке
		if (k) {
			sPos = Input(s, bvPos, sPos, k);
			bvPos++;
		}
		for (; sPos < d; bvPos++)// Заполняем те, что остались
			sPos = Input(s, bvPos, sPos, 8);
	}
	else {
		int m2 = d / 8; int k2 = d % 8; sPos = 0;
		if (k2) m2++;

		for (bvPos = 0; bvPos < m - m2; bvPos++) {
			bv[bvPos] = 0;
		}
		if (k2) {
			sPos = Input(s, bvPos, 0, k2);
			bvPos++;
		}
		for (; sPos < d; bvPos++)
			sPos = Input(s, bvPos, sPos, 8);
	}
}

BoolVector BoolVector::operator=(const BoolVector& x)
{
	if (this != &x)
	{
		if (m != x.m)
		{
			delete[]bv;
			m = x.m;
			bv = new UC[m];
		}
		for (int i = 0; i < m; i++)
			bv[i] = x.bv[i];
		n = x.n;
	}
	return *this;
}

BoolVector BoolVector::operator~ ()// Оператор побитовой инверсии
{
	int i;
	for (i = 0; i < m; i++)// инвертируем с помощью отрицания каждый элемент
		bv[i] = ~bv[i];
	return *this;
}

void BoolVector::Scan(int n1)// Функция ввода, используется в операторе ввода
{
	char* s; int m1, k;
	s = new char[n1];
	cin >> s;

	m1 = n1 / 8; k = n1 % 8;
	if (k) m1++;

	if (m != m1)
	{
		delete[]bv;
		m = m1;
		bv = new UC[m];
	}
	n = n1;
	int bvPos = 0, sPos = 0;
	if (k)
	{
		sPos = Input(s, bvPos, sPos, k);
		bvPos++;
	}
	for (; sPos < n; bvPos++)
		sPos = Input(s, bvPos, sPos, 8);
}

void BoolVector::Print()// Функция вывода, используется в операторе вывода
{
	int k = n % 8; int i = 0;
	if (k)
	{
		Output(0, k); i++;
	}
	for (; i < m; i++)Output(i, 8);
	cout << endl;
}

int BoolVector::Weight()// Функция определения веса вектора
{
	int w = 0;
	UC mask = 1;
	for (int i = 0; i < m; i++, mask = 1)
		for (mask <<= 7; mask != 0; mask >>= 1)
			if (bv[i] & mask)w++;// Сравниваем биты, и если они равны 1, увеличиваем вес на 1
	return w;
}

UC BoolVector::operator[] (int i)
{
	int m1 = i / 8, k = i % 8;
	UC mask = 1;
	mask <<= k;
	if (bv[m - 1 - m1] & mask) return '1';
	else return '0';
}

bool BoolVector::operator== (BoolVector &x)// Оператор сравнения двух векторов
{
	if (n != x.n) return false;
	for (int i = 0; i < m; i++)
		if (bv[i] != x.bv[i]) return false;
	return true;
}

bool BoolVector::operator!= (BoolVector &x)// Оператор неравенства двух векторов
{
	if (*this == x)return false;
	else return true;
}

bool BoolVector::operator< (BoolVector &x)
{
	if (n != x.n) return false;
	for (int i = 0; i < m; i++)
		if (bv[i] >= x.bv[i]) return false;
	return true;
}

bool BoolVector::operator> (BoolVector &x)
{
	if (n != x.n) return false;
	for (int i = 0; i < m; i++)
		if (bv[i] <= x.bv[i]) return false;
	return true;
}

BoolVector BoolVector::operator& (BoolVector &x)// Оператор побитого и, возвращает результатом новый вектор
{
	int N = n, bvRes = m - 1;
	if (N > x.n)
	{
		N = x.n;
		bvRes = x.m - 1;
	}
	BoolVector Res(N);
	int bvPos, bvX;
	for (bvPos = m - 1, bvX = x.m - 1; bvRes >= 0; bvPos--, bvX--, bvRes--)
		Res.bv[bvRes] = bv[bvPos] & x.bv[bvX];
	return Res;
}

BoolVector& BoolVector::operator&= (BoolVector &x)// Оператор побитого и, результат записывается в *this
{
	BoolVector res;
	res = (*this & x);
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator| (BoolVector& x)// Оператор побитового или, результатом возвращает новый вектор
{
	int n1 = n, bvRes = m - 1;


	if (x.n > n1)
	{
		n1 = x.n;
		bvRes = x.m - 1;

	}
	BoolVector res(n1);

	int bvPos, bvX;
	for (bvPos = m - 1, bvX = x.m - 1; ((bvPos >= 0) && (bvX >= 0)); bvPos--, bvX--, bvRes--)
		res.bv[bvRes] = bv[bvPos] | x.bv[bvX];
	if (bvPos >= 0)
		for (; bvRes > 0; bvRes--, bvPos--)
		{
			res.bv[bvRes] = bv[bvPos];
		}
	if (bvX >= 0)
		for (; bvRes > 0; bvRes--, bvX--)
		{
			res.bv[bvRes] = bv[bvX];
		}

	return res;

}

BoolVector& BoolVector::operator|= (BoolVector& x)// Оператор побитового или, результат записывается в *this
{
	BoolVector res;
	res = (*this | x);
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator^ (BoolVector& x)// Оператор побитового исключающего или, возвращает результатом BoolVector
{
	int n1 = n, bvRes = m - 1;


	if (x.n > n1)
	{
		n1 = x.n;
		bvRes = x.m - 1;

	}
	BoolVector res(n1);

	int bvPos, bvX;
	for (bvPos = m - 1, bvX = x.m - 1; ((bvPos >= 0) && (bvX >= 0)); bvPos--, bvX--, bvRes--)
		res.bv[bvRes] = bv[bvPos] ^ x.bv[bvX];
	if (bvPos >= 0)
		for (; bvRes > 0; bvRes--, bvPos--)
		{
			res.bv[bvRes] = bv[bvPos];
		}
	if (bvX >= 0)
		for (; bvRes > 0; bvRes--, bvX--)
		{
			res.bv[bvRes] = bv[bvX];
		}

	return res;

}

BoolVector& BoolVector::operator^= (BoolVector& x)// Оператор побитового исключающего или, результат записывается в *this
{
	BoolVector res;
	res = (*this) ^ x;
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator<< (int k)// Оператор побитового сдвига влево
{
	BoolVector res = (*this);
	if (k >= n) for (int i = 0; i < m; i++) bv[i] = 0;
	else {
		for (int i = n - 1; i >= k; i--) {
			if (res[i - k] == '1') {
				res.SetUp1(i);
			}
			else { res.SetUp0(i); }
		}
	}
	res.SetUp0(k, 0);
	return res;
}

BoolVector& BoolVector::operator<<=(int k)
{
	BoolVector res = *this;
	res = res << k;
	*this = res;
	return *this;
}

BoolVector BoolVector::operator>>(int k)// Оператор побитового сдвига вправо
{
	int temp = k;
	int i;
	for (i = 0; temp < n; i++, temp++)
	{
		if (operator[](temp) == '1')
		{
			this->SetUp1(i);
		}
		else
		{
			this->SetUp0(i);
		}
	}
	for (; i < n; i++)
	{
		this->SetUp0(i);
	}
	return *this;
}

BoolVector BoolVector::operator>>=(int k)
{
	BoolVector res = *this;
	res = res >> k;
	*this = res;
	return *this;
}

BoolVector BoolVector::SetUp1(int i)// Функция, которая устанавливает i-й элемент в 1
{
	if (i < 0 || i >= n) cout << "incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		bv[m - 1 - m1] |= mask;
	}
	return (*this);
}

BoolVector BoolVector::SetUp0(int i)// Функция, которая устанавливает i-й элемент в 0
{
	if (i < 0 || i >= n) cout << "Incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		mask = ~(mask);
		bv[m - 1 - m1] &= mask;
	}
	return (*this);
}

BoolVector BoolVector::Invert(int i)// Функция, которая инвертирует i-й элемент
{
	if (i < 0 || i >= n) cout << "Incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		bv[m - 1 - m1] ^= mask;
	}
	return (*this);
}

BoolVector BoolVector::SetUp0(int col, int pos)// Функция, которая устанавливает col элементов, начиная с pos в 0
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		SetUp0(i);
	}
	return *this;
}

BoolVector BoolVector::SetUp1(int col, int pos)// Функция, которая устанавливает col элементов, начиная с pos в 1
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		SetUp1(i);
	}
	return *this;
}

BoolVector BoolVector::Invert(int col, int pos)// Функция, которая инвертирует col элементов, начиная с pos
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		Invert(i);
	}
	return *this;
}

istream& operator>> (istream& r, BoolVector& x)// Оператор ввода
{
	x.Scan(x.n); return r;
}

ostream& operator<< (ostream& r, BoolVector& x)// Оператор вывода
{
	x.Print(); return r;
}