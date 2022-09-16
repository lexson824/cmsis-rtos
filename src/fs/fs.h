#ifndef __FS_H
#define __FS_H

#include <stdint.h>
#include <list.h>

#define PATH_MAX 32

#define DENTRY_TYPE_DIR 0
#define DENTRY_TYPE_FILE 1

#define INODE_TYPE_TMP 0
#define INODE_TYPE_DIR 1
#define INODE_TYPE_FILE 2
#define INODE_TYPE_CHAR 3
#define INODE_TYPE_BLOCK 4

struct file;
struct dentry;
struct inode;

struct file_operations {
    int (*open)(struct file *file);
    int (*close)(struct file *file);
    int (*ioctl)(struct file *file, unsigned int cmd, unsigned long arg);
    int (*write)(struct file *file, const void *buf, uint32_t len);
    int (*read)(struct file *file, void *buf, uint32_t len);
};

struct file {
    int fd;
    struct dentry *dentry;
    struct file_operations f_ops;
    struct list_head node;
    void *private_data;
};

struct dentry_operations {
    int (*create)(struct dentry *dentry);
    int (*unlink)(struct dentry *dentry);
};

struct dentry {
    char name[PATH_MAX];
    int type;
    struct inode *inode;
    struct dentry_operations d_ops;
    struct dentry *parent;
    struct list_head childs;
    struct list_head child_node;
};

struct inode {
    int type;
    struct file_operations f_ops;
    struct list_head node;
};

struct dentry *dentry_walk(const char *path);
int dentry_add(const char *path, struct dentry *child);
int dentry_del(const char *path);

struct dentry *fs_get_root(void);
void fs_init(void);
void fs_sys_init(void);

#endif
