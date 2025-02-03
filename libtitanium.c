/*
 *
 * libTitanium - Library for faking the uname() syscall
 * 
 * Copyright (C) 2025 PugzAreCute
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 3 of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#define _GNU_SOURCE
#include <sys/utsname.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef RELEASE
#define DEBUG true
#else
#define DEBUG false
#endif

#define RELEASE "500.250.125"
#define VERSION "#234 libtitanium DYNAMIC Sun, 6 Jun 2077 00:30:00 +9999"
#define ARCHITECTURE "arm128" // Early access.
#define SYSNAME "TitaniumOS"

int uname(struct utsname *buf){
	if(DEBUG) printf("[LibTitanium] uname() called.\n");

	char* release = getenv("TITANIUM_RELEASE");
	char* version = getenv("TITANIUM_VERSION");
	char* architecture = getenv("TITANIUM_ARCHITECTURE");
	char* sysname = getenv("TITANIUM_SYSNAME");

	int (*uname_syscall)(struct utsname *buffer) = dlsym(RTLD_NEXT, "uname");
	int exit_code = uname_syscall(buf);

	if(exit_code == 0){
		strncpy(buf->release, release ?: RELEASE, sizeof(buf->release));
		strncpy(buf->version, version ?: VERSION, sizeof(buf->version));
		strncpy(buf->machine, architecture ?: ARCHITECTURE, sizeof(buf->machine));
		strncpy(buf->sysname, sysname ?: SYSNAME, sizeof(buf->sysname));
	} else {
		if(DEBUG) printf("[LibTitanium] SYSCALL ERROR! %d\n", exit_code);
	}

	return exit_code;
}
