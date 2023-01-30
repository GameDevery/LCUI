﻿/*
 * css_fontstyle.c -- CSS font style parse and operation set.
 *
 * Copyright (c) 2018, Liu chao <lc-soft@live.cn> All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of LCUI nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdlib.h>
#include <LCUI/util.h>
#include <LCUI/font.h>
#include <LCUI/css.h>
#include <LCUI/ui.h>

static size_t unescape(const wchar_t *instr, wchar_t *outstr)
{
	int i = -1;
	wchar_t buff[6];
	wchar_t *pout = outstr;
	const wchar_t *pin = instr;

	for (; *pin; ++pin) {
		if (i >= 0) {
			buff[i++] = *pin;
			if (i >= 4) {
				buff[i] = 0;
				swscanf(buff, L"%hx", pout);
				++pout;
				i = -1;
			}
			continue;
		}
		if (*pin == L'\\') {
			i = 0;
			continue;
		}
		*pout++ = *pin;
	}
	if (i >= 4) {
		buff[i] = 0;
		swscanf(buff, L"%hx", pout);
		++pout;
	}
	*pout = 0;
	return pout - outstr;
}

static void ui_font_style_compute_size(ui_font_style_t *fs, css_unit_value_t *s)
{
	if (s->is_valid) {
		fs->font_size = ui_compute_actual(
		    y_max(UI_MIN_FONT_SIZE, s->value), s->unit);
		return;
	}
	fs->font_size = ui_compute_actual(UI_DEFAULT_FONT_SIZE, CSS_UNIT_PX);
}

static void ui_font_style_compute_color(ui_font_style_t *fs,
					css_unit_value_t *s)
{
	if (s->is_valid) {
		fs->color = s->color;
	} else {
		fs->color.value = UI_DEFAULT_FONT_COLOR;
	}
}

static void ui_font_style_compute_family(ui_font_style_t *fs,
					 css_unit_value_t *s)
{
	if (fs->font_ids) {
		free(fs->font_ids);
		fs->font_ids = NULL;
	}
	if (fs->font_family) {
		free(fs->font_family);
		fs->font_family = NULL;
	}
	if (!s->is_valid) {
		return;
	}
	fs->font_family = strdup2(s->string);
	fontlib_query(&fs->font_ids, fs->font_style, fs->font_weight,
			      fs->font_family);
}

static void ui_font_style_compute_style(ui_font_style_t *fs,
					css_unit_value_t *s)
{
	if (s->is_valid) {
		fs->font_style = s->val_int;
	} else {
		fs->font_style = FONT_STYLE_NORMAL;
	}
}

static void ui_font_style_compute_weight(ui_font_style_t *fs,
					 css_unit_value_t *s)
{
	if (s->is_valid) {
		fs->font_weight = s->val_int;
	} else {
		fs->font_weight = FONT_WEIGHT_NORMAL;
	}
}

static void ui_font_style_compute_text_align(ui_font_style_t *fs,
					     css_unit_value_t *s)
{
	if (s->is_valid) {
		fs->text_align = s->val_keyword;
	} else {
		fs->text_align = CSS_KEYWORD_LEFT;
	}
}

static void ui_font_style_compute_line_height(ui_font_style_t *fs,
					      css_unit_value_t *s)
{
	int h;
	if (s->is_valid) {
		if (s->unit == CSS_UNIT_INT) {
			h = y_iround(fs->font_size * s->val_int);
		} else if (s->unit == CSS_UNIT_SCALE) {
			h = y_iround(fs->font_size * s->val_scale);
		} else {
			h = ui_compute_actual(s->value, s->unit);
		}
	} else {
		h = y_iround(fs->font_size * UI_LINE_HEIGHT_SCALE);
	}
	fs->line_height = h;
}

static void ui_font_style_compute_content(ui_font_style_t *fs,
					  css_unit_value_t *s)
{
	size_t i;
	size_t len;
	wchar_t *content;

	if (fs->content) {
		free(fs->content);
		fs->content = NULL;
	}
	if (!s->is_valid) {
		return;
	}

	len = decode_utf8(NULL, s->val_string, 0);
	content = malloc((len + 1) * sizeof(wchar_t));
	len = decode_utf8(content, s->val_string, len);
	content[len] = 0;
	if (content[0] == '"') {
		for (i = 0; content[i + 1]; ++i) {
			content[i] = content[i + 1];
		}
		if (content[i - 1] != '"') {
			free(content);
			return;
		}
		content[i - 1] = 0;
	}
	unescape(content, content);
	fs->content = content;
}

static void ui_font_style_compute_white_space(ui_font_style_t *fs,
					      css_unit_value_t *s)
{
	if (s->is_valid && s->unit == CSS_UNIT_KEYWORD) {
		fs->white_space = s->val_keyword;
	} else {
		fs->white_space = CSS_KEYWORD_AUTO;
	}
}

void ui_font_style_init(ui_font_style_t *fs)
{
	fs->color.value = 0;
	fs->content = NULL;
	fs->font_ids = NULL;
	fs->font_family = NULL;
	fs->font_style = FONT_STYLE_NORMAL;
	fs->font_weight = FONT_WEIGHT_NORMAL;
}

void ui_font_style_destroy(ui_font_style_t *fs)
{
	if (fs->font_ids) {
		free(fs->font_ids);
		fs->font_ids = NULL;
	}
	if (fs->font_family) {
		free(fs->font_family);
		fs->font_family = NULL;
	}
	if (fs->content) {
		free(fs->content);
		fs->content = NULL;
	}
}

LCUI_BOOL ui_font_style_is_equal(const ui_font_style_t *a,
				 const ui_font_style_t *b)
{
	int i;

	if (a->color.value != b->color.value ||
	    a->line_height != b->line_height ||
	    a->text_align != b->text_align ||
	    a->white_space != b->white_space ||
	    a->font_style != b->font_style ||
	    a->font_weight != b->font_weight || a->font_size != b->font_size) {
		return FALSE;
	}
	if (a->font_family && b->font_family) {
		if (strcmp(a->font_family, b->font_family) != 0) {
			return FALSE;
		}
	} else if (a->font_family != b->font_family) {
		return FALSE;
	}
	if (a->content && b->content) {
		if (wcscmp(a->content, b->content) != 0) {
			return FALSE;
		}
	} else if (a->content != b->content) {
		return FALSE;
	}
	if (a->font_ids && b->font_ids) {
		for (i = 0; a->font_ids[i] && b->font_ids[i]; ++i) {
			if (a->font_ids[i] != b->font_ids[i]) {
				return FALSE;
			}
		}
	} else if (a->font_ids != b->font_ids) {
		return FALSE;
	}
	return TRUE;
}

void ui_font_style_compute(ui_font_style_t *fs, css_style_decl_t *style)
{
	ui_font_style_compute_color(fs, style->sheet + css_key_color);
	ui_font_style_compute_size(fs, style->sheet + css_key_font_size);
	ui_font_style_compute_family(fs, style->sheet + css_key_font_family);
	ui_font_style_compute_style(fs, style->sheet + css_key_font_style);
	ui_font_style_compute_weight(fs, style->sheet + css_key_font_weight);
	ui_font_style_compute_line_height(fs,
					  style->sheet + css_key_line_height);
	ui_font_style_compute_text_align(fs, style->sheet + css_key_text_align);
	ui_font_style_compute_white_space(fs,
					  style->sheet + css_key_white_space);
	ui_font_style_compute_content(fs, style->sheet + css_key_content);
}