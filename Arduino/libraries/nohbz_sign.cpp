#include "nohbz_sign.h"
#include <Adafruit_NeoPixel.h>

#define PIN 8


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_SIZE, PIN, NEO_GRB + NEO_KHZ800);

uint32_t full_strip_color[num_colors] = {0}; 
colors ch[20]; 

void strip_init(void)
{
	strip.setBrightness(100);
    strip.begin();
    strip.show(); 
    
    ch[black].red = 0;
    ch[black].green = 0;
    ch[black].blue = 0;
    full_strip_color[black] = strip.Color(0, 0, 0);
    ch[white].red = 255;
    ch[white].green = 255;
    ch[white].blue = 255;
    full_strip_color[white] = strip.Color(255, 255, 255);
    ch[red].red = 255;
    ch[red].green = 0;
    ch[red].blue = 0;
    full_strip_color[red] = strip.Color(255, 0, 0);
    ch[blue].red = 0;
    ch[blue].green = 0;
    ch[blue].blue = 255;
    full_strip_color[blue] = strip.Color(0, 0, 255);
    ch[green].red = 0;
    ch[green].green = 255;
    ch[green].blue = 0;
    full_strip_color[green] = strip.Color(0, 255, 0);
    ch[orange].red = 255;
    ch[orange].green = 165;
    ch[orange].blue = 0;
    full_strip_color[orange] = strip.Color(255, 165, 0);
    ch[yellow].red = 255;
    ch[yellow].green = 255;
    ch[yellow].blue = 0;
    full_strip_color[yellow] = strip.Color(255, 255, 0);
    ch[indigo].red = 75;
    ch[indigo].green = 0;
    ch[indigo].blue = 138;
    full_strip_color[indigo] = strip.Color(75, 0, 138);
    ch[violet].red = 238;
    ch[violet].green = 138;
    ch[violet].blue = 238;
    full_strip_color[violet] = strip.Color(238, 138, 238);
    ch[cyan].red = 0;
    ch[cyan].green = 255;
    ch[cyan].blue = 255;
    full_strip_color[cyan] = strip.Color(0, 255, 255);
    ch[magenta].red = 255;
    ch[magenta].green = 0;
    ch[magenta].blue = 255;
    full_strip_color[magenta] = strip.Color(255, 0, 255);
    ch[lime].red = 0;
    ch[lime].green = 255;
    ch[lime].blue = 0;
    full_strip_color[lime] = strip.Color(0, 255, 0);
    ch[maroon].red = 128;
    ch[maroon].green = 0;
    ch[maroon].blue = 0;
    full_strip_color[maroon] = strip.Color(128, 0, 0);
    ch[olive].red = 128;
    ch[olive].green = 128;
    ch[olive].blue = 0;
    full_strip_color[olive] = strip.Color(128, 128, 0);
    ch[chocolate].red = 210;
    ch[chocolate].green = 105;
    ch[chocolate].blue = 30;
    full_strip_color[chocolate] = strip.Color(210, 105, 30);
    ch[gold].red = 255;
    ch[gold].green = 215;
    ch[gold].blue = 0;
    full_strip_color[gold] = strip.Color(255, 215, 30);
    for(int i = 0; i < STRIP_SIZE; i++)
    {
		strip.setPixelColor(i, ch[black].red, ch[black].green, ch[black].blue);
    }
}


void strip_turn_off_pixel(uint16_t pixel)
{
	strip.setPixelColor(pixel, ch[black].red, ch[black].green, ch[black].blue);
	strip.show();
}


void strip_turn_on_pixel(uint16_t pixel, color_list_e color)
{
	strip.setPixelColor(pixel, ch[color].red, ch[color].green, ch[color].blue);
	strip.show();
}


void show_strip(void)
{
	strip.show();
}


void strip_set_brightness(uint8_t brightness)
{
	strip.setBrightness(brightness);
	strip.begin();
}


