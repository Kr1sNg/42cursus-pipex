/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-wstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/05 17:06:41 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int	main(int ac, char *av[])
{
	int	pid = fork();
	if (pid == -1)
		return (-42);
	if (pid == 0)
	{
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
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

