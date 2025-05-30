/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:32:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 23:12:35 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef enum s_file
{
	READ,
	WRITE,
	APPEND,
}	t_file;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* execute */
char	*get_env(char *word, char **env);
char	*get_path(char *cmd, char **env);
void	ft_execute(char *cmd, char **env);

/* here_doc */
void	input_heredoc(char **av, int *fd);
void	here_doc(char **av);

/* main */
int		ft_open(char *file, int read_write);
void	ft_pipex(char *cmd, char **env);


#endif
