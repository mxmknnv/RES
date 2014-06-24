#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LongNumber.h"

LongNum gcd (LongNum a, LongNum b, LongNum & x, LongNum & y);
LongNum inverse(LongNum a, LongNum mod);

int main(int argc, char *argv[])
{
	if(argc==1) 
	{
		printf("Schnorr: Error. Please read the README file.\n");
		return 1;		
	}	
	switch (argv[1][0])
	{
		case 'g':
		{
			printf("Schnorr: Initial generation.\n");
			LongNum p, q, g, x, y, w, r, e, s, one(1), zero(0);
			p.Read("./schnorr_files/p");
			q.Read("./schnorr_files/q");
			g.Read("./schnorr_files/g");
			w.Read("./schnorr_files/w");
			r.Read("./schnorr_files/r");
			x=inverse(g, p);
			y=x.DegWithMod(w, p);
			y.Write("./schnorr_files/y");
			x=g.DegWithMod(r, p);
			x.Write("./schnorr_files/x");
			printf("Schnorr: Initial generation is successfully complete.\n");
			return 0;
		} break;
		case 's':
		{
			printf("Schnorr: Generation S.\n");
			LongNum q, w, r, e, x, y;
			w.Read("./schnorr_files/w");
			r.Read("./schnorr_files/r");
			e.Read("./schnorr_files/e");
			q.Read("./schnorr_files/q");
			y=w*e;
			x=r+y;
			y=x%q;
			y.Write("./schnorr_files/s");
			printf("Schnorr: Generation S is successfully complete.\n");
			return 0;
		} break;
		case 'v':
		{
			printf("Schnorr: Verification.\n");
			LongNum p, g, e, z, x, temp1, temp2, y, s;
			p.Read("./schnorr_files/p");
			g.Read("./schnorr_files/g");
			y.Read("./schnorr_files/y");
			e.Read("./schnorr_files/e");
			s.Read("./schnorr_files/s");
			x.Read("./schnorr_files/x");
			temp1=g.DegWithMod(s, p);
			temp2=y.DegWithMod(e, p);
			temp1=temp1*temp2;
			z=temp1%p;
			z.Write("./schnorr_files/z");
			printf("Schnorr: Verification is successfully complete.\n");
			if(x==z)
				printf("Schnorr: Authentication passed.\n");
			else
				printf("Schnorr: Authentication failed.\n");
			return 0;
		} break;
		default:
		{
			printf("Schnorr: Error. Please read the README file.\n");
			return 1;
		}
	}
}

LongNum gcd (LongNum a, LongNum b, LongNum & x, LongNum & y) 
{
	LongNum zero(0), one(1);
	if (a == zero) {
		x = zero; y = b/b;
		return b;
	}
	LongNum x1, y1;
	LongNum d = gcd (b%a, a, x1, y1);
	one=b/a;
	zero=one*x1;
	x=y1-zero;
	y = x1;
	return d;
}

LongNum inverse(LongNum a, LongNum mod)
{
	LongNum g, x, y, one(1), zero(0);
	g=gcd(a, mod, x, y);
	if (g!=one) 
		return zero;
	else {
		x=x%mod;
		x=x+mod;
		x=x%mod;
		return x;
	}
}