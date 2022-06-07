// Print the following pattern
// Height: 8
//        #
//       ##
//      ###
//     ####
//    #####
//   ######
//  #######
// ########

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Please enter a number between 1 and 8\n ");
    }
    while ((height < 1) || (height > 8));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (height - i - 1); j++)
        {
            printf(" ");
        }
        for (int z = 0; z <= i; z++)
        {
            printf("#");
        }
        printf("\n");
    }
}