#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

int main() {
    std::string pathToCurrentDirectory = "";
    while (true) {
        DIR *dir;
        int parentInode;
        struct dirent *ent;
        if ((dir = opendir(".")) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                std::string dname(ent->d_name);
                if (ent->d_type == DT_DIR && dname == ".") {
                    //std::cout << "Name: " << dname << " and Inode: " << ent->d_ino << "\n";
                    parentInode = ent->d_ino;
                }
            }
            closedir(dir);
        } else {
            /* could not open directory */
            perror("");
            return EXIT_FAILURE;
        }

        chdir("..");

        if ((dir = opendir(".")) != NULL) {

            int pointInode;
            int pointPointInode;

            while ((ent = readdir(dir)) != NULL) {
                std::string dname(ent->d_name);
                if (ent->d_type == DT_DIR && parentInode == ent->d_ino) {
                    //std::cout << "Name: " << dname << " and Inode: " << ent->d_ino << "\n";
                    pathToCurrentDirectory=dname+"/"+pathToCurrentDirectory;
                }
                if (ent->d_type == DT_DIR && dname == ".") {
                    pointInode=ent->d_ino;
                }
                if (ent->d_type == DT_DIR && dname == "..") {
                    pointPointInode=ent->d_ino;
                }

            }
            if(pointInode==pointPointInode){

                std::cout << pathToCurrentDirectory << "\n";
                return 0;
            }
            closedir(dir);
        } else {
            /* could not open directory */
            perror("");
            return EXIT_FAILURE;
        }

    }
}