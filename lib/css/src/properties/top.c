﻿/*
 * lib/css/src/properties/top.c
 *
 * Copyright (c) 2023-2025, Liu Chao <i@lc-soft.io> All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file is part of LCUI, distributed under the MIT License found in the
 * LICENSE.TXT file in the root directory of this source tree.
 */

#include "../properties.h"
#include "./helpers.h"

static void set_top(css_computed_style_t* computed, uint8_t keyword,
		    css_numeric_value_t value, css_unit_t unit)
{
	computed->top = value;
	computed->unit_bits.top = unit;
	computed->type_bits.top = keyword;
}

int css_cascade_top(const css_style_array_value_t input,
		    css_computed_style_t* computed)
{
	return css_cascade_length_auto(input, computed, set_top);
}
