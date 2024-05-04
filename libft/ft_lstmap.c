/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:43:17 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/27 20:13:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_cur;

	new_cur = 0;
	if (lst)
	{
		new_cur = ft_lstnew(f(lst->content));
		new_list = new_cur;
		lst = lst->next;
	}
	while (lst && new_cur)
	{
		new_cur->next = ft_lstnew(f(lst->content));
		new_cur = new_cur->next;
		lst = lst->next;
	}
	if (!new_cur)
		ft_lstclear(&new_list, del);
	return (new_list);
}
