/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:11 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 18:41:57 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_open(char *file, int read_write)
{
	int	fd;

	if (read_write == READ)
		fd = open(file, O_RDONLY, 0777);
	if (read_write == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (fd);
}

void	child_routine(char **av, int *parent_fd, char **env)
{
	int	fd;

	fd = ft_open(av[1], READ);
	dup2(fd, STDIN_FILENO);
	dup2(parent_fd[1], STDOUT_FILENO);
	close(parent_fd[0]);
	ft_execute(av[2], env);
}

/* change stdout to fd (file2) to write into
	then change stdin to p_fd_in to get info from child
*/
void	parent_routine(char **av, int *parent_fd, char **env)
{
	int	fd;

	fd = ft_open(av[4], WRITE);
	dup2(fd, STDOUT_FILENO);
	dup2(parent_fd[0], STDIN_FILENO);
	close(parent_fd[1]);
	ft_execute(av[3], env);
}
