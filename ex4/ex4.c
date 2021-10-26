#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
typedef struct {
 	ino_t iNode;
 	char name[128];
 	nlink_t nLinks;
} FileInfo;

FileInfo newFile(ino_t iNode, char *name) {
 	FileInfo file;
 	file.iNode = iNode;
 	strcpy(file.name, name);
 	file.nLinks = 1;

 	return file;
}
 
int main() {
 	DIR *tmpDir = opendir("tmp");
 	if (!tmpDir) {
	 	perror("Failed to open directory.\n");
 		return ENOENT;
 	}

 	struct dirent *dir;
 	struct stat fileStat;
 	FileInfo files[100];
 	int fileCount = 0;
 	while ((dir = readdir(tmpDir))) {

 	char fileName[50];
 	strcpy(fileName, "tmp/");
 	strcat(fileName, dir->d_name);

 	if (stat(fileName, &fileStat)) {
	 	return ENOENT;
 	}

 	int found = 0;
 	for (int i = 0; i < fileCount; ++i) {
 		if (files[i].iNode == fileStat.st_ino) {
 			strcat(strcat(files[i].name, ", "), dir->d_name);
 			files[i].nLinks++;
 			found = 1;
 			break;
 		}
 	}
 	if (!found) {
 		if (fileCount >= 100) {
 		return EAGAIN;
 	}
 	files[fileCount] = newFile(fileStat.st_ino, dir->d_name);
 	fileCount++;
 	}
 	}
 	closedir(tmpDir);

 	FILE *outFile = fopen("ex4.txt", "w");
 	for (int j = 0; j < fileCount; ++j) {
 		if (files[j].nLinks > 1) {
 		fprintf(outFile, "I-node %lu ", files[j].iNode);
 		fprintf(outFile, "has %lu links: ", files[j].nLinks);
 		fprintf(outFile, "%s\n", files[j].name);
 	}
 	}
 	fclose(outFile);

 	return 0;
}
