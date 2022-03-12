/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:19 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 16:04:37 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy_list;
	t_list	*mapped_block;

	copy_list = NULL;
	while (lst != NULL && f != NULL)
	{
		mapped_block = ft_lstnew(f(lst->content));
		if (mapped_block == NULL)
		{
			ft_lstclear(&copy_list, del);
			return (NULL);
		}
		ft_lstadd_back(&copy_list, mapped_block);
		lst = lst->next;
	}
	return (copy_list);
}
