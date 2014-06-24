#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

BigInt newBigInt(int l, int a, char *name)
{
	BigInt x;	
	x.amount=l;
	x.number=(int*)calloc(x.amount, sizeof(int));
	if(x.number == NULL) 
	{
		printf("Can't allocate memory in function \"%s\".\n", name);
		exit(1);
	}
	if(a>=0)
		x.sign=0;
	else
	{
		x.sign=1;
		a=-a;
	}
	x.number[0]=a;
	return x;	
}

BigInt input(char *name)
{
	FILE *file=NULL;
	BigInt x;
	if (!(file = fopen(name, "r")))
	{
		printf("Can't open file \"%s\". Please, check its arrangement.\n", name);
		exit (1);
	}
	int k=0, r=0, j=0, left=0;
	char *str=NULL, sign=0, arr[BASE_DIG-1];	
	fseek(file,0,2);
	if(!(k=ftell(file))) 
	{
		printf("Error. File \"%s\" is empty. Please, check the file.\n", name);
		exit (1);
	}
	fseek(file,0,0);
	fscanf(file, "%c", &sign);
	if(sign=='-') 
		{
			k--;
		}
	else 
		{
			fseek(file,0,0);
		}
	str=(char*)calloc((k+1), sizeof(char));
	if(!(r=fscanf(file," %1000000[0-9]",str)))
	{
		printf("Error. The number in file \"%s\" written incorrectly. Please, check the file.\n", name);
		exit(1);
	}
	if(r==-1)
	{
		printf("Error. The number in file \"%s\" written incorrectly. Please, check the file.\n", name);
		exit(1);
	}
	r=strlen(str);
	if(r!=k)
		printf("Warning. File \"%s\" contain not only number. Quantity of the read figures: %i.\n", name, r);
	else
		printf("File \"%s\" is read. Quantity of the read figures: %i.\n", name, r);
	strrev(str);
	for(k=r-1; k>0 && str[k]=='0'; str[k]='\0', k--);
	strrev(str);
	r=strlen(str);
	left=r%BASE_DIG;
	x=newBigInt(left ? r/BASE_DIG+1 : r/BASE_DIG, 0, "read");	
	if(sign=='-')
		x.sign=1;
	for(k=0; k<x.amount-1; k++)
	{
		r=r-BASE_DIG;
		for(j=0; j<BASE_DIG; j++)
			arr[j]=str[r+j];
		x.number[k]=atoi(arr);	
	}
	for(k=0; k<BASE_DIG; k++) arr[k]='\0';
	if(left)
	{
		for(j=0; j<left; j++)
			arr[j]=str[j];			
	}
	else
	{
		for(j=0; j<BASE_DIG; j++)
			arr[j]=str[j];
	}
	x.number[x.amount-1]=atoi(arr);
	free(str);
	fclose(file);
	return x;
}

void output(BigInt x, char *name)
{
	FILE *file = fopen(name, "w");
	if(x.sign) fprintf(file, "-");
	fprintf(file, "%d", x.number[x.amount-1]);
	int i=0;
	for(i=x.amount-2; i>=0; i--) fprintf(file, "%04d", x.number[i]);
	fclose(file);
}

int max(BigInt a, BigInt b)
{														
	if (a.amount>b.amount)
		return 1;
	if (a.amount<b.amount)
		return 2;
	int i=0;
	for (i=a.amount-1; i>=0; i--)					
	{													
		if (a.number[i]>b.number[i])
			return 1;
		if (a.number[i]<b.number[i])
			return 2;
	}
	return 0;
}

BigInt add(BigInt a, BigInt b)
{ 	
	if (a.sign==b.sign)								
	{
		if (b.amount>a.amount)
		{
			return add(b,a);
		}
		BigInt x=newBigInt(a.amount, 0, "addition");
		x.sign=a.sign;		
		int carry=0, i=0;
		for (i=0; i<b.amount; i++)
		{
			x.number[i]=a.number[i]+b.number[i]+carry;							
			if (x.number[i]>=BASE)
			{
				x.number[i]-=BASE;
				carry=1;
			}
			else
				carry=0;
		}
		for (; i<a.amount; i++)
		{
			x.number[i]=a.number[i]+carry;							
			if (x.number[i]>=BASE)
			{
				x.number[i]-=BASE;
				carry=1;
			}
			else
				carry=0;
		}
		if (carry==1)
		{
			x.amount++;
			x.number=(int*)realloc(x.number, x.amount*sizeof(int));
			if(x.number == NULL) 
			{
				printf("Can't allocate memory in function addition.\n");
				exit(1);
			}
			x.number[x.amount-1]=1;
		}
		return x;
	}
	else 
		if (a.sign==1)							
		{
			a.sign=0;
			return sub(b, a);
		}
		else
		{
			b.sign=0;
			return sub(a, b);
		}
}

