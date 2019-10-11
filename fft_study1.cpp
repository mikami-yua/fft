#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<complex>
#include<iostream>
using namespace std;

typedef complex<double> cd;//������Ķ���
const int maxl=2094153;//nlogn����󳤶�(����leoѧ���Ĳ���)
const double PI=3.14159265358979;//Բ����,������

cd a[maxl],b[maxl];//���ڴ���任���м���
int rev[maxl];//���ڴ�������Ʒ�ת�Ľ��
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){//��λ�������������Ĵ�С
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
        //cout<<rev[i]<<" ";
    }//�ܱ�֤(x>>1)<x,�����������
}

void fft(cd* a,int n,int dft){//�任��Ҫ����
    for(int i=0;i<n;i++)
        cout<<a[i]<<"-";
    for(int i=0;i<n;i++){//���ն����Ʒ�ת
        if(i<rev[i])//��ֻ֤��ǰ������ͺ����������,(��������ᱻ������)
            swap(a[i],a[rev[i]]);

    }
    cout<<"^^^^^^^^^^^"<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i]<<"-";
    for(int step=1;step<n;step<<=1){//ö�ٲ�����һ��
        cd wn=exp(cd(0,dft*PI/step));//���㵥λ����
        for(int j=0;j<n;j+=step<<1){//����ÿһ��
            cd wnk(1,0);//!!ÿһ�鶼��һ����������,��������η�λΪ��ʼ��
            for(int k=j;k<j+step;k++){//��������������һ��
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;//������һ�εĸ���
            }
        }
    }
    if(dft==-1){//����Ƿ��任,��Ҫ�����г���n
        for(int i=0;i<n;i++)
            a[i]/=n;
    }
}



char s1[maxl],s2[maxl];
int main(){
    scanf("%s%s",s1,s2);//����������
    int l1=strlen(s1),l2=strlen(s2);//����"������"'''''''''''''''''''''''''''l1��l2�ֱ����������ĳ���
    cout<<l1<<"*************"<<l2<<endl;
    int bit=1,s=2;//s��ʾ�ָ�֮ǰ����ĳ���
    for(bit=1;(1<<bit)<l1+l2-1;bit++){
        s<<=1;//�ҵ���һ��������������ʹ��������������������ĳ˻�
        cout<<bit<<"**************"<<s<<endl;
    }
    cout<<bit<<"**************"<<s<<endl;

    for(int i=0;i<l1;i++){//��һ����װ��a
        a[i]=(double)(s1[l1-i-1]-'0');//s�����д�ŵ���char������Ҫ��ȥchar����0���ܵõ�������ֵ
        //cout<<i<<"##"<<l1-i-1<<"##"<<s1[l1-i-1]<<endl;
        //cout<<a[i]<<"-";
    }

    for(int i=0;i<l2;i++){//�ڶ�����װ��b
        b[i]=(double)(s2[l2-i-1]-'0');
        //cout<<b[i]<<"-";
    }
    //a��b�������Ը�����ʵ�����������������
    cout<<"before rev = ";
    for(int i=0;i<maxl;i++){
        if(rev[i]!=0){
            cout<<i<<"--"<<rev[i]<<"%";
        }
    }

    getrev(bit);
    cout<<endl;
    cout<<"after  rev = ";
    for(int i=0;i<maxl;i++){
        if(rev[i]!=0){
            cout<<i<<"--"<<rev[i]<<endl;
        }
    }
    //fft(a,s,1);
}
