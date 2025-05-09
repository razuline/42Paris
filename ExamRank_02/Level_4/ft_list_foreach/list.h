#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}			t_list;