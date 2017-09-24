#include <stdio.h>
#include <stdlib.h>


int main(void)
{
        int a, b;
        int i;
        unsigned int count_a, count_b;
        unsigned as, bs;
        
        printf(" please input two numbers which are (-32768 <= number <= 32768)\n");
        scanf("%d %d", &a, &b);

        if (!(-32768 <= a && a <= 32768) || !(-32768 <= b && b <= 32768)) {
                printf("-1\n");
                return -1;
        }

        as = abs(a);
        bs = abs(b);
        
        count_a = 0;
        count_b = 0;
        
        for (i = 0; i < sizeof(int) * 8; i++) {
                if ((as >> i) & 0x1)
                        count_a++;

                if ((bs >> i) & 0x1)
                        count_b++;
        }

        printf("%d\n", count_a > count_b ? a : count_a == count_b ? 0 : b);

        return 0;
}
