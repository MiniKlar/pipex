/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:51:50 by lomont            #+#    #+#             */
/*   Updated: 2025/03/22 18:55:22 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = initialise_data();
	data->command_arg = ft_split(argv[2], ' ');
	data->command_arg_2 = ft_split(argv[3], ' ');
	pipe(data->fdpipe);
	return (fork_pipex(data, argv, argc, envp));
}

int	fork_pipex(t_data *data, char **argv, int argc, char **envp)
{
	int	wstatus;

	wstatus = 0;
	data->id_fork = fork();
	fork_error(1, data);
	if (data->id_fork == 0)
		fork_pipex1(data, argv, envp);
	if (WEXITSTATUS(wstatus) == 127)
		free_close(data);
	close(data->fdpipe[1]);
	data->id_fork2 = fork();
	fork_error(2, data);
	if (data->id_fork2 == 0)
		fork_pipex2(data, argv, argc, envp);
	if (WEXITSTATUS(wstatus) == 127)
		free_close(data);
	close(data->fdpipe[0]);
	wstatus = ft_wait(data, wstatus);
	free_close(data);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_SUCCESS);
}

void	fork_pipex1(t_data *data, char **argv, char **envp)
{
	char	*command_path;
	int fd;

	if (access(argv[1], F_OK | R_OK) != 0)
	{
		perror("File not accessible");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		free_close(data), exit(1);
	}
	command_path = check_command_path(data->command_arg[0], envp);
	if (!command_path)
		printf("LOL\n\n"), free_close(data), close(fd), exit(1); // bien checker si le path est null pour ne pas rentrer dans execve
	close(data->fdpipe[0]);
	dup2(fd, 0);
	dup2(data->fdpipe[1], 1);
	if (execve(command_path, &data->command_arg[0], envp) == -1)
	{
		perror("execve failed: command not found");
		exit(127);
	}
}

void	fork_pipex2(t_data *data, char **argv, int argc, char **envp)
{
	char	*command_path;
	int		fd;

	if (access(argv[argc - 1], F_OK | W_OK) == 0)
		unlink(argv[argc - 1]);
	fd = open(argv[argc - 1], O_CREAT | O_RDWR, 0755);
	if (fd == -1)
		free(data), exit (1);
	command_path = check_command_path(data->command_arg_2[0], envp);
	if (!command_path)
		printf("LOL222\n\n"), free_close(data), close(fd), exit(1); // bien checker si le path est null pour ne pas rentrer dans execve
	dup2(data->fdpipe[0], 0);
	dup2(fd, 1);
	if (execve(command_path, &data->command_arg_2[0], envp) == -1)
	{
		perror("execve failed: command not found");
		exit(127);
	}
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
