#include <stdio.h>
#include <string.h>

#define OPTION argv[1]
#define KEY argv[2]
#define FILENAME argv[3]

#define CONTROL_KEY 26
#define ROW_SIZE 200

#define FAILED 1
#define INVALID_KEY 0

unsigned char convert_key(char key[]){
	unsigned char converted_key = 0, i;
	
	for(i = 0; key[i] != '\0'; i++)
		if(key[i] < '0' || key[i] > '9'|| i > 1)
			return INVALID_KEY;
			
	if(i == 1)
		converted_key += key[0] - '0';
	else{
		converted_key += key[1] - '0';
		converted_key += (key[0] - '0') * 10;
	}
	
	if(converted_key < 1 || converted_key > 25)
		return INVALID_KEY;
	else
		return converted_key;
}

char init_text_file(char filename[], FILE **text_file){
	*text_file = fopen(filename, "r");

	if(*text_file == NULL){
		printf("It wasn't possible to open %s\n", filename);
		return FAILED;
	}
}

char init_encrypted_file(FILE **encrypted_file){
	*encrypted_file = fopen("encrypted.txt", "w");

	if(*encrypted_file == NULL){
		puts("It wasn't possible to create the encrypted file.");
		return FAILED;
	}
}

char init_decrypted_file(FILE **decrypted_file){
	*decrypted_file = fopen("decrypted.txt", "w");

	if(*decrypted_file == NULL){
		puts("It wasn't possible to create the decrypted file.");
		return FAILED;
	}
}

void encrypting(FILE **text_file, FILE **encrypted_file, unsigned char key){
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

void decrypting(FILE **text_file, FILE **decrypted_file, unsigned char key){
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

void encrypt(char **argv){
	FILE *text_file, *encrypted_file;
	unsigned char key = convert_key(KEY);
	
	if(key == INVALID_KEY){
		puts("You've entered an invalid key.");
		return;
	}
	
	if(init_text_file(FILENAME, &text_file) == FAILED)
		return;
	
	if(init_encrypted_file(&encrypted_file) == FAILED)
		return;
	
	encrypting(&text_file, &encrypted_file, key);
	
	fclose(text_file);
	fclose(encrypted_file);
}

void decrypt(char **argv){
	FILE *text_file, *decrypted_file;
	unsigned char key = convert_key(KEY);
	
	if(key == INVALID_KEY){
		puts("You've entered an invalid key.");
		return;
	}
	
	if(init_text_file(FILENAME, &text_file) == FAILED)
		return;
	
	if(init_decrypted_file(&decrypted_file) == FAILED)
		return;
	
	decrypting(&text_file, &decrypted_file, key);
	
	fclose(text_file);
	fclose(decrypted_file);
}

int main(int argc, char **argv){
	if(argc == 1)
		help();
	else if(argc > 4)
		puts("You've entered too many arguments.");
	else if(strcmp(OPTION, "-e") == 0 || strcmp(OPTION, "--encrypt") == 0)
		encrypt(argv);
	else if(strcmp(OPTION, "-d") == 0 || strcmp(OPTION, "--decrypt") == 0)
		decrypt(argv);
	else
		puts("You've entered an invalid option.");

	return 0;
}
