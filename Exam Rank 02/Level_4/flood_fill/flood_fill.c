#include "flood_fill.h"

void	flood_fill(char **tab, t_point size, t_point begin)
{
	while (begin.y < size.y)
	{
		while (begin.x < size.x)
		{
			if (tab[begin.y][begin.x] == '1')
				tab[begin.y][begin.x] = 'F';
			begin.x++;
		}
		begin.x = 0;
		begin.y++;
	}
}
