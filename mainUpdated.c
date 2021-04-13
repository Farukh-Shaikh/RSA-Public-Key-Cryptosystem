
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//All functions prototypes declared

void Output(int, int, int);
void Input();
void RandomPrime(int *, int *);
int KeyGen(int, int, int, int*);
int encrypt(int, int, int);
char decrypt(int, int, int);


char inputarr[100];			//Globally declared array for storing input by user
int converted[100];			// Globally declared array for storing the values of inputted data
int temp[55];				// Globally declared array for storing the values of alphabets and special characters
/************************************************MAIN FUNCTION***********************************************************/
int main()
{
    int rand1 = 0, rand2 = 0, n = 0, e = 0, d = 1, i = 0, Qn = 1;					//declaring and initializing variables
    char choice, again='Y';

    while (d == Qn)
    {
        RandomPrime(&rand1, &rand2);											//Calls RandomPrime function which returns two random prime numbers
        n = rand1*rand2;
        Qn = (rand1 - 1)*(rand2 - 1);
        d = KeyGen(rand1, rand2, n, &e);
    }
    while(1){									    // Generates key and returns the d value which is needed for RSA encryption
		Output(e, d, n);														// Calls the output function which displays the output on console
		Input();																// Input function, takes input from user and convert it in integers corresponding to their alphabetical values

		int Cm[100];                                                             //Cm is ciphered message
		char Dm[100];															 //Dm is deciphered message

		for (i = 0; i < strlen(inputarr); i++)
			Cm[i] = encrypt(converted[i], e, n);							//Encrypted data is stored in the array after being encrypted by encrypt function

		printf("\t\t|ENCRYPTED|\n\n>>>");
		for (i = 0; i < strlen(inputarr); i++)								//Runs and prints the message after it is encrypted
			printf("%d", Cm[i]);
		printf("<<<");

		printf("\n\n\tPress 'Y' if you want to Decipher the Text: ");
		choice = getche();

		if (choice == 'Y' || choice == 'y')									//Runs if users choice is 'y' and decrypts the message
		{
			printf("\n");
			for (i = 0; i < strlen(inputarr); i++)
				Dm[i] = decrypt(Cm[i], d, n);

			printf("\n\t\t|DECRYPTED|\n\n>>>");                             //prints decrypted message
			for (i = 0; i < strlen(inputarr); i++)
				printf("%c", Dm[i]);
			printf("<<<");
		}
		printf("\n\n\n");

		//replaying the program
		printf("\t\t|Do you want to Encrypt your data again?|\n");
		printf("\n\t Press N to end program or press any key to encrypt from RSA Encryption: ");
		again=getche();
		system("cls");

		if(again ==78 || again ==110)
            {break;}

	}//while(again != 'y' || again != 'Y');

	printf("\n\n\n\n\n\n\n\n\n\t\t\tTTTTTTTTTTT H       H    AAAA    N         N  K    K   SSSSSSS\n");
    printf("\t\t\t     T      H       H   A    A   N N       N  K   K   S       S\n");
    printf("\t\t\t     T      H       H  A      A  N   N     N  K  K    S\n");
    printf("\t\t\t     T      HHHHHHHHH  AAAAAAAA  N     N   N  KK       SSSSSSS\n");
    printf("\t\t\t     T      H       H  A      A  N      N  N  K  K            S\n");
    printf("\t\t\t     T      H       H  A      A  N       N N  K   K    S      S\n");
    printf("\t\t\t     T      H       H  A      A  N         N  K    K    SSSSSS \n\n");

	getch();
	return 0;

}
/****************************************MAIN END*******************************************************************/

