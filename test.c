#include "get_next_line.h"

int main()
{
    int     fd;
    int     y;
    char    *line;

    y = 0;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file.\n");
        return (1);
    }
    while(y++ < 3)
    {
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
    }
    if (close(fd) == -1)
    {
        printf("Error closing file.\n");
        return (1);
    }
    return (0);
}