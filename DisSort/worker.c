#include "dependency.h"
#define MAX_CAPACITY 1000

struct addrinfo client_info, *client_pointer;                //STORES CLIENT CONFIGS
int sockfd;                                                  //SOCKET ID OF WORKER
int array[MAX_CAPACITY];
int numElements=0;

void swap(int* a, int* b)
{
    int t=*a;
    *a=*b;
    *b=t;
}

int partition(int arr[], int low, int high)
{
    int pivot=arr[high];    
    int i=low-1;
    int j;  
    for (j=low;j<=high-1;j++)
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

void quickSort(int arr[], int low, int high)
{
    if (low<high) {
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

int main(int argc, char *argv[])
{
	//INITIALIZE WORKER SPECS
	memset(&client_info,0,sizeof(client_info));
	client_info.ai_family=AF_UNSPEC;
	client_info.ai_socktype=SOCK_STREAM;

	//CONNECT CLIENT TO SERVER
	initWorker(&sockfd,argv[2],&client_info,&client_pointer,argv[1]);

	int num;
	while (read(sockfd,&num,sizeof(num)) && num != -1) {
		array[numElements++]=num;
	}

	int i;
	quickSort(array,0,numElements-1);

	for (i=0;i<numElements;i++) {
		write(sockfd,&array[i],sizeof(array[i]));
	}
	num=-1;
	write(sockfd,&num,sizeof(num));
	return 0;
}