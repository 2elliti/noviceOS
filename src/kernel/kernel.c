#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif


#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */



uint8_t intro_array[168] = {	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0,0,
				1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,
				1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,
				1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,
				1,0,1,0,1,1,1,0,0,1,0,0,1,1,1,0,1,1,1,0,0};

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;


void fill_the_screen(){	
	uint8_t bg = VGA_COLOR_MAGENTA;
	uint8_t fg = VGA_COLOR_WHITE;
	uint8_t attribute = bg << 4 | fg;
	
	unsigned char ch = ' ';
	
	uint16_t pixel = attribute << 8 | ch;
	size_t i;
	for(i=0;i<VGA_WIDTH*VGA_HEIGHT;i++){
		terminal_buffer[i] = pixel;
	}
}


void initialize_screen(){

	terminal_buffer = (uint16_t *)0xB8000;
	fill_the_screen();

}

uint16_t get_pixel(char ch){
	uint8_t bg = VGA_COLOR_MAGENTA;
	uint8_t fg = VGA_COLOR_WHITE;
	uint8_t attribute = bg << 4 | fg;
	return attribute << 8 | ch;
}


void vprintc(char ch){
	uint16_t pixel = get_pixel(ch);
	terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = pixel;
}

size_t _strlen(char *str){
	size_t len = 0;
	while(str[len]){
		len++;
	}
	return len;
}



void scroll_up(){
	
	for(int i =0;i <= 1919; i++){
		terminal_buffer[i] = terminal_buffer[i+80];
	}
	char ch = ' ';
	uint16_t pixel = get_pixel(ch);
	for(int i = 1920;i<1999;i++){
		terminal_buffer[i] = pixel;
	}
	
}



void vprintstr(char *str){
	size_t i;
	size_t str_size = _strlen(str);
	for(i = 0;i<str_size;i++){
		if(str[i] == '\n'){
			terminal_column = 0;
			terminal_row++;
			continue;
		}
		else if(str[i] == '\t'){
			if(terminal_column == VGA_WIDTH){
				terminal_row++;
				terminal_column = 0;
				continue;
			}
			terminal_column = terminal_column + 8;
			continue;
		}
		vprintc(str[i]);
		terminal_column++;
	}
	if(terminal_row == VGA_HEIGHT){
		terminal_row = VGA_HEIGHT-1;
		scroll_up();
	}
}




void kernel_main(){
	initialize_screen();
	
	// For VGA 
	vprintstr("This is noviceOs.\n");
	vprintstr("Under Construction.\n");
	
	vprintstr("This is line 2.\n");
	vprintstr("This is line 3.\n");
	vprintstr("This is line 4.\n");
	vprintstr("This is line 5.\n");
	vprintstr("This is line 6.\n");
	vprintstr("This is line 7.\n");
	vprintstr("This is line 8.\n");
	vprintstr("This is line 9.\n");
	vprintstr("This is line 10.\n");
	vprintstr("This is line 11.\n");
	vprintstr("This is line 12.\n");
	vprintstr("This is line 13.\n");
	vprintstr("This is line 14.\n");
	vprintstr("This is line 15.\n");
	vprintstr("This is line 16.\n");
	vprintstr("This is line 17.\n");
	vprintstr("This is line 18.\n");
	vprintstr("This is line 19.\n");
	vprintstr("This is line 20.\n");
	vprintstr("This is line 21.\n");
	vprintstr("This is line 22.\n");
	vprintstr("This is line 23.\n");
	vprintstr("This is line 24.\n");
	vprintstr("This is line 25.\n");
	for(int i = 0;i< 20; i++){
		vprintstr("Covered them lol\n");
	}
	// Things to do -> add support for scrollup feature.

	

}
