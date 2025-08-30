#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right) 
{
    int n1 = mid - left + 1;   
    int n2 = right - mid;      
  int i,k,j;
int *l=(int*)malloc(n1*sizeof(int));
int *r=(int*)malloc(n2*sizeof(int));
for (int i = 0; i < n1; i++)
    {
        l[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        r[j] = arr[mid + 1 + j];
    }
  i=0;j=0;k=left;
  while(i<n1&&j<n2)
  {
    if(l[i]<=arr[k])
    {
        arr[k++]=l[i++];
    }
    else
  {
arr[k++]=r[j++];
  }
}
while(i<n1)
{
    arr[k++]=l[i++];
}
while(j<n2)
{
    arr[k++]=r[j++];
}
free(l);
free(r);
}
void mergesort(int arr[], int left, int right) 
{
    if (left < right) 
    {
        int mid= left+(right-left)/2;
        mergesort(arr,left,mid);
        mergesort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}
void generaterandomarray(int arr[],int n)
{
    for(int i=0;i<n;i++)
    arr[i]=rand()%100000;// generate random intgers
}

int main()
{
    int n;
    printf("enter the number of elements");
    scanf("%d",&n);
   
    int *arr=(int*)malloc(n*sizeof(int));
    if(arr==NULL)
    {
        printf("memory allocation failed");
        return 1;
    }
    generaterandomarray(arr,n);
    clock_t start=clock();
     for(int i=0;i<1000;i++)// time can be recorded just to check;3 conditions here to check
     {
        mergesort(arr,0,n-1);
     }
     clock_t end=clock();


// calculate time for one iteration;
double timetaken=((double)(end-start))/CLOCKS_PER_SEC/1000.0;
printf("time taaken%f",timetaken);
free(arr);
return 0;
    }
