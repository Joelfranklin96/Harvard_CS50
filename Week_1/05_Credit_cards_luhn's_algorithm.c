#include <cs50.h>
#include <stdio.h>
#include <math.h>

int number_of_digits(long long number);
int valid_or_invalid(long long number, int digit_number);
int first_2_digits(long long number, int digit_number);
int first_digit(long long number,int digit_number);

int main(void)
{
    int flag, digit_number;
    long long number;
    number = get_long("Please enter your credit card number\n");

    digit_number = number_of_digits(number);
    flag = valid_or_invalid(number,digit_number);

    if (flag == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        int x = first_2_digits(number,digit_number);
        int y = first_digit(number,digit_number);
        if (x == 34 || x == 37)
        {
            printf("AMEX\n");
        }
        else if ((x == 51) || (x == 52) || (x == 53) || (x == 54) || (x == 55))
        {
            printf("MASTERCARD\n");
        }
        else if (y == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int number_of_digits(long long number)
{
    int i;
    for (i = 0; number != 0; i++)
    {
        number = number/10;
    }
    return i;
}

int valid_or_invalid(long long number, int digit_number)
{
    int sum = 0;
    long long n1;
    int n2,n3,n4,n5;
    if (number < (long long) pow(10,12))
    {
        return 0;
    }
    for (int j = 1; j <= digit_number; j++)
    {
        if (j % 2 == 0)
        {
            n1 = number % (long long) pow(10,j);
            n2 = n1 / (long long) pow(10,(j-1));
            n3 = (2*n2);
            if (n3 > 9)
            {
                n4 = n3/10;
                n5 = n3 % 10;
                sum = sum + n4 + n5;
            }
            else
            {
                sum = sum + n3;
            }
        }
        else
        {
            n1 = number % (long long) pow(10,j);
            n2 = n1 / (long long) pow(10,(j-1));
            sum = sum + n2;
        }
    }
    if ((sum % 10) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int first_2_digits(long long number, int digit_number)
{
    return number / (long long) pow(10,(digit_number-2));
}

int first_digit(long long number,int digit_number)
{
    return number / (long long) pow(10,(digit_number-1));
}
