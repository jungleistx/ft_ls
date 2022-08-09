/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:55:37 by rvuorenl          #+#    #+#             */
/*   Updated: 2022/08/09 14:46:19 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exit_usage(void)
{
	ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrsuwx1] [file ...]\n")
	exit(1);
}

void	read_options(char *argv, t_info *info)
{
	int	i;

	i = 0;
	if (argv[0] == '-' && argv[1] == '-')
	{
		exit_usage();
	}


// // 	lRart
// typedef	enum e_options
// {
// 	LONG = 1,			000001
// 	RECURSIVE = 2,		000010
// 	HIDDEN = 4,			000100
// 	REVERSE = 8,		001000
// 	SORT_TIME = 16		010000
// 	/*
// 	BONUS OPTIONS
// 	*/
// }t_options;
}

void	reset_info(t_info *info)
{
	info->options = 0;
}

void	ft_ls(int argc, char **argv, t_info *info)
{
	DIR	*dir;
	struct dirent *dp;

	dir = opendir(".");
	if (!dir)
	{
		perror("ft_ls");
		exit(1);
	}

	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_name[0] != '.')
			printf("%s\n", dp->d_name);
		dp = readdir(dir);
	}
	closedir(dir);
}

int main(int argc, char **argv)
{
	// DIR				*dir;
	// struct	dirent	*dp;
	t_info			info;

	reset_info(&info);
	read_options(argv[1], &info);
	ft_ls(argc, argv, &info);
}

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
