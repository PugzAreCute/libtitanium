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

int uname(struct utsname *buf){
	if(DEBUG) printf("[LibTitanium] uname() called.\n");

	int (*uname_syscall)(struct utsname *buffer) = dlsym(RTLD_NEXT, "uname");
	int exit_code = uname_syscall(buf);

	char* release = getenv("TITANIUM_RELEASE") ?: buf->release;
	char* version = getenv("TITANIUM_VERSION") ?: buf->version;
	char* architecture = getenv("TITANIUM_ARCHITECTURE") ?: buf->machine;
	char* sysname = getenv("TITANIUM_SYSNAME") ?: buf->sysname;

	if(exit_code == 0){
		strncpy(buf->release, release, sizeof(buf->release));
		strncpy(buf->version, version, sizeof(buf->version));
		strncpy(buf->machine, architecture, sizeof(buf->machine));
		strncpy(buf->sysname, sysname, sizeof(buf->sysname));
	} else {
		if(DEBUG) printf("[LibTitanium] SYSCALL ERROR! %d\n", exit_code);
	}

	return exit_code;
}
