/*
6
김정윤 10000 1/4
박병훈 1000 2/26
박동완 4000 7/12
임익균 300000 12/11
심기성 150000 3/24
조효진 2000 3/8
*/

#include <iostream>
using namespace std;

#define MAX_NUM 100

#define ASCENDING_ORDER 1
#define DESCENDING_ORDER 0

#define TYPE_MONEY 0
#define TYPE_BIRTHDAY 1

#define TRUE 1
#define FALSE 0


typedef struct tagData {
	char name[10];
	int money;
	int month;
	int day;
	int birthday;
}User;

User arr[10];
int input[MAX_NUM];
int num;

void quickSort(int first, int last, int order, int type)
{
	int pivot;
	int i;
	int j;
	User temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			if (ASCENDING_ORDER == order) {
				if (TYPE_MONEY == type) {
					while (arr[i].money <= arr[pivot].money && i < last)
					{
						i++;
					}
					while (arr[j].money > arr[pivot].money)
					{
						j--;
					}
				}
				else {
					while (arr[i].birthday <= arr[pivot].birthday && i < last)
					{
						i++;
					}
					while (arr[j].birthday > arr[pivot].birthday)
					{
						j--;
					}
				}
			}
			else {
				if (TYPE_MONEY == type) {
					while (arr[i].money >= arr[pivot].money && i < last)
					{
						i++;
					}
					while (arr[j].money < arr[pivot].money)
					{
						j--;
					}
				}
				else {
					while (arr[i].birthday >= arr[pivot].birthday && i < last)
					{
						i++;
					}
					while (arr[j].birthday < arr[pivot].birthday)
					{
						j--;
					}
				}

			}

			if (i < j)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}

		temp = arr[pivot];
		arr[pivot] = arr[j];
		arr[j] = temp;

		quickSort(first, j - 1, order, type);
		quickSort(j + 1, last, order, type);
	}
}

void printResult(void)
{
	int i;

	for (i = 0; i < num; ++i)
	{
		printf("%d ", input[i]);
	}
	printf("\n");
}

// 3/24
// 3/8
// 12/11
void getBirthday(User *user, char birthday[]) {
	int idx = 0;
	int month;
	int day;

	int m[2];
	int mCur = 0;
	int d[2];
	int dCur = 0;
	int isMonth = TRUE;
	while (birthday[idx]) {
		char ch = birthday[idx];
		if (ch == '/') {
			isMonth = FALSE;
			idx++;
			continue;
		}
		
		if (isMonth == TRUE) {
			m[mCur++] = ch - '0';
		}
		else {
			d[dCur++] = ch - '0';
		}
		idx++;
	}

	int month_ = 0;
	if (mCur == 1) {
		month_ = m[0];
	}
	if (mCur == 2) {
		month_ = m[0] * 10;
		month_ = month_+m[1];
	}

	int day_ = 0;
	if (dCur == 1) {
		day_ = d[0];
	}
	if (dCur == 2) {
		day_ = d[0] * 10;
		day_ = day_ + d[1];
	}

	user->month = month_;
	user->day = day_;
	user->birthday = (month_ * 31) + (day_);
}

void print_(int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i].name << " ";
		cout << arr[i].money << " ";
		cout << arr[i].month << "/";
		cout << arr[i].day << endl;
	}
	cout << endl;
}

int main() {
	freopen("input.txt", "r", stdin);
	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin>>arr[i].name;
		cin >> arr[i].money;
		char birthday[10];
		cin >> birthday;
		getBirthday(&arr[i], birthday);

	}
	cout << endl;

	cout << "ORIGIN" << endl;
	print_(n);

	cout << "ASCENDING_ORDER TYPE_MONEY" << endl;
	quickSort(0, n - 1, ASCENDING_ORDER, TYPE_MONEY);
	print_(n);
	
	cout << "DESCENDING_ORDER TYPE_MONEY" << endl;
	quickSort(0, n - 1, DESCENDING_ORDER, TYPE_MONEY);
	print_(n);
	
	cout << "ASCENDING_ORDER TYPE_BIRTHDAY" << endl;
	quickSort(0, n - 1, ASCENDING_ORDER, TYPE_BIRTHDAY);
	print_(n);
	
	cout << "DESCENDING_ORDER TYPE_BIRTHDAY" << endl;
	quickSort(0, n - 1, DESCENDING_ORDER, TYPE_BIRTHDAY);
	print_(n);

	return 0;
}
