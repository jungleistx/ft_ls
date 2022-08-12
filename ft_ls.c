/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:55:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/12 15:59:01 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//	change printf -> ft_printf	!!!!

int	ft_strcmp(const char *s1, const char *s2);
void	error_notfound(char *filename);
void	exit_usage(void);
void	exit_illegal(void);
void	exit_malloc_error(char *str);
void	exit_dup_error(char *str);
void	error_dir(char *str);
void	reset_info(t_info *info, t_node *head);
int	option_validity(char *str);
void	shift_options(char *argv, t_info *info);
void	read_options(int argc, char **argv, t_info *info);
void	print_list_errors(t_node *head);
void	list_sort_add(t_node **head, t_node *node);
void	delete_list(t_node *head);
void	list_create_node(t_node **head, char *filename, int type);
void	dispatch_filetype(t_node **head, struct stat filestat, char *filename);
void	list_add_current(t_node **head);
void	read_arguments(t_node **head, int argc, char **argv, t_info *info);
void	ft_ls(t_node **head, t_info *info);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

//	libft
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
		i++;
	}
	return (0);
}
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = (char *) malloc(sizeof(*s2) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
//	/libft

//	errors.c	---	---	---	---	---	---	---	---	---	---	---	---
void	error_notfound(char *filename)
{
	printf("ft_ls: %s: No such file or directory\n", filename);
}

void	exit_usage(void)		//	NOT NEEDED ?
{
	printf("usage: ft_ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	exit(1);
}

void	exit_illegal(void)
{
	printf("ft_ls: illegal option -- -\n");
	// exit_usage();
	printf("usage: ./ft_ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	exit(1);
}

void	exit_malloc_error(char *str)
{
	printf("ERROR with malloc in %s\n", str);		//	LEGIT ERROR??
	exit(2);
}

void	exit_dup_error(char *str)
{
	printf("ERROR with  dup in %s\n", str);			//	LEGIT ERROR??
	exit(3);
}

void	error_dir(char *str)
{
	perror(str);
	exit(4);
}
//	/errors.c	---	---	---	---	---	---	---	---	---	---	---	---

//	utilities.c	---	---	---	---	---	---	---	---	---	---	---	---
void	reset_info(t_info *info, t_node *head)
{
	info->options = 0;
	info->args = 0;
	info->path = NULL; 		// needed ?
	head = NULL;
}

int	option_validity(char *str)
{
	int	i;
	int	dash;

	dash = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '-')
			dash++;
	}
	if (dash > 1)
		return (0);		//	too many '-', exit_illegal
	return (1);			//	valid option
}

void	shift_options(char *argv, t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (OPTIONS[++j])	//	traverse the valid options
		{
			if (OPTIONS[j] == argv[i])	//	compare with the char in argv
			{
				if (info->options ^ (1 << j))	//	if not on already
					info->options |= (1 << j);	//	turn the correct option on
			}
		}
	}
}

void	read_options(int argc, char **argv, t_info *info)
{
	int	i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
		{
			info->args = argc - i - 1;
			// printf("read a\n");
			return ;
		}
		else if (!(option_validity(argv[i])))
			exit_illegal();
		else
			shift_options(&argv[i][1], info);	//	start from the next to '-'
		i++;
	}
	if (i < argc)
		info->args = argc - i;
	// printf("read b\n");
}
//	/utilities.c	---	---	---	---	---	---	---	---	---	---	---	---

//	prints.c		---	---	---	---	---	---	---	---	---	---	---	---
void	print_list_errors(t_node *head)
{
	t_node			*ptr;

	ptr = head;
	while (ptr)
	{
		if (ptr->type == 0)
			error_notfound(ptr->name);
		ptr = ptr->next;
	}
}

//	/prints.c		---	---	---	---	---	---	---	---	---	---	---	---

//	lists.c		---	---	---	---	---	---	---	---	---	---	---	---
void	list_sort_add(t_node **head, t_node *node)
{
	t_node	*tmp;
	t_node	*prev;

	tmp = *head;
	prev = NULL;
	// printf("in list sort\n");
	if (!tmp)
	{
		*head = node;
	}
	else if (ft_strcmp(node->name, tmp->name) < 0)		//	if new is first node
	{
		*head = node;
		node->next = tmp;
		tmp->prev = node;
	}
	else			//	new node != first
	{
		while (tmp)
		{
			if (ft_strcmp(node->name, tmp->name) < 0)
			{
				if (prev)
				{
					prev->next = node;
					node->prev = prev;
				}
				tmp->prev = node;
				node->next = tmp;
				return ;
			}
			else
			{
				prev = tmp;
				if (tmp->next)
					tmp = tmp->next;
				else		// tmp is last, update last to new
				{
					tmp->next = node;
					node->prev = tmp;
					return ;
				}
			}
		}
	}
}