letters_in_sign_t draw_letter(letters_in_sign_t letter, color_list_e color)
{
    uint16_t lower_bound = 0;
    uint16_t upper_bound = 0;
    switch(letter)
    {
        case N_LETTER:
            lower_bound = N_LEFT_POST_PIXEL_NUM_START;
            upper_bound = N_RIGHT_POST_PIXEL_NUM_STOP;
        break;
        case O_LETTER:
            lower_bound = O_PIXEL_NUM_START;
            upper_bound = O_PIXEL_NUM_STOP;
        break;
        case H_LETTER:
            lower_bound = H_LEFT_POST_PIXEL_NUM_START;
            upper_bound = H_MID_PIXEL_NUM_STOP;
        break;
        case B_LETTER:
            lower_bound = B_LEFT_POST_PIXEL_NUM_START;
            upper_bound = B_MID_PIXEL_NUM_STOP;
        break;
        case Z_LETTER:
            lower_bound = Z_TOP_POST_PIXEL_NUM_START;
            upper_bound = Z_BOTTOM_POST_PIXEL_NUM_STOP;
        break;
        default:
            return;
        break;
    }
    for(int i = lower_bound; i <= upper_bound; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    }
    strip.show();
    return letter;
}


void draw_letters(color_list_e color, uint16_t delay_time)
{
    letters_in_sign_t letter = N_LETTER;
    while(Z_LETTER != draw_letter(letter, color))
    {
        letter = (uint8_t)letter + 1;
        delay(delay_time);
    }
}


void draw_word(color_list_e color, uint16_t strip_size, bool spell, uint32_t delay_time)
{
	if(!spell) strip.clear();
    for(int i = 0; i < strip_size; i++)
    {
        strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
        if(spell) 
        {
        	strip.show();
        	delay(delay_time);
        }
    }
    strip.show();
}


void blink_word(color_list_e color, uint16_t strip_size, uint16_t delay_time)
{
	strip.fill(full_strip_color[color], 0, strip_size);
	strip.show();
	delay(delay_time);
	strip.clear();
	strip.show();
	delay(delay_time);
}


