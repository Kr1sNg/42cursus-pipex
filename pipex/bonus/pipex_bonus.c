/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:11 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 21:57:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int ac, char *av[], char *env[])
{
	int	fd_in;
	int	fd_out;
	int	i;

	if (ac < 5)
		return (ft_putstr_fd("./pipex file1 cmd1 ... cmd2 file2\n",
			STDERR_FILENO), EXIT_FAILURE);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			return (ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n",
			STDERR_FILENO), EXIT_FAILURE);
		i = 3;
		fd_out = ft_open(av[ac - 1], APPEND);
		here_doc(av); //TODO
	}
	else
	{
		i = 2;
		fd_in = ft_open(av[1], READ);
		fd_out = 
}
