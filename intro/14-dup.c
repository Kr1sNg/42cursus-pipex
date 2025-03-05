/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14-dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/05 18:57:51 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* dup dup2: duplicate a file descriptor to change stdout to a file */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

int	main(int ac, char *av[])
{
	int	pid = fork();
	if (pid == -1)
		return (-42);
	if (pid == 0)
	{
		/*create file -> it will have the file descriptors number 3 */ 
		int file = open("14-dup2.txt", O_WRONLY | O_CREAT, 0777); //create if not exist
		if (file == -1)
			return (-42);
		
		/*duplicate file into descriptor stdout */
		printf("The fd to pingres: %i\n", file);
		int file2 = dup2(file, STDOUT_FILENO); // it change file descriptor number 1 (stdout) to be 3 (file)
		if (file2 == -1)
			return (-42);
		printf("The duplicated fd: %i\n", file2);
		close(file);
		
		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find program to execute!\n");
			return (-43);
		}
		printf("This line should not print on the terminal because execlp \
		already terminates the child process before this!\n");
	}
	else
	{// Parent process
		
		/* test if child process terminated without error signal */
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus)) // status bit of wait()
		{
			int statuscode = WEXITSTATUS(wstatus);
			if (statuscode == 0)
				printf("Success!\n");
			else
				printf("Failure with status code %i\n", statuscode);
		}
		printf("Some post proccessing goes here!\n");
	}
	return (0);
}

