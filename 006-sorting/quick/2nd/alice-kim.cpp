#include <iostream>
using namespace std;

#define MAX_NUM 100

struct Person {
	char birthday[6];
	int money;
	int birth;
	char name[6];
};

Person person[MAX_NUM];
void quickSort(int first, int last);
void quickSortmoney2(int first, int last);
void quickSortBirth(int first, int last);
void quickSortBirth2(int first, int last);
int sort[MAX_NUM];

void printResult(bool money)
{
	int i;
	if (money) {
		for (i = 0; i < 6; ++i)
		{
			cout << "이름 : " << person[sort[i]].name << "  의 " << person[sort[i]].money << endl;
		}
	}
	else {
		for (i = 0; i < 6; ++i)
		{
			cout << "이름 : " << person[sort[i]].name << "  의 생일 " << person[sort[i]].birthday << endl;
		}
	}
	printf("\n");
}

int main(void)
{
	int T;
	int test_case;
	int i;

	scanf("%d", &T);

	for (test_case = 0; test_case < T; test_case++)
	{
		sort[test_case] = test_case;
		char tmp[100];
		cin >> tmp;
		strcpy(person[test_case].name, tmp);
		int money;
		cin >> money;
		person[test_case].money = money;
		cin >> tmp;
		strcpy(person[test_case].birthday, tmp);
		int idx = 0;
		int tmpDate = 0;
		while (tmp[idx] != 0) {
			if (tmp[idx] == '\/') {
				person[test_case].birth = tmpDate * 100;
				tmpDate = 0;
			}
			else {
				int tmpDate2 = tmp[idx] - '0';
				if (tmpDate > 0) {
					tmpDate *= 10;
				}
				tmpDate += tmpDate2;
			}
			idx++;
		}
		person[test_case].birth += tmpDate;

	}
	quickSort(0, T - 1);
	printResult(true);

	quickSortmoney2(0, T - 1);
	printResult(true);

	quickSortBirth2(0, T - 1);
	printResult(false);

	quickSortBirth(0, T - 1);
	printResult(false);
	return 0;
}

void quickSort(int first, int last)
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
			while (person[sort[i]].money <= person[sort[pivot]].money && i < last)
			{
				i++;
			}
			while (person[sort[j]].money > person[sort[pivot]].money)
			{
				j--;
			}
			if (i < j)
			{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}

		temp = sort[pivot];
		sort[pivot] = sort[j];
		sort[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}


void quickSortmoney2(int first, int last)
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
			while (person[sort[i]].money >= person[sort[pivot]].money && i < last)
			{
				i++;
			}
			while (person[sort[j]].money < person[sort[pivot]].money)
			{
				j--;
			}
			if (i < j)
			{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}

		temp = sort[pivot];
		sort[pivot] = sort[j];
		sort[j] = temp;

		quickSortmoney2(first, j - 1);
		quickSortmoney2(j + 1, last);
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
			while (person[sort[i]].birth <= person[sort[pivot]].birth && i < last)
			{
				i++;
			}
			while (person[sort[j]].birth > person[sort[pivot]].birth)
			{
				j--;
			}
			if (i < j)
			{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}

		temp = sort[pivot];
		sort[pivot] = sort[j];
		sort[j] = temp;

		quickSortBirth(first, j - 1);
		quickSortBirth(j + 1, last);
	}
}


void quickSortBirth2(int first, int last)
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
			while (person[sort[i]].birth >= person[sort[pivot]].birth && i < last)
			{
				i++;
			}
			while (person[sort[j]].birth < person[sort[pivot]].birth)
			{
				j--;
			}
			if (i < j)
			{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}

		temp = sort[pivot];
		sort[pivot] = sort[j];
		sort[j] = temp;

		quickSortBirth2(first, j - 1);
		quickSortBirth2(j + 1, last);
	}
}
