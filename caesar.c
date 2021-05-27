#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPT 'e'
#define DECRYPT 'd'

uint8_t convert_key(char *key){
	uint8_t converted_key = atoi(key);
	
	if(converted_key < 1 || converted_key > 25){
		puts("Error: invalid key.\nTry 'caesar --help'");
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
	puts("Usage:\n"
	     "  caesar <options> <key> <input file> <output file>\n"
	     "  caesar [-h | --help]\n\n"
	     "Options:\n"
	     "  -e, --encrypt  Encrypt the input file using the key.\n"
	     "  -d, --decrypt  Decrypt the input file using the key.\n"
	     "  -h, --help     Print usage message.\n\n"
	     "Key: It must be an integer number from 1 to 25.");
}

int main(int argc, char **argv){
	if(argc == 1)
		help();
	else if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
		help();
	else if(argc != 5)
		puts("Error: invalid number of arguments.\nTry 'caesar --help'");
	else if(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0)
		encryption(argv, ENCRYPT);
	else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0)
		encryption(argv, DECRYPT);
	else
		puts("Error: unrecognized option.\nTry 'caesar --help'");

	return 0;
}
