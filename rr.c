#include<stdio.h>

const int max = 10;

void main(){
    int id[max],bt[max],temp_bt[max],wt[max],tat[max],n,i;
    int tq=2;
    int x=0;//present time
    int completed=0;
    int currp=0;

    float awt= 0.0,atat=0.0;
    printf("Enter no of process");
    scanf("%d",&n);
 	for (i=0;i<n;i++){
 		printf("Enter id of process %d :\n",(i+1));
 		id[i] = i+1;
        printf("Enter bt of process %d :",(i+1));
 		scanf("%d",&bt[i]);
        temp_bt[i]=bt[i];
 	}
	i=0;
    while(1){
        while(bt[i]!=0){
            //bt>tq
            if(bt[i]>tq){
                bt[i]-=tq;
                x+=tq;
            }else{
                //bt<=tq
                x+=bt[i];
                bt[i]=0;
                tat[i]=x;
                wt[i]= tat[i]-temp_bt[i];
                completed++;
                while(completed==n){
                    break;
                }
            }

        }
        if(i==n-1){
            i=0;
        }
        else{
            i++;
        }
    }
    // Print the results
	    printf("Process\t Burst\t Arrival\t Waiting\t TAT\t CT\n");
	    for (i = 0; i < n; i++) {
		printf("%d\t \t%d\t\t%d\t\t%d\n", id[i], bt[i], wt[i], tat[i]);
	    }

}
