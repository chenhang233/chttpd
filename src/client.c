#include "client.h"
#include <stdio.h>
#include <fcntl.h>

void c_config_init()
{
    // ...
}

void c_config_parse()
{
    const char *path = conf.file;
    FILE *c;
    char line[512];
    if (!path)
        path = "../config.conf";
    c = open(path, "r");
    if (!c)
        return;
}