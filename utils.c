/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:24:46 by lomont            #+#    #+#             */
/*   Updated: 2025/03/18 00:13:29 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*initialise_data(void)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->command_arg = NULL;
	data->command_arg_2 = NULL;
	data->fd = 0;
	data->out_fd = 0;
	data->id_fork = 0;
	data->id_fork2 = 0;
	return (data);
}

char	*check_command_path(char *command, char **envp)
{
	int		i;
	char	*new_command;
	char	**new_env;
	char	*command_path;
	char	*tmp;

	if (!command)
		return (NULL);
	i = 0;
	new_env = ft_split(decoup_env(envp), ':');
	new_command = ft_strjoin("/", command);
	while (new_env[i])
	{
		tmp = ft_strjoin(new_env[i], new_command);
		if (access(tmp, F_OK) == 0)
		{
			command_path = ft_strtrim(tmp, "PATH=");
			return (free(new_command), free(tmp), command_path);
		}
		else
			free(tmp);
		i++;
	}
	tmp = ft_strtrim(new_command, "/");
	return (free(new_command), tmp);
}

char *decoup_env(char **envp)
{
	int		i;
	char	*tmp;
	char	*new_envp;

	i = 0;
	tmp = NULL;
	new_envp = ft_strdup("");
	while (envp[i] != 0)
	{
		if (new_envp == NULL)
			new_envp = ft_strjoin("", envp[i]);
		else
			tmp = ft_strjoin(new_envp, envp[i]);
		free(new_envp);
		new_envp = ft_strjoin(tmp, ":");
		free(tmp);
		i++;
	}
	return (new_envp);
}

// char	*find_env(void)
// {
// 	int		i;
// 	char	*env;

// 	i = 0;
// 	while (ENVIRON[i] != NULL)
// 	{
// 		if (ft_strnstr(ENVIRON[i], "PATH=", 5) != 0)
// 		{
// 			env = ENVIRON[i];
// 			return (env);
// 		}
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }
