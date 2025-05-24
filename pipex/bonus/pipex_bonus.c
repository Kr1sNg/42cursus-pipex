/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:11 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 23:43:03 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_open(char *file, int read_write)
{
	int	fd;

	if (read_write == READ)
		fd = open(file, O_RDONLY, 0777);
	if (read_write == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (read_write == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (fd);
}

void	ft_pipex(char *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_execute(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	ft_exit(int code)
{
	if (code == 1)
		ft_putstr_fd("./pipex_bonus file1 cmd1 ... cmd2 file2\n",
			STDERR_FILENO);
	if (code == 2)
		ft_putstr_fd("./pipex_bonus here_doc LIMITER cmd cmd1 file\n",
			STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	main(int ac, char *av[], char *env[])
{
	int	fd[2];
	int	i;

	if (ac < 5)
		return (ft_exit(1));
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			return (ft_exit(2));
		i = 3;
		fd[1] = ft_open(av[ac - 1], APPEND);
		here_doc(av);
	}
	else
	{
		i = 2;
		fd[0] = ft_open(av[1], READ);
		fd[1] = ft_open(av[ac - 1], 1);
		dup2(fd[0], STDIN_FILENO);
	}
	while (i < ac - 2)
		ft_pipex(av[i++], env);
	dup2(fd[1], STDOUT_FILENO);
	ft_execute(av[ac - 2], env);
	return (EXIT_SUCCESS);
}
