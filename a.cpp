#include<iostream>
#include<stdlib.h>
using namespace std;
class Node
{
    public:
    short int status;
    //1->min terms
    //0->max terms
    //-1->dont care
    //2->if it is crossed out in unique group-2/4/8/16
    int num;
    int bin;
};
void free_mem(Node **map,int n)
{
    int i=0;
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
}
Node ** create_map(int n)
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
        return map;
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
        return map;
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
        return map;
    }
    else
    {
        cout<<"Only K-map upto 4 variables are calculated"<<endl;
        return NULL;
    }
}
Node ** input(Node **map,int no,bool ismax)
{
    //ismax true->min terms are provided
    //make their status 1
    //else make their status -1 ->dont care 
    return map;
}
Node **prime_imp(Node **map)
{
    //if prime implicants are there make their status 2 indicates cross out
    //and prints string related to them
    //NOTE:check all prime implicants
    return map;
}
Node ** Group_2(Node **map,int row,int col)
{
    //check for unique group 2 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return map;
}
Node ** Group_4(Node **map,int row,int col)
{
    //check for unique group 4 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return map;
}
Node ** Group_8(Node **map,int row,int col)
{
    //check for unique group 8 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return map;
}
Node ** Group_16(Node **map,int row,int col)
{
    //check for unique group 16 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    return map;
}
Node ** leftovers(Node **map)
{
    return map;
}
void min_output(Node **map)
{
    //governing method for group_2,4,8,16 and left overs
}
int main()
{
    int n=4;
    Node **map=NULL;
    map=create_map(n);
    free_mem(map,n);
    return 0;
}