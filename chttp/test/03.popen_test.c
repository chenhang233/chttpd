#include <stdio.h>

int main()
{
    FILE *fp = popen("ls -l", "r");
    if (!fp)
    {
        perror("popen fail: ");
    }
    printf("1111\n");
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        printf("%s", buf);
    }

    pclose(fp);
    return 0;
}
