#include<iostream>
#include<stdlib.h>
#include<stdio.h>
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
        map[0][1].bin=100;
        map[0][2].num=12;
        map[0][2].bin=1100;
        map[0][3].num=8;
        map[0][3].bin=1000;
        map[1][0].num=1;
        map[1][0].bin=1;
        map[1][1].num=5;
        map[1][1].bin=101;
        map[1][2].num=13;
        map[1][2].bin=1101;
        map[1][3].num=9;
        map[1][3].bin=1001;
        map[2][0].num=3;
        map[2][0].bin=11;
        map[2][1].num=7;
        map[2][1].bin=111;
        map[2][2].num=15;
        map[2][2].bin=1111;
        map[2][3].num=11;
        map[2][3].bin=1011;
        map[3][0].num=2;
        map[3][0].bin=10;
        map[3][1].num=6;
        map[3][1].bin=110;
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
Map prime_imp(Map m,int row,int col)
{
    //if prime implicants are there make their status 2 indicates cross out
    //and prints string related to them
    //NOTE:check all prime implicants
    if(m.arr[row][col].status!=1) return m;
    int row_max=0,col_max=0,i=0;
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
    if(m.arr[eff_row(row_max,row-1)][col].status>0) return m;
    if(m.arr[eff_row(row_max,row+1)][col].status>0) return m;
    if(m.arr[row][eff_col(col_max,col+1)].status>0) return m;
    if(m.arr[row][eff_col(col_max,col-1)].status>0) return m;
    m.arr[row][col].status=-1; //crossing out
    int temp=m.arr[row][col].bin,alpha=64+m.n;
    for(i=0;i<m.n;i++)
    {
        if(temp%10==0) printf("%c'",alpha);
        else printf("%c",alpha);
        alpha=alpha-1;
        temp=temp/10;
    }
    cout<<" + ";
    return m;
}
Map Group_2(Map m,int row,int col)
{
    //check for unique group 2 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    if(m.arr[row][col].status!=1) return m;
    int row_max,col_max,i=-1,j,k;
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
    if(m.arr[eff_row(row_max,row-1)][col].status>0)
    {
        i=eff_row(row_max,row-1);
        j=col;
    }
    if(m.arr[eff_row(row_max,row+1)][col].status>0)
    {
        if(i>-1)return m;
        i=eff_row(row_max,row+1);
        j=col;
    } 
    if(m.arr[row][eff_col(col_max,col+1)].status>0)
    {
        if(i>-1)return m;
        i=row;
        j=eff_col(col_max,col+1);
    } 
    if(m.arr[row][eff_col(col_max,col-1)].status>0)
    {
        if(i>-1)return m;
        i=row;
        j=eff_col(col_max,col-1);
    } 
    m.arr[row][col].status=-1;
    m.arr[i][j].status=-1;
    int temp1=m.arr[row][col].bin,temp2=m.arr[i][j].bin;
    j=64+m.n;
    for(i=0;i<m.n;i++)
    {
        if(temp1%10==temp2%10)
        {
            if(temp1%10==0) printf("%c'",j);
            else printf("%c",j);
        }
        temp1=temp1/10;
        temp2=temp2/10;
        j=j-1;
    }
    cout<<" + ";
    return m;
}
Map Group_4(Map m, int row, int col)
{
    // variables ==4
    if (m.n == 4)
    {
        short int cas = 0;
        bool unique = 0;
        //
        // case-1
        int p, q, r, s;
        p = m.arr[row][col].status;
        q = m.arr[row][(col + 1) % 4].status;
        r = m.arr[row][(col + 2) % 4].status;
        s = m.arr[row][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {
            cas = 1;
        }
        // case 2
        p = m.arr[row][col].status;
        q = m.arr[(row + 1) % 4][col].status;
        r = m.arr[(row + 2) % 4][col].status;
        s = m.arr[(row + 3) % 4][col].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {

            if (cas > 0)
            {
                return m;
            }
            else
            {
                cas = 2;
            }
        }
        // case 3
        p = m.arr[row][col].status;
        q = m.arr[(row)][(col + 1) % 4].status;
        r = m.arr[(row + 1) % 4][col].status;
        s = m.arr[(row + 1) % 4][(col + 1) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {

            if (cas > 0)
            {
                return m;
            }

            else
            {

                cas = 3;
            }
        }
        // case 4
        p = m.arr[row][col].status;
        q = m.arr[(row)][(col + 3) % 4].status;
        r = m.arr[(row + 1) % 4][col].status;
        s = m.arr[(row + 1) % 4][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {
            if (cas > 0)
            {
                return m;
            }

            else
            {

                cas = 4;
            }
        }
        // case 5
        p = m.arr[row][col].status;
        q = m.arr[(row)][(col + 1) % 4].status;
        r = m.arr[(row + 3) % 4][col].status;
        s = m.arr[(row + 3) % 4][(col + 1) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {

            if (cas > 0)
            {
                return m;
            }

            else
            {

                cas = 5;
            }
        }
        // case 6
        p = m.arr[row][col].status;
        q = m.arr[(row)][(col + 3) % 4].status;
        r = m.arr[(row + 3) % 4][col % 4].status;
        s = m.arr[(row + 3) % 4][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {

            if (cas > 0)
            {
                return m;
            }

            else
            {

                cas = 6;
            }
        }
        if (cas > 0)
        {
            if (cas == 1)
            {
                m.arr[row][col].status = -1;
                m.arr[row][(col + 1) % 4].status = -1;
                m.arr[row][(col + 2) % 4].status = -1;
                m.arr[row][(col + 3) % 4].status = -1;
                p = m.arr[row][col].bin;
                q = m.arr[row][(col + 1) % 4].bin;
                r = m.arr[row][(col + 2) % 4].bin;
                s = m.arr[row][(col + 3) % 4].bin;
                if (p % 10 == 1 && q % 10 == 1 && r % 10 == 1 && s % 10 == 1)
                    cout << "D";
                else if (p % 10 == 1 && q % 10 == 1 && r % 10 == 0 && s % 10 == 0)
                    cout << "D'";
                p = p / 10;
                q = q / 10;
                r = r / 10;
                s = s / 10;
                if (p % 10 == 1 && q % 10 == 1 && r % 10 == 1 && s % 10 == 1)
                    cout << "C"
                         << " + ";
                else if (p % 10 == 1 && q % 10 == 1 && r % 10 == 0 && s % 10 == 0)
                    cout << "C'"
                         << " + ";
            }
            else if (cas == 2)
            {
                m.arr[row][col].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 3) % 4][col].status = -1;
                m.arr[(row + 2) % 4][col].status = -1;
                p = m.arr[row][col].bin;
                q = m.arr[(row + 1) % 4][col].bin;
                r = m.arr[(row + 3) % 4][col].bin;
                s = m.arr[(row + 2) % 4][col].bin;
                p = p / 100;
                q = q / 100;
                r = r / 100;
                s = s / 100;
                if (p % 10 == 1 && q % 10 == 1 && r % 10 == 1 && s % 10 == 1)
                    cout << "B";
                else if (p % 10 == 1 && q % 10 == 1 && r % 10 == 0 && s % 10 == 0)
                    cout << "B'";
                p = p / 10;
                q = q / 10;
                r = r / 10;
                s = s / 10;
                if (p % 10 == 1 && q % 10 == 1 && r % 10 == 1 && s % 10 == 1)
                    cout << "A"
                         << " + ";
                else if (p % 10 == 1 && q % 10 == 1 && r % 10 == 0 && s % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
            else if (cas == 3)
            {
                m.arr[row][col].status = -1;
                m.arr[(row)][(col + 1) % 4].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 1) % 4][(col + 1) % 4].status = -1;
                p = m.arr[row][col].bin;
                q = m.arr[(row)][(col + 1) % 4].bin;
                r = m.arr[(row + 1) % 4][col].bin;
                s = m.arr[(row + 1) % 4][(col + 1) % 4].bin;
                if (p % 10 == 1 && r % 10 == 1)
                    cout << "D";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "D'";
                p = p / 10;
                r = r / 10;
                if (p % 10 == 1 && r % 10 == 1)
                    cout << "C";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "C'";

                p = p / 10;
                q = q / 100;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "B"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "B'"
                         << " + ";
                p = p / 10;
                q = q / 10;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "A"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
            else if (cas == 4)
            {
                m.arr[row][col].status = -1;
                m.arr[(row)][(col + 3) % 4].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 1) % 4][(col + 3) % 4].status = -1;
                p = m.arr[row][col].bin;
                q = m.arr[(row)][(col + 3) % 4].bin;
                r = m.arr[(row + 1) % 4][col].bin;
                s = m.arr[(row + 1) % 4][(col + 3) % 4].bin;
                if (p % 10 == 1 && r % 10 == 1)
                    cout << "D";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "D'";
                p = p / 10;
                r = r / 10;
                if (p % 10 == 1 && r % 10 == 1)
                    cout << "C";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "C'";

                p = p / 10;
                q = q / 100;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "B"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "B'"
                         << " + ";
                p = p / 10;
                q = q / 10;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "A"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
            else if (cas == 5)
            {
                m.arr[row][col].status = -1;
                m.arr[(row)][(col + 1) % 4].status = -1;
                m.arr[(row + 3) % 4][col].status = -1;
                m.arr[(row + 3) % 4][(col + 1) % 4].status = -1;
                p = m.arr[row][col].bin;
                q = m.arr[(row)][(col + 1) % 4].bin;
                r = m.arr[(row + 3) % 4][col].bin;
                s = m.arr[(row + 3) % 4][(col + 1) % 4].bin;

                if (p % 10 == 1 && r % 10 == 1)
                    cout << "D";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "D'";
                p = p / 10;
                r = r / 10;
                if (p % 10 == 1 && r % 10 == 1)
                    cout << "C";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "C'";

                p = p / 10;
                q = q / 100;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "B"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "B'"
                         << " + ";
                p = p / 10;
                q = q / 10;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "A"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
            else if (cas == 6)
            {
                m.arr[row][col].status = -1;
                m.arr[(row)][(col + 3) % 4].status = -1;
                m.arr[(row + 3) % 4][col % 4].status = -1;
                m.arr[(row + 3) % 4][(col + 3) % 4].status = -1;
                p = m.arr[row][col].bin;
                q = m.arr[(row)][(col + 3) % 4].bin;
                r = m.arr[(row + 3) % 4][col % 4].bin;
                s = m.arr[(row + 3) % 4][(col + 3) % 4].bin;

                if (p % 10 == 1 && r % 10 == 1)
                    cout << "D";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "D'";
                p = p / 10;
                r = r / 10;
                if (p % 10 == 1 && r % 10 == 1)
                    cout << "C";
                else if (p % 10 == 0 && r % 10 == 0)
                    cout << "C'";

                p = p / 10;
                q = q / 100;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "B"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "B'"
                         << " + ";
                p = p / 10;
                q = q / 10;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "A"
                         << " + ";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
        }
    }
    //     variables==3
    else if (m.n == 3)
    {
        short int cas = 0;
        bool unique = 0;
        //
        // case-1
        int p, q, r, s;
        p = m.arr[row][col].status;
        q = m.arr[row][(col + 1) % 4].status;
        r = m.arr[row][(col + 2) % 4].status;
        s = m.arr[row][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {
            cas = 1;
        }
        // case 2
        p = m.arr[row][col].status;
        q = m.arr[(row)][(col + 1) % 4].status;
        r = m.arr[(row + 1) % 4][col].status;
        s = m.arr[(row + 1) % 4][(col + 1) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {

            if (cas > 0)
            {
                return m;
            }

            else
            {

                cas = 2;
            }
        }
        // case 3
        p = m.arr[row][col].status;
        q = m.arr[(row)][(col + 3) % 4].status;
        r = m.arr[(row + 1) % 4][col].status;
        s = m.arr[(row + 1) % 4][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {
            if (cas > 0)
            {
                return m;
            }

            else
            {

                cas = 3;
            }
        }

        if (cas > 0)
        {
            if (cas == 1)
            {

                m.arr[row][col].status = -1;
                m.arr[row][(col + 1) % 4].status = -1;
                m.arr[row][(col + 2) % 4].status = -1;
                m.arr[row][(col + 3) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[row][(col + 1) % 4].bin;
                r = m.arr[row][(col + 2) % 4].bin;
                s = m.arr[row][(col + 3) % 4].bin;
                if (p % 10 == 1)
                    cout << "C";
                else
                    cout << "C'"
                         << " + ";
            }
            else if (cas == 2)
            {

                m.arr[row][col].status = -1;
                m.arr[(row)][(col + 1) % 4].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 1) % 4][(col + 1) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[(row)][(col + 1) % 4].bin;
                r = m.arr[(row + 1) % 4][col].bin;
                s = m.arr[(row + 1) % 4][(col + 1) % 4].bin;
                p = p / 100;
                q = q / 100;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "B";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "B'";
                p = p / 10;
                q = q / 10;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "A";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
            else if (cas == 3)
            {
                m.arr[row][col].status = -1;
                m.arr[(row)][(col + 3) % 4].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 1) % 4][(col + 3) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[(row)][(col + 3) % 4].bin;
                r = m.arr[(row + 1) % 4][col].bin;
                s = m.arr[(row + 1) % 4][(col + 3) % 4].bin;

                p = p / 100;
                q = q / 100;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "B";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "B'";
                p = p / 10;
                q = q / 10;
                if (p % 10 == 1 && q % 10 == 1)
                    cout << "A";
                else if (p % 10 == 0 && q % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
        }
    }
    // variables==2
    else if (m.n == 2)
    {
        int p, q, r, s;
        p = m.arr[row][col].status;
        q = m.arr[row][(col + 1) % 4].status;
        r = m.arr[(row + 1) % 4][col].status;
        s = m.arr[(row + 1) % 4][(col + 1) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0)
        {
            cout << "1" << endl;
        }
    }

    return m;
}
Map Group_8(Map m, int row, int col)
{
    if (m.n == 4)
    {
        int cas;
        int p, q, r, s, t, u, v, w;
        // case 1
        p = m.arr[row][col].status;
        q = m.arr[row][(col + 1) % 4].status;
        r = m.arr[row][(col + 2) % 4].status;
        s = m.arr[row][(col + 3) % 4].status;
        t = m.arr[(row + 1) % 4][col].status;
        u = m.arr[(row + 1) % 4][(col + 1) % 4].status;
        v = m.arr[(row + 1) % 4][(col + 2) % 4].status;
        w = m.arr[(row + 1) % 4][(col + 3) % 4].status;

        if (p > 0 && q > 0 && r > 0 && s > 0 && t > 0 && u > 0 && v > 0 && w > 0)
        {
            cas = 1;
        }
        // case 2

        p = m.arr[row][col].status;
        q = m.arr[row][(col + 1) % 4].status;
        r = m.arr[row][(col + 2) % 4].status;
        s = m.arr[row][(col + 3) % 4].status;
        t = m.arr[(row + 3) % 4][col].status;
        u = m.arr[(row + 3) % 4][(col + 1) % 4].status;
        v = m.arr[(row + 3) % 4][(col + 2) % 4].status;
        w = m.arr[(row + 3) % 4][(col + 3) % 4].status;

        if (p > 0 && q > 0 && r > 0 && s > 0 && t > 0 && u > 0 && v > 0 && w > 0)
        {
            if (cas > 0)
            {
                return m;
            }
            else
            {
                cas = 2;
            }
        }

        // case 3

        p = m.arr[row][col].status;
        q = m.arr[(row + 1) % 4][col].status;
        r = m.arr[(row + 2) % 4][col].status;
        s = m.arr[(row + 3) % 4][col].status;
        t = m.arr[row][(col + 1) % 4].status;
        u = m.arr[(row + 1) % 4][(col + 1) % 4].status;
        v = m.arr[(row + 2) % 4][(col + 1) % 4].status;
        w = m.arr[(row + 3) % 4][(col + 1) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0 && t > 0 && u > 0 && v > 0 && w > 0)
        {
            if (cas > 0)
            {
                return m;
            }
            else
            {
                cas = 3;
            }
        }

        // case 4

        p = m.arr[row][col].status;
        q = m.arr[(row + 1) % 4][col].status;
        r = m.arr[(row + 2) % 4][col].status;
        s = m.arr[(row + 3) % 4][col].status;
        t = m.arr[row][(col + 3) % 4].status;
        u = m.arr[(row + 1) % 4][(col + 3) % 4].status;
        v = m.arr[(row + 2) % 4][(col + 3) % 4].status;
        w = m.arr[(row + 3) % 4][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0 && t > 0 && u > 0 && v > 0 && w > 0)
        {
            if (cas > 0)
            {
                return m;
            }
            else
            {
                cas = 4;
            }
        }

        if (cas > 0)
        {
            if (cas == 1)
            {

                m.arr[row][col].status = -1;
                m.arr[row][(col + 1) % 4].status = -1;
                m.arr[row][(col + 2) % 4].status = -1;
                m.arr[row][(col + 3) % 4].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 1) % 4][(col + 1) % 4].status = -1;
                m.arr[(row + 1) % 4][(col + 2) % 4].status = -1;
                m.arr[(row + 1) % 4][(col + 3) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[row][(col + 1) % 4].bin;
                r = m.arr[row][(col + 2) % 4].bin;
                s = m.arr[row][(col + 3) % 4].bin;
                t = m.arr[(row + 1) % 4][col].bin;
                u = m.arr[(row + 1) % 4][(col + 1) % 4].bin;
                v = m.arr[(row + 1) % 4][(col + 2) % 4].bin;
                w = m.arr[(row + 1) % 4][(col + 3) % 4].bin;

                if (p % 10 == 1 && t % 10 == 1)
                    cout << "D";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "D'"
                         << " + ";
                p = p / 10;
                t = t / 10;
                if (p % 10 == 1 && t % 10 == 1)
                    cout << "C";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "C'"
                         << " + ";
            }

            else if (cas == 2)
            {

                m.arr[row][col].status = -1;
                m.arr[row][(col + 1) % 4].status = -1;
                m.arr[row][(col + 2) % 4].status = -1;
                m.arr[row][(col + 3) % 4].status = -1;
                m.arr[(row + 3) % 4][col].status = -1;
                m.arr[(row + 3) % 4][(col + 1) % 4].status = -1;
                m.arr[(row + 3) % 4][(col + 2) % 4].status = -1;
                m.arr[(row + 3) % 4][(col + 3) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[row][(col + 1) % 4].bin;
                r = m.arr[row][(col + 2) % 4].bin;
                s = m.arr[row][(col + 3) % 4].bin;
                t = m.arr[(row + 3) % 4][col].bin;
                u = m.arr[(row + 3) % 4][(col + 1) % 4].bin;
                v = m.arr[(row + 3) % 4][(col + 2) % 4].bin;
                w = m.arr[(row + 3) % 4][(col + 3) % 4].bin;

                if (p % 10 == 1 && t % 10 == 1)
                    cout << "D";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "D'"
                         << " + ";
                p = p / 10;
                t = t / 10;
                if (p % 10 == 1 && t % 10 == 1)
                    cout << "C";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "C'"
                         << " + ";
            }

            else if (cas == 3)
            {
                m.arr[row][col].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 2) % 4][col].status = -1;
                m.arr[(row + 3) % 4][col].status = -1;
                m.arr[row][(col + 1) % 4].status = -1;
                m.arr[(row + 1) % 4][(col + 1) % 4].status = -1;
                m.arr[(row + 2) % 4][(col + 1) % 4].status = -1;
                m.arr[(row + 3) % 4][(col + 1) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[(row + 1) % 4][col].bin;
                r = m.arr[(row + 2) % 4][col].bin;
                s = m.arr[(row + 3) % 4][col].bin;
                t = m.arr[row][(col + 1) % 4].bin;
                u = m.arr[(row + 1) % 4][(col + 1) % 4].bin;
                v = m.arr[(row + 2) % 4][(col + 1) % 4].bin;
                w = m.arr[(row + 3) % 4][(col + 1) % 4].bin;

                if (p % 10 == 1 && t % 10 == 1)
                    cout << "B";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "B'"
                         << " + ";
                p = p / 10;
                t = t / 10;
                if (p % 10 == 1 && t % 10 == 1)
                    cout << "A";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "A'"
                         << " + ";
            }

            else if (cas == 4)
            {

                m.arr[row][col].status = -1;
                m.arr[(row + 1) % 4][col].status = -1;
                m.arr[(row + 2) % 4][col].status = -1;
                m.arr[(row + 3) % 4][col].status = -1;
                m.arr[row][(col + 3) % 4].status = -1;
                m.arr[(row + 1) % 4][(col + 3) % 4].status = -1;
                m.arr[(row + 2) % 4][(col + 3) % 4].status = -1;
                m.arr[(row + 3) % 4][(col + 3) % 4].status = -1;

                p = m.arr[row][col].bin;
                q = m.arr[(row + 1) % 4][col].bin;
                r = m.arr[(row + 2) % 4][col].bin;
                s = m.arr[(row + 3) % 4][col].bin;
                t = m.arr[row][(col + 3) % 4].bin;
                u = m.arr[(row + 1) % 4][(col + 3) % 4].bin;
                v = m.arr[(row + 2) % 4][(col + 3) % 4].bin;
                w = m.arr[(row + 3) % 4][(col + 3) % 4].bin;

                if (p % 10 == 1 && t % 10 == 1)
                    cout << "B";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "B'"
                         << " + ";
                p = p / 10;
                t = t / 10;
                if (p % 10 == 1 && t % 10 == 1)
                    cout << "A";
                else if (p % 10 == 0 && t % 10 == 0)
                    cout << "A'"
                         << " + ";
            }
        }
    }
    else if (m.n == 3)
    {
        int p, q, r, s, t, u, v, w;
        p = m.arr[row][col].status;
        q = m.arr[row][(col + 1) % 4].status;
        r = m.arr[row][(col + 2) % 4].status;
        s = m.arr[row][(col + 3) % 4].status;
        t = m.arr[(row + 1) % 4][col].status;
        u = m.arr[(row + 1) % 4][(col + 1) % 4].status;
        v = m.arr[(row + 1) % 4][(col + 2) % 4].status;
        w = m.arr[(row + 1) % 4][(col + 3) % 4].status;
        if (p > 0 && q > 0 && r > 0 && s > 0 && t > 0 && u > 0 && v > 0 && w > 0)
        {
            m.arr[row][col].status = -1;
            m.arr[row][(col + 1) % 4].status = -1;
            m.arr[row][(col + 2) % 4].status = -1;
            m.arr[row][(col + 3) % 4].status = -1;
            m.arr[(row + 1) % 4][col].status = -1;
            m.arr[(row + 1) % 4][(col + 1) % 4].status = -1;
            m.arr[(row + 1) % 4][(col + 2) % 4].status = -1;
            m.arr[(row + 1) % 4][(col + 3) % 4].status = -1;
            cout << "1"
                 << " + " << endl;
        }
    }
    // check for unique group 8 elements for map[row][col]
    // if exits make status 2 and print string corresponding
    // else return map
    return m;
}
Map Group_16(Map m,int row,int col)
{
    //check for unique group 16 elements for map[row][col]
    //if exits make status 2 and print string corresponding
    //else return map
    int i,j;
    if(m.arr[row][col].status!=1||m.n!=4) return m;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(m.arr[i][col].status<=0) return m;
        }
    }
    m.arr[row][col].status=-1;
    cout<<"1"<<endl;
    return m;
}
int * init(Map m,int *arr)
{
    //extra element in index corresponding to last valid element
    //arr ->leftovers insert
    //-1-->1
    //crossover w.r.t to array
    //if element in array becomes -1 remove element from array
    return arr;
}
Map leftovers(Map m)
{
    int *make,i,j,index=0,col_max,row_max;
    make=(int *)malloc(sizeof(int)*(my_pow(2,m.n)));
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
    for(i=0;i<my_pow(2,m.n);i++)
    {
        if(m.arr[m.sort_arr[i]/col_max][m.sort_arr[i]%col_max].status==-1) 
        {
            make[index]=m.arr[m.sort_arr[i]/col_max][m.sort_arr[i]%col_max].num;
            index++;
            m.arr[m.sort_arr[i]/col_max][m.sort_arr[i]%col_max].status=1;
        }
    }
    if(index==0) return m;
    //if array have 1 element  make[my_pow(2,m.n)]=0
    while(i<index-1)
    {
        m=Group_16(m,make[i]/col_max,make[i]%col_max);
        m=Group_8(m,make[i]/col_max,make[i]%col_max);
        m=Group_4(m,make[i]/col_max,make[i]%col_max);
        m=Group_2(m,make[i]/col_max,make[i]%col_max);
        for(j=0;j<index-1;j++)
        {
            if(m.arr[make[j]/col_max][make[j]%col_max].status=-1)
            {
                m.arr[make[j]/col_max][make[j]%col_max].status=1;
                i++;
            }
        }
    }
    free(make);
    return m;
}
void k_map(Map m)
{
    int i,row,col;
    if(m.n==4||m.n==3) col=4;
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
    cout<<"0"<<endl;
}
void prin(Map m)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            cout<<m.arr[i][j].status<<" asd "<<m.arr[i][j].num<<endl;
        }
        cout<<endl;
    }
}
int main()
{
    int temp,n=4;
    Map map;
    map=create_map(4);
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
    k_map(map);
    free_mem(map,map.n);
    return 0;
}