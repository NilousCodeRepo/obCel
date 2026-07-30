#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define BASH_RED(word) "\x1B[31m" word "\x1B[0m"
#define BASH_GREEN(word) "\x1B[32m" word "\x1B[0m"
#define BASH_BLUE(word) "\x1B[34m" word "\x1B[0m"
#define BASH_MAGENTA(word) "\x1B[35m" word "\x1B[0m"
#define BASH_YELLOW(word) "\x1B[93m" word "\x1B[0m"
#define LOG_SIZE 512
