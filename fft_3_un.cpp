#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN=4e6;
const double pi=acos(-1.0);

inline int read(){//得到输入的数字
    char c = getchar(); int x = 0, f = 1;
    while (c < '0' || c > '9') {if (c == '-')f = -1; c = getchar();}
    while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}


//////////复数定义，及复数运算/////////////////
struct complex {
    double x,y;
    complex(double xx=0,double yy=0){
        x=xx;y=yy;
    }
};

complex a[MAXN],b[MAXN];
complex operator + (complex a,complex b){return complex(a.x+b.x,a.y+b.y);}
complex operator - (complex a, complex b) { return complex(a.x - b.x , a.y - b.y);}
complex operator * (complex a, complex b) { return complex(a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x);}
////////////////////////////////////////////////////////////////////////////////////////////



void fast_fft(int limit,complex *a,int type){
    if(limit==1) return;
    complex a1[limit >> 1],a2[limit >>1];//右移一位相当于除2，位移操作比除法更快
    for(int i=0;i<=limit;i=i+2){
        a1[i>>1]=a[i],
        a2[i>>1]=a[i+1];//通过n/2次for循环写两个数组。
    }//完成奇数偶数分组
    fast_fft(limit>>1,a1,type);
    fast_fft(limit>>1,a2,type);
    complex Wn=complex(cos(2.0*pi/limit),type*sin(2.0*pi/limit)),w=complex(1,0);//Wn表示单位根，w表示幂
    for(int i=0;i<(limit>>1);i++,w=w*Wn){//for循环完成的是公式A(Wn)k=A1(Wn/2)k+Wnk*A2(Wn/2)k和A(Wn)k+n/2=A1(Wn/2)k-Wnk*A2(Wn/2)k
        a[i]=a1[i]+w*a2[i],
        a[i+(limit>>1)]=a1[i]-w*a2[i];
    }
}
int main(){
    int N = read(), M = read();
    for (int i = 0; i <= N; i++) a[i].x = read();
    for (int i = 0; i <= M; i++) b[i].x = read();
    int limit = 1;
    while (limit <= N + M) limit <<= 1;//limit每次左移两位保证是2的倍数
    fast_fft(limit, a, 1);
    fast_fft(limit, b, 1);
    //后面的1表示要进行的变换是什么类型
    //1表示从系数变为点值
    //-1表示从点值变为系数
    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    fast_fft(limit, a, -1);
    for (int i = 0; i <= N + M; i++) printf("%d ", (int)(a[i].x / limit + 0.5)); //按照推倒的公式，这里还要除以n
    return 0;

}