void Output(int e, int d, int n)														//Prints the below shown data on console app
{
	printf("                        +********************************+\n");
	printf("                        |   RSA Public Key Cryptosystem  |\n");
	printf("                        +********************************+\n\n");

	printf("+----------------+\n");
	printf("| Key Generation |\n");
	printf("+----------------+\n\n");

	printf("Public Key.  (e,n) = (%d,%d)\n", e, n);
	printf("Private Key. (d,n) = (%d,%d)\n\n", d, n);

	printf("+---------------------+\n");
	printf("| Cipher and Decipher |\n");
	printf("+---------------------+\n\n");

	printf("\t\t|Enter the text to encrypt|\n\n");
}
void Input()												//Takes the input from user, the data which needs to be encrypted and convert it
{
	int i = 0, j = 65;

	fgets(inputarr, sizeof(inputarr), stdin);
	inputarr[strlen(inputarr) - 1] = '\0';					//Replaces the enter sign in array with \0
	{                                                       //new scope to do work in generating temp because we do not need a and b anymore
	    int a = 65, b = 97;
	    temp[0] = 63;                                       //assigning '?' in temp[0]. 63 is Ascii value of question mark

    //Assigning the Ascii values of alphabets to temp array starting from temp[1]
		for (i = 1; i<53; i++)
		{
			if (i <= 26)					//from temp[1] to temp[26] contains capital alphabets values
			{
				temp[i] = a;
				a++;
			}
			if (i>26)						//from temp[27] to temp[52] contains small alphabets values
			{
				temp[i] = b;
				b++;
			}
		}
	}
	temp[53] = ' ';
	temp[54] = 46;                          //46 is ascii value of '.'(dot)
	temp[55] = '\0';

	printf("\n\n");
	for (i = 0; i<strlen(inputarr); i++)						//Runs for the length of string entered
	{
		for (j = 0; j<55; j++)
		{
			if (inputarr[i] == temp[j])							//if the alphabets matches, then j is stored in converted array
			{                                                   //A=1 to Z=26 and a=27 to z=52. converted array will store the values corresponding to the English alphabet that is entered as a message
				converted[i] = j;                               //and we will encrypt that converted array of integers
			}
		}
	}
}
void RandomPrime(int *q1, int *q2)								// Used to generate two random prime numbers
{
	srand(time(NULL));											// for random numbers to change
	unsigned long long counter;
	unsigned long long counter_1;
	unsigned long long prime = 0;
	unsigned long long half = 0;
	unsigned long long prand1;
	unsigned long long prand2;
	while (1)													// Infinite loop
	{
		prime = 0;
		prand1 = ((rand() % 90) + 9);
		half = prand1 / 2;
		for (counter = 2; counter <= half; counter++)
			if (prand1 % counter == 0)							// if the random number is divisible then prime is assigned value 1 and for loop breaks
			{
				prime = 1;
				break;
			}
		if (prime == 0)											// runs if prime is equal to zero assigns the random value to *q1 and breaks the while loop
		{
			*q1 = prand1;
			break;
		}
	}
	while (1)													// the above loop repeated for the purpose of second random number
	{
		prime = 0;
		prand2 = ((rand() % 90) + 9);
		half = prand2 / 2;
		for (counter_1 = 2; counter_1 <= half; counter_1++)
			if (prand2 % counter_1 == 0)
			{
				prime = 1;
				break;
			}
		if (prime == 0)
		{
			*q2 = prand2;
			break;
		}
	}
}
int KeyGen(int p, int q, int n, int *ptr)					// Used to generate key for RSA encryption
{
	int D = 0, e = 0, i = 0, j = 0, flag = 0;

	int Qn = (p - 1)*(q - 1);

	for (i = 2; i<(Qn / 2); i++) {							// Finding the co-prime of Qn
		for (j = 2; j<i; j++) {
			if (i%j == 0 && Qn%j == 0) {					// Checks if the number divides both i and Qn. If yes then flag zero and breaks and finds another value for i which satisfies the co prime condition
				flag = 0;
				break;
			}
			else if(i%j != 0 && Qn%j != 0)					// Proceeds if the number is actually a co prime and assigns flag value 1
				flag = 1;
		}
		if (flag == 1) {									// If flag is 1 then assigns the value to e and end the for loop
			e = i;
			*ptr = i;
			break;
		}
	}

	for(D=1; D<Qn; D++)									// runs until D is found, which is needed for private key(used for decryption)
	{
		if(1== e*D % Qn)
            break;
	}
	return D;
}
int encrypt(int M, int exp, int n)					// Used to encrypt the message
{
	int Em = 1, i = 0;
	for (i = 0; i<exp; i++)							// Formula being used for RSA encryption
	{
		Em = Em*M;
		Em = Em%n;
	}

	return Em;
}
char decrypt(int C, int exp, int n)					// Used to decrypt the message
{
	int Em = 1, i = 0, temp = 0;
	for (i = 0; i<exp; i++)							// Formula being used for RSA decryption
	{
		Em = Em*C;
		Em = Em%n;
	}

	// Conditions for different values that needs to be decrypted

	if (Em >= 1 && Em<27)
		temp = Em + 64;
	else if (Em>26 && Em<53)
		temp = Em + 70;
	else if (Em == 0)
		temp = '?';
	else if (Em == 53)
		temp = 32;
	else if (Em == 54)
		temp = 46;

	return temp;
}
