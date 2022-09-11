#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
#define TAB_SIZE 256

void fillTab(int *tab, string &subStr)
{
	fill(tab, tab + TAB_SIZE, subStr.length());
	for (int i = 0; i < subStr.length() - 1; i++)
	{
		tab[subStr[i]] = subStr.length() - i - 1;
	}// занесение в TAB-массив расстояние до конца подстроки символов из подстроки
	// чтобы в случае несовпадения свинуться на это расстояние
}

int calcTab(int*tab, string &subStr, string &str, int j)// функция, пробегающая справа налево и сравнивающая подстроку со строкой
{
	int m = subStr.length();
	for (int i = m - 1; i >= 0 and j >= 0; i--, j--)
	{
		if (subStr[i] != str[j])
		{
			return tab[str[j]];// в случае несоответствия возвращает число, на которое необходимо сместиться
		}
	}

	return 0;
}

int bmSearch(int *tab, string subStr, string str)
{
	fillTab(tab, subStr);
	int m = subStr.length(), nTab;

	for (int j = m - 1; j < str.length();)// идем по строке и ищем совпадение по алгоритму
	{
		nTab = calcTab(tab, subStr, str, j);// значение смещения
		cout << "Shift = " << nTab << endl;
		if (nTab == 0) return j - m + 1;
		else j += nTab;
	}

	return -1;
}

int main() {

	int dictionary[TAB_SIZE];// таблица сдвигов (TAB-массив)

	string x = "y";
	while (x == "y")
	{
		string subStr, str;

		cout << "Enter the string in which the search will be carried out: " << endl;
		getline(cin, str);
		cout << "Enter the substring that will be searched for: " << endl;
		getline(cin, subStr);

		cout << bmSearch(dictionary, subStr, str) << endl;

		cout << "Would you like to continue? Enter y if you want to continue\n";
		cin >> x;
		while (cin.get() != '\n');// эта строка нужна для того,
		//чтобы при повторном поиске не пропустился ввод строки
	}

	return 0;
}