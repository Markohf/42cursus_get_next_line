#include "get_next_line.h"

int main()
{
    int fd;
    int y;

    y = 1;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file.\n");
        return (1);
    }
    while(y > 0)
    {
        printf("y1=%i\n", y);
        y = printf("%s", get_next_line(fd));
        printf("y2=%i\n", y);
    }
    if (close(fd) == -1)
    {
        printf("Error closing file.\n");
        return (1);
    }
    return (0);
}