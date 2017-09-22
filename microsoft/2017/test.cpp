 #include<stdio.h>
 2 #include<string.h>
 3 #include<math.h>
 4 #include<algorithm>
 5 using namespace std;
 6 
 7 const int maxn=1e6+5;
 8 const int INF=0x3f3f3f3f;
 9 const int mod=1e9+7;
10 double ans=0;
11 double num[105] = {0};
12 int n,p,q;
13 
14 int main(){
15     scanf("%d%d%d",&p,&q,&n);
16     for(int pre = 0 ; pre <= 100 ; ++ pre ){
17         int cnt = 0;
18         double p1 = 1;
19         while(1){
20             double xq = ( pre + cnt * q) / 100.0;
21             if( pre + cnt * q >= 100 ){
22                 num[pre] += ( cnt + 1 ) * p1 ;
23                 break;
24             }
25             num[pre] += p1 * xq * ( cnt + 1 );
26             p1 *= ( 1 - xq );
27             cnt++;
28         }
29     }
30 
31     int pre = p;
32     for(int i = 1 ; i <= n ; ++ i ){
33         if( pre == 0 ){
34             ans += ( n - i + 1 ) * num[0];
35             break;
36         }
37         ans += num[pre];
38         pre >>= 1;
39     }
40     
41     printf("%.2lf\n",ans);
42     return 0;
43 }
