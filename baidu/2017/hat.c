#include <stdio.h>
#include <stdlib.h>

#define VERIFY_NUMBER_MINUS(n) (n < 0)
#define VERIFY_NUMBER_IN_RANGE(n) ((0 < n) && (n <= 1000))

void main()
{
	int num;
	unsigned int i;
	int *a;
	int first, second, third;

	first = second = third = -1;
	printf("please input the number of hat\n");
	scanf("%d", &num);
	if (VERIFY_NUMBER_MINUS(num))
		return;
	a = malloc(sizeof(int) * num);
	
	for (i = 0; i < num; i++) {
		scanf("%d", &a[i]);
		if (!VERIFY_NUMBER_IN_RANGE(a[i])) {
			free(a);
			return;
		}

		if (first == -1 || first > a[i]) {
			third = second;
			second = first;
			first = a[i];
		} else if (first < a[i]) {
			if (second == -1 || second > a[i]) {
				third = second;
				second = a[i];
			} else if (second < a[i])
				if (third == -1 || third > a[i])
					third = a[i];
		}
	}

	printf("%d\n", third);
	free(a);
}
