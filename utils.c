/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:24:46 by lomont            #+#    #+#             */
/*   Updated: 2025/03/14 23:43:35 by lomont           ###   ########.fr       */
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
	data->new_pathcommand = NULL;
	data->new_pathcommand_2 = NULL;
	data->fd = 0;
	data->out_fd = 0;
	data->id_fork = 0;
	data->id_fork2 = 0;
	return (data);
}

char	*check_command_path(char *command)
{
	int		i;
	char	*new_command;
	char	*command_path;
	char	**env;
	char	*tmp;

	i = 0;
	new_command = ft_strjoin("/", command);
	env = ft_split(find_env(), ':');
	while (env[i])
	{
		tmp = ft_strjoin(env[i], new_command);
		//printf("%s\n\n", tmp);
		if (access(tmp, F_OK) == 0)
		{
			command_path = ft_strtrim(tmp, "PATH=");
			return (free(new_command), free_tab(env), free(tmp), command_path);
		}
		else
			free(tmp);
		i++;
	}
	return (command);
}

char	*find_env(void)
{
	int		i;
	char	*env;

	i = 0;
	while (ENVIRON[i] != NULL)
	{
		if (ft_strnstr(ENVIRON[i], "PATH=", 5) != 0)
		{
			env = ENVIRON[i];
			return (env);
		}
		else
			i++;
	}
	return (NULL);
}
