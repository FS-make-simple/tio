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

#pragma once

#include <stdbool.h>
#include <stdio.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

char * current_time(void);
void delay(long ms);
long string_to_long(char *string);
int ctrl_key_code(unsigned char key);
void alert_connect(void);
void alert_disconnect(void);
bool fs_dir_exists(const char *path);
bool regex_match(const char *string, const char *pattern);
int read_poll(int fd, void *data, size_t len, int timeout);
