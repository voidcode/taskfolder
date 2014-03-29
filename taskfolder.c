/*
* GCC 2014 Project
* This c program open all .pdf file in it root folder an luncher them with evince.
* based on code by voidcode copyright (C) 2014
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
* Github: https://github.com/voidcode/taskfolder
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define APP ((char *)"evince")
int detect_spaceing(char s[])
{
	int i;
	for(i=0; i < sizeof(s); i++)
		if(s[i] == ' ')
			 return 1;
	return 0;
}
int main(int argc, char *argv[])
{
	char *ROOTFOLDER;
	int ARGUMENTS_IS_ADDED=0;
	if(argv[1] != NULL)
	{
		ROOTFOLDER = malloc(strlen(argv[1]));
		strcat(ROOTFOLDER, argv[1]);
		printf("\nROOTFOLDER==%s\n", ROOTFOLDER);
		ARGUMENTS_IS_ADDED =1;
	}
	else /* if argument 1 is not set then, open any pdf in 'taskfolder' current root  */
	{
		ROOTFOLDER = malloc(strlen("./"));
		strcat(ROOTFOLDER, "./");
	}
	DIR *d;
	struct dirent *dir;
	char *ext;
	d = opendir(ROOTFOLDER);
	if(d)
	{
		char *cmd = malloc(1);
		strcat(cmd, APP);
		while((dir = readdir(d)) != NULL)
		{			
			if(detect_spaceing(dir->d_name) == 0)
			{
				ext = strchr(dir->d_name, '.');
				if((ext != NULL) && (ext != 0) && (strcmp(ext, ".pdf") == 0))
				{
					cmd = realloc(cmd, strlen(cmd)+strlen(ROOTFOLDER)+strlen(dir->d_name)+2);
					strcat(cmd, " ");
					strcat(cmd, ROOTFOLDER);
					if(ARGUMENTS_IS_ADDED == 1)
						strcat(cmd, "/");
					strcat(cmd, dir->d_name);
				}
			}
		}
		closedir(d);
		printf("\nrun:\n%s\n", cmd);
		system(cmd);
		free(cmd);
		free(ROOTFOLDER);
	}
	return 0;
}
