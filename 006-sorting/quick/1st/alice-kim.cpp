#include <iostream>
using namespace std;

#define MAX_NUM 100

struct Friends {
	char name[10];
	int money;
	int month;
	int day;
	int birth;
};

Friends fList[10];
int input[MAX_NUM];

void quickSortMoneyPoor(int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (fList[input[i]].money <= fList[input[pivot]].money && i < last)
			{
				i++;
			}
			while (fList[input[j]].money > fList[input[pivot]].money)
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSortMoneyPoor(first, j - 1);
		quickSortMoneyPoor(j + 1, last);
	}
}

void quickSortMoney(int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (fList[input[i]].money >= fList[input[pivot]].money && i < last)
			{
				i++;
			}
			while (fList[input[j]].money < fList[input[pivot]].money)
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSortMoney(first, j - 1);
		quickSortMoney(j + 1, last);
	}
}
void quickSortBirth(int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (fList[input[i]].birth <= fList[input[pivot]].birth && i < last)
			{
				i++;
			}
			while (fList[input[j]].birth > fList[input[pivot]].birth)
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSortBirth(first, j - 1);
		quickSortBirth(j + 1, last);
	}
}
void quickSortBirthSlow(int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (fList[input[i]].birth >= fList[input[pivot]].birth && i < last)
			{
				i++;
			}
			while (fList[input[j]].birth < fList[input[pivot]].birth)
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSortBirthSlow(first, j - 1);
		quickSortBirthSlow(j + 1, last);
	}
}
int main(void)
{
	int tc = 0;
	cin >> tc;
	for (int i = 0; i < tc; i++)
	{
		input[i] = i;
		int money;
		char name[10], birth[10];
		cin >> name >> money>> birth;
		strcpy(fList[i].name, name);
		fList[i].money = money;
		int pos = 0;
		int month = 0;
		int day = 0;
		for (; pos <= strlen(birth); pos++) {
			month = month + birth[pos] - '0';
			if (birth[pos + 1] != '/') {
				month = month * 10;
			}
			else {
				pos=pos+2;
				break;
			}
		}
		for (; pos <= strlen(birth); pos++) {
			day = day + birth[pos] - '0';
			if (birth[pos + 1] != '\0') {
				day = day * 10;
			}
			else {
				break;
			}
		}

		fList[i].month = month;
		fList[i].day = day;
		fList[i].birth = month * 100 + day;
	}

	cout << "돈 많은 순서 " << endl;
	quickSortMoney(0, tc - 1);
	for (int i = 0; i < tc; i++) {
		cout << fList[input[i]].name << " : " << fList[input[i]].money << endl;
	}

	cout << endl << "돈 적은 순서 " << endl;
	quickSortMoneyPoor(0, tc - 1);
	for (int i = 0; i < tc; i++) {
		cout << fList[input[i]].name << " : " << fList[input[i]].money << endl;
	}

	cout << endl << "생일 빠른 순서 " << endl << endl;
	quickSortBirth(0, tc - 1);
	for (int i = 0; i < tc; i++) {
		cout << fList[input[i]].name << " : " << fList[input[i]].month << "월 "<<fList[input[i]].day<<"일" << endl;
	}

	cout << endl << "생일 느린 순서 " << endl << endl;
	quickSortBirthSlow(0, tc - 1);
	for (int i = 0; i < tc; i++) {
		cout << fList[input[i]].name << " : " << fList[input[i]].month << "월 " << fList[input[i]].day << "일" << endl;
	}

	return 0;
}