BigInt sub(BigInt a, BigInt b)
{ 
	BigInt x;
	if (!a.sign && b.sign) 				 {																		
		b.sign=0;
		return add(a,b);
	}
	if (a.sign && !b.sign)
	{
		a.sign=0;
		x=add(a, b);
		x.sign=1;
		return x;	
	}										
	int h=max(a,b);
	if(!h)
	{
		x=newBigInt(1, 0, "subtraction");		
		return x;
	}
	if(h==1) 
		x=subsub(a, b);
	else
		x=subsub(b, a);
	if ((a.sign && h==1)||(!a.sign && h==2))
		x.sign=1;	
	else
		x.sign=0;
	h=x.amount-1;
	while(x.number[h]==0)
		h--;
	if (h!=x.amount-1)
	{
		x.amount=h+1;
		x.number=(int*)realloc(x.number, x.amount*sizeof(int));
		if(x.number == NULL) 
		{
			printf("Can't allocate memory in function subtraction.\n");
			exit(1);
		}
	}
	return x;
}

BigInt subsub(BigInt a, BigInt b)
{
	int i=0, carry=0;	
	BigInt x=newBigInt(a.amount, 0, "subtraction");
	for (i=0; i<b.amount; i++)
	{
		x.number[i]=a.number[i]-b.number[i]-carry;
		if (x.number[i]<0)						
		{
			x.number[i]+=BASE;
			carry=1;
		}
		else
			carry=0;
	}
	for (; i<a.amount; i++)
	{
		x.number[i]=a.number[i]-carry;
		if (x.number[i]<0)						
		{
			x.number[i]+=BASE;
			carry=1;
		}
		else
			carry=0;
	}
	return x;
}

BigInt mul(BigInt a, BigInt b)
{
	BigInt x;											
	if(a.amount==1 && a.number[0]==0) 
	{
		x=newBigInt(1, 0, "multiplication");		
		return x;
	}
	if(b.amount==1 && b.number[0]==0) 
	{
		x=newBigInt(1, 0, "multiplication");		
		return x;
	}	
	x=newBigInt(a.amount+b.amount, 0, "multiplication");	
	if (a.sign==b.sign)
		x.sign=0;
	else x.sign=1;					
	int i=0, j=0, carry=0;
	for (i=0; i<a.amount; i++)
	{
		carry=0;
		for (j=0; j<b.amount; j++)					
		{
			x.number[i+j]+=a.number[i]*b.number[j];
			carry=x.number[i+j]/BASE;
			x.number[i+j] -= carry*BASE;					
			x.number[i+j+1]+=carry;
		}
	}
	carry=x.amount-1;
	while(x.number[carry]==0)
		carry--;
	if (carry!=x.amount-1)
	{
		x.amount=carry+1;
		x.number=(int*)realloc(x.number, x.amount*sizeof(int));
		if(x.number == NULL) 
		{
			printf("Can't allocate memory in function multiplication.\n");
			exit(1);
		}
		
	}
	return x;
}

BigInt int_mul(BigInt a, int n)
{														
	BigInt x=newBigInt(a.amount, 0, "division or module");											
	int i=0, carry=0, tmp=x.amount-1;
	for (i=0; i<a.amount; i++)
	{
		x.number[i]+=a.number[i]*n;
		carry=x.number[i]/BASE;
		x.number[i] -= carry*BASE;
		if ((i==a.amount-1)&&(carry!=0))
		{
			x.amount++;
			x.number=(int*)realloc(x.number, x.amount*sizeof(int));
			if(x.number == NULL) 
			{
				printf("Can't allocate memory in function division or module.\n");
				exit(1);
			}
			x.number[i+1]=0;
		}
		x.number[i+1]+=carry;
	}
	return x;
}

BigInt my_div(BigInt a, BigInt b)
{
	BigInt x;		
	if (b.amount==1 && b.number[0]==0)				
	{
		printf("Error. Division by zero!\n");
		x=newBigInt(1, 0, "division");
		return x;
	}
	int i=max(a, b);
	if (i==2)						
	{	
		x=newBigInt(1, 0, "division");
		return x;
	}
	if (i==0)						
	{	
		x=newBigInt(1, 1, "division");
		return x;
	}
	x=newBigInt(a.amount, 0, "division");
	if (a.sign==b.sign)						
		x.sign=0;
	else 
		x.sign=1;
	BigInt current, tmp;
	current=newBigInt(b.amount, 0, "division");
	int cur_num=0, index=0, cur_q=0, r=0, m=0;
	cur_num=a.amount-b.amount;
	for (i=0; i<current.amount; i++)
		current.number[i]=a.number[cur_num+i];
	index=x.amount-1;							
	while (1)
	{
		if (max(b, current)==1)
		{										
			current.amount++;
			current.number=(int*)realloc(current.number, current.amount*sizeof(int));
			if(current.number == NULL) 
			{
				printf("Can't allocate memory in function division.\n");
				exit(1);
			}
			for (i=current.amount-1; i>0; i--)
				current.number[i]=current.number[i-1];
			cur_num--;
			current.number[0]=a.number[cur_num];
		}
		cur_q=0; i=0; r=BASE;						
		while(i<=r)
		{
			m=(i+r)/2;
			tmp = int_mul(b, m);
			if (max(tmp, current)!=1)
			{	
				cur_q=m; 
				i=m+1;
			}
			else 
				r=m-1; 
			free(tmp.number);
		}
		x.number[index]=cur_q;						
		index--;	
		tmp=sub(current, int_mul(b, cur_q));
		free(current.number);
		current=newBigInt(tmp.amount, 0, "division");
		for (i=0; i<current.amount; i++)
			current.number[i]=tmp.number[i];
		free(tmp.number);	
		if (cur_num==0)								
			break;
		if (!((current.amount==1)&&(current.number[0]==0)))
		{
			current.amount++;
			current.number = (int*)realloc(current.number, current.amount*sizeof(int));
			if(current.number == NULL) 
			{
				printf("Can't allocate memory in function division.\n");
				exit(1);
			}
			for (i=current.amount-1; i>0; i--)
				current.number[i]=current.number[i-1];
		}
		cur_num--;
		current.number[0]=a.number[cur_num];
	}			
	if (index>-1)
	{
		index++;
		x.amount-=index;
		for (i=0; i<x.amount; i++)
			x.number[i]=x.number[i+index];
		x.number=(int*)realloc(x.number, x.amount*sizeof(int));
		if(x.number == NULL) 
		{
			printf("Can't allocate memory in function division.\n");
			exit(1);
		}
	}
	free(current.number);
	return x;
}

