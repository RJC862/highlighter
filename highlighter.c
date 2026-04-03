#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

/*
This is the implementation of the highlighter program.
Please read the documentation in the README before you start working on this file.
*/

// Color codes to use in your program. Print a color first, then your text, then the reset color.
static const char* COLOR_RED = "\033[0;31m";
static const char* COLOR_GREEN = "\033[0;32m";
static const char* COLOR_BLUE = "\033[0;34m";
static const char* COLOR_YELLOW = "\033[1;33m";
static const char* COLOR_MAGENTA = "\033[0;35m";
static const char* COLOR_CYAN = "\033[0;36m";
static const char* COLOR_WHITE = "\033[1;37m";
static const char* COLOR_RESET_COLOR = "\033[0m";


// These function prototypes / definitions are suggestions but not required to implement.
// typedef struct Settings with fields FILE*/handle input_stream, output_stream; strings search_text, prefix, postfix; and boolean no_color;
// void print_help()
// void print_error(const char* error_message)
// void output_final_result(int count, const char* search_text)
// const char* get_color_code(const char* color_str)
// int process_args(int argc, char* argv[], Settings* settings)
// int parse_line(Settings* settings, char* line)
// ...

typedef struct Settings{
	FILE *input_stream, *output_stream;
	char *search_text, *prefix, *postfix, *color_str;
	bool no_color;
} Settings;

void print_help(){

	// prints the help menu for the application
	
	printf("usage: ./highlighter [-h] [-i INPUT] [-o OUTPUT] [-c {RED,GREEN,BLUE,YELLOW,MAGENTA,CYAN,WHITE}] [--no-color] [--prefix PREFIX] [--postfix POSTFIX] text\n\n"
		"highlighter\n\n"

		"positional arguments:\n"
		"  text			text to match and highlight\n\n"

		"options:\n"
		"-h, -- help 		show this help message and exit\n"
		"-i INPUT, --input INPUT\n"
		"			input file (default:stdin)\n"
		"-o OUTPUT, --output OUTPUT\n"
		"			output file (default: stdout)\n"
		"-c {RED,GREEN,BLUE,YELLOW,MAGENTA,CYAN,WHITE}, --color {RED,GREEN,BLUE,YELLOW,MAGENTA,CYAN,WHITE}\n"
		"			color option (default: RED)\n"
		"--no-color		do not print color\n"
		"--prefix PREFIX	print prefix before highlighted text (default: empty string)\n"
		"--postfix POSTFIX 	print postfix after highlighted text (default: empty string)\n\n"

		"examples:\n"
		" ./highlighter -i file.txt \"error\" (highlights \"error\" in file.txt in red via STDOUT)\n"
		" ./highlighter -c GREEN \"warning\" (highlights \"warning\" in green from STDIN to STDOUT)\n"
		" ./highlighter --prefix \">>\" --postfix \"<<\" \"keyword\" -o out.txt (highlights \"keyword\" with prefix \">>\" and postfix \"<<\" in red from STDIN to out.txt)\n");
}


void print_error(const char* error_message){
	// printing error message
	printf("Error: %s\n", error_message);
}

void output_final_result(int count, const char *search_text){
	//code
}


const char *get_color_code(const char *color_str){
	//code
}

int process_args(int argc, char *argv[], Settings *settings){

	// sets data fields in the settings struct
	
	// tracking positional argument count
	int positional_arguments = 0;

	// parsing command line arguments
	for (int i = 1; i < argc; i++){

		// identifying arguments

		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){

			// printing the help menu then exiting
	    		print_help();
			return 0;

		} else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0){

			// opening the input file for reading
			
			// checking that there exists an argument after the flag
			if (i + 1 < argc){
		    		settings->input_stream = fopen(argv[i+1], "r");
				i += 1;
			} else {
				print_error("Missing file argument");
				return -1;
			}
			
			// checking that the file exists
			if (settings->input_stream == NULL) {
				print_error("Invalid file name");
				return -1;
			}

		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0){

			// opening output file for writing
			
			//checking that there exists an argument after the flag
			if (i + 1 < argc){
				settings->output_stream = fopen(argv[i+1], "w");
				i += 1;
			} else {
				print_error("Missing file argument");
				return -1;
			}

			// checking that the file exists
			if (settings->output_stream == NULL){
				print_error("Invalid file name");
				return -1;
			}

		} else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--color") == 0){
			// setting the highlight color

			// checking that there is an argument after the flag
			if (i+1<argc){
				// checking that the color is valid
				
				    if (strcmp(argv[i+1], "GREEN") == 0){
					    settings->color_str = "GREEN";
				    } else if (strcmp(argv[i+1],"BLUE") == 0){
					    settings->color_str = "BLUE";
				    } else if(strcmp(argv[i+1], "YELLOW") == 0){
					    settings->color_str = "YELLOW";
				    } else if (strcmp(argv[i+1], "MAGENTA") == 0){
					    settings->color_str = "MAGENTA";
				    } else if (strcmp(argv[i+1], "WHITE") == 0){
					    settings->color_str = "WHITE";
				    } else if (strcmp(argv[i+1], "RED") == 0){
					    settings->color_str = "RED";
				    } else{
					    print_error("Invalid color");
					    return -1;
				    }
			} else {
				print_error("Missing color argument");
				return -1;
			}

		} else if (strcmp(argv[i], "--no-color")==0){

			// disabling color printing

			settings->no_color = true;

		} else if (strcmp(argv[i], "--prefix")==0){

			// setting the prefix

			// checking that there is an argument after the flag
			if (i + 1 < argc){
				settings->prefix = argv[i+1];
			} else {
				print_error("Missing prefix argument");
				return -1;
			}

		} else if (strcmp(argv[i], "--postfix") == 0){

			// setting the postfix
			
			// checking that there is an argument after the flag
			if (i + 1 < argc){
				settings->postfix = argv[i+1];
			} else {
				print_error("Missing postfix argument");
				return -1;
			}

		} else {
			// setting the text to highlight
			
			// checking if there already exists a chosen text to highlight
			if (positional_arguments >= 1){
				print_error("Only one positional argument allowed");
				return -1;
			}

			settings->search_text = argv[i];

			positional_arguments++;
		}
	}

	// checking if there exists a text to highlight
	if (positional_arguments == 0){
		print_error("Missing text to highlight");
		return -1;
	}

	// successful parsing
	return 0;
}

int main (int argc, char *argv[]){
	Settings settings = {	
		.input_stream = stdin, 
		.output_stream = stdout, 
		.color_str = "RED", 
		.search_text = "", 
		.prefix = "", 
		.postfix = "", 
		.no_color = false};

	int process_args_status = process_args(argc, argv, &settings);

	return 0;
}
