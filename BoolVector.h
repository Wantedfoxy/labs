#include <iostream>
#include <string.h>

using namespace std;
typedef unsigned char UC;

class BoolVector
{
	UC *bv;
	int n, m;    	//n -����� ������ �������,
					   //m - ���������� ��������� � ������� bv
					   //����� n � m: m=n/8 ���� n%8=0;
					   //         	  m=n/8+1, ���� n%8!=0
	int Input(const char *, int, int, int);		//������������ �������� ������� bv
	void Output(int, int);                   		 //����� �������� ������� bv

public:

	// ������������, ����������, ���������� ��������� ����������
	BoolVector(int n1 = 1);          			// n1 - ����� ������ �������
	BoolVector(const char *s);
	BoolVector(const char *s, int n);			// strlen(s) != n
	BoolVector(const BoolVector &);
	BoolVector operator= (const BoolVector &);
	~BoolVector() { delete[]bv; }

	//����, �����, ���, ����������� k-� ����������
	void Scan(int);
	void Print();
	int Weight();
	UC operator[] (int);

	//���������
	bool operator== (BoolVector &);
	bool operator!= (BoolVector &);
	bool operator< (BoolVector &y);   	//x<y ���� x[i]<=y[i]
	bool operator> (BoolVector &y);		 //x>y ���� x[i]>=y[i]

   //��������� ��������
	BoolVector operator & (BoolVector &x);		//��������� ����� ������
	BoolVector & operator &=(BoolVector &x);		//���������� *this
	BoolVector operator |(BoolVector &x);			//��������� ����� ������
	BoolVector & operator |=(BoolVector &x);		//���������� *this
	BoolVector operator ^(BoolVector &x);			//��������� ����� ������
	BoolVector & operator ^=(BoolVector &x);		//���������� *this
	BoolVector operator ~();						//���������� *this
	BoolVector operator <<(int);					//��������� ����� ������
	BoolVector  & operator <<=(int);				//���������� *this
	BoolVector operator >>(int);					//��������� ����� ������
	BoolVector operator >>=(int);				//���������� *this


	//��������� ����� ���������� �������
	BoolVector SetUp1(int pos);        	//���������� � 1 ���������� pos
	BoolVector SetUp0(int pos);        	//�������� � 0 ���������� pos
	BoolVector Invert(int pos);           	//������������� ���������� pos

	//��������� ���������� ��������� �������
	BoolVector SetUp1(int kol, int pos);
	//���������� � 1 kol ��������� ������� � ������� pos, ���������� *this
	BoolVector SetUp0(int kol, int pos);
	//�������� � 0 kol ��������� ������� � ������� pos, ���������� *this
	BoolVector Invert(int kol, int pos);
	//������������� kol ��������� ������� � ������� pos, ���������� *this

	friend ostream & operator<< (ostream &r, BoolVector &V);
	friend istream & operator>> (istream &r, BoolVector &V);

};

int BoolVector::Input(const char* s, int bvPos, int sPos, int k)
{
	UC mask = 1;
	bv[bvPos] = 0;
	for (int i = 0; i < k; i++, sPos++)
	{
		bv[bvPos] <<= 1; // ����� ����� �� 1 ���
		if (s[sPos] == '1') bv[bvPos] |= mask;// ������������� 1 � ������ ���
	}
	return sPos;
}

