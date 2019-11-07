#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H

#define _GNU_SOURCE
extern char *program_invocation_name;
extern char *program_invocation_short_name;
#define MAJORV 0
#define MINORV 3

#define CRED  "\x1b[31m"
#define CRSET "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <errno.h>

#include "config.h"
#include "fileread.h"
#include "ds_memsim.h"
#include "ds_table.h"

//#pragma message __FILE__
#endif // INCLUDE_MAIN_H