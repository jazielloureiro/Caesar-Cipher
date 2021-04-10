#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTION argv[1]
#define KEY argv[2]
#define FILENAME argv[3]

#define ENCRYPT 'e'
#define DECRYPT 'd'

#define CONTROL_KEY 26
#define ROW_SIZE 200

unsigned char convert_key(char *key){
	unsigned char converted_key = atoi(key);
	
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

void encrypt(FILE **text_file, FILE **encrypted_file, unsigned char key){
	unsigned char row_text[ROW_SIZE];

	while(fgets(row_text, ROW_SIZE, *text_file) != NULL){
		for(unsigned char *i = row_text; *i != '\0'; i++){
			if(*i >= 'A' && *i <= 'Z'){
				*i += key;
				
				if(*i > 'Z')
					*i -= CONTROL_KEY;
			}
			if(*i >= 'a' && *i <= 'z'){
				*i += key;
				
				if(*i > 'z')
					*i -= CONTROL_KEY;
			}
		}
		
		fputs(row_text, *encrypted_file);
	}
}

void decrypt(FILE **text_file, FILE **decrypted_file, unsigned char key){
	unsigned char row_text[ROW_SIZE];
	
	while(fgets(row_text, ROW_SIZE, *text_file) != NULL){
		for(unsigned char *i = row_text; *i != '\0'; i++){
			if(*i >= 'A' && *i <= 'Z'){
				*i -= key;
				
				if(*i < 'A')
					*i += CONTROL_KEY;
			}
			if(*i >= 'a' && *i <= 'z'){
				*i-= key;
				
				if(*i < 'a')
					*i += CONTROL_KEY;
			}
		}
		
		fputs(row_text, *decrypted_file);
	}
}

void help(){
	puts("Syntax:\v./CaesarCipher [OPTION] [KEY] [FILENAME]"
	     "\n\nOptions:\v"
	     "-e, --encrypt:\vencrypting the file using the key, It create an encrypted file in the directory of the program.\n\t"
	     "-d, --decrypt:\vdecrypting the file using the key, It create an decrypted file in the directory of the program.\n"
	     "\nKey: It must be an integer number from 1 to 25.\n"
	     "\nFilename: the name of the file that will be encypted/decrypted.");
}

void encryption(char **argv, char operation){
	unsigned char key = convert_key(KEY);
	FILE *text_file = init_file(FILENAME, "r");
		
	if(operation == ENCRYPT){
		FILE *encrypted_file = init_file("encrypted.txt", "w");
		
		encrypt(&text_file, &encrypted_file, key);
		
		fclose(encrypted_file);
	}else{
		FILE *decrypted_file = init_file("decrypted.txt", "w");
	
		decrypt(&text_file, &decrypted_file, key);
		
		fclose(decrypted_file);
	}
	
	fclose(text_file);
}

int main(int argc, char **argv){
	if(argc == 1)
		help();
	else if(argc > 4)
		puts("You've entered too many arguments.");
	else if(strcmp(OPTION, "-e") == 0 || strcmp(OPTION, "--encrypt") == 0)
		encryption(argv, ENCRYPT);
	else if(strcmp(OPTION, "-d") == 0 || strcmp(OPTION, "--decrypt") == 0)
		encryption(argv, DECRYPT);
	else
		puts("You've entered an invalid option.");

	return 0;
}
