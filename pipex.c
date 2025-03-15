/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:51:50 by lomont            #+#    #+#             */
/*   Updated: 2025/03/14 23:43:48 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_pipex(t_data *data)
{
	data->id_fork = fork();
	if (data->id_fork == 0)
	{
		//printf("%s\n\n", data->new_pathcommand);
		dup2(data->fd, 0);
		dup2(data->fdpipe[1], 1);
		if (execve(data->new_pathcommand, &data->command_arg[0], ENVIRON) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(data->fdpipe[1]);
		data->id_fork2 = fork();
		if (data->id_fork2 == 0)
			fork_pipex2(data);
		else
		{
			waitpid(data->id_fork, NULL, WNOHANG);
			waitpid(data->id_fork2, NULL, WNOHANG);
			free_close(data);
		}
	}
}

void	fork_pipex2(t_data *data)
{
	dup2(data->fdpipe[0], 0);
	dup2(data->out_fd, 1);
	if (execve(data->new_pathcommand_2, &data->command_arg_2[0], ENVIRON) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
