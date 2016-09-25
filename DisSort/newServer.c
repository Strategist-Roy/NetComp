#include "dependency.h"
#define BACKLOG 10
#define NUM_WORKERS 2

struct addrinfo server_info, *server_pointer;              //STORES SERVER CONFIGS
int sockfd;                                           //SOCKET ID ON WHICH SERVER LISTENS
client workers[NUM_WORKERS];                  //STORES CONFIGS OF EACH WORKER
int response[NUM_WORKERS];
FILE *fInput, *fOutput;                           //FILE POINTERS FOR DATA AND OUTPUT

int findMin()
{
	int i, min=INT_MAX, index=-1;
	for (i=0;i<NUM_WORKERS;i++) {
		if (response[i]==-1)
			continue;
		if (min>response[i]) {
			min=response[i];
			index=i;
		}
	}
	if (index != -1)
		fprintf(fOutput,"%d ", min);
	return index;
}

int main(int argc, char *argv[])
{
	//INITIALIZE SERVER SPECS
	memset(&server_info,0,sizeof(server_info));
	server_info.ai_family=AF_UNSPEC;
	server_info.ai_socktype=SOCK_STREAM;

	//SERVER SETUP AND LISTENING
	initServer(&sockfd,argv[1],&server_info,&server_pointer,BACKLOG);

	//CONNECT EACH CLIENT
	int i;
	for (i=0;i<NUM_WORKERS;i++) {
		workers[i].sockfd=accept(sockfd,(struct sockaddr *)&(workers[i].client_info),&(workers[i].client_size));
	}

	fInput=fopen(argv[2],"r");
	fOutput=fopen(argv[3],"w");
	int num;

	while (fscanf(fInput,"%d",&num) != EOF) {
		i=(i+1)%NUM_WORKERS;
		write(workers[i].sockfd,&num,sizeof(num));
	}

	num=-1;
	for (i=0;i<NUM_WORKERS;i++)
		write(workers[i].sockfd,&num,sizeof(num));

	for (i=0;i<NUM_WORKERS;i++) 
		read(workers[i].sockfd,&response[i],sizeof(response[i]));

	int index;
	while ((index=findMin()) != -1) {
		read(workers[index].sockfd,&response[index],sizeof(response[index]));
	}
	
	return 0;
}