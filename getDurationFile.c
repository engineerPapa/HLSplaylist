#include<stdio.h>
#include<stdlib.h>

#if 0
#define BUFSIZE	1024
float getDuration(char *foldername)
{
        FILE *fp1;
        char fileRead[56] = {0};
        char sequenceString[1024] = {0};
	int size = 0;
	float duration;

        sprintf(fileRead, "%s/config/Duration", foldername);
	fp1 = fopen(fileRead,"r");
	size = fread(sequenceString, 1, BUFSIZE, fp1);
	duration = atof(sequenceString);
	printf("[%s] %s float: %f\n", __func__, sequenceString, duration);
	fclose(fp1);
	return duration;
}
#endif
#if 0
int main()
{
	float duration = 0;
	char fname[256] = {0};
	sprintf(fname, "t1");
	duration = getDuration(fname);
	printf("duration : %f\n", duration);
}
#endif
