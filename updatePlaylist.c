#include <stdio.h>
#include<string.h>

#define BUFSIZE	1024
int updatePlaylist(char *foldername, char *fname, char* duration, int counter)
{
	FILE *fp1, *fp2;
	char fileRead[56] = {0}, fileWrite[56] = {0};
	char string[BUFSIZE] = {0};
	char sequenceString[BUFSIZE] = {0};
	char delFile[256] = {0};
	int cntr = 0;

	sprintf(fileRead, "%s/live.m3u8", foldername);
	sprintf(fileWrite, "%s/live.m3u8.bckup", foldername);

	fp1 = fopen(fileRead,"r");
	fp2 = fopen(fileWrite,"w+");

	while(fgets(string, BUFSIZE, fp1)) {
//		printf("%s", string);
		cntr++;
		if(cntr == 3) {
			sprintf(sequenceString, "#EXT-X-MEDIA-SEQUENCE:%d\n", counter);
			fputs(sequenceString, fp2);
		} else if ((counter != 1 ) && ((cntr == 6) || (cntr == 7))) {
			continue;
		}
		else {
			fputs(string, fp2);
		}
		memset(string, 0, BUFSIZE);
	}
	printf("[%s] Duration %s\n", __func__, duration);
	memset(sequenceString, 0, BUFSIZE);
	sprintf(sequenceString,	"#EXTINF:%s,\n", duration);
	fputs(sequenceString, fp2);
	memset(sequenceString, 0, BUFSIZE);
	sprintf(sequenceString,"%s\n", fname);
	fputs(sequenceString, fp2);
	counter = counter - 10;
	if ( (counter >= 0) && (counter < 10) ) {
		sprintf(delFile, "%s/video-00%d.ts",foldername, counter);
		printf("delfile %s\n", delFile);
	} else if ( (counter > 9) && (counter < 100) ) {
		sprintf(delFile, "%s/video-0%d.ts", foldername, counter);
		printf("delfile %s\n", delFile);
	} else if ( (counter > 99) && (counter < 10000) ) {
		sprintf(delFile, "%s/video-%d.ts", foldername, counter);
		printf("delfile %s\n", delFile);
	}

	printf("[%s] File to delete %s\n", __func__, delFile);
	remove(delFile);
	fclose(fp1);
	fclose(fp2);
	rename(fileWrite, fileRead);
}
#if 0
int main()
{
	char fname[256] = {0};
	char folder[256] = {0};
	float duration = 9.769;
	sprintf(fname, "test-anshul.ts");
	sprintf(folder, "t1");
	updatePlaylist(folder, fname, duration);
}
#endif
