/* 42 HEADER */

#include "rush02.h"

char	*read_file(int fd, long *file_size)
{
	char	buff[4096];
	char	*content;
	long	total_read;
	int		bytes_read;
	
	total_read = 0;
	while ((bytes_read = read(fd, buff, 4096)) > 0)
		total_read += bytes_read;
	*file_size = total_read;
	close(fd);
	
	content = malloc(sizeof(char) * (total_read + 1));
	if (!content)
		return (NULL);
		
	fd = open("numbers.dict", O_RDONLY);
	read(fd, content, total_read);
	content[total_read] = '\0';
	close(fd);
	return (content);
}
