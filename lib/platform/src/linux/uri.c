﻿/*
 * lib/platform/src/linux/uri.c: -- uri processing
 *
 * Copyright (c) 2018-2023, Liu chao <lc-soft@live.cn> All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file is part of LCUI, distributed under the MIT License found in the
 * LICENSE.TXT file in the root directory of this source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../app.h"

#ifdef LIBPLAT_LINUX

int open_uri(const char *uri)
{
	char cmd[512] = { 0 };
	snprintf(cmd, 511, "xdg-open %s", uri);
	return system(cmd);
}

#endif