void BoolVector::Output(int bvPos, int k)
{
	UC mask = 1;
	mask <<= k - 1;
	for (int i = 0; i < k; i++)
	{
		if (bv[bvPos] & mask)// �������� bvPos ���� ����� ��������� � ������
		{
			cout << " " << '1';
		}
		else cout << " " << '0';
		mask >>= 1;// ����� ������ �� 1 ���
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
	if (k) {// � ������, ����� n%8 �� ����� 0, ��������� n%8 ���
		sPos = Input(s, bvPos, sPos, k);
		bvPos++;
	}
	for (; bvPos < m; bvPos++)// ��������� ���������
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
		bvPos = 0; sPos = d - n;// ���������� d-n �������� � ������
		if (k) {
			sPos = Input(s, bvPos, sPos, k);
			bvPos++;
		}
		for (; sPos < d; bvPos++)// ��������� ��, ��� ��������
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

BoolVector BoolVector::operator~ ()// �������� ��������� ��������
{
	int i;
	for (i = 0; i < m; i++)// ����������� � ������� ��������� ������ �������
		bv[i] = ~bv[i];
	return *this;
}

void BoolVector::Scan(int n1)// ������� �����, ������������ � ��������� �����
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

void BoolVector::Print()// ������� ������, ������������ � ��������� ������
{
	int k = n % 8; int i = 0;
	if (k)
	{
		Output(0, k); i++;
	}
	for (; i < m; i++)Output(i, 8);
	cout << endl;
}

int BoolVector::Weight()// ������� ����������� ���� �������
{
	int w = 0;
	UC mask = 1;
	for (int i = 0; i < m; i++, mask = 1)
		for (mask <<= 7; mask != 0; mask >>= 1)
			if (bv[i] & mask)w++;// ���������� ����, � ���� ��� ����� 1, ����������� ��� �� 1
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

bool BoolVector::operator== (BoolVector &x)// �������� ��������� ���� ��������
{
	if (n != x.n) return false;
	for (int i = 0; i < m; i++)
		if (bv[i] != x.bv[i]) return false;
	return true;
}

bool BoolVector::operator!= (BoolVector &x)// �������� ����������� ���� ��������
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

BoolVector BoolVector::operator& (BoolVector &x)// �������� �������� �, ���������� ����������� ����� ������
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

BoolVector& BoolVector::operator&= (BoolVector &x)// �������� �������� �, ��������� ������������ � *this
{
	BoolVector res;
	res = (*this & x);
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator| (BoolVector& x)// �������� ���������� ���, ����������� ���������� ����� ������
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

BoolVector& BoolVector::operator|= (BoolVector& x)// �������� ���������� ���, ��������� ������������ � *this
{
	BoolVector res;
	res = (*this | x);
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator^ (BoolVector& x)// �������� ���������� ������������ ���, ���������� ����������� BoolVector
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

BoolVector& BoolVector::operator^= (BoolVector& x)// �������� ���������� ������������ ���, ��������� ������������ � *this
{
	BoolVector res;
	res = (*this) ^ x;
	*this = res;
	return (*this);
}

BoolVector BoolVector::operator<< (int k)// �������� ���������� ������ �����
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

BoolVector BoolVector::operator>>(int k)// �������� ���������� ������ ������
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

BoolVector BoolVector::SetUp1(int i)// �������, ������� ������������� i-� ������� � 1
{
	if (i < 0 || i >= n) cout << "incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		bv[m - 1 - m1] |= mask;
	}
	return (*this);
}

BoolVector BoolVector::SetUp0(int i)// �������, ������� ������������� i-� ������� � 0
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

BoolVector BoolVector::Invert(int i)// �������, ������� ����������� i-� �������
{
	if (i < 0 || i >= n) cout << "Incorrect index" << endl;
	else {
		int m1 = i / 8, k = i % 8;
		UC mask = 1;  mask <<= k;
		bv[m - 1 - m1] ^= mask;
	}
	return (*this);
}

BoolVector BoolVector::SetUp0(int col, int pos)// �������, ������� ������������� col ���������, ������� � pos � 0
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		SetUp0(i);
	}
	return *this;
}

BoolVector BoolVector::SetUp1(int col, int pos)// �������, ������� ������������� col ���������, ������� � pos � 1
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		SetUp1(i);
	}
	return *this;
}

BoolVector BoolVector::Invert(int col, int pos)// �������, ������� ����������� col ���������, ������� � pos
{
	for (int i = pos; (i < n) & (i < pos + col); i++) {
		Invert(i);
	}
	return *this;
}

istream& operator>> (istream& r, BoolVector& x)// �������� �����
{
	x.Scan(x.n); return r;
}

ostream& operator<< (ostream& r, BoolVector& x)// �������� ������
{
	x.Print(); return r;
}