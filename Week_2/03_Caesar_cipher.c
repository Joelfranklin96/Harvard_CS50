#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if ((argc == 1) || (argc >= 3))
    {
        printf("You have either entered 0 arguements or more than 1 arguement\n");
        return 1;
    }
    else if (atoi(argv[1]))
    {
        int k = atoi(argv[1]);
        if (k > 26)
        {
           k = k % 26;
        }

        string plaintext = get_string("Please enter plaintext\n");
        int length = strlen(plaintext);
        char ciphertext[length];

        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (isalpha(plaintext[i]))
            {
                if islower(plaintext[i])
                {
                    int a = 'z' - plaintext[i];
                    if (k <= a)
                    {
                        ciphertext[i] = plaintext[i] + k;
                    }
                    else
                    {
                        ciphertext[i] = 'a' + k - a - 1;
                    }
                }
                else
                {
                    int a = 'Z' - plaintext[i];
                    if (k <= a)
                    {
                        ciphertext[i] = plaintext[i] + k;
                    }
                    else
                    {
                        ciphertext[i] = 'A' + k - a - 1;
                    }
                }
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
        }
        printf("plaintext: %s\n",plaintext);
        printf("ciphertext: %s\n",ciphertext);
        return 0;
    }
    else
    {
        //printf("Usage: ./caesar key\n");
        return 1;
    }
}