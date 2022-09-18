/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:01:47 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 13:54:47 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h> // perror
# include <string.h> // strerror
# include <time.h> // ctime time
# include <dirent.h> // open- read- closedir, works with sys/types?
# include <sys/stat.h> // lstat
# include <pwd.h> // getpwuid
# include <sys/types.h> //getgrgid getpwuid
# include <grp.h> // getgrgid
# include <unistd.h> // readlink
// # include "./libft/libft.h"
# include <stdlib.h>		// --------------------	 DELETE ??	----------------
# include <sys/ioctl.h> // formatting

# define OPTIONS "lRart" //ufgdG, bonus P

typedef struct		s_long
{
	char			permissions[11];
	char			date[13];	// parse from mod_time
	int				year;	// needed ? if mod_time > 6 months
	int				links;
	int				size;
	// char			size_c[2];	//	BONUS
	// MALLOC
	char			*sym_link;
	char			*owner;
	char			*group;
}					t_long;

typedef	struct		s_node
{
	// struct s_node	*prev;
	struct s_node	*next;
	int				type;	//	4 dir, 8 file, 10 link, 0 error, 1 perm
								//  add S,s,t,b,p....?
	long			sec;		//	in seconds
	long			n_sec;		//	in nanosecs
	// malloc
	char			*path;	//	path to the file
	char			*name;	//	name of file, if no path
	struct s_long	*l_opt;	//	if -l, malloc and assign struct
}					t_node;

typedef	struct	s_info
{
	// char		*path;		// 	???
	int			ret_nr;
	uint16_t	options;	// 	options stored as a int (check enum)
	int			args;		// 	# of files/dirs to ls: ls author file1 file2 = 3
	long		total;		//  total

}				t_info;

typedef	enum e_options
{
	LONG = 1 << 0,
	RECURSIVE = 1 << 1,
	HIDDEN = 1 << 2,
	REVERSE = 1 << 3,
	SORT_TIME = 1 << 4,
	DIR_NAME = 1 << 5,
	SYM_LINK = 1 << 6
	// ADD_SLASH = 1 << 6

	// LONG = 1,
	// RECURSIVE = 2,
	// HIDDEN = 4,
	// REVERSE = 8,
	// SORT_TIME = 16
	// DIR_NAME = 32

	/*
	BONUS OPTIONS
	HUMAN_READ = 32
	*/
}			t_options;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	ft_memdel(void **ap);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char const *s, int fd);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_strcat(char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strncpy(char *dst, const char *src, size_t len);

char	*ft_strdup_exit(char *src);
// void	create_node_fullpath(t_node **head, char *name, int opts, char *full);
	// not needed if create_node saves the path always
void	add_symbolic_link(t_node *node);
int		check_link_validity(t_node *node, int opts);
void	create_node(t_node **head, char *name, t_info *info, char *path);
void	error_dir(char *str);
void	error_notfound(char *filename);
void	exit_dup_error(char *str);
void	exit_illegal(void);
void	exit_malloc_error(char *str);
void	exit_readlink_error(char *str);
void	exit_usage(void);
int		find_multiple_dirs(t_node *head);
void	free_file_nodes(t_node **head, int options);
void	free_list(t_node **head, int options);
void	free_node(t_node *node, int options);
void	free_non_dir_nodes(t_node **head, int options);
void	ft_ls(t_node **head, t_info *info);
char	*get_full_path(char *name, char *path);
// char	*get_full_path(char *name, char *path, t_node *node);
void	list_add_directory(t_node **head, char *path, t_info *info, char *name);
void	list_add_long_filetype(t_node *node, struct stat filestat, int a);
void	list_add_long(t_node *node, struct stat filestat, t_info *info);
void	list_find_spot(t_node **head, t_node *prev, t_node *node, t_node *tmp);
void	list_find_spot_r(t_node **head, t_node *prev, t_node *node, t_node *tmp);
void	list_sort_add(t_node **head, t_node *node, int options);
void	list_sort_time_dispatch(t_node **head, int opts);
void	list_sort_time_reverse(t_node **head);
void	list_sort_time(t_node **head);
// int	node_filetype(struct stat filestat);
int		node_filetype(struct stat filestat, t_node *node, int opts);
int		option_validity(char *str);
void	print_dir_recursive(t_node **head, t_info *info);
void	print_dir(t_node *head, t_info *info);
void	print_list_all(t_node *head, t_info *info);
void	print_list_errors(t_node *head, t_info *info);
void	print_list_files(t_node **head, t_info *info);
void	print_list(t_node **head, t_info *info);
t_node	*print_list_find_dir(t_node *head, int opts);
void	print_list_node(t_node *node, int opts);
void	print_long_list_node(t_node *node);
void	print_long_list(t_node *head);
void	print_path(char *str, int opts);
void	print_sym_link(t_node *node, int opts);
void 	print_test(t_node *head);
void	print_test2(t_node *head);
void	read_arguments(t_node **head, int argc, char **argv, t_info *info);
void	read_options(int argc, char **argv, t_info *info);
void	reset_info(t_info *info, t_node **head);
void	shift_options(char *argv, t_info *info);
void	update_list_time(t_node **prev, t_node *node, t_node **head, int *sort);

#endif

/*	exit codes

1	exit_usage
1	exit_illegal		//usage needed??
2	exit_malloc_error
3	exit_dup_error		// UNFINISHED
4	error_dir
5	exit_readlink_error

*/

/*	bitwise operators

& (AND)	takes two numbers, is 1 if both are 1
	1100
&	0101
=	0100

	101010101
&	000010000
		10000 > 0 = 0 int 24

| (OR) takes two numbers, is 1 if any is 1
	1100
|	0101
=	1101

^ (XOR) takes two numbers, XOR, 1 if two bits are different
	1100
^	0101
=	1001

<< (left shift) takes two numbers, 1st to shift, 2nd how much
	0011
<< 2
=	1100

>> (right shift) takes two numbers, 1st to shift, 2nd how much
	1100
>> 2
=	0011

~ (NOT) takes one number and inverts
~	1101
= 	0010

a = 	00000101
b = 	00001001
~a = 	11111010

b<<1 =	00010010
b>>1 = 	00000100
a ^ b = 00001100
a & b = 00000001
a | b =	00001101

shift
63	0000 0000 0000 0000 48
47	0000 0000 0000 0000 32
31	0000 0000 0000 0000 16
15	0000 0000 0000 0000 0

*/
