// myls.c ... my very own "ls" implementation

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

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
	// string buffers for various names
	char dirname[MAXDIRNAME];
	char uname[MAXNAME+1]; // UNCOMMENT this line
	char gname[MAXNAME+1]; // UNCOMMENT this line
	char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
   // DIR *df; // UNCOMMENT this line
    DIR *fp = opendir(dirname);
    if(fp == NULL){
   		{fprintf(stderr,"%s :No such a directory\n",argv[1]);exit(EXIT_FAILURE);}
    }
    
   char dirname1[MAXDIRNAME];
   strlcpy(dirname1,dirname,sizeof(dirname));

   // read directory entries
   // struct dirent *entry; // UNCOMMENT this line
	struct dirent *entry;
	while((entry = readdir(fp)) != NULL){
		if(entry->d_name[0] != '.'){
			//get path
			strlcat(dirname,"/",sizeof(dirname)+1);
			strlcat(dirname,entry->d_name,sizeof(dirname)+sizeof(entry->d_name));
		
			struct stat info1;
			if(lstat(dirname,&info1) < 0)
				{ perror(entry->d_name); exit(EXIT_FAILURE); }
		
			printf("%s  %-8.8s %-8.8s %8lld  %s\n",
			rwxmode(info1.st_mode, mode),
			username(info1.st_uid, uname),
			groupname(info1.st_gid, gname),
			(long long)info1.st_size,
			entry->d_name);
		}
		strlcpy(dirname,dirname1,sizeof(dirname1));
	}
	
	closedir(fp);
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
	//file type
	switch (mode & S_IFMT) {
		case S_IFLNK:	str[0] = 'l';				break;
		case S_IFREG:	str[0] = '-';				break;
		case S_IFDIR:	str[0] = 'd';				break;
		default:		str[0] = '?';				break;
	}
	//owner permission
	if((mode & S_IRUSR) == S_IRUSR)
		str[1] = 'r';
	else
		str[1] = '-';

	if((mode & S_IWUSR) == S_IWUSR)
		str[2] = 'w';
	else
		str[2] = '-';

	if((mode & S_IXUSR) == S_IXUSR)
		str[3] = 'x';
	else
		str[3] = '-';
	
	//group permission	
	if((mode & S_IRGRP) == S_IRGRP)
		str[4] = 'r';
	else
		str[4] = '-';

	if((mode & S_IWGRP) == S_IWGRP)
		str[5] = 'w';
	else
		str[5] = '-';

	if((mode & S_IXGRP) == S_IXGRP)
		str[6] = 'x';
	else
		str[6] = '-';
	
	//public permission
	if((mode & S_IROTH) == S_IROTH)
		str[7] = 'r';
	else
		str[7] = '-';

	if((mode & S_IWOTH) == S_IWOTH)
		str[8] = 'w';
	else
		str[8] = '-';

	if((mode & S_IXOTH) == S_IXOTH)
		str[9] = 'x';
	else
		str[9] = '-';
	
	
	//end of line
	str[10] = '\0';
	
	
	
	return str;

}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
