/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:55:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/30 13:38:11 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//	change printf -> ft_printf	!!!!

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

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int	size;
	int				i;

	i = 0;
	size = 0;
	while (size < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		size++;
	}
	while (size < len)
	{
		dst[i] = '\0';
		i++;
		size++;
	}
	return (dst);
}
int	ft_atoi(const char *str)
{
	unsigned long	num;
	int				i;
	int				negative;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
		i++;
	num = 0;
	negative = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i++] - '0');
		if (negative == 1 && num > 9223372036854775807)
			return (-1);
		if (negative == -1 && num >= 9223372036854775808u)
			return (0);
	}
	return (num * (negative));
}
void	ft_memdel(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	letter;
	unsigned int	i;

	letter = c;
	i = 0;
	while (i < len)
	{
		*(char *)&b[i] = letter;
		i++;
	}
	return (b);
}
//	/libft

//	needs the loop for the path and searching for the correct file
int	ft_strcmp_case_insen(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if ((s1[i] >= 65 && s1[i] <= 90) || (s1[i] >= 97 && s1[i] <= 122))
		{
			if ((s1[i] == s2[i]) || (s1[i] - s2[i] == 32) ||
			(s1[i] - s2[i] == -32))
				i++;
			else
				return (0);
		}
		else
		{
			if (s1[i] != s2[i])
				return (0);
			else
				i++;
		}
	}
	return (1);
}

void print_test(t_node *head)
{
	t_node *tmp = head;
	while (tmp)
	{
		// printf("(%s %d) (%ld %ld) -> \n", tmp->name, tmp->type,
		// 	tmp->sec, tmp->n_sec);
		printf("(%s) -> ", tmp->name);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}

void	list_add_directory(t_node **head, char *path, int opts)
{
	DIR				*dir;
	struct dirent	*dp;

	dir = opendir(path);
	if (!dir)
		error_dir("list_add_directory");		//	proper error code ???
	dp = readdir(dir);
	while (dp != NULL)
	{
		// printf("\t%s\n", dp->d_name);
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && (opts & HIDDEN)))
			create_node(head, dp->d_name, opts);
		dp = readdir(dir);
	}
	closedir(dir);
	if (opts & SORT_TIME && opts & REVERSE)
		list_sort_time_reverse(head);
	else if (opts & SORT_TIME)
		list_sort_time(head);
}

void	ft_ls(t_node *head, int options, int *ret_nr)
{
	// t_node	*tmp;

	// tmp = *head;
	// printf("ls\n");
	// print_test(*head);
	print_list_errors(head, ret_nr);
	print_list_files(&head, options);
	// if (options & RECURSIVE)
	// 	print_dir_recursive(head, options);
	// else
	// print_test(head);
		print_dir(head, options);

/*		TODO

dir content_list doesnt reverse with -r

*/

	// printf("testing\n");
	// print_test(head);
	// printf("testing\n");
	if (head)
		free_list(&head, options);
	// print_test(head);
}

int main(int argc, char **argv)
{
	t_info	info;
	t_node	*head;

	reset_info(&info, &head);
	if (argc > 1)
		read_options(argc, argv, &info);
	read_arguments(&head, argc, argv, &info);
	ft_ls(head, info.options, &info.ret_nr);

	return (info.ret_nr);
}

/*
readdir(d)
if d type == 4
append list1
if (R)
append list2
D1 F D2 F F D3 D4 F F D5 30000
D1 D2 D3 D4 D5
*/