// void	delete_node(t_node *node, t_node *next, t_node *prev, t_node **head)
void	delete_node(t_node *node, t_node **head)
{
	if (node->prev)
	{
		(node->next)->prev = node->prev;
		(node->prev)->next = node->next;
	}
	else
	{
		(node->next)->prev = NULL;
		*head = node->next;
	}
	node->next = NULL;
	node->prev = NULL;
	free(node->name);
	free(node);
}

void	delete_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp->name);
		free(tmp);
	}
	head = NULL;
}

void	list_create_node(t_node **head, char *filename, int type)
{
	t_node	*node;

	// printf("list create a\n");
	node = (t_node*)malloc(sizeof(t_node));
	if (!node)
		exit_malloc_error("list_add_file");
	// printf("\tfirst\n");
	node->type = type;
	// printf("\tsec1\t%s\n", filename);
	node->name = ft_strdup(filename);
	// printf("\tsec2\n");
	if (!node->name)
		exit_dup_error("list_add_file");
	// printf("\tsec3\n");
	node->prev = NULL;
	node->next = NULL;
	// node->path = ????

	// printf("list create b\n");
	list_sort_add(head, node);
	// printf("list create c\n");
}

void	list_add_current(t_node **head)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		filestat;

	// printf("list_add_curr\n");
	dir = opendir(".");
	if (!dir)
		error_dir("list_add_current");		//	proper error code ???
	dp = readdir(dir);
	while (dp != NULL)
	{
		lstat(dp->d_name, &filestat);
		dispatch_filetype(head, filestat, dp->d_name);
		dp = readdir(dir);
	}
	closedir(dir);
}
//	/lists.c		---	---	---	---	---	---	---	---	---	---	---	---

void	dispatch_filetype(t_node **head, struct stat filestat, char *filename)
{
	// printf("dispatch a\n");
	if (S_ISDIR(filestat.st_mode))
		list_create_node(head, filename, 4);
	else if (S_ISREG(filestat.st_mode))
		list_create_node(head, filename, 8);
	else if (S_ISLNK(filestat.st_mode))
		list_create_node(head, filename, 10);
	else
		list_create_node(head, filename, 0);
		// need to check spesific error with new func?
	// printf("dispatch b\n");
}

void	read_arguments(t_node **head, int argc, char **argv, t_info *info)
{
	struct stat	filestat;

	if (info->args == 0)
		list_add_current(head);
	else
	{
		// printf("read arg a\n");
		// printf("arg = %d, iargs = %d\n", argc, info->args);
		while (info->args > 0)
		{
			lstat(argv[argc - info->args], &filestat);
			dispatch_filetype(head, filestat, argv[argc - info->args]);
			//	segfault
			// lstat(argv[argc - info->args + 1], &filestat);
			// dispatch_filetype(head, filestat, argv[argc - info->args + 1]);
			info->args--;
		}
	}
	// printf("rea arg b\n");
}

