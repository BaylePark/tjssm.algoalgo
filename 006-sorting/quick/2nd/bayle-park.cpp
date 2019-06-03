#include <stdio.h>

struct Person {
	char name[7];
	int money;
	char birthday[6];
	int month;
	int day;
};

typedef bool (*compare_fn)(const Person& p1, const Person& p2);

void quick_sort(Person data[], int first, int last, compare_fn cmpfn)
{
	int pivot;
	int i;
	int j;
	Person temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (cmpfn(data[i], data[pivot]) && i < last)
			{
				i++;
			}
			while (!cmpfn(data[j], data[pivot]))
			{
				j--;
			}
			if (i < j)
			{
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}

		temp = data[pivot];
		data[pivot] = data[j];
		data[j] = temp;

		quick_sort(data, first, j - 1, cmpfn);
		quick_sort(data, j + 1, last, cmpfn);
	}
}

bool birthday_asc(const Person& p1, const Person& p2) {
	if (p1.month < p2.month) return true;
	else if (p1.month == p2.month && p1.day <= p2.day) return true;
	else return false;
}
bool birthday_desc(const Person& p1, const Person& p2) {
	if (p1.month > p2.month) return true;
	else if (p1.month == p2.month && p1.day >= p2.day) return true;
	else return false;
}
bool money_asc(const Person& p1, const Person& p2) {
	return p1.money <= p2.money;
}
bool money_desc(const Person& p1, const Person& p2) {
	return p1.money >= p2.money;
}
void print_all(const Person people[], const int count) {
	for (int i = 0; i < count; i++) {
		printf("%s %d %s\n", people[i].name, people[i].money, people[i].birthday);
	}
}

inline int _ctoi(const char c) {
	return (int)(c - '0');
}

void parse_birthday(Person& p) {
	int len = 0;
	p.month = p.day = 0;
	int* target = &(p.month);
	while (char c = p.birthday[len++]) {
		if (c == '/') {
			target = &(p.day);
			continue;
		}
		*target *= 10;
		*target += _ctoi(c);
	}
}

int main() {
	int N;
	Person people[100] = { 0 };
	int count = 0;

	scanf("%d", &N);

	while (N--) {
		Person& p = people[count++];
		scanf("%s %d %s", p.name, &(p.money), p.birthday);
		parse_birthday(p);
	}

	printf("\n돈 많은 순서 :\n");
	quick_sort(people, 0, count - 1, money_desc);
	print_all(people, count);

	printf("\n돈 적은 순서 :\n");
	quick_sort(people, 0, count - 1, money_asc);
	print_all(people, count);

	printf("\n생일 빠른 순서 :\n");
	quick_sort(people, 0, count - 1, birthday_asc);
	print_all(people, count);

	printf("\n생일 느린 순서 :\n");
	quick_sort(people, 0, count - 1, birthday_desc);
	print_all(people, count);
}