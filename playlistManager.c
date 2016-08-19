/*This is the sample program to notify us for the file creation and file deletion takes place in “/tmp” directory*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include<pthread.h>
#include<stdlib.h>
#include <linux/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define CHANNEL		5
#define BUFSIZE	1024
//#define C

pthread_t tid[CHANNEL];

char channels[CHANNEL][256] = {
"CNWK",
"Cricket",
"darkKnight",
"despicableme",
"RusselPeter",
};

int getDuration(char *foldername, char *duration)
{
        FILE *fp1;
        char fileRead[56] = {0};
        char sequenceString[1024] = {0};
	int size = 0;
	int len =0;

        sprintf(fileRead, "%s/config/Duration", foldername);
	fp1 = fopen(fileRead,"r");
	size = fread(sequenceString, 1, BUFSIZE, fp1);
	strcpy(duration, sequenceString);
	len = strlen(duration);
	if (duration[len-1] == '\n')
		duration[len-1] = '\0';	
//	*duration = atof(sequenceString);
	printf("[%s] %s float: %s\n", __func__, sequenceString, duration);
	fclose(fp1);
	return 1;
}

int playlistManager(char *foldername)
{

	int length, i = 0;
	int fd;
	int wd;
	char buffer[EVENT_BUF_LEN];
	char duration[64] = {0};
	int counter = 0;
/*creating the INOTIFY instance*/
	fd = inotify_init();

/*checking for error*/
	if ( fd < 0 ) {
		perror( "inotify_init" );
	}
/*Here, the suggestion is to validate the existence of the directory before adding into monitoring list.*/
	printf("      [%s] Thread invoked for %s\n", __func__, foldername);
	wd = inotify_add_watch( fd, foldername , IN_CLOSE_WRITE | IN_CREATE | IN_DELETE | IN_ALL_EVENTS | IN_OPEN);
/*read to determine the event change happens on “/tmp” directory. Actually this read blocks until the change event occurs*/
	while(1)
	{
		length = read( fd, buffer, EVENT_BUF_LEN );
//		printf("hello bhiyo, %s!!\n", foldername);
		if ( length < 0 ) {
			perror( "read" );
		}
		while ( i < length ) {
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			if ( event->len ) {
				if ( event->mask & IN_CREATE ) {
					if ( event->mask & IN_ISDIR ) {
					//	printf( "New directory %s created.\n", event->name );
					}
					else {
						/*if ( (strcmp(event->name,"live.m3u8") == 0) || (strcmp(event->name,"live.m3u8.bckup") == 0) || (strncmp(event->name,".live.m3u8", 10) == 0)) {
						  printf("      [%s] Skipping %s\n", __func__, event->name );
						  }*/
						if(strncmp(event->name,"video", 5) == 0) {
							counter++;
							printf("      [%s] New file %s created.\n", __func__, event->name );
							getDuration(foldername, duration);
							printf("      [%s] duration %s\n", __func__, duration);	
							updatePlaylist(foldername, event->name, duration, counter);
						}
					}
				}
			}
			i += EVENT_SIZE + event->len;
		}
		i = 0;
		length = 0;
		memset(buffer, 0, EVENT_BUF_LEN);
	}
	inotify_rm_watch( fd, wd );
	close( fd );
}

void* letTheStreamBegin(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("   [%s] Thread processing for %s\n", __func__, channels[0]);
	playlistManager(channels[0]);
    }
    else if(pthread_equal(id,tid[1]))
    {
        printf("   [%s] Thread processing for %s\n", __func__, channels[1]);
	playlistManager(channels[1]);
    }
    else if(pthread_equal(id,tid[2]))
    {
        printf("   [%s] Thread processing for %s\n", __func__, channels[2]);
	playlistManager(channels[2]);
    }
    else if(pthread_equal(id,tid[3]))
    {
        printf("   [%s] Thread processing for %s\n", __func__, channels[3]);
	playlistManager(channels[3]);
    }
    else if(pthread_equal(id,tid[4]))
    {
        printf("   [%s] Thread processing for %s\n", __func__, channels[4]);
	playlistManager(channels[4]);
    }

    return NULL;
}


int main( )
{
    int i = 0;
    int err;

    while(i < 5)
    {
        err = pthread_create(&(tid[i]), NULL, &letTheStreamBegin, NULL);
        if (err != 0)
            printf("can't create thread :[%s]", strerror(err));
        else
            printf("[%s] Thread [%d] created successfully.\n", __func__, i);

        i++;
    }
	while(1){}

    return 0;
}
