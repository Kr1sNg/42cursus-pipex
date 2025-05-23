/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23a-pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/05/23 10:44:05 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	int	dprintf(int fd, const char *,...) - write output to the fd
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int 	fd[2]; /* fd[0]: read in - fd[1]: write out */
	pid_t	pid, wpid;
	char	*words[] = {"peach", "pear", "banana", "apple", "strawberry"};
	size_t	num;
	int		i = 0;
	int		status;
	
	// create a pipe and check if there's error
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	
	// create child process
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0) // in child process
	{
		close(fd[1]); // fd unused in child
		dup2(fd[0], STDIN_FILENO); // fd[0] (the read end of pipe) donates its data to stdin
		close(fd[0]); // close since stdin is a copy
		
		char *av[] = {(char *)"sort", NULL}; // create argument vector
		
		// run sort command (from /usr/bin) and it sends output to terminal
		if (execvp(av[0], av) < 0)
			exit(EXIT_FAILURE);
	}
	
	// in parent process
	close(fd[0]); // fd unused in parent
	num = sizeof(words)/sizeof(words[0]);
	
	// write input to the fd[1] so it can be read in from child (by fd[0] of child)
	while (i < num)
	{
		dprintf(fd[1], "%s\n", words[i]);
		i++;
	}
	close(fd[1]);
	// wait for child to finish before exiting
	wpid = waitpid(pid, &status, 0);
	
	return (wpid == pid && WIFEXITED(status)) ? WEXITSTATUS(status) : -1;
	/*
	// explain this code
	if (wpid == pid && WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1); 
	*/
}
