/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:01:47 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/19 18:05:01 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <string.h>
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <sys/types.h>
# include <grp.h>
# include <unistd.h>
// # include "./libft/libft.h"
# include <stdlib.h>
# include <sys/ioctl.h>

# define OPTIONS "lRart"

typedef struct s_long
{
	char			permissions[11];
	char			date[13];
	int				year;
	int				links;
	int				size;
	char			*sym_link;
	char			*owner;
	char			*group;
}					t_long;

typedef struct s_node
{
	struct s_node	*next;
	int				type;
	long			sec;
	long			n_sec;
	char			*path;
	char			*name;
	struct s_long	*l_opt;
}					t_node;

typedef struct s_info
{
	int			ret_nr;
	uint16_t	options;
	int			args;
	long		total;
}				t_info;

typedef enum e_options
{
	LONG = 1 << 0,
	RECURSIVE = 1 << 1,
	HIDDEN = 1 << 2,
	REVERSE = 1 << 3,
	SORT_TIME = 1 << 4,
	DIR_NAME = 1 << 5,
	SYM_LINK = 1 << 6,
	ERROR_FILE = 1 << 7,
	FIRST_LINE = 1 << 8
}				t_options;


// errors.c
void	error_notfound(char *filename);
void	exit_illegal(void);
void	exit_malloc_error(char *str);
void	exit_dup_error(char *str);
void	error_dir(char *str);

// free.c
void	free_node(t_node *node, int options);
void	free_file_nodes(t_node **head, int options);
void	free_non_dir_nodes(t_node **head, int options);
void	free_list(t_node **head, int options);

// list.c
void	list_sort_add(t_node **head, t_node *node, int options);
int		check_link_validity(t_node *node, int opts);
int		node_filetype(struct stat filestat, t_node *node, int opts);
char	*get_full_path(char *name, char *path);
void	create_node(t_node **head, char *name, t_info *info, char *path);

// print.c
void	print_long_list(t_node *head);
void	print_list_all(t_node *head, t_info *info);
void	print_list(t_node **head, t_info *info);
void	print_dir(t_node *head, t_info *info);
void	print_path(char *str, int opts);

// print2.c
void	print_list_errors(t_node *head, t_info *info);
void	print_long_list_node(t_node *node);
void	print_list_files(t_node **head, t_info *info);
void	print_free_list(t_node **head, t_info *info)

// utilities.c
int		option_validity(char *str);
void	print_current_dir(t_node **head, t_info *info);
void	read_arguments(t_node **head, int argc, char **argv, t_info *info);
void	read_options(int argc, char **argv, t_info *info);
void	shift_options(char *argv, t_info *info);

// recursion.c
void	print_dir_recursive(t_node **head, t_info *info);
void	check_null_head(t_node **head, t_info *info);

// list_sort.c
void	update_list_time(t_node **prev, t_node *node, t_node **head, int *sort);
void	list_sort_time_reverse(t_node **head);
void	list_sort_time(t_node **head);
void	list_find_spot(t_node **head, t_node *prev, t_node *node, t_node *tmp);
void	list_find_spot_r(t_node **head, t_node *pre, t_node *node, t_node *tmp);

// list_long.c
void	list_add_long_filetype(t_node *node, struct stat filestat, int a);
void	exit_readlink_error(char *str);
void	print_sym_link(t_node *node, int opts);
void	add_symbolic_link(t_node *node);
void	list_add_long(t_node *node, struct stat filestat, t_info *info);

// ft_ls.c
char	*ft_strdup_exit(char *src);
void	reset_info(t_info *info, t_node **head);
void	list_add_directory(t_node **head, char *path, t_info *info, char *name);
void	ft_ls(t_node **head, t_info *info);
// int	main

// libft
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	ft_memdel(void **ap);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char const *s, int fd);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
size_t	ft_strlen(const char *s);

// void	print_list_node(t_node *node, int opts);
// void	list_sort_time_dispatch(t_node **head, int opts);
// int		find_multiple_dirs(t_node *head);
// void 	print_test(t_node *head);
// void	print_test2(t_node *head);
// void	exit_usage(void);
// t_node	*print_list_find_dir(t_node *head, int opts);	//?

#endif
