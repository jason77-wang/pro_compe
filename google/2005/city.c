#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

char *result;

static void printmap(char *map, int row, int column)
{
	int i;

	for (i = 0; i < row * column; i++) {
		if (i % column == 0)
			printf("\n");
		printf("%c", map[i]);
	}
	printf("\n");
}

static void search_up_left(char *map, int myx, int myy, int row, int column, int step)
{
	if (step < 0)
		return;
	//	printf("(%d,%d) step = %d\n", myx, myy, step);
	if (map[column * (myy - 1) + (myx - 1)] == 'b')
		result[column * (myy - 1) + (myx - 1)] = '1';

	map[column * (myy - 1) + (myx - 1)] = 's'; /* means searched */
	/* checking up */
	if (myy > 1) {
		char a = map[column * (myy - 2) + (myx - 1)];
		if (a == 'b' || a == '.')
			search_up_left(map, myx, (myy - 1), row, column, (step - 1));
	}

	/* checking left */
	if (myx > 1) {
		char a = map[column * (myy - 1) + (myx - 2)];
		if (a == 'b' || a == '.')
			search_up_left(map, (myx - 1), myy, row, column, (step - 1));
	}
	
}

static void search_down_left(char *map, int myx, int myy, int row, int column, int step)
{
	if (step < 0)
		return;
	//	printf("(%d,%d) step = %d\n", myx, myy, step);
	if (map[column * (myy - 1) + (myx - 1)] == 'b')
		result[column * (myy - 1) + (myx - 1)] = '1';

	map[column * (myy - 1) + (myx - 1)] = 's'; /* means searched */

	/* checking down */
	if (myy < row) {
		char a = map[column * myy + (myx - 1)];
		if (a == 'b' || a == '.')
			search_down_left(map, myx, (myy + 1), row, column, (step - 1));
	}

	/* checking left */
	if (myx > 1) {
		char a = map[column * (myy - 1) + (myx - 2)];
		if (a == 'b' || a == '.')
			search_down_left(map, (myx - 1), myy, row, column, (step - 1));
	}

}

static void search_down_right(char *map, int myx, int myy, int row, int column, int step)
{
	if (step < 0)
		return;
	//	printf("(%d,%d) step = %d\n", myx, myy, step);
	if (map[column * (myy - 1) + (myx - 1)] == 'b')
		result[column * (myy - 1) + (myx - 1)] = '1';

	map[column * (myy - 1) + (myx - 1)] = 's'; /* means searched */

	/* checking down */
	if (myy < row) {
		char a = map[column * myy + (myx - 1)];
		if (a == 'b' || a == '.')
			search_down_right(map, myx, (myy + 1), row, column, (step - 1));
	}

	/* checking right */
	if (myx < column) {
		char a = map[column * (myy - 1) + myx];
		if (a == 'b' || a == '.')
			search_down_right(map, (myx + 1), myy, row, column, (step - 1));
	}
}

static void search_up_right(char *map, int myx, int myy, int row, int column, int step)
{
	if (step < 0)
		return;
	//	printf("(%d,%d) step = %d\n", myx, myy, step);
	if (map[column * (myy - 1) + (myx - 1)] == 'b')
		result[column * (myy - 1) + (myx - 1)] = '1';

	map[column * (myy - 1) + (myx - 1)] = 's'; /* means searched */

	/* checking up */
	if (myy > 1) {
		char a = map[column * (myy - 2) + (myx - 1)];
		if (a == 'b' || a == '.')
			search_up_right(map, myx, (myy - 1), row, column, (step - 1));
	}

	/* checking right */
	if (myx < column) {
		char a = map[column * (myy - 1) + myx];
		if (a == 'b' || a == '.')
			search_up_right(map, (myx + 1), myy, row, column, (step - 1));
	}
}

