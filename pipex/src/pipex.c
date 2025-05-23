/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:11 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 18:42:38 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char *av[], char *env[])
{
	int		parent_fd[2];
	pid_t	pid;

	if (ac != 5)
		return (ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO),
			EXIT_FAILURE);
	if (pipe(parent_fd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		child_routine(av, parent_fd, env);
	parent_routine(av, parent_fd, env);
	wait(&pid);
	return (EXIT_SUCCESS);
}
