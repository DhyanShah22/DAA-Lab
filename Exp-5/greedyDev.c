#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data
{
    char event[2];
    int start_time;
    int end_time;
};

int compareEvents(const void *a, const void *b) {
    return ((struct data*)a)->end_time - ((struct data*)b)->end_time;
}
void intervalScheduling(struct data d[], int n) {
    qsort(d, n, sizeof(struct data), compareEvents);
    for (int i = 0; i < n; i++)
    {
        printf("%s ",d[i].event);
    }
    printf("\n");
    
    int count = 1;
    int lastEndTime = d[0].end_time;
    int firstEventIndex = 0;
    for (int i = 1; i < n; i++) {
        if (d[i].start_time >= lastEndTime) {
            printf("%s and %s\n", d[firstEventIndex].event, d[i].event);
            count++;
            lastEndTime = d[i].end_time;
        }
        else {
            // firstEventIndex = i; 
            continue;
        }
    }
    printf("Maximum number of events that can be scheduled: %d\n", count);
}


int main(){
    int n;
    char data[2];
    printf("Name: Dev Mehta\n");
    printf("Roll No: 22BCP282\n");
    printf("Enter the number of events:");
    scanf("%d",&n);
    struct data d[n];
    for (int i = 1; i <= n; i++)
    {
        printf("Enter the %d event info:\n",i);
        scanf("%s",data);
        strcpy(d[i-1].event,data);
        scanf("%d",&d[i-1].start_time);
        scanf("%d",&d[i-1].end_time);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("Event:%s ",d[i-1].event);
        printf("start_time:%d ",d[i-1].start_time);
        printf("End_time:%d\n",d[i-1].end_time);

    }
    intervalScheduling(d,n);
    return 0;
}