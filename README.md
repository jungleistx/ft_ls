# ft_ls

## About
Ft_ls is the first project of the Unix-branch in Hive Helsinki. <br>

This is my implementation of the unix command 'ls'. 

## Allowed functions
* write
* opendir
* readdir
* closedir
* stat
* lstat
* getpwuid
* getgrgid
* listxattr
* getxattr
* time
* ctime
* readlink
* malloc
* free
* perror
* strerror
* exit

## Usage

1. make
2. ./ft_ls [options] [filename(s)]

## Options
* -l  show additional long output of files
* -a  show hidden files / folders
* -R  show output recursively
* -r  output is reversed, default is order by ASCII
* -t  output is sorted by modification-time

## Example usage

``` 
./ft_ls -l ft_ls.h author
-rw-r--r--  1 owner  group     9 28 Sep 12:30 author
-rw-r--r--  1 owner  group  4468 28 Sep 12:30 ft_ls.h
```

## Known issues
Tested and created with intel-mac, but with M1-processor the program segfaults with option '-l'. Currently debugging the reason.
