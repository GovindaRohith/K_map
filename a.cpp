#include<iostream>
#include<stdlib.h>
using namespace std;
class Node
{
    public:
    short int status;
    //1->min terms
    //0->max terms
    //2->dont care
    //-1->if it is crossed out in unique group-2/4/8/16
    int num;
    int bin;
};
class Map
{
    public:
    int n;
    Node **arr;
    int *sort_arr;
    //sort_arr[i]=contains index of matrix which consists of i 
    //sort_arr[i]=index of i in matrix
    //NOTE row_no=index/no of cols
    //NORE col_no=index%no of cols
};
void free_mem(Map temp,int n)
{
    int i=0;
    Node **map=temp.arr;
    if(n==4||n==3)
    {
        for(i=0;i<4;i++)
        {
            delete[] map[i];
        }
    }
    else
    {
        delete map[0];
        delete map[1];
    }
    delete[] map;
    free(temp.sort_arr);
}
Map create_map(int n)
{
    int i,j;
    if(n==4)
    {
        Node ** map=new Node*[4];
        for(i=0;i<4;i++)
        {
            map[i]=new Node[4];
        }
        map[0][0].num=0;
        map[0][0].bin=0000;
        map[0][1].num=4;
        map[0][1].bin=0100;
        map[0][2].num=12;
        map[0][2].bin=1100;
        map[0][3].num=8;
        map[0][3].bin=1000;
        map[1][0].num=1;
        map[1][0].bin=0001;
        map[1][1].num=5;
        map[1][1].bin=0101;
        map[1][2].num=13;
        map[1][2].bin=1101;
        map[1][3].num=9;
        map[1][3].bin=1001;
        map[2][0].num=3;
        map[2][0].bin=0011;
        map[2][1].num=7;
        map[2][1].bin=0111;
        map[2][2].num=15;
        map[2][2].bin=1111;
        map[2][3].num=11;
        map[2][3].bin=1011;
        map[3][0].num=2;
        map[3][0].bin=0010;
        map[3][1].num=6;
        map[3][1].bin=0110;
        map[3][2].num=14;
        map[3][2].bin=1110;
        map[3][3].num=10;
        map[3][3].bin=1010;
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                map[i][j].status=0;
            }
        }
        Map temp;
        temp.arr=map;
        int *sort;
        sort=(int *)malloc(sizeof(int)*16);
        sort[0]=0;
        sort[1]=4;
        sort[2]=12;
        sort[3]=8;
        sort[4]=1;
        sort[5]=5;
        sort[6]=13;
        sort[7]=9;
        sort[8]=3;
        sort[9]=7;
        sort[10]=15;
        sort[11]=4;
        sort[12]=2;
        sort[13]=6;
        sort[14]=14;
        sort[15]=10;
        temp.sort_arr=sort;
        temp.n=n;
        return temp;
    }
    else if(n==3)
    {
        Node ** map=new Node*[2];
        int i;
        for(i=0;i<2;i++)
        {
            map[i]=new Node[4];
        }
        map[0][0].num=0;
        map[0][0].bin=000;
        map[0][1].num=2;
        map[0][1].bin=010;
        map[0][2].num=6;
        map[0][2].bin=110;
        map[0][3].num=4;
        map[0][3].bin=100;
        map[1][0].num=1;
        map[1][0].bin=001;
        map[1][1].num=3;
        map[1][1].bin=011;
        map[1][2].num=7;
        map[1][2].bin=111;
        map[1][3].num=5;
        map[1][3].bin=101;
        for(i=0;i<2;i++)
        {
            for(j=0;j<4;j++)
            {
                map[i][j].status=0;
            }
        }
        Map temp;
        temp.arr=map;
        int *sort;
        sort=(int *)malloc(sizeof(int)*8);
        sort[0]=0;
        sort[1]=4;
        sort[2]=1;
        sort[3]=5;
        sort[4]=3;
        sort[5]=7;
        sort[6]=2;
        sort[7]=6;
        temp.sort_arr=sort;
        temp.n=n;
        return temp;
    }
    else if(n==2)
    {
        Node ** map=new Node*[2];
        int i;
        for(i=0;i<2;i++)
        {
            map[i]=new Node[2];
        }
        map[0][0].num=0;
        map[0][0].bin=00;
        map[0][1].num=2;
        map[0][1].bin=10;
        map[1][0].num=1;
        map[1][0].bin=01;
        map[1][1].num=3;
        map[1][1].bin=11;
        for(i=0;i<2;i++)
        {
            for(j=0;j<2;j++)
            {
                map[i][j].status=0;
            }
        }
        Map temp;
        temp.arr=map;
        int *sort;
        sort[0]=0;
        sort[1]=1;
        sort[2]=1;
        sort[3]=3;
        temp.sort_arr=sort;
        temp.n=n;
        return temp;
    }
    else
    {
        cout<<"Only K-map upto 4 variables are calculated"<<endl;
        Map m;
        m.arr=NULL;
        m.sort_arr=NULL;
        return m;
    }
}
Map input(Map m,int no,bool ismax)
{
    if(no>m.n*m.n||no==-1) return m;
    //ismax true->min terms are provided
    //false implies they are dont care;
    //make their status 1
    //else make their status -1 ->dont care 
    int cols=0,n=m.n;
    if(n==4||n==3) cols=4;
    if(n==2) cols=2;
    if(ismax)m.arr[m.sort_arr[no]/cols][m.sort_arr[no]%cols].status=1;
    else m.arr[m.sort_arr[no]/cols][m.sort_arr[no]%cols].status=2;
    return m;
}
int eff_row(int row,int n)
{
    return (row+n)%row;
    //-4  0
    //-3  1
    //-2  2
    //-1  3
}
int eff_col(int col,int n)
{
    return (col+n)%col;
}
Map prime_imp(Map m,int row,int col)
{
    //if prime implicants are there make their status 2 indicates cross out
    //and prints string related to them
    //NOTE:check all prime implicants
    int row_max,col_max;
    if(m.n==4)
    {
        row_max=4;
        col_max=4;
    }
    else if(m.n==3)
    {
        row_max=2;
        col_max=4;
    }
    else if(m.n==2)
    {
        row_max=2;
        col_max=2;
    }

    return m;
}
Map Group_2(Map m,int row,int col)
{
    //check for unique group 2 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return m;
}
Map Group_4(Map m,int row,int col)
{
    //check for unique group 4 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return m;
}
Map Group_8(Map m,int row,int col)
{
    //check for unique group 8 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return m;
}
Map Group_16(Map m,int row,int col)
{
    //check for unique group 16 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return m;
}
Map leftovers(Map m)
{
    return m;
}
int my_pow(int a,int b)
{
    // return a^b;
    int i,value=1;
    for(i=0;i<b;i++)
    {
        value=value*a;
    }
    return value;
}
void k_map(Map m)
{
    int i,row,col;
    if(m.n==4||m.n==3) col==4;
    if(m.n==4) row=4;
    if(m.n==3) row=2;
    if(m.n==2) 
    {
        row=2;
        col=2;
    }
    for(i=0;i<my_pow(2,m.n);i++)
    {
        m=prime_imp(m,i/col,i%col);
    }
    for(i=0;i<my_pow(2,m.n);i++)
    {
        //m.arr[m.sort_arr[no]/cols][m.sort_arr[no]%cols].status
        if(m.arr[m.sort_arr[i]/col][m.sort_arr[i]%col].status==1) m=Group_2(m,m.sort_arr[i]/col,m.sort_arr[i]%col);
    }
    for(i=0;i<my_pow(2,m.n);i++)
    {
        if(m.arr[m.sort_arr[i]/col][m.sort_arr[i]%col].status==1) m=Group_4(m,m.sort_arr[i]/col,m.sort_arr[i]%col);
    }
    for(i=0;i<my_pow(2,m.n);i++)
    {
        if(m.arr[m.sort_arr[i]/col][m.sort_arr[i]%col].status==1) m=Group_8(m,m.sort_arr[i]/col,m.sort_arr[i]%col);
    }
    for(i=0;i<my_pow(2,m.n);i++)
    {
        if(m.arr[m.sort_arr[i]/col][m.sort_arr[i]%col].status==1) m=Group_16(m,m.sort_arr[i]/col,m.sort_arr[i]%col);
    }
    m=leftovers(m);
}
int main()
{
    //
    int n=4,temp;
    Map map;
    map=create_map(n);
    cout<<"Enter min terms numbers after completion enter '-1'"<<endl;
    cin>>temp;
    map=input(map,temp,true);
    while(temp>=0&&temp<n*n)
    {
        cin>>temp;
        map=input(map,temp,true);
    }
    cout<<"Enter dont care numbers after completion enter '-1'"<<endl;
    cin>>temp;
    map=input(map,temp,false);
    while(temp>=0&&temp<n*n) //make cases when entered a values who is already entered
    {
        cin>>temp;
        map=input(map,temp,false);
    }
    free_mem(map,n);
    return 0;
}