void fade_letter_l_to_r(letters_in_sign_t letter, color_list_e color, uint16_t delay_time)
{
    uint16_t o_forward_count = 0;
    uint16_t o_backward_count = 0;
    uint8_t b_backward_count = 0;
    uint8_t b_forward_count = 0;
    switch(letter)
    {
    	case N_LETTER:
    		for(int i = N_LEFT_POST_PIXEL_NUM_START; i <= N_LEFT_POST_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();
    		for(int i = N_MID_POST_PIXEL_NUM_START; i <= N_MID_POST_PIXEL_NUM_STOP; i++)
    		{
    			delay(delay_time);
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();
    		}
    		for(int i = N_RIGHT_POST_PIXEL_NUM_START; i <= N_RIGHT_POST_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();
    	break;
    	
    	case O_LETTER:
    		for(int i = 0; i <= O_PIXEL_NUM_FROM_TOP_TO_MID; i++)
    		{
    			delay(delay_time);
    			strip.setPixelColor(O_PIXEL_NUM_LEFT_START + o_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(O_PIXEL_NUM_LEFT_START - o_backward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();
    		}
    		o_backward_count = 0;
    		for(int i = 0; i <= O_PIXEL_NUM_FROM_TOP_TO_MID; i++)
    		{
    			delay(delay_time);
    			strip.setPixelColor(O_PIXEL_NUM_STOP - o_backward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(O_PIXEL_NUM_LEFT_START + o_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.setPixelColor(O_PIXEL_NUM_LEFT_START + o_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.show();
    	break;
    	
    	case H_LETTER:
    		for(int i = H_LEFT_POST_PIXEL_NUM_START; i <= H_LEFT_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();  
			for(int i = H_MID_PIXEL_NUM_START; i <= H_MID_PIXEL_NUM_STOP; i++)
			{
				delay(delay_time);
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();  
			}	
    	break;
    	
    	case B_LETTER:
    		for(int i = B_LEFT_POST_PIXEL_NUM_START; i <= B_LEFT_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();  
    		for(int i = 0; i <= B_TOP_CURVE_TO_MID; i++)
			{
				delay(delay_time);
				strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_backward_count++, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(B_MID_PIXEL_NUM_START + b_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();  
			}	
    	break;
    	
    	case Z_LETTER:
    		for(int i = 0; i <= Z_POST_LENGTH; i++)
    		{
    			delay(delay_time);
				strip.setPixelColor(Z_TOP_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(Z_BOTTOM_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();  
    		}
    	break;
    	default:
    	break;
    }
}


void fade_letter_r_to_l(letters_in_sign_t letter, color_list_e color, uint16_t delay_time)
{
    uint16_t o_forward_count = 0;
    uint16_t o_backward_count = 0;
    uint8_t b_backward_count = 0;
    uint8_t b_forward_count = 0;
    switch(letter)
    {
    	case N_LETTER:
    		for(int i = N_RIGHT_POST_PIXEL_NUM_START; i <= N_RIGHT_POST_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();
    		for(int i = N_MID_POST_PIXEL_NUM_STOP; i >= N_MID_POST_PIXEL_NUM_START; i--)
    		{
    			delay(delay_time);
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();
    		}
    		for(int i = N_LEFT_POST_PIXEL_NUM_START; i <= N_LEFT_POST_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();
    	break;
    	
    	case O_LETTER:
    		for(int i = 0; i <= O_PIXEL_NUM_FROM_TOP_TO_MID; i++)
    		{
    			delay(delay_time);
    			strip.setPixelColor(O_PIXEL_NUM_RIGHT_START + o_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(O_PIXEL_NUM_RIGHT_START - o_backward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();
    		}
    		o_forward_count = 0;
    		for(int i = 0; i <= O_PIXEL_NUM_FROM_TOP_TO_MID; i++)
    		{
    			delay(delay_time);
    			strip.setPixelColor(O_PIXEL_NUM_RIGHT_START - o_backward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(O_PIXEL_NUM_START + o_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();
    		}
    		strip.setPixelColor(O_PIXEL_NUM_START + o_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.show();
    	break;
    	
    	case H_LETTER:
    		for(int i = H_MID_PIXEL_NUM_STOP; i >= H_MID_PIXEL_NUM_START; i--)
    		{
    			delay(delay_time);
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show(); 
    		}
			for(int i = H_LEFT_POST_PIXEL_NUM_START; i <= H_LEFT_POST_PIXEL_NUM_STOP; i++)
			{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
			}	
    		strip.show();  
    	break;
    	
    	case B_LETTER:
    		for(int i = 0; i <= B_TOP_CURVE_TO_MID; i++)
			{
				delay(delay_time);
				strip.setPixelColor(B_MID_POINT_PIXEL_NUM - b_backward_count++, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(B_MID_POINT_PIXEL_NUM + b_forward_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();  
			}	
			for(int i = B_LEFT_POST_PIXEL_NUM_START; i <= B_LEFT_POST_PIXEL_NUM_STOP; i++)
    		{
				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		strip.show();  
    	break;
    	
    	case Z_LETTER:
    		for(int i = 0; i <= Z_POST_LENGTH; i++)
    		{
    			delay(delay_time);
				strip.setPixelColor(Z_TOP_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(Z_MID_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(Z_BOTTOM_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
    			strip.show();  
    		}
    	break;
    	default:
    	break;
    }
}


void fade_word_bottom_to_top(color_list_e color, uint16_t delay_time)
{
	// top to bottom..
	uint8_t h_tail_count = 0;
	uint8_t b_tail_count = 0;
	uint8_t o_tail_count = 0;
	uint8_t z_tail_count = 0;
	uint8_t n_tail_count = 0;
	for(int i = 0; i <= VERTICAL_POST_NUM_PIXELS; i++)
	{
		delay(delay_time);
		strip.setPixelColor(N_LEFT_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(N_RIGHT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
    	strip.setPixelColor(H_LEFT_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(H_MID_PIXEL_NUM_STOP - h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(B_LEFT_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);    		
		strip.setPixelColor(N_MID_POST_PIXEL_NUM_STOP - n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
		if(0 == i)
    	{
    		strip.setPixelColor(N_MID_POST_PIXEL_NUM_STOP - n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		for(int i = 0; i <= Z_POST_LENGTH; i++)
    		{
    			if(i < 5)
    			{
					strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				}
				strip.setPixelColor(Z_BOTTOM_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
    		} 
    		strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
    	}
    	else if(i <= 4)
    	{
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
			
			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		if(4 == i)
    		{
    			strip.setPixelColor(N_MID_POST_PIXEL_NUM_STOP - n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				strip.setPixelColor(Z_MID_POST_PIXEL_NUM_STOP - z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			for(int i = Z_TOP_POST_PIXEL_NUM_STOP; i >= Z_TOP_POST_PIXEL_NUM_START; i--)
    			{
					strip.setPixelColor(B_MID_PIXEL_NUM_STOP - b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
					strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
					strip.setPixelColor(H_MID_PIXEL_NUM_STOP - h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			}
    		}
    	}
    	else if(5 == i)
    	{
    		strip.setPixelColor(O_PIXEL_NUM_BOTTOM_LEFT - o_tail_count, ch[color].red, ch[color].green, ch[color].blue);    		
			strip.setPixelColor(O_PIXEL_NUM_BOTTOM_RIGHT + o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
    			
    	}
    	strip.show(); 
	}
}


void fade_word_top_to_bottom(color_list_e color, uint16_t delay_time)
{
	// top to bottom..
	uint8_t h_tail_count = 0;
	uint8_t b_tail_count = 0;
	uint8_t o_tail_count = 0;
	uint8_t z_tail_count = 0;
	uint8_t n_tail_count = 0;
	for(int i = 0; i <= VERTICAL_POST_NUM_PIXELS; i++)
	{
		delay(delay_time);
		strip.setPixelColor(N_LEFT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(N_RIGHT_POST_PIXEL_NUM_STOP - i, ch[color].red, ch[color].green, ch[color].blue);
    	strip.setPixelColor(H_LEFT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(B_LEFT_POST_PIXEL_NUM_START + i, ch[color].red, ch[color].green, ch[color].blue);
		strip.setPixelColor(N_MID_POST_PIXEL_NUM_START + n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
    	if(VERTICAL_POST_NUM_PIXELS == i)
    	{
    		for(int i = Z_BOTTOM_POST_PIXEL_NUM_START; i <= Z_BOTTOM_POST_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
    		for(int i = B_MID_PIXEL_NUM_START + b_tail_count; i <= B_MID_PIXEL_NUM_STOP; i++)
    		{
    			strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
    		}
			strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.show();
    	}
    	if(i >= TOP_TO_TAIL_NUM_PIXELS)
    	{
    		strip.setPixelColor(H_MID_PIXEL_NUM_START + h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(B_MID_PIXEL_NUM_START + b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    		strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    		if(TOP_TO_TAIL_NUM_PIXELS == i)
    		{
				strip.setPixelColor(O_PIXEL_NUM_START + o_tail_count, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(O_PIXEL_NUM_STOP - o_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			for(int i = Z_TOP_POST_PIXEL_NUM_START; i <= Z_TOP_POST_PIXEL_NUM_STOP; i++)
    			{
    				strip.setPixelColor(i, ch[color].red, ch[color].green, ch[color].blue);
				}
				for(int i = B_MID_PIXEL_NUM_START; i <= B_MID_PIXEL_NUM_START + 4; i++)
				{
    				strip.setPixelColor(B_MID_PIXEL_NUM_START + b_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				}
				for(int i = H_MID_PIXEL_NUM_START; i <= H_MID_PIXEL_NUM_START + 4; i++)
				{
    				strip.setPixelColor(H_MID_PIXEL_NUM_START + h_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
				}
			}
			else
			{
				strip.setPixelColor(N_MID_POST_PIXEL_NUM_START + n_tail_count++, ch[color].red, ch[color].green, ch[color].blue);    		
				strip.setPixelColor(Z_MID_POST_PIXEL_NUM_START + z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
    			strip.setPixelColor(Z_MID_POST_PIXEL_NUM_START + z_tail_count++, ch[color].red, ch[color].green, ch[color].blue);
			}
    	}
    	strip.show(); 
	}
}


void fade_word(color_list_e color, uint16_t delay_time, bool l_to_r)
{
    if(l_to_r)
    {
        fade_letter_l_to_r(N_LETTER, color, delay_time);
        fade_letter_l_to_r(O_LETTER, color, delay_time);
        fade_letter_l_to_r(H_LETTER, color, delay_time);
        fade_letter_l_to_r(B_LETTER, color, delay_time);
        fade_letter_l_to_r(Z_LETTER, color, delay_time);
    }
    else
    {
        fade_letter_r_to_l(Z_LETTER, color, delay_time);
        fade_letter_r_to_l(B_LETTER, color, delay_time);
        fade_letter_r_to_l(H_LETTER, color, delay_time);
        fade_letter_r_to_l(O_LETTER, color, delay_time);
        fade_letter_r_to_l(N_LETTER, color, delay_time);
    }
}


#if 0
void crash(color_list_e color_left, color_list_e color_right, color_list_e blend_color, uint16_t delay_time)
{
	// not a huge fan of all the locals here, but crash gets complicated..
	uint16_t o_g_forward_count = 0;
    uint16_t o_g_backward_count = 0;
    uint16_t o_g_backward_count_2 = 0;
    uint16_t r_forward_count = 0;
	uint16_t r_backward_count = 0;
	uint16_t e_backward_count = 0;
	uint16_t h_backward_count = 0;
	uint8_t every_other_count = 1;
	
    for(int i = T_FIRST_PIXEL_NUM_START; i < T_FIRST_PIXEL_NUM_MID; i++)
    {
        delay(delay_time);
        strip.setPixelColor(i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(R_CURVE_RIGHT_MID_START + r_forward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        strip.setPixelColor(R_CURVE_RIGHT_MID_START - r_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        strip.setPixelColor(R_PIXEL_NUM_STOP - r_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        strip.show();
    }
    for(int i = T_FIRST_PIXEL_NUM_STOP; i >= T_FIRST_PIXEL_NUM_STOP - T_FIRST_MID_POST_LENGTH; i--)
    {
        strip.setPixelColor(i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
    }
    strip.setPixelColor(R_CURVE_RIGHT_MID_START + r_forward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    strip.setPixelColor(R_CURVE_RIGHT_MID_START - r_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    strip.setPixelColor(R_PIXEL_NUM_STOP - r_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    strip.show();
    for(int i = T_FIRST_PIXEL_NUM_START + T_FIRST_PIXEL_NUM_MID; i <= T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH; i++)
    {
        delay(delay_time);
        strip.setPixelColor(i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(R_CURVE_RIGHT_MID_START - r_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    	strip.setPixelColor(R_CURVE_RIGHT_MID_START + r_forward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    	strip.setPixelColor(R_PIXEL_NUM_STOP - r_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        strip.show();
    }
    for(int i = R_PIXEL_NUM_START; i <= R_PIXEL_NUM_START + R_LEFT_POST_LENGTH; i++)
    {
        strip.setPixelColor(i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    	
    }
    strip.show();
    
    for(int i = 0; i <= O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID; i++)
    {
        delay(delay_time);
        strip.setPixelColor(O_PIXEL_NUM_LEFT_MID - o_g_backward_count++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(O_PIXEL_NUM_LEFT_MID + o_g_forward_count++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        if(every_other_count)
        {
        	strip.setPixelColor(E_LAST_TOP_POST_START + E_LAST_COMMON_POST_LENGTH - e_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
            strip.setPixelColor(E_LAST_MID_POST_START + E_LAST_COMMON_POST_LENGTH - e_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
            strip.setPixelColor(E_LAST_BOTTOM_POST_START + E_LAST_COMMON_POST_LENGTH - e_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        }
        every_other_count ^= 1;
        strip.show();
    }
    o_g_backward_count = 0; // only reset backward count
    for(int i = 0; i <= E_LAST_COMMON_POST_LENGTH; i++)
    {
        delay(delay_time);
        strip.setPixelColor(O_PIXEL_NUM_STOP - o_g_backward_count++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(O_PIXEL_NUM_LEFT_MID + o_g_forward_count++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        if(every_other_count)
        {
        	strip.setPixelColor(E_LAST_TOP_POST_START + E_LAST_COMMON_POST_LENGTH - e_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        	strip.setPixelColor(E_LAST_MID_POST_START + E_LAST_COMMON_POST_LENGTH - e_backward_count, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        	strip.setPixelColor(E_LAST_BOTTOM_POST_START + E_LAST_COMMON_POST_LENGTH - e_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        }
        every_other_count ^= 1;
        strip.show();
    }
    for(int i = E_LAST_LEFT_POST_START; i <= E_LAST_LEFT_POST_START + E_LAST_LEFT_POST_LENGTH; i++)
    {
        strip.setPixelColor(i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    }
    strip.show();

    o_g_backward_count = 0;
    o_g_forward_count = 0;
    for(int i = 0; i <= O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID; i++)
    {
        delay(delay_time);
        strip.setPixelColor(G_PIXEL_NUM_LEFT_MID - (o_g_backward_count++), ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(G_PIXEL_NUM_LEFT_MID + (o_g_forward_count++), ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        if(!i)
        {
            for(int i = H_RIGHT_PIXEL_NUM_START; i <= H_PIXEL_NUM_STOP; i++)
    		{
    		    strip.setPixelColor(i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    		}
        }
        if(every_other_count)
        {
        	strip.setPixelColor(H_MID_PIXEL_NUM_START + H_MID_POST_LENGTH - h_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        }
        every_other_count ^= 1;
        strip.show();
    }
    o_g_backward_count_2 = 0;
    for(int i = 0; i < O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID; i++)
    {
        delay(delay_time);
        if(!((G_PIXEL_NUM_LEFT_MID - (o_g_backward_count)) < O_PIXEL_NUM_STOP))
        {
            strip.setPixelColor(G_PIXEL_NUM_LEFT_MID - o_g_backward_count++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        }
        strip.setPixelColor(G_PIXEL_NUM_LEFT_MID + o_g_forward_count++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(G_PIXEL_NUM_STOP - o_g_backward_count_2++, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        if(every_other_count)
        {
        	strip.setPixelColor(H_MID_PIXEL_NUM_START + H_MID_POST_LENGTH - h_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        	strip.show();
        }
        every_other_count ^= 1;
        if(O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID - 1 == i)
        {
        	strip.setPixelColor(H_MID_PIXEL_NUM_START + H_MID_POST_LENGTH - h_backward_count++, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        	for(int i = H_PIXEL_NUM_START; i <= H_PIXEL_NUM_START + H_RIGHT_POST_LENGTH; i++)
    		{
        		strip.setPixelColor(i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    		}
        }
        strip.show();
    }
    o_g_backward_count = 0;
    o_g_forward_count = 0;
    for(int i = E_FIRST_PIXEL_NUM_START; i < E_FIRST_PIXEL_NUM_START + 12; i++)
    {
        strip.setPixelColor(i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
    }
    strip.show();
    for(int i = 0; i <= E_FIRST_COMMON_POST_LENGTH; i++)
    {
        delay(delay_time);
        strip.setPixelColor(E_FIRST_TOP_POST_START + i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(E_FIRST_MID_POST_START + i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        strip.setPixelColor(E_FIRST_BOTTOM_POST_START + i, ch[color_left].red, ch[color_left].green, ch[color_left].blue);
        if(i < T_LAST_PIXEL_NUM_MID - T_LAST_PIXEL_NUM_START)
        {
        	strip.setPixelColor(T_LAST_PIXEL_NUM_START + T_LAST_TOP_POST_LENGTH - i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        }
        else if((T_LAST_PIXEL_NUM_MID - T_LAST_PIXEL_NUM_START) == i)
        {
        	strip.setPixelColor(T_LAST_PIXEL_NUM_START + T_LAST_TOP_POST_LENGTH - i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        	for(int j = T_LAST_MID_POST_PIXEL_NUM_START; j <= T_LAST_MID_POST_PIXEL_NUM_START + T_LAST_MID_POST_LENGTH; j++)
    		{
       	 		strip.setPixelColor(j, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
    		}
        }
        else
        {
        	strip.setPixelColor(T_LAST_PIXEL_NUM_START + T_LAST_TOP_POST_LENGTH - i, ch[color_right].red, ch[color_right].green, ch[color_right].blue);
        }
        strip.show();
    }    
    // blend time.. 
    e_backward_count = 0;
    for(int i = T_LAST_PIXEL_NUM_START; i < T_LAST_PIXEL_NUM_MID; i++)
    {
        delay(delay_time);
        strip.setPixelColor(i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(E_FIRST_TOP_POST_START + E_FIRST_COMMON_POST_LENGTH - 1 - e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(E_FIRST_MID_POST_START + E_FIRST_COMMON_POST_LENGTH  - 1 - e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(E_FIRST_BOTTOM_POST_START + E_FIRST_COMMON_POST_LENGTH - 1 - e_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.show();
    }
	strip.setPixelColor(T_LAST_PIXEL_NUM_MID, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    for(int i = T_LAST_MID_POST_PIXEL_NUM_START; i <= T_LAST_MID_POST_PIXEL_NUM_START + T_LAST_MID_POST_LENGTH; i++)
    {
        strip.setPixelColor(i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    }
    strip.show();
    for(int i = T_LAST_PIXEL_NUM_MID; i <= T_LAST_PIXEL_NUM_START + T_LAST_TOP_POST_LENGTH; i++)
    {
        delay(delay_time);
        strip.setPixelColor(i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(E_FIRST_TOP_POST_START + E_FIRST_COMMON_POST_LENGTH - 1 - e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(E_FIRST_MID_POST_START + E_FIRST_COMMON_POST_LENGTH  - 1 - e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(E_FIRST_BOTTOM_POST_START + E_FIRST_COMMON_POST_LENGTH - 1 - e_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.show();
    }
	for(int i = 0; i <= E_FIRST_LEFT_POST_LENGTH; i++)
    {
        strip.setPixelColor(E_FIRST_LEFT_POST_START + i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    }
	strip.show();
	
    h_backward_count = 0;
    o_g_backward_count = 0;
    o_g_forward_count = 0;
    for(int i = 0; i < O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID; i++)
    {
        delay(delay_time);
        strip.setPixelColor(G_PIXEL_NUM_RIGHT_MID + o_g_forward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(G_PIXEL_NUM_RIGHT_MID - o_g_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(G_PIXEL_NUM_START + o_g_forward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        if(!i)
        {
        	for(int j = H_PIXEL_NUM_START; j <= H_PIXEL_NUM_START + H_LEFT_POST_LENGTH; j++)
    		{
       	 		strip.setPixelColor(j, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    		}
        }
        if(every_other_count)
        {
        	strip.setPixelColor(H_MID_PIXEL_NUM_START + h_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        }
        every_other_count ^= 1;
        strip.show();
    }
    every_other_count = 1;
    for(int i = O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID; i < 16; i++)
    {
        delay(delay_time);
        strip.setPixelColor(G_PIXEL_NUM_RIGHT_MID - o_g_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(G_PIXEL_NUM_START + o_g_forward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        if(H_MID_PIXEL_NUM_START + h_backward_count < H_RIGHT_PIXEL_NUM_START)
        {
        	if(every_other_count)
        	{
        		strip.setPixelColor(H_MID_PIXEL_NUM_START + h_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	}
        }
        every_other_count ^= 1;
        strip.show();
    }
    strip.setPixelColor(H_MID_PIXEL_NUM_START + h_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
	for(int i = H_RIGHT_PIXEL_NUM_START; i <= H_RIGHT_PIXEL_NUM_START + H_RIGHT_POST_LENGTH; i++)
    {
        strip.setPixelColor(i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    }  
    strip.show();
	o_g_backward_count = 0;
	e_backward_count = 0;
    for(int i = 0; i <= E_LAST_COMMON_POST_LENGTH; i++)
    {
        delay(delay_time);
        strip.setPixelColor(O_PIXEL_NUM_RIGHT_MID - i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(O_PIXEL_NUM_RIGHT_MID + i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        if(!i)
        {
        	for(int j = E_LAST_PIXEL_NUM_START; j <= E_LAST_PIXEL_NUM_START + E_LAST_LEFT_POST_LENGTH; j++)
    		{
        		strip.setPixelColor(j, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    		}
        }
        if(every_other_count)
        {
        	strip.setPixelColor(E_LAST_TOP_POST_START + e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	strip.setPixelColor(E_LAST_MID_POST_START + e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	strip.setPixelColor(E_LAST_BOTTOM_POST_START + e_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        }
        every_other_count ^= 1;
        strip.show();
    }
    for(int i = 0; i <= O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID; i++)
    {
        delay(delay_time);
        strip.setPixelColor(O_PIXEL_NUM_RIGHT_MID - O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID - i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(O_PIXEL_NUM_START + i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        if(every_other_count)
        {
        	strip.setPixelColor(E_LAST_TOP_POST_START + e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	strip.setPixelColor(E_LAST_MID_POST_START + e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	strip.setPixelColor(E_LAST_BOTTOM_POST_START + e_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        }
        if(O_PIXEL_NUM_PIXELS_TO_TOP_BOTTOM_FROM_MID == i)
        {
        	strip.setPixelColor(E_LAST_TOP_POST_START + e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	strip.setPixelColor(E_LAST_MID_POST_START + e_backward_count, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        	strip.setPixelColor(E_LAST_BOTTOM_POST_START + e_backward_count++, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        }
        every_other_count ^= 1;
    	strip.show();
    }
	o_g_backward_count = 0;
    o_g_forward_count = 0;
    for(int i = R_PIXEL_NUM_START; i <= R_PIXEL_NUM_START + R_LEFT_POST_LENGTH; i++)
    {
        strip.setPixelColor(i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    }
	strip.setPixelColor(T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    strip.show();
    for(int i = 0; i <= T_FIRST_TOP_POST_LENGTH + 1; i++)
    {
        delay(delay_time);
        strip.setPixelColor(R_CURVE_PIXEL_NUM_START + i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(R_CURVE_PIXEL_NUM_STOP - i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        strip.setPixelColor(R_END_POST_PIXEL_NUM_START + i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        if((T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH - i) == T_FIRST_PIXEL_NUM_MID)
        {
        	for(int j = T_FIRST_MID_POST_PIXEL_NUM_START; j <= T_FIRST_MID_POST_PIXEL_NUM_START + T_FIRST_MID_POST_LENGTH; j++)
    		{
        		strip.setPixelColor(j, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
    		}
    		strip.setPixelColor(T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH - i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        }
        else if((T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH - i) >= T_FIRST_PIXEL_NUM_START)
        {
    		strip.setPixelColor(T_FIRST_PIXEL_NUM_START + T_FIRST_TOP_POST_LENGTH - i, ch[blend_color].red, ch[blend_color].green, ch[blend_color].blue);
        }
        strip.show();
    }
 	return;
} 

#endif