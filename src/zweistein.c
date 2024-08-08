#include"pdf_cdf.h"
#include"zweistein.h"
#include <stdio.h>

const int red_distance_to_corner[25]=
{
    4,4,4,4,4,
    4,3,3,3,3,
    4,3,2,2,2,
    4,3,2,1,1,
    4,3,2,1,0
};
const int blue_distance_to_corner[25]=
{
    0,1,2,3,4,
    1,1,2,3,4,
    2,2,2,3,4,
    3,3,3,3,4,
    4,4,4,4,4
};
double zweistein(int red_pos[6],int blue_pos[6])
{
    int red_dist[6],blue_dist[6];
    printf(" red dist:{");
    for(int i=0;i<6;i++)
    {
        if(red_pos[i]==-1)
            red_dist[i]=0;
        else
            red_dist[i]=red_distance_to_corner[red_pos[i]];
        printf(" %d,",red_dist[i]);
    }
    printf("\b}\n");
    printf("blue dist:{");
    for(int i=0;i<6;i++)
    {
        if(blue_pos[i]==-1)
            blue_dist[i]=0;
        else
            blue_dist[i]=blue_distance_to_corner[blue_pos[i]];
        printf(" %d,",blue_dist[i]);
    }
    printf("\b}\n");
    double sum=0;
    for(int i=1;i<=19;i++)
    {
        sum+=DTC_cdf[encode_id(red_dist)][i-1]*DTC_pdf[encode_id(blue_dist)][i];
    }
    printf("red cdf:\n{");
    for(int i=1;i<=19;i++)
    {
        printf("%lf,",DTC_cdf[encode_id(red_dist)][i]);
    }
    printf("\b}\n");
    printf("blue pdf:\n{");
    for(int i=1;i<=19;i++)
    {
        printf("%lf,",DTC_pdf[encode_id(blue_dist)][i]);
    }
    printf("\b}\n");
    return sum;
}