#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static double count_quest(double p, double q);
int main()
{
        double n, p, q;
        double t = 0.0;
        int i;

        printf("n (1<=n<=1000000) =");
        scanf("%lf", &n);
        printf("p (0<=n<=100) =");
        scanf("%lf", &p);
        printf("q (1<=n<=100) =");
        scanf("%lf", &q);

        /* for 1st item */
        t = count_quest(p, q);

        /* for 2nd ~ nth items */
        for(i = 1; i < n; i++) {
                int mi = pow(2,i);
                int newp = p / mi;

                t += count_quest((double)newp, q);
        }

        printf("t = %0.2lf\n", t);
}


static double count_quest(double p, double q)
{
        double add_count;
        int yu, i_count;
        double r, rt;
        int i, j;

        /* i_count is the max steps that can't get item */
        add_count = (100 - p) / q;
        yu = (100 - (int)p) % (int)q;
        if (yu != 0)
                add_count += 1;
        i_count = (int)add_count;

        r = 1 * p / 100;

        for (i = 0; i < i_count; i++) {
                rt = (100 - p) / 100;
                for (j = 1; j <= i; j++) {
                        rt *= (100 - p - j * q) / 100;
                }

                if ((p + j * q) <= 100)
                        rt *= (j + 1) * (p + j * q) / 100;
                else
                        rt *= (j + 1) * 100 / 100;
                
                r += rt;
        }

        return r;
}
