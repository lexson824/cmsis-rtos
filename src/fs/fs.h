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
#define INODE_TYPE_SOCKET 5

struct file;
struct inode;
struct dentry;

struct file_operations {
    int (*open)(struct file *filp);
    int (*close)(struct file *filp);
    int (*ioctl)(struct file *filp, unsigned int cmd, unsigned long arg);
    int (*read)(struct file *filp, void *buf, uint32_t len);
    int (*write)(struct file *filp, const void *buf, uint32_t len);
};

struct file {
    int fd;
    struct dentry *dentry;
    struct inode *inode;
    const struct file_operations *f_ops;
    void *private_data;
};

struct inode_operations {
    int (*link)(struct inode *inode);
    int (*unlink)(struct inode *inode);
};

struct inode {
    int type;
    const struct file_operations *f_ops;
    //const struct inode_operations *i_ops;
};

struct dentry_operations {
    int (*create)(struct dentry *);
    void (*release)(struct dentry *);
};

struct dentry {
    char name[PATH_MAX];
    int type;
    struct inode *inode;
    //const struct dentry_operations *d_ops;
    struct dentry *parent;
    struct list_head childs;
    struct list_head child_node;
};

struct dentry *dentry_walk(const char *path);
int dentry_add(const char *path, struct dentry *child);
int dentry_del(const char *path);

struct file *alloc_file(int fd, struct dentry *dentry, struct inode *inode);
struct inode *alloc_inode(int type, const struct file_operations *f_ops);
struct dentry *alloc_dentry(const char *name, int type, struct inode *inode);

struct dentry *fs_get_root(void);
void fs_init(void);
void fs_sys_init(void);

#endif