BigInt my_mod(BigInt a, BigInt b)
{
	BigInt current;		
	if (b.amount==1 && b.number[0]==0)				
	{
		printf("Error. Division by zero!\n");
		current=newBigInt(1, 0, "module");
		return current;
	}
	int i=max(a, b);
	if (i==2)					
	{	
		current=newBigInt(a.amount, 0, "module");
		current.sign=a.sign;
		for(i=0; i<current.amount; i++)
			current.number[i]=a.number[i];
		return current;
	}
	if (i==0)						
	{	
		current=newBigInt(1, 0, "module");
		return current;
	}
	BigInt tmp;
	current=newBigInt(b.amount, 0, "module");
	current.sign=b.sign;							
	int cur_num=0, cur_q=0, r=0, m=0;
	cur_num=a.amount-b.amount;
	for (i=0; i<current.amount; i++)
		current.number[i]=a.number[cur_num+i];							
	while (1)
	{
		if (max(b, current)==1)
		{										
			current.amount++;
			current.number=(int*)realloc(current.number, current.amount*sizeof(int));
			if(current.number == NULL) 
			{
				printf("Can't allocate memory in function module.\n");
				exit(1);
			}
			for (i=current.amount-1; i>0; i--)
				current.number[i]=current.number[i-1];
			cur_num--;
			current.number[0]=a.number[cur_num];
		}
		cur_q=0; i=0; r=BASE;						
		while(i<=r)
		{
			m=(i+r)/2;
			tmp = int_mul(b, m);
			if (max(tmp, current)!=1)
			{	
				cur_q=m; 
				i=m+1;
			}
			else 
				r=m-1; 
			free(tmp.number);
		}
		tmp=sub(current, int_mul(b, cur_q));
		free(current.number);
		current=newBigInt(tmp.amount, 0, "module");
		for (i=0; i<current.amount; i++)
			current.number[i]=tmp.number[i];
		free(tmp.number);	
		if (cur_num==0)								
			break;
		if (!((current.amount==1)&&(current.number[0]==0)))
		{
			current.amount++;
			current.number = (int*)realloc(current.number, current.amount*sizeof(int));
			if(current.number == NULL) 
			{
				printf("Can't allocate memory in function module.\n");
				exit(1);
			}
			for (i=current.amount-1; i>0; i--)
				current.number[i]=current.number[i-1];
		}
		cur_num--;
		current.number[0]=a.number[cur_num];
	}			
	return current;
}

BigInt deg_with_mod(BigInt a, BigInt b, BigInt mod)
{														
	BigInt x;
	if (mod.amount==1 && mod.number[0]==0)				
	{
		printf("Error. Module = 0!\n");
		x=newBigInt(1, 0, "division with module");
		return x;
	}
	if (mod.amount==1 && mod.number[0]==1)				
	{
		x=newBigInt(1, 0, "division with module");
		return x;
	}
	BigInt num, deg, zero, one, two;
	num=newBigInt(a.amount, 0, "division with module");
	num.sign=a.sign;
	int i=0;
	for(i=0; i<a.amount; i++)
		num.number[i]=a.number[i];
	deg=newBigInt(b.amount, 0, "division with module");
	deg.sign=b.sign;
	for(i=0; i<b.amount; i++)
		deg.number[i]=b.number[i];
	zero=newBigInt(1, 0, "division with module");	
	one=newBigInt(1, 1, "division with module");
	two=newBigInt(1, 2, "division with module");
	x=newBigInt(1, 1, "division with module");
	while (max(deg, zero)==1)						
	{
		if (max(my_mod(deg, two), one)==0)
		{
			x=my_mod(mul(x, num), mod);
		}
		num=my_mod(mul(num, num), mod);
		deg=my_div(deg, two);
	}
	free(num.number);
	free(deg.number);
	free(zero.number);
	free(one.number);
	free(two.number);
	return x;
}
