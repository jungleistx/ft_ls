/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:01:47 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/23 20:13:48 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>
# include "printf/includes/ft_printf.h"

# define OPTIONS "lRart"

typedef struct s_long
{
	char			permissions[11];
	char			date[13];
	int				year;
	int				links;
	int				size;
	unsigned int	majorminor;
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

typedef struct s_inf
{
	int			ret_nr;
	uint16_t	options;
	int			args;
	long		total;
}				t_inf;

typedef enum e_options
{
	LON = 1 << 0,
	RECURSIVE = 1 << 1,
	HIDDEN = 1 << 2,
	REVERSE = 1 << 3,
	SORT_TIME = 1 << 4,
	DIR_NAME = 1 << 5,
	SYM_LINK = 1 << 6,
	ERROR_FILE = 1 << 7,
	FIRST_LINE = 1 << 8,
	PRINT_PATH = 1 << 9,
	DOT_ARG = 1 << 10
}				t_options;

// utilities2.c
void	free_error_nodes(t_node **head, int options);
void	print_year(t_node *node);
void	get_owner_group(t_node *node, struct stat filestat);
void	print_major_minor(t_node *node);

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
void	create_node(t_node **head, char *name, t_inf *info, char *path);

// print.c
void	print_long_list(t_node *head, t_inf *info);
void	print_list_all(t_node *head, t_inf *info);
void	print_list(t_node **head, t_inf *info);
void	print_dir(t_node *head, t_inf *info);
void	print_path(char *str, t_inf *info);

// print2.c
void	print_list_errors(t_node *head, t_inf *info);
void	print_long_list_node(t_node *node);
void	print_list_files(t_node **head, t_inf *info);
void	print_free_list(t_node **head, t_inf *info);
void	print_current_dir(t_node **head, t_inf *info);

// utilities.c
int		option_validity(char *str);
void	read_arguments(t_node **head, int argc, char **argv, t_inf *info);
void	read_options(int argc, char **argv, t_inf *info);
void	shift_options(char *argv, t_inf *info);
void	create_node_dots(t_node **head, char *name, t_inf *info);

// recursion.c
void	check_null_head(t_node **head, t_inf *info);
int		traverse_hidden_files(char *name);
void	print_dir_recursive(t_node **head, t_inf *info, int dot_dir);

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
void	list_add_long(t_node *node, struct stat filestat, t_inf *info);

// ft_ls.c
char	*ft_strdup_exit(char *src);
void	reset_info_ls(t_inf *info, t_node **head);
void	list_add_directory(t_node **head, char *path, t_inf *info, char *name);
void	ft_ls(t_node **head, t_inf *info);

#endif
