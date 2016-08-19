#include <stdio.h>

int updateSequenceNumber(char *foldername)
{
	FILE *fp1, *fp2;
	char fileRead[56] = {0}, fileWrite[56] = {0};
	char string[1024] = {0};
	char sequenceString[1024] = {0};
	int cntr = 0;

	sprintf(fileRead, "%s/live.m3u8", foldername);
	sprintf(fileWrite, "%s/live.m3u8.bckup", foldername);

	fp1 = fopen(fileRead,"r");
	fp2 = fopen(fileWrite,"w+");

	while(fgets(string, 1024, fp1)) {
		printf("%s", string);
		cntr++;
		if(cntr == 3) {
			sprintf(sequenceString, "#EXT-X-MEDIA-SEQUENCE:%d\n", cntr);
			fputs(sequenceString, fp2);
		} else {
			fputs(string, fp2);
		}
	}
	fclose(fp1);
	fclose(fp2);
	rename(fileWrite, fileRead);


}
/*
int main(void)
{
	updateSequenceNumber();
	return 0;
}*/
