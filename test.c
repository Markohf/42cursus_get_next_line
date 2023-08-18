#include "get_next_line.h"

int main()
{
    int fd;
    int y;

    y = 0;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file.\n");
        return (1);
    }
    while(y++ < 30)
        printf("%s", get_next_line(fd));
    if (close(fd) == -1)
    {
        printf("Error closing file.\n");
        return (1);
    }
    return (0);
}