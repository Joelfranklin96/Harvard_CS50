#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Please enter the text\n ");

    int total_letters = count_letters(text);
    int total_words = count_words(text);
    int total_sentences = count_sentences(text);

    float L = (((float) total_letters / total_words) * 100);
    float S = (((float) total_sentences / total_words) * 100);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);
    int main_index = (int) index;

    if (main_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (main_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", main_index);
    }

}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < (int) strlen(text); i++)
    {
        if isalpha(text[i])
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; i < (int) strlen(text); i++)
    {
        if ((int) text[i] == 32)
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < (int) strlen(text); i++)
    {
        if (((int) text[i] == 33) || ((int) text[i] == 46) || ((int) text[i] == 63))
        {
            count++;
        }
    }
    return count;
}