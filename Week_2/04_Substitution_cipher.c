#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if ((argc > 2) || (argc == 1))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int key_length = strlen(key);
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char key_lower[key_length];
    char key_upper[key_length];

    for (int i = 0; i < key_length; i++)
    {
        key_lower[i] = tolower(key[i]);
        key_upper[i] = toupper(key[i]);
    }

    for (int i = 0; i < key_length; i++)
    {
        for (int j = i + 1; j < key_length; j++)
        {
            if (key_lower[i] == key_lower[j])
            {
                printf("Duplicate characters in the string\n");
                return 1;
            }
        }
    }

    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key_lower[i]))
        {
            printf("Invalid characters in the string\n");
            return 1;
        }
    }

    string plaintext = get_string("Please enter the text\n");
    int length = strlen(plaintext);
    char ciphertext[length + 1];
    string alpha_lower = "abcdefghijklmnopqrstuvwxyz";
    string alpha_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++)
    {
        int counter = 0;
        if isalpha(plaintext[i])
        {
            if islower(plaintext[i])
            {
                for (int j = 0; plaintext[i] != alpha_lower[j]; j++)
                {
                    counter++;
                }
                ciphertext[i] = key_lower[counter];
            }
            else
            {
                for (int j = 0; plaintext[i] != alpha_upper[j]; j++)
                {
                    counter++;
                }
                ciphertext[i] = key_upper[counter];
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
    printf("plaintext: %s\n", plaintext);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}