#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LongNumber.h"

LongNum::LongNum() 
{
	Number.sign=0;
	Number.amount=1;
	Number.number=(int*)calloc(Number.amount, sizeof(int));
	Number.number[0]=0;
}

LongNum::~LongNum() 
{
	free(Number.number);
}

LongNum::LongNum(const LongNum &A) 
{
	Number.sign = A.Number.sign;
	Number.amount = A.Number.amount;
	Number.number = (int*)calloc(Number.amount, sizeof(int));
	for(int i=0; i<Number.amount; i++)
		Number.number[i]=A.Number.number[i];
}

LongNum::LongNum(int a) 
{
	if(a>=0)	
		Number.sign=0;
	else
	{
		Number.sign=1;
		a=-a;
	}
	Number.amount = 1;
	Number.number = (int*)calloc(Number.amount, sizeof(int));
	Number.number[0]=a;
}

LongNum& LongNum::operator =(const LongNum &A) 
{
	if (this==&A)
		return *this;
	Number.sign = A.Number.sign;
	Number.amount = A.Number.amount;
	free(Number.number);
	Number.number = (int*)calloc(Number.amount, sizeof(int));
	for(int i=0; i<Number.amount; i++)
		Number.number[i]=A.Number.number[i];
	return *this;
}

const LongNum LongNum::operator +(LongNum &A) 
{
	LongNum X;
	X.Number=add(Number, A.Number);
	return X;
}

const LongNum LongNum::operator -(LongNum &A) 
{
	LongNum X;
	X.Number=sub(Number, A.Number);
	return X;
} 

const LongNum LongNum::operator *(LongNum &A) 
{
	LongNum X;
	X.Number=mul(Number, A.Number);
	return X;
}

const LongNum LongNum::operator /(LongNum &A) 
{
	LongNum X;
	X.Number=my_div(Number, A.Number);
	return X;
}

const LongNum LongNum::operator %(LongNum &A) 
{
	LongNum X;
	X.Number=my_mod(Number, A.Number);
	return X;
}

const LongNum LongNum::DegWithMod(LongNum &A, LongNum &M) 
{
	LongNum X;
	X.Number=deg_with_mod(Number, A.Number, M.Number);
	return X;
}

bool LongNum::operator ==(const LongNum &A) 
{
	if(max(Number, A.Number)==0)
		return true;
	else
		return false;
}

bool LongNum::operator >(const LongNum &A) 
{
	if(Number.sign==1 && A.Number.sign==0)
		return false;
	if(Number.sign==0 && A.Number.sign==1)
		return true;	
	if(Number.sign==1)
	{		
		if(max(Number, A.Number)==1)
			return false;
		else
			return true;
	}
	if(max(Number, A.Number)==1)
			return true;
		else
			return false;
}

bool LongNum::operator <(const LongNum &A) 
{
	if(Number.sign==1 && A.Number.sign==0)
		return true;
	if(Number.sign==0 && A.Number.sign==1)
		return false;	
	if(Number.sign==1)
	{		
		if(max(Number, A.Number)==2)
			return false;
		else
			return true;
	}
	if(max(Number, A.Number)==2)
			return true;
		else
			return false;
}

bool LongNum::operator ==(int a) 
{
	if(Number.sign==1 && a>0)
		return false;
	if(Number.sign==0 && a<0)
		return false;	
	if(Number.amount>1)
		return false;
	if(a<0) a=-a;
	if(Number.number[0]==a)
		return true;
	else
		return false;
}

bool LongNum::operator >(int a) 
{
	if(Number.sign==1 && a>0)
		return false;
	if(Number.sign==0 && a<0)
		return true;	
	if(a>0)
		if(Number.amount>1)
			return true;
	if(a<0)
		if(Number.amount>1)
			return false;
	if(a<0)
	{
		a=-a;		
		if(Number.number[0]>a)
			return false;
		else
			return true;
	}
	if(Number.number[0]>a)
			return true;
		else
			return false;
}

bool LongNum::operator <(int a) 
{
	if(Number.sign==1 && a>0)
		return true;
	if(Number.sign==0 && a<0)
		return false;	
	if(Number.amount>1)
		return false;
	if(a<0)
	{
		a=-a;
		if(Number.number[0]<a)
			return false;
		else
			return true;
	}
	if(Number.number[0]<a)
			return true;
		else
			return false;
}

bool LongNum::operator >=(const LongNum &A)
{
	int i=max(Number, A.Number);
	if(i==0)
		return true;
	if(i==1)
		return true;
	return false;
}


bool LongNum::operator <=(const LongNum &A)
{
	int i=max(Number, A.Number);
	if(i==0)
		return true;
	if(i==2)
		return true;
	return false;
}

bool LongNum::operator >=(int a)
{
	if(Number.sign==1 && a>0)
		return false;
	if(Number.sign==0 && a<0)
		return true;	
	if(a>0)
		if(Number.amount>1)
			return true;
	if(a<0)
		if(Number.amount>1)
			return false;
	if(a<0)
	{
		a=-a;		
		if(Number.number[0]>=a)
			return false;
		else
			return true;
	}
	if(Number.number[0]>=a)
			return true;
		else
			return false;
}


bool LongNum::operator <=(int a)
{
	if(Number.sign==1 && a>0)
		return true;
	if(Number.sign==0 && a<0)
		return false;	
	if(a>0)
		if(Number.amount>1)
			return false;
	if(a<0)
		if(Number.amount>1)
			return true;
	if(a<0)
	{
		a=-a;		
		if(Number.number[0]<=a)
			return false;
		else
			return true;
	}
	if(Number.number[0]<=a)
			return true;
		else
			return false;
}

bool LongNum::operator !=(const LongNum &A)
{
	if(max(Number, A.Number)!=0)
		return true;
	else
		return false;
}

bool LongNum::operator !=(int a)
{
	if(Number.sign==1 && a>0)
		return true;
	if(Number.sign==0 && a<0)
		return true;	
	if(Number.amount>1)
		return true;
	if(a<0) a=-a;
	if(Number.number[0]==a)
		return false;
	else
		return true;
}

void LongNum::Write(char *name) 
{
	output(Number, name);
}

void LongNum::Read(char *name) 
{
	Number = input(name);
}
