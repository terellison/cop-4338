#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	int fd = open(argv[1], O_RDWR);
	long file_size = lseek(fd, 0, SEEK_END);//find the file size
	fprintf(stderr, "The file size is %ld bytes!\n", file_size);
	lseek(fd, 0, SEEK_SET);//rewind
    
	for(long i = 0; i < (file_size-1) / 2;i++){
		long loc = (file_size - 1) - i;
		fprintf(stderr, "Swapped chars at index %ld and %ld.\n", i, loc);
		char from, to;
		read(fd, &from,1);
		lseek(fd,loc,SEEK_SET);
		read(fd, &to, 1);
		lseek(fd,loc,SEEK_SET);
		write(fd, &from,1);
		lseek(fd,i,SEEK_SET);
		write(fd, &to,1);
	}
	close(fd);
}