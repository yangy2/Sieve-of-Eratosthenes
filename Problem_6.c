#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

struct PARAM
{
	int a;
	bool b;
};

void* sieve(void* arg)
{
	struct PARAM *param = (struct PARAM*)arg;

	int input = (*param).a;
	bool reverse = (*param).b;

	/*Create array representing numbers*/
	bool array[input+1];
	
	/*Initialize all values to true*/
	/*If a number is prime, it will stay true*/
	memset(array, true, sizeof(array));

	/*Sieve of Eratosthenes*/
	for(int i=2; i*i<=input; i++)
	{
		if(array[i] == true)
		{
			/*All multiples of number i are not prime*/
			for(int j=i+i; j<=input;j += i)
				array[j] = false;
		}
	}

	if(reverse == true)
	{
		/*Print prime numbers with digits reversed*/
		printf("Prime Numbers < %d with Digits Reversed\n", input);
		for(int i=2; i<=input; i++)
		{
			int num = 0;
			int newnum = 0;

			/*Reverse the digits of primes*/
			if(array[i] == true)
			{
				num = i;
				printf("%d --> ", num);
				while(num != 0)
				{
					newnum = newnum*10 + num%10;
					num = num/10;
				}

				printf("%d", newnum);
				
				/*Check if new number still prime*/
				for(int j=2; j<newnum; j++)
				{
					if((newnum % j) == 0)
					{
						printf(" (Not Prime)");
						break;
					}
				}

				printf("\n");
			}
		}
	}

	else
	{
		/*Print prime numbers*/
		printf("Prime Numbers < %d\n", input);
		for(int i=2; i<=input; i++)
			if(array[i] == true)
				printf("%d\n", i);
	}
}

int main(int argc, char** argv)
{
	const int x = atoi(argv[1]); /*x is limit to sieve*/

	pthread_t prime1, prime2;

	/*Arguments for thread 1 to pass*/
	/*Thread 1 finds prime numbers*/
	struct PARAM *param1;	
	param1 = malloc(sizeof(struct PARAM));
	(*param1).a = x;
	(*param1).b = false;

	/*Arguments for thread 2 to pass*/
	/*Thread 2 reverses prime numbers*/
	struct PARAM *param2;
	param2 = malloc(sizeof(struct PARAM));
	(*param2).a = x;
	(*param2).b = true;

	/*Create and join threads*/
	pthread_create(&prime1, NULL, sieve, (void*)param1);
	pthread_create(&prime2, NULL, sieve, (void*)param2);

	pthread_join(prime1, NULL);
	pthread_join(prime2, NULL);

	printf("Complete!\n");
}