int	list_find_dir(t_node *head)
{
	t_node		*tmp;
	struct stat	filestat;

	tmp = head;
	while (tmp)
	{
		stat(tmp->name, &filestat);
		if (S_ISDIR(filestat.st_mode))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}


// void	list_add_current(t_node **head)
// {
// 	DIR				*dir;
// 	struct dirent	*dp;
// 	struct stat		filestat;

// 	// printf("list_add_curr\n");
// 	dir = opendir(".");
// 	if (!dir)
// 		error_dir("list_add_current");		//	proper error code ???
// 	dp = readdir(dir);
// 	while (dp != NULL)
// 	{
// 		lstat(dp->d_name, &filestat);
// 		dispatch_filetype(head, filestat, dp->d_name);
// 		dp = readdir(dir);
// 	}
// 	closedir(dir);
// }

void	print_long(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while(tmp)
	{
		// print total
		// print chmod
		// print links
		// print owner
		// print year?
		// print size
		// print mod time
		// print name
		// if (options & DIRECTORY)		//	bonus
		// 	printf("/");
		printf("\n");
		tmp = tmp->next;
	}

}
void	print_long__reverse(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while(tmp->next)
		tmp = tmp->next;
	while(tmp)
	{
		// print total
		// print chmod
		// print links
		// print owner
		// print year?
		// print size
		// print mod time
		// print name
		// if (options & DIRECTORY)		//	bonus
		// 	printf("/");
		printf("\n");
		tmp = tmp->prev;
	}
}

void	list_sort_time(t_node **head)
{
	t_node	*tmp;
	int		sorted;
	t_node	*prev;

	sorted = 0;
	tmp = *head;
	while (!sorted)
	{
		while (tmp->next)
		{
			prev = tmp->prev;
			if (tmp->time > (tmp->next)->time)
			{
				// OK
				prev->next = tmp->next;
				(tmp->next)->prev = prev;

				((tmp->next)->next)->prev = tmp;
				(tmp->next)->next = tmp;
				tmp->next = (tmp->next)->next;

				sorted = 0;

				if (tmp->prev = NULL)
					*head = tmp;
			}
			tmp = tmp->next;
		}
		sorted = 1;
		tmp = *head;
	}
}

void	print_dispatch(t_node *head, int options)
{
	if (options & LONG && !(options & REVERSE))
		//print_long(head);
	else if (options & LONG && (options & REVERSE))
		//print_long_reverse(head);
	else if ()
}

void	print_directory(t_node *head, t_info *info)
{
	t_node			*newhead;
	DIR				*dir;
	struct dirent	*dp;
	struct stat		filestat;

	newhead = head;
	dir = opendir(newhead->name);
	if (!dir)
		error_dir("print_directory");
	dp = readdir(dir);
	while (dp)
	{
		lstat(dp->d_name, &filestat);
		dispatch_filetype(&newhead, filestat, dp->d_name);
		dp = readdir(dir);
	}
	closedir(dir);

	print_dispatch(newhead, info->options);

	if ((!(info->options & RECURSIVE)) && (list_find_dir(newhead)))
		delete_list(newhead);
	else
		// find and print the dirs inside recursively
}

void	print_reverse_list(t_node **head)
{
	t_node *tmp;

	tmp = *head;

	while(tmp->next)
		tmp = tmp->next;

	while(tmp)
	{
		// printf("%-*s %d\n", 20, tmp->name, tmp->type);
		printf("%s\n",tmp->name);

		tmp = tmp->prev;
	}
}

// void	ft_ls(t_node **head, t_info *info)
// {
// 	t_node	*tmp;

// 	tmp = *head;
// 	while(tmp)
// 	{
// 		printf("%s\n",tmp->name);
// 		// printf("Name: '%-*s'Type: %-*d", 20, tmp->name, 5, tmp->type);
// 		// if(tmp->type == 8)
// 		// 	printf("'file'\n");
// 		// else if(tmp->type == 4)
// 		// 	printf("'directory'\n");
// 		// else if(tmp->type == 10)
// 		// 	printf("'symbolic link'\n");
// 		// else
// 		// 	printf("'other'\n");

// 		// if (tmp->next)
// 		// 	printf("****%s****\n", (tmp->next)->name);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// 	print_reverse_list(head);
// 	delete_list(*head);
// }
void	ft_ls(t_node **head, t_info *info)
{
	t_node	*tmp;

	print_list_errors(*head);
	tmp = *head;
	if (info->options & REVERSE)
	{
		while (tmp->next)
			tmp = tmp->next;
		while(tmp)
		{
			// if (tmp->name[0] != '.')
			{
				printf("%s\n", tmp->name);
			}
			tmp = tmp->prev;
		}
	}
	else
	{
		while(tmp)
		{
			// if (tmp->name[0] != '.')
				printf("%s\n", tmp->name);
			tmp = tmp->next;
		}
	}
	delete_list(*head);
}

int main(int argc, char **argv)
{
	t_info	info;
	t_node	*head;

	reset_info(&info, head);
	if (argc > 1)
		read_options(argc, argv, &info);
	read_arguments(&head, argc, argv, &info);
	ft_ls(&head, &info);
}

// structure:
// print agruments: errors, files, foldername, folder content

// void	TEST_STRUCTURE(t_node *head)
// {
// 	print_list_errors(head);
// 	print_list_files(head);
// 	print_list_dirs(head);
// }

//????
// void	ft_ls(int argc, char **argv, t_info *info)
// {
// 	DIR	*dir;
// 	struct dirent	*dp;
// 	if (info->args > 0)
// 	{
// 		while (info->args > 0)
// 		{
// 			dir = opendir(argv[argc - info->args + 1]);
// 			if (!dir)		//	arg is a file
// 				list_add_file(argv[argc - info->args + 1], );
// 			else
// 			{}
// 			info->args--;
// 		}
// 	}
// 	else
// 		dir = opendir()
// }
//???

// 	0	1	2	3	4	5	6
// ls  -l  -a  -f  -a  file file		argc 6, arguments 2(5-6)
// argc - arguments + 1

// void	ft_ls(int argc, char **argv, t_info *info)
// {
// 	DIR	*dir;

// 	struct dirent	*dp;
// 	if (info->args > 0)
// 	{
// 		while (info->args > 0)
// 		{
// 			dir = opendir(argv[argc - info->args + 1]);
// 			if (!dir)		//	arg is a file
// 				list_add_file(argv[argc - info->args + 1], );
// 			else
// 			{

// 			}

// 			info->args--;
// 		}

// 	}
// 	else
// 	{
// 		dir = opendir()
// 	}

// }

// void	ft_ls(int argc, char **argv, t_info *info)
// {
// 	DIR	*dir;
// 	struct dirent *dp;

// 	dir = opendir(".");
// 	if (!dir)
// 	{
// 		perror("ft_ls");
// 		exit(1);
// 	}

// 	dp = readdir(dir);
// 	while (dp)
// 	{
// 		if (dp->d_name[0] != '.')
// 			printf("%s\n", dp->d_name);
// 		dp = readdir(dir);
// 	}
// 	closedir(dir);
// }



// int main(int ac, char **av)		// 	GETTING STARTED PDF
// {
// 	DIR *dir;
// 	struct dirent *dp;

// 	if ((dir = opendir(".")) == NULL)
// 	{
// 		perror("main");
// 		exit(1);
// 	}

// 	while ((dp = readdir(dir)) != NULL)
// 	{
// 		if (dp->d_name[0] != '.')	// hide hidden files/folders
// 			printf("%s\t\tABV", dp->d_name);
// 			printf("'%d'\n", dp->d_type);
// 	}
// 	closedir(dir);

// 	(void)ac;
// 	struct stat filestat;
// 	stat(av[1], &filestat);
// 	// struct passwd = getpwuid(filestat.st_uid);

// 	printf("\nInformation for %s\n", av[1]);
// 	printf("--------------------------------------------\n");
// 	printf("%-33s %lld bytes\n", "File size:", filestat.st_size);
// 	printf("%-33s %d\n", "Number of links:", filestat.st_nlink);
// 	printf("%-33s %d\n", "Mode:", filestat.st_mode);
// 	printf("%-33s %llu\n", "File inode:", filestat.st_ino);
// 	printf("%-33s %d\n", "Id of the device:", filestat.st_dev);
// 	printf("%-33s %d\n", "User ID of the owner:", filestat.st_uid);
// 	// printf("%-33s %s\n", "Username of the owner:", passwd->pw_name);
// 	printf("%-33s %d\n", "Group ID of the owner:", filestat.st_gid);
// 	printf("%-33s %d\n", "Device ID:", filestat.st_rdev);
// 	printf("%-33s %d\n", "Block size for filesystem I/O:", filestat.st_blksize);
// 	printf("%-33s %lld\n", "Number of 512B blocks allocated:", filestat.st_blocks);

// 	printf("%-33s ", "File permissions:");
// 	if (S_ISDIR(filestat.st_mode))
// 		printf("d");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IRUSR)
// 		printf("r");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IWUSR)
// 		printf("w");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IXUSR)
// 		printf("x");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IRGRP)
// 		printf("r");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IWGRP)
// 		printf("w");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IXGRP)
// 		printf("x");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IROTH)
// 		printf("r");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IWOTH)
// 		printf("w");
// 	else
// 		printf("-");
// 	if (filestat.st_mode & S_IXOTH)
// 		printf("x");
// 	else
// 		printf("-");
// 	printf("\n");
// }
