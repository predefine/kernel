#include <fs.h>
#include <tar.h>

static file file_fd[FD_MAX];

void fs_nameptr_to_array(char* name, char name2[FILENAME_MAX]){
    uint32_t pos = 0;
    while(*name != 0  && pos < FILENAME_MAX){
        name2[pos++] = *name++;
    }
    name2[pos++] = 0;
}

uint32_t fs_open(char* name, filesystem_info* filesystem){
    file _file = {};
    fs_nameptr_to_array(name, (char*)&_file.filename);
    tar_open(&_file, filesystem);
    if(_file.type == FILETYPE_NONE)
        return -1;
    int fd;
    for(fd = 0; fd < FD_MAX && file_fd[fd].type != FILETYPE_NONE; fd++);
    file_fd[fd] = _file;
    return fd;
}
