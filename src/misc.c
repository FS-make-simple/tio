/*
 * tio - a serial device I/O tool
 *
 * Copyright (c) 2014-2022  Martin Lund
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

#include "config.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <sys/poll.h>
#include "error.h"
#include "print.h"
#include "options.h"

void delay(long ms)
{
    struct timespec ts;

    if (ms <= 0)
    {
        return;
    }

    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;

    nanosleep(&ts, NULL);
}

long string_to_long(char *string)
{
    long result;
    char *end_token;

    errno = 0;
    result = strtol(string, &end_token, 10);
    if ((errno != 0) || (*end_token != 0))
    {
        printf("Error: Invalid digit\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

int ctrl_key_code(unsigned char key)
{
    if ((key >= 'a') && (key <= 'z'))
    {
        return key & ~0x60;
    }

    return -1;
}

bool fs_dir_exists(const char *path)
{
    struct stat st;

    if (stat(path, &st) != 0)
    {
        return false;
    }
    else if (!S_ISDIR(st.st_mode))
    {
        return false;
    }

    return true;
}

bool regex_match(const char *string, const char *pattern)
{
    regex_t regex;
    int status;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0)
    {
        // No match
        return false;
    }

    status = regexec(&regex, string, (size_t) 0, NULL, 0);
    regfree(&regex);

    if (status != 0)
    {
        // No match
        return false;
    }

    // Match
    return true;
}

int read_poll(int fd, void *data, size_t len, int timeout)
{
    struct pollfd fds;
    int ret = 0;

    fds.events = POLLIN;
    fds.fd = fd;

    /* Wait data available */
    ret = poll(&fds, 1, timeout);
    if (ret < 0)
    {
        tio_error_print("%s", strerror(errno));
        return ret;
    }
    else if (ret > 0)
    {
        if (fds.revents & POLLIN)
        {
            // Read ready data
            return read(fd, data, len);
        }
    }

    /* Timeout */
    return ret;
}
