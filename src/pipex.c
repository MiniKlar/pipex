/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:51:50 by lomont            #+#    #+#             */
/*   Updated: 2025/03/19 05:11:45 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = initialise_data();
	data->fd = open(argv[1], O_RDWR);
	if (data->fd == -1)
	{
		perror("Cannot open file");
		free(data);
		exit(0);
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
		return (free(data), 1);
	data->command_arg = ft_split(argv[2], ' ');
	data->command_arg_2 = ft_split(argv[3], ' ');
	pipe(data->fdpipe);
	return (fork_pipex(data, envp));
}

int	fork_pipex(t_data *data, char **envp)
{
	int	wstatus;

	wstatus = 0;
	data->id_fork = fork();
	fork_error(1, data);
	if (data->id_fork == 0)
		if (fork_pipex1(data, envp) == 127)
			free_close(data);
	data->id_fork2 = fork();
	fork_error(2, data);
	if (data->id_fork2 == 0)
		if (fork_pipex2(data, envp) == 127)
			free_close(data);
	close(data->fdpipe[0]);
	close(data->fdpipe[1]);
	wstatus = ft_wait(data, wstatus);
	free_close(data);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_SUCCESS);
}

int	fork_pipex1(t_data *data, char **envp)
{
	char	*command_path;

	command_path = check_command_path(data->command_arg[0], envp);
	close(data->fdpipe[0]);
	dup2(data->fd, 0);
	dup2(data->fdpipe[1], 1);
	if (execve(command_path, &data->command_arg[0], envp) == -1)
	{
		perror("execve failed: command not found");
		free_close(data);
		free(command_path);
		exit(127);
	}
	exit(EXIT_SUCCESS);
}

int	fork_pipex2(t_data *data, char **envp)
{
	char	*command_path;

	command_path = check_command_path(data->command_arg_2[0], envp);
	close(data->fdpipe[1]);
	dup2(data->fdpipe[0], 0);
	dup2(data->out_fd, 1);
	if (execve(command_path, &data->command_arg_2[0], envp) == -1)
	{
		perror("execve failed: command not found");
		free_close(data);
		free(command_path);
		exit(127);
	}
	exit(EXIT_SUCCESS);
}

int	ft_wait(t_data *data, int wstatus)
{
	if (waitpid(data->id_fork, &wstatus, 0) == -1)
	{
		perror("waitpid error");
		free_close(data);
		exit(errno);
	}
	else if (waitpid(data->id_fork2, &wstatus, 0) == -1)
	{
		perror("waitpid error 2");
		free_close(data);
		exit(errno);
	}
	return (wstatus);
}
