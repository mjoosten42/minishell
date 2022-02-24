/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:53:38 by mjoosten          #+#    #+#             */
/*   Updated: 2022/01/24 14:05:42 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int			ft_linelen(char *buf);
void		ft_rmline(char *buf);
static char	*ft_strsjoin(t_list **lst);
static int	ft_strslen(t_list **lst);
static void	del(void *content);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*str;
	int			bytes_read;
	t_list		*lst;

	if (read(fd, buf, 0) < 0 || *buf == 127)
		return (0);
	lst = 0;
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buf)));
	while (ft_linelen(buf) == -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (0);
		if (bytes_read < BUFFER_SIZE)
			buf[bytes_read] = 127;
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buf)));
	}
	ft_rmline(buf);
	str = ft_strsjoin(&lst);
	ft_lstclear(&lst, del);
	return (str);
}

static char	*ft_strsjoin(t_list **lst)
{
	char	*str;
	t_list	*ptr;
	int		i;

	if (!ft_strslen(lst))
		return (0);
	str = malloc(ft_strslen(lst) + 1);
	if (!str)
		return (0);
	ptr = *lst;
	while (ptr)
	{
		i = 0;
		while (*(char *)(ptr->content + i)
			&& *(char *)(ptr->content + i) != 127)
		{
			*str++ = *((char *)ptr->content + i);
			if (*(char *)(ptr->content + i) == '\n')
				break ;
			i++;
		}
		ptr = ptr->next;
	}
	*str = 0;
	return (str - ft_strslen(lst));
}

static int	ft_strslen(t_list **lst)
{
	t_list	*ptr;
	int		len;
	int		i;

	len = 0;
	ptr = *lst;
	while (ptr)
	{
		i = 0;
		while (*(char *)(ptr->content + i)
			&& *(char *)(ptr->content + i) != 127)
		{
			if (*(char *)(ptr->content + i) == '\n')
				return (len + 1);
			i++;
			len++;
		}
		ptr = ptr->next;
	}
	return (len);
}

static void	del(void *content)
{
	free(content);
}
