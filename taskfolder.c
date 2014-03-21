#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define APP ((char *)"evince")
#define ROOTFOLDER ((char *)"./")
int main()
{
	char *
	DIR *d;
	struct dirent *dir;
	char *ext;
	d = opendir(ROOTFOLDER);
	if(d)
	{
		char *chunk_arr[];
		char *cmd = malloc(1);
		strcat(cmd, APP);
		while((dir = readdir(d)) != NULL)
		{
			ext = strchr(dir->d_name, '.');
			for(int i=0; i < 0; i++)
			{
				if((ext != NULL) && (ext != 0) && (strcmp(ext, ".pdf") == 0))
				{
					cmd = realloc(cmd, strlen(cmd)+strlen(ROOTFOLDER)+strlen(dir->d_name)+1);
					strcat(cmd, " ");
					strcat(cmd, ROOTFOLDER);
				  	strcat(cmd, dir->d_name);
				}
			}
		}
		closedir(d);
		printf("\nrun:\n%s\n", cmd);
		system(cmd);
		free(cmd);
	}
	return 0;
}
