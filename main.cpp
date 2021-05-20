#include <iostream>
#include <conio.h>

using namespace std;

int compare (int a[100],int b[100])
{
    int z = 1;
    for (int i=0 ; i<4 ; i++)
    {
        if(a[i] < b[i])
        {
            z=0;
            break;
        }
    }
    return z;
}
void algorithm(int available1[100] , int need1 [100] ,int max1[100],int allocation[100])
{
    for(int m = 0 ;m < 100 ; m++)
    {
        available1[m]-=need1[m];
        allocation[m]+=need1[m];
        available1[m]+=allocation[m];
    }

}
int end_loop(int u [100]){
    int f =1;
    for(int i =0;i<5 ;i++)
    {
        if(u[i] == 0){
            f = 0;
            break;
        }
    }
    return f;
}
int iterate (int available1[100] ,int allocation[100][100], int need1 [100][100] ,int max1[100][100] ,int finish1[100] ,int sequence1[100] ,int index)
{
    int r =0;
    for(int i =0 ;i<5 ; i++)
    {
        if(compare (available1 , need1[i]) == 1 && finish1[i]==0)
        {
            algorithm(available1 , need1 [i] ,max1[i],allocation[i]);
            finish1[i]=1;
            sequence1[index]=i;

            index++;

        }
    }
    return index;
}
void safe(int max[100][100],int allocation[100][100],int available [100],int finish [100],int need [100][100] ,int req)
{
    int sequence[100]; //sequence of processes in output
    int index=0; //index for sequence
    int counter=0; //counter to test for unsafe
    int safe2 = 0; //flag

    while (true)
    {
        index= iterate(available,allocation,need,max,finish,sequence,index);//iterate
        counter++;

        if(end_loop(finish)==1) //all finish
        {
            safe2 =1;
            break; //safe

        }
        if(counter>100)//unsafe
        {
            break;
        }

    }
    if(safe2==1 && req ==-1)//safe with request
    {
        cout<<"\n";
        cout<<"Yes , Safe state";
        cout<<"< ";
        for(int i =0 ;i<5 ;i++)
        {
            cout<<"P"<<sequence[i]<<" ";
        }
        cout<<">";

    }
    if(safe2==1 && req !=-1)//safe without request
    {
        cout<<"\n";
        cout<<"Yes , Safe state";
        cout<<"< ";
        cout<<"req p"<<req<<" ";
        for(int i =0 ;i<5 ;i++)
        {
            cout<<"P"<<sequence[i]<<" ";
        }
        cout<<">";

    }

    if(safe2==0 ) //not safe
    {
        cout<<"system is not safe";
    }

}
void safe_request(int p,int req_need[100],int allocation[100][100],int max[100][100],int available [100],int finish [100],int need [100][100])
{
    for(int i=0 ;i<100;i++)
    {
        finish[i]=0;
    }
    if(compare(need[p],req_need)==1)
    {
        if(compare(available,req_need)==1)
        {
            for(int i =0 ;i<100 ;i++)
            {
                available[i] -= req_need[i];
                need[p][i]-=req_need[i];
                allocation[p][i]+=req_need[i];
            }

            safe(max,allocation,available,finish,need,p);

        }
        if(compare(available,req_need)==0)
        {
            cout<<" request cannot be granted ";
        }

    }
    else
    {
        cout<<" request cannot be granted ";
    }

}


int main() {
    //safe algorithm

    int x ; //number of processes
    int y; //number of resources
    cout<<"please enter no of processes: ";
    cin>>x;
    cout<<"\n";
    cout<<"please enter no of resources: ";
    cin>>y;
    cout<<"\n";

    int allocation[100][100];
    int max[100][100];
    int available[100];
    int need[100][100];
    int finish[100];

    //defining another copy to be used in request
    int allocation2[100][100];
    int max2[100][100];
    int available2[100];
    int need2[100][100];


    for(int i=0 ;i<x;i++)
    {
        finish[i]=0;
    }




    cout<<"please enter allocation matrix: "<<"\n";
    for(int i=0 ; i<x ;i++)
    {
        for(int j=0 ; j<y ;j++)
        {
           cin>>allocation[i][j];
           allocation2[i][j]=allocation[i][j];

        }

    }


    cout<<"\n"<<"please enter max matrix: "<<"\n";
    for(int i=0 ; i<x ;i++)
    {
        for(int j=0 ; j<y ;j++)
        {
            cin>>max[i][j];
            max2[i][j]=max[i][j];
        }

    }

    cout<<"\n"<<"please enter available matrix: "<<"\n";
    for(int i=0 ; i<y ;i++)
    {
        cin>>available[i];
        available2[i]=available[i];
    }

    cout<<"\n";
    cout<<"the need matrix is :";
    for(int i =0 ; i<x ; i++)
    {
        cout<<"\n";
        for(int j=0 ; j<y ; j++)
        {
            need[i][j] = max[i][j]-allocation[i][j];
            need2[i][j]=need[i][j];
            cout<<need[i][j]<<" " ;

        }
    }
    cout<<"\n"<<"safe algorithm?(yes/no)";
    string d;
    cin>>d;
    if(d=="yes")
    {
        safe(max,allocation,available,finish,need,-1);
    }
    cout<<"\n"<<"immediate request?(yes/no)";
    cin>>d;
    if(d=="yes")
    {

        int p;
        cout<<"please enter the process's order"<<"\n";
        cin>>p;
        cout<<"please enter the needed matrix for it:"<<"\n";
        int req_need[100];
        for (int i =0;i<y;i++)
        {
            cin >> req_need[i];
        }
        safe_request(p,req_need,allocation2,max2,available2,finish,need2);



    }
    cout<<"\n";
    cout<<"enter 0 to exit"<<"\n";
    int g;
    cin>>g;
    if(g ==0)
        return 0;








}
