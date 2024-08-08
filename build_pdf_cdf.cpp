#include<stdio.h>
#include<string.h>

double DTC_pdf[15625][20];
double DTC_cdf[15625][20];
char data_available[15625];

int encode_id(int dist[])
{
    int multiplier=1;
    int sum=0;
    for(int i=0;i<6;i++)
    {
        sum+=dist[i]*multiplier;
        multiplier*=5;
    }
    return sum;
}
void decode_id(int board_id,int dist[])
{
    for(int i=0;i<6;i++)
    {
        dist[i]=board_id%5;
        board_id/=5;
    }
}
void right_shift(double pdf[])
{
    for(int i=20;i>0;i--)
    {
        pdf[i]=pdf[i-1];
    }
    pdf[0]=0;
}
double calculate_DTC_exp(double pdf[])
{
    double sum=0;
    for(int i=0;i<20;i++)
    {
        sum+=i*pdf[i];
    }
    return sum;
} 
double* tree_serach(int board_id)
{
    if(data_available[board_id]==1)
    {
        return DTC_pdf[board_id];
    }
    // the distance array
    int dist[6]={};
    int dist_copy[6];
    // decode the id to distance array
    decode_id(board_id,dist);
    double pdf_sum[20]={};
    for (int dice=0;dice<6;dice++)
    {
        // find steps
        // piece with dice number is alive
        if(dist[dice]>1)
        {
            memcpy(dist_copy,dist,sizeof(dist));
            dist_copy[dice]--;
            double pdf_child[20];
            memcpy(pdf_child,tree_serach(encode_id(dist_copy)),sizeof(pdf_child));
            right_shift(pdf_child);
            for(int i=0;i<20;i++)
            {
                pdf_sum[i]+=pdf_child[i];
            }
        }
        else if(dist[dice]==1)
        {
            pdf_sum[1]+=1;
        }
        // piece with dice number is captured
        // dist[dice]=0
        else 
        {
            double min_exp=10000;
            double cur_exp;
            int min_arg=0;
            double pdf_child[2][20]={{}};
            for(int i=dice+1;i<6;i++)
            {
                if(dist[i]>1)
                {
                    memcpy(dist_copy,dist,sizeof(dist));
                    dist_copy[i]--;
                    memcpy(pdf_child[0],tree_serach(encode_id(dist_copy)),sizeof(pdf_child[0]));
                    right_shift(pdf_child[0]);
                    min_exp=calculate_DTC_exp(pdf_child[0]);
                    break;
                }
                else if(dist[i]==1)
                {
                    pdf_child[0][0]=0;
                    pdf_child[0][1]=1;
                    min_exp=1;
                    break;
                }
            }
            for(int i=dice-1;i>=0;i--)
            {
                if(dist[i]>1)
                {
                    memcpy(dist_copy,dist,sizeof(dist));
                    dist_copy[i]--;
                    memcpy(pdf_child[1],tree_serach(encode_id(dist_copy)),sizeof(pdf_child[1]));
                    right_shift(pdf_child[1]);
                    cur_exp=calculate_DTC_exp(pdf_child[1]);
                    if(cur_exp<min_exp)
                    {
                        min_arg=1;
                    }
                    break;
                }
                else if(dist[i]==1)
                {
                    memset(pdf_child[1],0,sizeof(pdf_child[1]));
                    pdf_child[1][0]=0;
                    pdf_child[1][1]=1;
                    min_arg=1;
                    break;
                }
            }
            for(int i=0;i<20;i++)
            {
                pdf_sum[i]+=pdf_child[min_arg][i];
            }
        }
    }
    for(int i=0;i<20;i++)
    {
        DTC_pdf[board_id][i]=pdf_sum[i]/6;
    }
    data_available[board_id]=1;
    return DTC_pdf[board_id];
}

void init()
{
    memset(data_available,0,sizeof(data_available));
    for(int i=0;i<15625;i++)
    {
        tree_serach(i);
    }
    //build cdf after building pdf
    for(int i=0;i<15625;i++)
    {
        double sum=0;
        for(int j=0;j<20;j++)
        {
            sum+=DTC_pdf[i][j];
            DTC_cdf[i][j]=sum;
        }
    }
}

int main()
{
    init();

}