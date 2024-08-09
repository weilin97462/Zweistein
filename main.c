#include <stdio.h>
#include"src/pdf_cdf.h"
#include"src/zweistein.h"

int main()
{
    int red_pos[6],blue_pos[6];
    init();
    printf("enter the position of red pieces (seperated by space, -1 means captured):\n");
    printf("e.g. 0 2 13 -1 12 19 means:\n");
    printf("1_2__\n_____\n__53_\n____6\n_____\n");
    for(int i=0;i<6;i++)
    {
        int _=scanf("%d",&red_pos[i]);
        if(red_pos[i]==24)
        {
            printf("Red already wins, the win rate of Red in EWN-simple is 1.000000\n");
            return;
        }
    }
    printf("enter the position of blue pieces (seperated by space, -1 means captured):\n");
    for(int i=0;i<6;i++)
    {
        int _=scanf("%d",&blue_pos[i]);
        if(blue_pos[i]==0)
        {
            printf("Blue already wins, the win rate of Red in EWN-simple is 0.000000\n");
            return;
        }
    }
    printf("Blue moves first, the win rate of Red in EWN-simple is %lf\n",zweistein(red_pos,blue_pos));
}