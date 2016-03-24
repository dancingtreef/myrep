#include "matri.h"
#include <signal.h>
#include <setjmp.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>




using namespace std;

int Destrib(double pc);


class Strip
{
private:
    int N,a;
    long int L,l;
    double R1,R2;
    MATRIX A,Y;
public:
    //Strip();
    Strip(long int L,int N,double r1, double r2);
    //~Strip();
    void AddS();
    long int getL();
    int getN();
    double getCond();
    void MakeStrip();
};


double ABS(double a)
{
    if (a < 0)
        return -a;
    else
        return a;
}


int main()
{
    /*srand(time(NULL));
    int N,L,i;
    double pc = 0.46;
    ostringstream str;
    ofstream fout("azaza.txt");
    for(i = 2;i < 41;i++){
        str << i << ' ';
        while (pc <= 0.54)
        {
            Strip ST(120000,i,pc);
            ST.MakeStrip();
            str << scientific << setprecision(4) << ST.getCond() << ' ';
            pc += 0.02;
        }
        pc = 0.46;
        str << endl;
        cout << i << endl;
    }
    fout << str.str();
    fout.close();
    cin.get();*/
    int N,L,i;
    ostringstream str;
    ofstream fout("azaz3.txt");
    int j = 100;
    while(j < 120)
    {
        str << j << ' ';
        for (int i = 2;i < 10;i++)
        {
            Strip ST(120000,j,1,i);
            ST.MakeStrip();
            str << scientific << setprecision(4) <<ST.getCond() <<' '<< ABS(ST.getCond() - 1 / sqrt(i)) << ' ';
        }
    cout << j << endl;
    str << '\n';
    j += 10;
    }
    fout << str.str();
    fout.close();
}


int Destrib(double pc)
{
    unsigned int K = RAND_MAX;
    K = round(K * pc);
    if (rand() < K)
        return 1;
    else
        return 0;
}


Strip::Strip(long int C,int B,double r1,double r2)
{
    N = B;
    L = C;
    MATRIX V(N);
    A = V;//Что-то не ладное
    l = 1;
    a = 1;
    R1 = r1;
    R2 = r2;

}

void Strip::AddS()
{
    /*int R = Destrib(pc);
    MATRIX Y(A.GET_n());
    Y = A;
    int i,j;
    if (a != N-1)
    {
        if (R){
        if(A.GET_M()[a][a] !=0)
                for(i = 0;i < N;i++)
                    for(j = 0;j < N;j++){

                                A.GET_M()[i][j] -= (Y.GET_M()[i][a] * Y.GET_M()[a][j]) / (1 + Y.GET_M()[a][a]);
                }
        }
        else
            if(Y.GET_M()[a][a] != 0)
                for(i = 0;i < N;i++)
                    for(j = 0;j < N;j++){
                                A.GET_M()[i][j] -= (Y.GET_M()[i][a] * Y.GET_M()[a][j]) / Y.GET_M()[a][a];
                    }
    }
    R = Destrib(pc);
    if (R == 1)
        for(i = 0;i < N;i++)
            for(j = 0;j < N;j++)
            {
                A.GET_M()[i][j] += ((Kronecker(a,j) - Kronecker(a-1,j))*(Kronecker(a,i) - Kronecker(a-1,i)));
            }
    if (a == N-1)   // !!!!!!!!!!!!
    {
        a = 1;
        l++;
    }
    else
        a++;
        */
    double R;
    int i,j;
    //MATRIX Y(A.GET_m());
    Y = A;
    //R = Destrib(pc);
    R = Kronecker((a + l % 2) % 2,0) * R1 + Kronecker((a + l % 2)% 2,1) * R2;
    if (a != N-1)
    {
        if (R != 0)
        {
            if (Y.GET_M()[a][a] != 0)
            for(i = 0;i < N;i++)
                for(j = 0;j < N;j++)
                    A.GET_M()[i][j] -= Y.GET_M()[i][a] * Y.GET_M()[a][j] / (1 + Y.GET_M()[a][a] * R);
        }
        else
        {
            if (!(Y.GET_M()[a][a] < 0.00000000001 && Y.GET_M()[a][a] > -0.00000000001))

            {
                for(i = 0;i < N;i++)
                    for(j = 0;j < N;j++){
                        A.GET_M()[i][j] -= Y.GET_M()[i][a] * Y.GET_M()[a][j] / Y.GET_M()[a][a];

                    }
            }
        }
    }
    //R = Destrib(pc);
    R = Kronecker((a + l % 2) % 2,0) * R1 + Kronecker((a + l % 2) % 2,1) * R2;
    if (R != 0)
    {
        for(i = 0;i < N;i++)
            for(j = 0;j < N;j++)
                A.GET_M()[i][j] += (Kronecker(a,j) - Kronecker(a - 1,j)) * (Kronecker(a,i) - Kronecker(a - 1,i)) / R;
    }
    if (a == N - 1)
    {
        a = 1;
        l++;
    }
    else
        a++;

}

void Strip::MakeStrip()
{
    while (l < L)
    {
        AddS();
        /*if( a == 1)
        {
        cout << A;
        cin.get();
        }
        */

    }
}

long int Strip::getL()
{
    return L;
}

double Strip::getCond()
{
    return N * A.GET_M()[0][0] / L;

}
