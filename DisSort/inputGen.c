#include <stdio.h>
#include <stdlib.h>
#define NUM_INPUTS 100
#define MAX_RANGE_NUMBER 1000

int main(int argc, char *argv[])
{
	FILE *fp=fopen("input.txt","w");
	int t=NUM_INPUTS;
	while (t--) {
		fprintf (fp, "%d ", rand() % MAX_RANGE_NUMBER);
	}
	return 0;
}