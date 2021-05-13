#include <iostream>
#include "givevalue.h"
#include "convect.h"
#include "dif3.h"
#include "mean.h"
#include "transvalue.h"

using namespace std;

extern double w[194][258];
extern double wi[194][258];
extern double ne[194][258];
extern double phi[194][258];
extern double tau;
extern double alpha0;
extern double delta_ne[194][258];
extern double delta_phi[194][258];

void sw(double& f,double& fi)
{
    double fxy[194][258]={};
    convect(fxy,wi);
    double dif2t[194][258]={};
    dif3(dif2t,w);

    double work[194][258];
    double meanphi[194];
    double meandeni[194];
    mean(meanphi,phi);
    mean(meandeni,ne);

    givevalue(meanphi,phi,delta_phi);
    givevalue(meandeni,ne,delta_ne);

    for(int i=1;i<=194;i++)
    {
        for(int j=1;j<=258;j++)
        {
            work[i-1][j-1]=w[i-1][j-1]*f+wi[i-1][j-1]*fi;
            work[i-1][j-1]+=dif2t[i-1][j-1]-fxy[i-1][j-1];
            work[i-1][j-1]+=alpha0*(delta_phi[i-1][j-1]-delta_ne[i-1][j-1])*tau;
        }
    }

    if(f<0.6)
    {
        transvalue(w,wi);
        transvalue(wi,work);
    }
    else transvalue(wi,work);

    edgey(wi);
}
