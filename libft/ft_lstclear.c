/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:31:20 by zanikin           #+#    #+#             */
/*   Updated: 2024/01/29 16:54:05 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*next;

	if (lst && del)
	{
		cur = *lst;
		while (cur)
		{
			next = cur->next;
			ft_lstdelone(cur, del);
			cur = next;
		}
		*lst = 0;
	}
}
