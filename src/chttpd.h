#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#pragma once

struct log_config
{
    char *log_path;
};

typedef struct config
{
    bool log_on;
    bool fork_on;
    struct log_config log_config;
} Config;
