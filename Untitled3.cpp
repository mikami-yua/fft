#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
int main()
{
    vector<double>A,B;
    cout<<"input A:";
    for(int i=0;i<3;i++)//��0���ʼ����A�ĸ���ϵ��
    {
        int x;
        cin>>x;
        A.push_back(x);
        cout<<A.size()<<endl;

    }
        system("pause");
    return 0;
}

