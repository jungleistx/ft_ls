/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:55:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/09/18 13:13:07 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//	change printf -> ft_printf	!!!!

//	libft
void	ft_putstr_fd(char const *s, int fd)
{
	int		i;
	char	*ptr;

	if (s == NULL)
		return ;
	i = 0;
	ptr = (char *)s;
	while (ptr[i])
	{
		write(fd, &ptr[i], 1);
		i++;
	}
}
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
char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
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
char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
	{
		s1[i] = s2[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
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

char	*ft_strdup_exit(char *src)
{
	char	*ret;
	ret = ft_strdup((const char *)src);
	if (!ret)
		exit_dup_error("ft_strdup_exit");
	return (ret);
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

void print_test2(t_node *head)
{
	t_node *tmp = head;
	while (tmp)
	{
		printf("(%s) -> ", tmp->name);
		tmp = tmp->next;
	}
	printf("(NULL)\n");
}

void	list_add_directory(t_node **head, char *path, t_info *info, char *name)
{
	DIR				*dir;
	struct dirent	*dp;

	info->total = 0;
	dir = opendir(path);
	if (!dir)
		error_dir(name);
	else
	{
		dp = readdir(dir);
		while (dp != NULL)
		{
			if (dp->d_name[0] != '.' ||
			(dp->d_name[0] == '.' && (info->options & HIDDEN)))
			{
				create_node(head, dp->d_name, info, path);
			}
			dp = readdir(dir);
		}
		closedir(dir);
	}
}

void	ft_ls(t_node **head, t_info *info)
{
	// print_test(*head);
	print_list_errors(*head, info);
	print_list_files(head, info);
	// print_test(*head);
	if (info->options & RECURSIVE)
		print_dir_recursive(head, info);
	else
		print_dir(*head, info);

	if (head)
		free_list(head, info->options);
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
	ft_ls(&head, &info);
	return (info.ret_nr);
}
