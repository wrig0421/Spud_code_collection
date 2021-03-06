// Spud 2021

#include <Arduino.h>
#include "color_led.h"

// static definitions
#define COLOR_LED_MAX_BRIGHTNESS_DIVISOR	(10)

// global variables
color_hex_code_e g_color_hex_codes[NUM_COLORS];;
all_colors_e g_led_color = COLORS_RED;


void color_led_init(void)
{
    g_color_hex_codes[COLORS_RED] = COLOR_HEX_RED;
    g_color_hex_codes[COLORS_WHITE] = COLOR_HEX_WHITE;
    g_color_hex_codes[COLORS_LIME] = COLOR_HEX_LIME;
    g_color_hex_codes[COLORS_BLUE] = COLOR_HEX_BLUE;
    g_color_hex_codes[COLORS_YELLOW] = COLOR_HEX_YELLOW;
    g_color_hex_codes[COLORS_CYAN] = COLOR_HEX_CYAN;
    g_color_hex_codes[COLORS_MAGENTA] = COLOR_HEX_MAGENTA;
    g_color_hex_codes[COLORS_GREEN] = COLOR_HEX_GREEN;
    g_color_hex_codes[COLORS_PURPLE] = COLOR_HEX_PURPLE;
    g_color_hex_codes[COLORS_TEAL] = COLOR_HEX_TEAL;
    g_color_hex_codes[COLORS_NAVY] = COLOR_HEX_NAVY;
}


void color_led_reset_color(void)
{
	g_led_color = COLORS_RED;
}


bool color_led_adjust_color(void)
{
	bool return_val = false;
	if (COLORS_LAST == g_led_color) 
	{
		g_led_color = COLORS_FIRST;
		return_val = true;
	}
	else g_led_color = (all_colors_e) (g_led_color + 1);
	return return_val;
}


color_hex_code_e color_led_cur_color_hex(void)
{
	return g_color_hex_codes[g_led_color];
}


uint8_t color_led_white_hex(void)
{
	return (0xFF / COLOR_LED_MAX_BRIGHTNESS_DIVISOR);
}


uint8_t color_led_cur_color_red_hex(void)
{
	return (((g_color_hex_codes[g_led_color] & 0xFF0000) >> 16) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR);
}


uint8_t color_led_cur_color_green_hex(void)
{
	return (((g_color_hex_codes[g_led_color] & 0x00FF00) >> 8) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR);
}


uint8_t color_led_cur_color_blue_hex(void)
{
	return ((g_color_hex_codes[g_led_color] & 0x0000FF) / COLOR_LED_MAX_BRIGHTNESS_DIVISOR);
}


color_hex_code_e color_led_hex(all_colors_e color)
{
	return g_color_hex_codes[color];
}


void color_led_randomize(void)
{
	all_colors_e color = (all_colors_e)(random(NUM_COLORS));
	if (g_led_color == color)
    {
        if ((COLORS_LAST) == color) g_led_color = (all_colors_e)(color - 1);
        else g_led_color = (all_colors_e)(color + 1);
    }
	else
	{
		g_led_color = color;
	}
}

