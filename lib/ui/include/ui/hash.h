#ifndef LIB_UI_INCLUDE_UI_HASH_H
#define LIB_UI_INCLUDE_UI_HASH_H

#include "common.h"
#include "types.h"

LIBUI_BEGIN_DECLS

LIBUI_PUBLIC void ui_widget_generate_self_hash(ui_widget_t *widget);
LIBUI_PUBLIC void ui_widget_generate_hash(ui_widget_t *w);
LIBUI_PUBLIC size_t ui_widget_export_hash(ui_widget_t *w, unsigned *hash_list,
				      size_t len);
LIBUI_PUBLIC size_t ui_widget_import_hash(ui_widget_t *w, unsigned *hash_list,
				      size_t maxlen);

LIBUI_END_DECLS

#endif