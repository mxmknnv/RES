#define BASE_DIG 4
#define BASE 10000

typedef struct _BigInt
{
	int *number, amount;
	char sign;
} BigInt;

char *strrev(char *str);
BigInt input(char *name);
void output(BigInt x, char *name);
BigInt add(BigInt a, BigInt b);
BigInt sub(BigInt a, BigInt b);
BigInt subsub(BigInt a, BigInt b);
BigInt mul(BigInt a, BigInt b); 
BigInt int_mul(BigInt a, int n); 
BigInt my_div(BigInt a, BigInt b);
BigInt my_mod(BigInt a, BigInt b);
BigInt deg_with_mod(BigInt a, BigInt b, BigInt mod);
int max(BigInt a, BigInt b); //Возвращает 1 - когда больше первый аргумент, 2 - больше второй аргумент, 0 - равны
BigInt newBigInt(int l, int a, char *name);
