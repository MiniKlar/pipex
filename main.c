/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:43:51 by lomont            #+#    #+#             */
/*   Updated: 2025/03/05 05:38:06 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (access(argv[1], F_OK) != 0)
	{
		perror("File not accessible");
		exit(EXIT_FAILURE);
	}
	new_pathcommand = check_command_path(command_arg[0]);
	new_pathcommand_2 = check_command_path(command_arg_2[0]);
	pipe(fdpipe);
	//printf("pipe 0 =%d\n", fdpipe[0]);
	//printf("pipe 1 =%d\n", fdpipe[1]);
	fd = open(argv[1], O_RDWR);
	if (access(new_pathcommand, F_OK) == 0)
	{
		printf("Delete previous outfile\n");
		unlink(argv[argc - 1]);
	}
	else
	{
		//printf("CEST CA MON GROS\n");
		exit(EXIT_FAILURE);
	}
	out_fd = open(argv[argc - 1], O_CREAT | O_RDWR, 0755);
	id_fork = fork();
	if (id_fork == 0)
	{
		//printf("TU ES ICI\n");
		dup2(fd, 0);
		dup2(fdpipe[1], 1);
		if (execve(new_pathcommand, &command_arg[0], __environ) == -1)
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
			if (execve(new_pathcommand_2, command_arg_2, __environ) == -1)
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
		}
	}
}

char *check_command_path(char *command)
{
	char *new_command_path;

	new_command_path = NULL;
	//printf("%s\n\n", command);
	if (ft_strnstr(command, "/usr/bin/", ft_strlen(command)) != NULL)
	{
		//printf("PATHNAME COMPLET\n");
		return (command);
	}
	else if ((ft_strnstr(command, "bin/", ft_strlen(command)) != NULL) && command[0] == 'b')
	{
		//printf("HERE 1\n");
		new_command_path = ft_strjoin("/usr/", command);
	}
	else if ((ft_strnstr(command, "/bin/", ft_strlen(command)) != NULL) && command[0] == '/')
	{
		//printf("HERE 2\n");
		new_command_path = ft_strjoin("/usr", command);
	}
	else if ((ft_strnstr(command, "usr/bin/", ft_strlen(command)) != NULL) && command[0] == 'u')
	{
		//printf("HERE 3\n");
		new_command_path = ft_strjoin("/", command);
	}
	else if ((ft_strnstr(command, "/", ft_strlen(command)) != NULL) && (ft_strnstr(command, "bin", 3) == NULL))
	{
		//printf("HERE 4\n");
		new_command_path = ft_strjoin("/usr/bin", command);
	}
	else
	{
		//printf("HERE 5\n");
		new_command_path = ft_strjoin("/usr/bin/", command);
	}
	//printf("VOICI LE COMMAND PATH = %s\n\n", new_command_path);
	return (new_command_path);
}

