#include <iostream>
using namespace std;

#define SORT_QUICK 1
#define MAX_STR 20
#define TYPE_M 0
#define TYPE_B 1
#define ORDER_D 0
#define ORDER_A 1
int N;

typedef struct tagData {
	char name[MAX_STR];
	char birthday[MAX_STR];
	int type[2];
}User;

User user[100];

int getNum(char* day) {
	int num = 0;
	int idx = 0;
	while (day[idx]) {
		if (num != 0) {
			num *= 10;
		}
		num += day[idx] - '0';
		idx++;
	}
	return num;
}
int getBirthdayInt(char *str) {
	char m[3];
	char d[3];
	int dayIdx = 0;
	
	int idx = 0;
	int flag = 0;
	while (str[idx]) {
		if (str[idx] == '/') {
			flag = 1;
			m[dayIdx] = '\0';
			dayIdx = 0;
			idx++;
			continue;
		}
			
		if (flag == 0) {
			m[dayIdx++] = str[idx];
		}
		else {
			d[dayIdx++] = str[idx];
		}
		idx++;
	}
	d[dayIdx] = '\0';
	int returnValue = (getNum(m) * 31) + (getNum(d));
	return returnValue;
}

void quickSort(int type, int order, int first, int last)
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
			if (order == ORDER_D) {
				while (user[i].type[type] <= user[pivot].type[type] && i < last)
				{
					i++;
				}
				while (user[j].type[type] > user[pivot].type[type])
				{
					j--;
				}
			}
			else {
				while (user[i].type[type] >= user[pivot].type[type] && i < last)
				{
					i++;
				}
				while (user[j].type[type] < user[pivot].type[type])
				{
					j--;
				}
			}

			if (i < j)
			{
				temp = user[i];
				user[i] = user[j];
				user[j] = temp;
			}
		}

		temp = user[pivot];
		user[pivot] = user[j];
		user[j] = temp;

		quickSort(type, order, first, j - 1);
		quickSort(type, order, j + 1, last);
	}
}

void printResult()
{
	int i;

	for (i = 0; i < N; ++i)
	{
		cout << "name:" << user[i].name << '\t' << "money:" << user[i].type[TYPE_M] << '\t' << "birthday:" << user[i].birthday << endl;
	}
}


int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> user[i].name;
		cin >> user[i].type[TYPE_M];
		cin >> user[i].birthday;
		user[i].type[TYPE_B] = getBirthdayInt(user[i].birthday);
	}
	cout << endl;
	printResult();

	cout << endl << endl;
	cout << "MONEY ORDER_A" << endl;
	quickSort(TYPE_M, ORDER_A, 0, N - 1); 
	printResult();
	cout << "MONEY ORDER_D" << endl;
	quickSort(TYPE_M, ORDER_D, 0, N - 1); 
	printResult();

	cout << endl;
	cout << "BIRTHDAY ORDER_A" << endl; 
	quickSort(TYPE_B, ORDER_A, 0, N - 1);  
	printResult();
	cout << "BIRTHDAY ORDER_D" << endl;
	quickSort(TYPE_B, ORDER_D, 0, N - 1);  
	printResult();


	return 0;
}