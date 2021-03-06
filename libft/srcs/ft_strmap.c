/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:20:27 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*s1;
	size_t	i;

	i = 0;
	s1 = NULL;
	s1 = (char *)malloc((ft_strlen(s) + 1) * sizeof(*s1));
	if (s1 == NULL)
		return (s1);
	while (s[i] != '\0')
	{
		s1[i] = (*f)(s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
