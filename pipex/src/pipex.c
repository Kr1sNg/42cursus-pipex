/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:11 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/04 14:50:39 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char *av[], char *env[])
{
	t_pipex	*pipex;
	int		i;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_init_pipex(pipex); //struct initiation
	if (!ft_check_args(pipex, ac, av))
		return (ft_cleanup(pipex), ft_err(error));
	if (!ft_parse_cmd_paths(pipex, ac, av, env))
		return (ft_cleanup(pipex), ft_err(error));
	if (!ft_parse_cmd_args(pipex, ac, av))
		return (ft_cleanup(pipex), ft_err(error));
	i = -1;
	while (++i < pipex->cmd_count)
		if (!ft_spawn_child(pipex, env, i))
			return (ft_cleanup(pipex), ft_err(error));
	i = -1;
	while (++i < pipex->cmd_count)
		wait(NULL);
	return (ft_cleanup(pipex), 0);
}

void	ft_init_pipex(t_pipex *pipex)
{
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->here_doc = false;
	pipex->is_invalid_input = false;
	pipex->is_urandom = false;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_count = 0;
}

ft_exec()
{
	pipe();
	fork();
	if (child)
	{
		dup2();
		execve();
	}
	else
	{
		close()
	}

}