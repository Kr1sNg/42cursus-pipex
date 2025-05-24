/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:11 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 23:37:14 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// text input in heredoc while comparing with LIMITER
void	input_heredoc(char **av, int *fd)
{
	char	*text;

	close(fd[0]);
	while (1)
	{
		text = get_next_line(STDIN_FILENO);
		if (ft_strncmp(text, av[2], ft_strlen(av[2])) == 0)
		{
			free(text);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(text, fd[1]);
		free(text);
	}
}

void	here_doc(char **av)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		input_heredoc(av, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}
