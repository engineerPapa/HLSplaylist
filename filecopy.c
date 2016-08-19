#if 0
int filecopy()
{
	int in_fd, out_fd;
	char buf[8192] = {0};
	in_fd = open("source", O_RDONLY);
	if (in_fd) {} 
	out_fd = open("dest", O_WRONLY);
	while (1) {
		ssize_t result = read(in_fd, &buf[0], sizeof(buf));
		if (!result) break;
		assert(result > 0);
		write(out_fd, &buf[0], result);
	}
}
#endif


int copyFiles(char *source, char *destination)
{
	int in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];
	/* open files */
	if( (in_fd=open(source, O_RDONLY)) == -1 ) {
		oops("Cannot open ", source);
	}
	if( (out_fd=creat(destination, COPYMORE)) == -1 ) {
		oops("Cannot creat ", destination);
	}

	/* copy files */
	while( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0 ) {
		if( write(out_fd, buf, n_chars) != n_chars ) {
			oops("Write error to ", destination);
		}
		if( n_chars == -1 ) {
			oops("Read error from ", source);
		}
	}
	/* close files */
	if( close(in_fd) == -1 || close(out_fd) == -1 )	{
		oops("Error closing files", "");
	}
	return 1;
}


void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);
}


int main()
{
//	filecopy();
	copyFiles();
}
