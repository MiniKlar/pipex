/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/14 13:39:13 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_tab(char **tab);
char *find_env(void);
char *check_command_path(char *command);

int main(int argc, char **argv)
{
	int fd;
	int out_fd;
	char **command_arg;
	char **command_arg_2;
	char *new_pathcommand;
	char *new_pathcommand_2;
	pid_t id_fork;
	pid_t id_fork2;
	int fdpipe[2];

	command_arg = ft_split(argv[2], ' ');
	command_arg_2 = ft_split(argv[3], ' ');
	if (access(argv[1], F_OK | R_OK) != 0)
	{
		perror("File not accessible");
		exit(EXIT_FAILURE);
	}
	new_pathcommand = check_command_path(command_arg[0]);
	new_pathcommand_2 = check_command_path(command_arg_2[0]);
	pipe(fdpipe);
	fd = open(argv[1], O_RDWR);
	printf("\n\n%s |||||| %s\n\n", new_pathcommand, new_pathcommand_2);
	if (access(new_pathcommand, F_OK) == 0)
	{
		printf("Delete previous outfile\n");
		unlink(argv[argc - 1]);
	}
	else
	{
		printf("TU ES sorti\n");
		exit(EXIT_FAILURE);
	}
	out_fd = open(argv[argc - 1], O_CREAT | O_RDWR, 0755);
	id_fork = fork();
	if (id_fork == 0)
	{
		//printf("TU ES ICI\n");
		dup2(fd, 0);
		dup2(fdpipe[1], 1);
		if (execve(new_pathcommand, &command_arg[0], ENVIRON) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(fdpipe[1]);
		id_fork2 = fork();
		//printf("id_fork2 = %d\n",id_fork2);
		if (id_fork2 == 0)
		{
			//printf("pid child 2 = %d\n",getpid());
			dup2(fdpipe[0], 0);
			dup2(out_fd, 1);
			//printf("TU ES ICI MAINTENANT LL\n");
			if (execve(new_pathcommand_2, command_arg_2, ENVIRON) == -1)
			{
				perror("execve failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(id_fork, NULL, 0);
			waitpid(id_fork2, NULL, 0);
			//printf("MAIN FINI\n");
			close(fdpipe[0]);
			close(out_fd);
			close(fd);
			free(new_pathcommand);
			free(new_pathcommand_2);
			free_tab(command_arg);
			free_tab(command_arg_2);
		}
	}
}

char *check_command_path(char *command)
{
	int i;
	char *new_command;
	char *new_command_path;
	char **env;
	char *tmp;

	i = 0;
	new_command = ft_strjoin("/", command);
	env = ft_split(find_env(), ':');
	new_command_path = NULL;

	while (env[i])
	{
		tmp = ft_strjoin(env[i], new_command);
		if (access(tmp, F_OK) == 0)
		{
			new_command_path = ft_strtrim(tmp, "PATH=");
			printf("env[%d]%s\n", i, tmp);
			return (free(new_command), free_tab(env), free(tmp), new_command_path);
		}
		else
		{
			free(tmp);
			i++;
		}
	}
	return (NULL);
}

char *find_env(void)
{
	int i;
	char *env;

	i = 0;
	while (ENVIRON[i] != NULL)
	{
		if (ft_strnstr(ENVIRON[i], "PATH=", 5) != 0)
		{
			env = ENVIRON[i];
			printf("%s\n", env);
			return (env);
		}
		else
			i++;
	}
	return (NULL);
}

void free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}