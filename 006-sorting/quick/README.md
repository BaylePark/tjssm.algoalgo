# Quick sort

## 기본 내용
- 40분 해결

## 목표
- 레퍼런스 코드 이용해 다양한 방식으로 sorting 해보기
- 레퍼런스 코드를 정확히 알고, 자신의 것처럼 응용할 수 있는게 목표

## 필수 구현 목표
1. 돈이 많은 사람 순서
2. 돈이 적은 사람 순서
3. 생일 빠른 사람 순서
4. 생일 느린 사람 순서

## Test case
```
6
김정윤 10000 1/4
박병훈 1000 2/26
박동완 4000 7/12
임익균 300000 12/11
심기성 150000 3/24
조효진 2000 3/8
```

## Reference Code
```cpp
#include <stdio.h>

#define MAX_NUM 100

int input[MAX_NUM];
int num;

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
			while (input[i] <= input[pivot] && i < last)
			{
				i++;
			}
			while (input[j] > input[pivot])
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

		quickSort(first, j - 1);
		quickSort(j + 1, last);
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

int main(void)
{
	int T;
	int test_case;
	int i;

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d", &num);
		for (i = 0; i < num; i++)
		{
			scanf("%d", &input[i]);
		}
		quickSort(0, num - 1);
		printf("#%d ", test_case);
		printResult();
	}

	return 0;
}
```
