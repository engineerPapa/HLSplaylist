CC=gcc
playlistManager: playlistManager.o getDurationFile.o updatePlaylist.o fileDelete.o
	$(CC) -o playlistManager playlistManager.o getDurationFile.o updatePlaylist.o fileDelete.o -lpthread 

