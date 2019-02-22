#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_TABLE 100
#define MAX_BIRTH_STR_SIZE 5
#define MAX_NAME_SIZE 20

struct Table {
	int money;
	int birthday;
	char name[MAX_NAME_SIZE + 1];
	char strBirthday[MAX_BIRTH_STR_SIZE + 1];
} DB[MAX_TABLE];
int TableCount = 0;

#define OFFSET(ptr, offset) (*(int*)(((char*)&(ptr))+(offset)))

void quickSort(Table db[], int first, int last, const int byteOffset)
{
	int pivot;
	int i;
	int j;
	Table temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (OFFSET(db[i], byteOffset) <= OFFSET(db[pivot], byteOffset) && i < last)
			{
				i++;
			}
			while (OFFSET(db[j], byteOffset) > OFFSET(db[pivot], byteOffset))
			{
				j--;
			}
			if (i < j)
			{
				temp = db[i];
				db[i] = db[j];
				db[j] = temp;
			}
		}

		temp = db[pivot];
		db[pivot] = db[j];
		db[j] = temp;

		quickSort(db, first, j - 1, byteOffset);
		quickSort(db, j + 1, last, byteOffset);
	}
}

void quickSortReverse(Table db[], int first, int last, const int byteOffset)
{
	int pivot;
	int i;
	int j;
	Table temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (OFFSET(db[i], byteOffset) >= OFFSET(db[pivot], byteOffset) && i < last)
			{
				i++;
			}
			while (OFFSET(db[j], byteOffset) < OFFSET(db[pivot], byteOffset))
			{
				j--;
			}
			if (i < j)
			{
				temp = db[i];
				db[i] = db[j];
				db[j] = temp;
			}
		}

		temp = db[pivot];
		db[pivot] = db[j];
		db[j] = temp;

		quickSortReverse(db, first, j - 1, byteOffset);
		quickSortReverse(db, j + 1, last, byteOffset);
	}
}

void printResult(const int num, const Table db[])
{
	for (int i = 0; i < num; ++i)
	{
		printf("%2d. %5s %7d %5s\n", i + 1, db[i].name, db[i].money, db[i].strBirthday);
	}
}

void parseBirthday(Table& db) {
	int idx = 0;
	bool checkdate = false;
	db.birthday = 0;
	while (db.strBirthday[idx] != '\0') {
		if (db.strBirthday[idx] == '/') {
			checkdate = true;
			idx++;
			continue;
		}
		db.birthday *= 10;
		if (checkdate && db.strBirthday[idx + 1] == '\0') {
			checkdate = false;
			continue;
		}
		else {
			checkdate = false;
			db.birthday += db.strBirthday[idx] - '0';
		}
		idx++;
	}
}

/*
6
김정윤 10000 1/4
박병훈 1000 2/26
박동완 4000 7/12
임익균 300000 12/11
심기성 150000 3/24
조효진 2000 3/8
*/

int main(void)
{
	int num;
	scanf("%d", &num);

	for (int i = 0; i < num; i++)
	{
		Table &db = DB[TableCount++];
		scanf("%s %d %s", db.name, &db.money, db.strBirthday);
		parseBirthday(db);
	}
	printf("sorting...\n");
	printf("\tby Money (ASC)\n");
	quickSort(DB, 0, num - 1, 0);
	printResult(num, DB);
	
	printf("\n\tby Money (DESC)\n");
	quickSortReverse(DB, 0, num - 1, 0);
	printResult(num, DB);

	printf("\n\tby Birth (ASC)\n");
	quickSort(DB, 0, num - 1, sizeof(int));
	printResult(num, DB);

	printf("\n\tby Birth (Desc)\n");
	quickSortReverse(DB, 0, num - 1, sizeof(int));
	printResult(num, DB);

	return 0;
}