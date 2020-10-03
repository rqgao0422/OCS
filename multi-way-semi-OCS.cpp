/*
input: 
	n, number of elements in each tuple
output:
	gmin, minimum Gamma that appears in a feasible solution of the stricter LP
	gmax, maximum Gamma that appears in a feasible solution of the stricter LP
latex link:
	https://www.overleaf.com/3486144463wrhdwyywfqhy
*/
#include<bits/stdc++.h>
using namespace std;

const int N=100000055;
const long double eps=1e-15;
long double f[N];

int main(){
	int n;
	while(scanf("%d",&n)!=EOF){//n<=100,000,000
		int m=n;
		f[0]=1;
		for(int k=1;k<=m+5;k++)
			f[k]=f[k-1]*(1.-1./(long double)n)*(1-(long double)min(k-1,n-1)/(long double)n/(long double)(n-min(k-1,n-1)));
		for(int k=0;k<=m+5;k++)
			f[k]=1.-f[k];
		/*for(int k=0;k<=m+5;k++)
			printf("%.12Lf ",f[k]);puts("");*/
		long double l=0,r=1;
		while(l+eps<r){
			long double mid=(l+r)/2.;
			long double b=mid/(long double)n;
			bool isok=true;
			for(int k=1;k<=m+1;k++){
				b=(long double)(n+1)/(long double)(n)*b-1./(long double)n*(f[k]-f[k-1]);
				if(b>f[k+1]-f[k]){isok=false;break;}
			}
			if(b>0) isok=false;
			if(!isok) r=mid; else l=mid;
		}
		long double gmax=r;
		l=0,r=1;
		while(l+eps<r){
			long double mid=(l+r)/2.;
			long double b=mid/(long double)n;
			bool isok=true;
			for(int k=1;k<=m+1;k++){
				b=(long double)(n+1)/(long double)(n)*b-1./(long double)n*(f[k]-f[k-1]);
				if(f[k+1]-f[k]<0){isok=false;break;}
			}
			if(!isok) l=mid; else r=mid;
		}
		long double gmin=l;
		printf("%.12Lf %.12Lf\n",gmin,gmax);
	}
}
