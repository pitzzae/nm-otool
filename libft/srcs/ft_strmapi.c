/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:54:17 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 17:00:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		s1[i] = (*f)((unsigned int)s[i], (char)i);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
