/* 42 HEADER */

#ifndef RUSH02_H
# define RUSH02_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_dict
{
	char	*key;
	char	*value;
}			t_dict;

/* Utils */
void		ft_putstr(char *str);
int			ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *src);

/* Other func prototypes */

#endif
