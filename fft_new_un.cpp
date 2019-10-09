#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <complex>
using namespace std;

typedef complex<double> cp;//复数类的定义
const int MAXN=4e6;
const double pi=acos(-1.0);
cp a[MAXN],b[MAXN];



//////////复数定义，及复数运算/////////////////
/*
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
*/
////////////////////////////////////////////////////////////////////////////////////////////

cp omega(int n,int k){//公式计算Wnk
    return cp(cos(2*pi*k/n),sin(2*pi*k/n));
}

void new_fft(cp *a,int limit,int type){
    if(limit==1) return;
    static cp c[MAXN];
    int half=limit>>1;
    for(int i=0;i<half;i++){//这里可以通过设置两个数组，每次i+2.用内存空间换执行时间
        c[i]=a[i<<1];
        c[i+half]=a[(i<<1)+1];
    }
    for(int i=0;i<limit;i++)
        a[i]=c[i];

    new_fft(a,half,1);
    new_fft(a+half,half,1);
    for(int i=0;i<half;i++){
        cp x=omega(limit,i);//计算每个Wnk
        if(type==1)
            x=conj(x);
        c[i] = a[i] + x * a[i + half]; //根据之前推出的结论计算
        c[i + half] = a[i] - x * a[i + half];
    }
    for(int i=0;i<limit;i++)
        a[i]=c[i];
}
/*
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
*/

int main(){
    /*
    int N = read(), M = read();
    for (int i = 0; i <= N; i++)
        a[i].x = read();
    for (int i = 0; i <= M; i++)
        b[i].x = read();
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
    */
    int n,m;

    cout<<"please input n:"<<endl;
    cin>>n;
    cout<<"please input m:"<<endl;
    cin>>m;
    cout<<"please input duoxiangshi1's numbers:"<<endl;

    for(int i=0;i<n;i++){
        int temp;
        cout<<"No. "<<i<<"is :";
        cin>>temp;
        a[i].real(temp);
    }
    cout<<"please input duoxiangshi1's numbers:"<<endl;
    for(int i=0;i<m;i++){
        int temp;
        cout<<"No. "<<i<<"is :";
        cin>>temp;
        b[i].real(temp);
    }
    for(int i=0;i<n;i++)
        cout<<a[i]<<"------"<<b[i]<<endl;

    int limit = 1;
    while (limit <= n + m) limit <<= 1;//limit每次左移两位保证是2的倍数
    new_fft(a,n,1);
    new_fft(b,m,1);
    for(int i=0;i<n;i++)
        cout<<a[i]<<"------"<<b[i]<<endl;
    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    for(int i=0;i<n;i++)
        cout<<a[i]<<endl;
    new_fft(a,limit,-1);
    for (int i = 0; i < n + m; i++) printf("%d ", (int)(a[i].real() / limit + 0.5));
    return 0;
}

