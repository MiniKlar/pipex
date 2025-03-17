/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:51:50 by lomont            #+#    #+#             */
/*   Updated: 2025/03/18 00:13:48 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int pipex(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc == 5)
	{
		data = initialise_data();
		data->fd = open(argv[1], O_RDWR);
		if (data->fd == -1)
		{
			printf("file not accessible\n");
			return(free(data), 1);
		}
		if (access(argv[1], F_OK | R_OK) != 0)
		{
			perror("File not accessible");
			exit(EXIT_FAILURE);
		}
		if (access(argv[argc - 1], F_OK | W_OK) == 0)
			unlink(argv[argc - 1]);
		data->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR, 0755);
		if (data->out_fd == -1)
			return(free(data), 1);
		data->command_arg = ft_split(argv[2], ' ');
		data->command_arg_2 = ft_split(argv[3], ' ');
		pipe(data->fdpipe);
		fork_pipex(data, envp);
		return (0);
	}
	return (1);
}

void	fork_pipex(t_data *data, char **envp)
{
	data->id_fork = fork();
	fork_error(1, data);
	if (data->id_fork == 0)
		fork_pipex1(data, envp);
	else
	{
		data->id_fork2 = fork();
		fork_error(2, data);
		if (data->id_fork2 == 0)
			fork_pipex2(data, envp);
		else
		{
			waitpid(data->id_fork, NULL, WNOHANG);
			waitpid(data->id_fork2, NULL, WNOHANG);
			free_close(data);
		}
	}
}

void fork_pipex1(t_data *data, char **envp)
{
	char *command_path;

	close(data->fdpipe[0]);
	dup2(data->fd, 0);
	dup2(data->fdpipe[1], 1);
	command_path = check_command_path(data->command_arg[0], envp);
	if (execve(command_path, &data->command_arg[0], envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	fork_pipex2(t_data *data, char **envp)
{
	char *command_path;

	close(data->fdpipe[1]);
	dup2(data->fdpipe[0], 0);
	dup2(data->out_fd, 1);
	command_path = check_command_path(data->command_arg_2[0], envp);
	if (execve(command_path, &data->command_arg_2[0], envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
