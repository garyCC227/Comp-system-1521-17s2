#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

int main(int argc, char *argv[])
{
	// string buffers for various names
	char dirname[MAXDIRNAME];

	if (argc != 3){
		fprintf(stderr,"wrong command input\n");
		return EXIT_FAILURE;
	}else if (strcmp(argv[2],"ls") != 0){
		fprintf(stderr,"did u type 'ls' ?\n");
		return EXIT_FAILURE;
	}else
		strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }


    DIR *fp = opendir(dirname);
    if(fp == NULL){
   		{fprintf(stderr,"%s :No such a directory\n",argv[1]);exit(EXIT_FAILURE);}
    }
	strlcat(dirname,"/",sizeof(dirname)+1);

	struct dirent *entry;
	while((entry = readdir(fp)) != NULL){
		if(entry->d_name[0] != '.'){
			struct stat info1;
			if(lstat(dirname,&info1) < 0)
				{ perror(entry->d_name); exit(EXIT_FAILURE); }
			
			if((info1.st_mode & S_IFMT) == S_IFLNK){
				printf("%s is symlink ",entry->d_name);
			}else{
				printf("%s ",entry->d_name);
			}
		}	
	}
	printf("\n");
	closedir(fp);
   return EXIT_SUCCESS;
}

