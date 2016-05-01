/*
 * Go TTY - The Really Simple Terminal Application
 *
 * Copyright (c) 2014-2016  Martin Lund
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "gotty/options.h"
#include "gotty/print.h"

static FILE *fp;
static bool error = false;

void log_open(char *filename)
{
    fp = fopen(filename, "w+");

    if (fp == NULL)
    {
        error = true;
        exit(EXIT_FAILURE);
    }
}

void log_write(char c)
{
    if (fp != NULL)
        fputc(c, fp);
}

void log_close(void)
{
    if (fp != NULL)
        fclose(fp);
}

void log_exit(void)
{
    if (option.log)
        log_close();

    if (error)
        printf("Error: Could not open log file %s (%s)\n", option.log_filename, strerror(errno));
}
