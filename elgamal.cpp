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
		printf("Elgamal: Error. Please read the README file.\n");
		return 1;		
	}	
	switch (argv[1][0])
	{
		case 'g':
		{
			printf("Elgamal: Generation.\n");
			LongNum p, g, x, y;
			p.Read("./elgamal_files/p");
			g.Read("./elgamal_files/g");
			x.Read("./elgamal_files/x");
			y=g.DegWithMod(x, p);
			y.Write("./elgamal_files/y");
			printf("Elgamal: Generation is successfully complete.\n");
			return 0;
		} break;
		case 'e':
		{
			printf("Elgamal: Encription.\n");
			LongNum p, g, k, a, m, b, y;
			p.Read("./elgamal_files/p");
			g.Read("./elgamal_files/g");
			k.Read("./elgamal_files/k");
			m.Read("./elgamal_files/message");
			y.Read("./elgamal_files/y");
			a=g.DegWithMod(k, p);
			a.Write("./elgamal_files/a");
			a=y.DegWithMod(k, p);
			y=a*m;
			b=y%p;
			b.Write("./elgamal_files/b");
			printf("Elgamal: Encription is successfully complete.\n");
			return 0;
		} break;
		case 'd':
		{
			printf("Elgamal: Decription.\n");
			LongNum p, k, a, m, b, x, y;
			p.Read("./elgamal_files/p");
			a.Read("./elgamal_files/a");
			b.Read("./elgamal_files/b");
			x.Read("./elgamal_files/x");
			y=a.DegWithMod(x, p);
			a=inverse(y, p);
			x=b*a;
			m=x%p;
			m.Write("./elgamal_files/decrypted_message");			
			printf("Elgamal: Decription is successfully complete.\n");
			return 0;
		} break;
		default:
		{
			printf("Elgamal: Error. Please read the README file.\n");
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