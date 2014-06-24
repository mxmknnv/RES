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
		printf("RSA: Error. Please read the README file.\n");
		return 1;		
	}	
	switch (argv[1][0])
	{
		case 'g':
		{
			printf("RSA: Generation.\n");
			LongNum p, q, e, n, d, one(1), func;
			p.Read("./rsa_files/p");
			q.Read("./rsa_files/q");
			e.Read("./rsa_files/e");
			n=p*q;
			n.Write("./rsa_files/n");
			p=p-one;
			q=q-one;
			func=p*q;
			d=inverse(e, func);
			d.Write("./rsa_files/d");
			printf("RSA: Generation is successfully complete.\n");
			return 0;
		} break;
		case 'e':
		{
			printf("RSA: Encription.\n");
			LongNum e, n , m, em;
			e.Read("./rsa_files/e");
			n.Read("./rsa_files/n");
			m.Read("./rsa_files/message");
			em=m.DegWithMod(e, n);
			em.Write("./rsa_files/encrypted_message");
			printf("RSA: Encription is successfully complete.\n");
			return 0;
		} break;
		case 'd':
		{
			printf("RSA: Decription.\n");
			LongNum d, n , dm, em;
			d.Read("./rsa_files/d");
			n.Read("./rsa_files/n");
			em.Read("./rsa_files/encrypted_message");
			dm=em.DegWithMod(d, n);
			dm.Write("./rsa_files/decrypted_message");
			printf("RSA: Decription is successfully complete.\n");
			return 0;
		} break;
		default:
		{
			printf("RSA: Error. Please read the README file.\n");
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
