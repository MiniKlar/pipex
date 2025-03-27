/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:24:46 by lomont            #+#    #+#             */
/*   Updated: 2025/03/27 13:14:43 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_data	*initialise_data(void)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->command_arg = NULL;
	data->command_arg_2 = NULL;
	data->id_fork = 0;
	data->id_fork2 = 0;
	return (data);
}

char	*check_command_path(char *command, char **envp)
{
	char	**path_tab;
	char	*new_command;
	char	*path;

	if (!command || !envp[0])
		return (NULL);
	if (access(command, F_OK | X_OK) == 0)
		return (command);
	if (ft_strchr(command, '/') != NULL && access(command, F_OK | X_OK) != 0)
		return (NULL);
	path = recup_env(envp);
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	new_command = ft_strjoin("/", command);
	free(path);
	return (new_command_function(path_tab, new_command));
}

char	*new_command_function(char **path, char *new_command)
{
	int		i;
	char	*command_path;

	i = 0;
	while (path[i])
	{
		command_path = ft_strjoin(path[i], new_command);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		else
			free(command_path);
		i++;
	}
	free_tab(path);
	free(new_command);
	return (NULL);
}

char	*recup_env(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (ft_strtrim(envp[i], "PATH="));
		}
		else
			path = NULL;
		i++;
	}
	return (path);
}

int	open_access_infile(t_data *data, char *argv)
{
	int	fd;

	if (access(argv, F_OK) != 0)
	{
		perror("File not accessible");
		free_close(data);
		exit(EXIT_FAILURE);
	}
	else if (access(argv, R_OK) != 0)
	{
		perror("File not readable");
		free_close(data);
		exit(EXIT_FAILURE);
	}
	fd = open(argv, O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		free_close(data);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
