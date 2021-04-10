#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPT 'e'
#define DECRYPT 'd'

uint8_t convert_key(char *key){
	uint8_t converted_key = atoi(key);
	
	if(converted_key < 1 || converted_key > 25){
		puts("You've entered an invalid key.");
		exit(EXIT_FAILURE);
	}
	
	return converted_key;
}

FILE *init_file(char *filename, char *mode){
	FILE *file = fopen(filename, mode);

	if(file == NULL){
		printf("It wasn't possible to open the file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	return file;
}

void encryption(char **argv, char operation){
	const uint8_t CONTROL_KEY = 26;
	uint8_t key = convert_key(argv[2]);
	FILE *input = init_file(argv[3], "r"),
	     *output = init_file(argv[4], "w");

	while(1){
		uint8_t buffer = fgetc(input);

		if(feof(input))
			break;
		if(buffer >= 'A' && buffer <= 'Z' || buffer >= 'a' && buffer <= 'z'){
			if(operation == ENCRYPT){
				buffer += key;
				
				if(buffer > 'Z' && buffer - key <= 'Z' || buffer > 'z')
					buffer -= CONTROL_KEY;
			}else{
				buffer -= key;
				
				if(buffer < 'A' || buffer < 'a' && buffer + key >= 'a')
					buffer += CONTROL_KEY;
			}
		}
		
		fputc(buffer, output);
	}

	fclose(input);
	fclose(output);
}

void help(){
	puts("Syntax:\n\t./CaesarCipher [OPTION] [KEY] [INPUT FILE] [OUTPUT FILE]"
	     "\n\nOptions:\n\t"
	     "-e, --encrypt:\n\t\tencrypting the input file using the key,\n\t\t"
	     "It create an encrypted output file in the directory of the program.\n\t"
	     "-d, --decrypt:\n\t\tdecrypting the input file using the key,\n\t\t"
	     "It create a decrypted output file in the directory of the program.\n\t"
	     "-h, --help:\n\t\tshow this help and exit.\n"
	     "\nKey: It must be an integer number from 1 to 25.");
}

int main(int argc, char **argv){
	if(argc > 5)
		puts("You've entered too many arguments.");
	else if(argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		help();
	else if(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0)
		encryption(argv, ENCRYPT);
	else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0)
		encryption(argv, DECRYPT);
	else
		puts("You've entered an invalid option.");

	return 0;
}
