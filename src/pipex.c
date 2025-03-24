/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:51:50 by lomont            #+#    #+#             */
/*   Updated: 2025/03/24 22:22:45 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = initialise_data();
	data->command_arg = ft_split(argv[2], ' ');
	data->command_arg_2 = ft_split(argv[3], ' ');
	if (pipe(data->fdpipe) == -1)
	{
		free(data->command_arg);
		free(data->command_arg_2);
		free(data);
	}
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
	int		fd;

	fd = open_access_infile(data, argv[1]);
	command_path = check_command_path(data->command_arg[0], envp);
	if (!command_path)
	{
		ft_printf("command not found\n");
		free_close(data);
		close(fd);
		exit(1);
	}
	close(data->fdpipe[0]);
	dup2(fd, 0);
	dup2(data->fdpipe[1], 1);
	close(fd);
	close(data->fdpipe[1]);
	if (execve(command_path, &data->command_arg[0], envp) == -1)
	{
		free_close(data);
		close(fd);
		exit(127);
	}
}

void	fork_pipex2(t_data *data, char **argv, int argc, char **envp)
{
	char	*command_path;
	int		fd;

	fd = open_access_outfile(data, argv[argc -1]);
	command_path = check_command_path(data->command_arg_2[0], envp);
	if (!command_path)
	{
		ft_printf("command not found\n");
		free_close(data);
		close(fd);
		exit(127);
	}
	dup2(data->fdpipe[0], 0);
	dup2(fd, 1);
	close(data->fdpipe[0]);
	close(fd);
	if (execve(command_path, &data->command_arg_2[0], envp) == -1)
	{
		free_close(data);
		close(fd);
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
