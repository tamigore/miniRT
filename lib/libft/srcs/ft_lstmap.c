/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:06:18 by tamigore          #+#    #+#             */
/*   Updated: 2019/11/06 15:04:51 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_p(void *p, t_list *lst, void (*del)(void *))
{
	if (!p)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	return (p);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	p = ft_lstnew(f(lst->content));
	if (!free_p(p, lst, del))
		return (NULL);
	tmp = p;
	lst = lst->next;
	while (lst)
	{
		p->next = ft_lstnew(f(lst->content));
		if (!free_p(p->next, lst, del))
			return (NULL);
		lst = lst->next;
		p = p->next;
	}
	p = tmp;
	return (p);
}
