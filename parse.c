/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/01 20:03:15 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"cub.h"

//check extention

int check_exet(char *str,char *exe)
{
    int len_all;
    int len_exe;
    
    len_all = ft_strlen(str);
    len_exe = ft_strlen(exe);

    while(len_all > len_exe)
    {
        str++;
        len_all--;
        
    }
    return(ft_strncmp(str,exe,len_all));
}

int check_before_map(char *path)
{
    int fd;
   static char *str;
   char *line;

   fd = open(path,O_RDONLY);
   while(line)
   {
     str = ft_strjoin(str,line);
     line = get_next_line(fd);
     if(line && line[0] == '\n')
     {
        write(1,"Error\n",6);
        exit(0);
     }
     free(line);
   }
   close(fd);
   return(str);
}
