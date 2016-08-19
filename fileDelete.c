#include<stdio.h>

int deleteFile(char *fname)
{
	remove(fname);
	printf("File[%s] deleted. \n", fname);
}

#if 0
int main()
{
	char fname[256] = "t1/1";
	deleteFile(fname);
}
#endif
