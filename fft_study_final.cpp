#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<complex>
#include<iostream>
using namespace std;

typedef complex<double> cd;//复数类的定义
const int maxl=2094153;//nlogn的最大长度(来自leo学长的博客)
const double PI=3.14159265358979;//圆周率,不解释

cd a[maxl],b[maxl];//用于储存变换的中间结果
int rev[maxl];//用于储存二进制反转的结果
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){//高位决定二进制数的大小
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));//把二进制反过来其实也不复杂
        //cout<<rev[i]<<" ";
    }//能保证(x>>1)<x,满足递推性质
}

void fft(cd* a,int n,int dft){//变换主要过程
    for(int i=0;i<n;i++){//按照二进制反转
        if(i<rev[i])//保证只把前面的数和后面的数交换,(否则数组会被翻回来)
            swap(a[i],a[rev[i]]);

    }
    for(int step=1;step<n;step<<=1){//枚举步长的一半
        cd wn=exp(cd(0,dft*PI/step));//计算单位复根
        for(int j=0;j<n;j+=step<<1){//对于每一块
            cd wnk(1,0);//每一块都是一个独立序列,都是以零次方位为起始的
            for(int k=j;k<j+step;k++){//蝴蝶操作处理这一块
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;//计算下一次的复根
            }
        }
    }
    if(dft==-1){//如果是反变换,则要将序列除以n
        for(int i=0;i<n;i++)
            a[i]/=n;
    }
}


int output[maxl];
char s1[maxl],s2[maxl];
int main(){
    scanf("%s%s",s1,s2);//读入两个数
    int l1=strlen(s1),l2=strlen(s2);//就算"次数界"'''''''''''''''''''''''''''l1，l2分别存放两个数的长度
    cout<<l1<<"*************"<<l2<<endl;
    int bit=1,s=2;//s表示分割之前整块的长度
    for(bit=1;(1<<bit)<l1+l2-1;bit++){
        s<<=1;//找到第一个二的整数次幂使得其可以容纳这两个数的乘积
        cout<<bit<<"**************"<<s<<endl;
    }
    cout<<bit<<"**************"<<s<<endl;

    for(int i=0;i<l1;i++){//第一个数装入a
        a[i]=(double)(s1[l1-i-1]-'0');//s数组中存放的是char类型需要减去char类型0才能得到本来的值
        //cout<<i<<"##"<<l1-i-1<<"##"<<s1[l1-i-1]<<endl;
        //cout<<a[i]<<"-";
    }

    for(int i=0;i<l2;i++){//第二个数装入b
        b[i]=(double)(s2[l2-i-1]-'0');
        //cout<<b[i]<<"-";
    }
    //a，b数组中以复数的实部逆序存放输入的数字
    getrev(bit);
    fft(a,s,1);
    cout<<endl;
    cout<<"a[i]:";
    for(int i=0;i<s;i++)
        cout<<a[i]<<"-";
    cout<<endl;
    cout<<"b[i]:";
    fft(b,s,1);
    for(int i=0;i<s;i++)
        cout<<b[i]<<"-";
    cout<<endl;
    for(int i=0;i<s;i++)a[i]*=b[i];//对应相乘
    cout<<"before idft a[i] :";
    for(int i=0;i<s;i++)
        cout<<a[i]<<"-";
    cout<<endl;
    fft(a,s,-1);//idft
    cout<<"after idft  a[i] :";
    for(int i=0;i<s;i++)
        cout<<a[i]<<"-";
    for(int i=0;i<s;i++){//还原成十进制数
        output[i]+=(int)(a[i].real()+0.5);//注意精度误差
        output[i+1]+=output[i]/10;
        output[i]%=10;
    }
    cout<<endl;
    cout<<"final multiply answers : ";
    int i;
    for(i=l1+l2;!output[i]&&i>=0;i--);//去掉前导零
    if(i==-1)printf("0");//特判长度为0的情况
    for(;i>=0;i--){//输出这个十进制数
        printf("%d",output[i]);
    }
    putchar('\n');
    return 0;
}