static void search_four_sides(char *map, int myx, int myy, int row, int column, int step)
{
	if (step < 0)
		return;
	//	printf("(%d,%d) step = %d\n", myx, myy, step);
	if (map[column * (myy - 1) + (myx - 1)] == 'b')
		printf("found a bus stop, it is at (%d,%d)\n", myx, (myy - 1));

	if (map[column * (myy - 1) + (myx - 1)] == '.' || map[column * (myy - 1) + (myx - 1)] == 'b')
		map[column * (myy - 1) + (myx - 1)] = 's'; /* means searched */
	/* checking up */
	if (myy > 1) {
		char a = map[column * (myy - 2) + (myx - 1)];
		if (a == 'b' || a == '.' || a == 's')
			search_four_sides(map, myx, (myy - 1), row, column, (step - 1));
	}

	/* checking left */
	if (myx > 1) {
		char a = map[column * (myy - 1) + (myx - 2)];
		if (a == 'b' || a == '.' || a == 's')
			search_four_sides(map, (myx - 1), myy, row, column, (step - 1));
	}

	/* checking down */
	if (myy < row) {
		char a = map[column * myy + (myx - 1)];
		if (a == 'b' || a == '.' || a == 's')
			search_four_sides(map, myx, (myy + 1), row, column, (step - 1));
	}

	/* checking right */
	if (myx < column) {
		char a = map[column * (myy - 1) + myx];
		if (a == 'b' || a == '.' || a == 's')
			search_four_sides(map, (myx + 1), myy, row, column, (step - 1));
	}

}

static char * dup_map(char *map, int size)
{
	char *tmp;

	tmp = malloc(size);
	if (tmp == NULL)
		return NULL;
	memcpy(tmp, map, size);

	return tmp;
}

void main()
{
	int row, column, step;
	char *map, *tmpmap;
	int x, y, myx, myy;
	int total = 0;
	int i, j;
	
	scanf("%d", &row);
	if (row < 1 || row > 50)
		return;
	
	scanf("%d", &column);
	if (column < 1 || column > 50)
		return;


	map = malloc(row * column);
	if (map == NULL)
		return;

	memset(map, '.', row * column);

	result = malloc(row * column);
	if (result == NULL)
		goto exit;
	memset(result, '0', row * column);
	
	//	printmap(map, row, column);

	printf("please input your position (x and y):");

        scanf("%d %d", &x, &y);
	if (x < 1 || x > column)
		goto exit;
	if (y < 1 || y > row)
		goto exit;
	printf("y = %d, x = %d\n", y, x);
	map[column * (y - 1) + (x - 1)] = 'x';
	myx = x;
	myy = y;
	
	printmap(map, row, column);

	printf("please input bus stop position (x and y), end up with (-1 -1):");

	while (1) {
		scanf("%d %d", &x, &y);
		if (x == -1 || y == -1)
			break;
		
		if (x < 1 || x > column)
			goto exit;
		if (y < 1 || y > row)
			goto exit;

		if (map[column * (y - 1) + (x - 1)] != 'x')
			map[column * (y - 1) + (x - 1)] = 'b';
	}

	printf("input searchinng steps:");
	scanf("%d", &step);
	printmap(map, row, column);

	tmpmap = dup_map(map, row * column);
	if (tmpmap == NULL)
		goto exit;

	search_up_left(tmpmap, myx, myy, row, column, step);
	//	search_four_sides(map, myx, myy, row, column, 4);
	//	printmap(tmpmap, row, column);
	free(tmpmap);
	
	tmpmap = dup_map(map, row * column);
	if (tmpmap == NULL)
		goto exit;

	search_down_left(tmpmap, myx, myy, row, column, step);
	//	printmap(tmpmap, row, column);
	free(tmpmap);


	tmpmap = dup_map(map, row * column);
	if (tmpmap == NULL)
		goto exit;

	search_down_right(tmpmap, myx, myy, row, column, step);
	//	printmap(tmpmap, row, column);
	free(tmpmap);

	tmpmap = dup_map(map, row * column);
	if (tmpmap == NULL)
		goto exit;

	search_up_right(tmpmap, myx, myy, row, column, step);
	//	printmap(tmpmap, row, column);
	free(tmpmap);

	for (i = 0; i < column * row; i++) {
		if(result[i] == '1') {
			printf("found a bus stop at(%d,%d)\n", i%column, i/column);
			total++;
		}
	}
	printf("found %d bus stop in total\n", total);
	free(result);
 exit:
	free(map);
}
