#include <fs.h>

void fs_nameptr_to_array(char* name, char name2[FILENAME_MAX]){
    uint32_t pos = 0;
    while(*name != 0  && pos < FILENAME_MAX){
        name2[pos++] = *name++;
    }
    name2[pos++] = 0;
}

uint32_t fs_open(char* name, filesystem_info* filesystem, const filesystem_ops* ops){
    file _file;
    fs_nameptr_to_array(name, (char*)&_file.filename);
    ops->open(&_file, filesystem);
    if(_file.type == FILETYPE_NONE)
        return -1;
    int fd;
    for(fd = 0; fd < FD_MAX && filesystem->files_fd[fd].type != FILETYPE_NONE; fd++);
    filesystem->files_fd[fd] = _file;
    return fd;
}

uint32_t fs_getsize(uint32_t fd, filesystem_info* filesystem, const filesystem_ops* ops){
    file _file = filesystem->files_fd[fd];
    if(_file.type != FILETYPE_FILE) return 0;
    uint32_t size = ops->get_size(&_file, filesystem);
    filesystem->files_fd[fd] = _file;
    return size;
}

void fs_close(uint32_t fd, filesystem_info* filesystem, const filesystem_ops* ops){
    file _file = filesystem->files_fd[fd];
    if(_file.type == FILETYPE_NONE) return;
    ops->close(&_file, filesystem);
    _file.type = FILETYPE_NONE;
    filesystem->files_fd[fd] = _file;
}

uint32_t fs_read(uint32_t fd, char* buffer, uint32_t count, filesystem_info* filesystem, const filesystem_ops* ops){
    file _file = filesystem->files_fd[fd];
    if(_file.type != FILETYPE_FILE) return -1;
    uint32_t readed = ops->read(&_file, buffer, count, filesystem);
    filesystem->files_fd[fd] = _file;
    return readed;
}
