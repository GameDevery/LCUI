#include "../../include/css/computed.h"
#include "../../include/css/properties.h"
#include "./helpers.h"

static void set_bottom(css_computed_style_t* computed, uint8_t keyword,
		       css_numeric_value_t value, css_unit_t unit)
{
	computed->bottom = value;
	computed->unit_bits.bottom = unit;
	computed->type_bits.bottom = keyword;
}

int css_cascade_bottom(const css_style_array_value_t input,
		       css_computed_style_t* computed)
{
	return css_cascade_length_auto(input, computed, set_bottom);
}
