#include <stdio.h>
#include <string.h>

#define OPTION argv[1]
#define KEY argv[2]
#define FILENAME argv[3]

#define MAX_KEY_SIZE 2
#define CONTROL_KEY 26
#define ROW_SIZE 200

#define ENCRYPT 'e'
#define DECRYPT 'd'

#define FAILED 1
#define INVALID_KEY 0

unsigned char convert_key(char key[]){
	unsigned char converted_key = 0, key_length = strnlen(key, MAX_KEY_SIZE + 1);
	
	if(key_length <= MAX_KEY_SIZE){
		char decimal_place = 1, i;
	
		for(i = key_length - 1; i >= 0; i--){
			if(key[i] < '0' || key[i] > '9'){
				converted_key = INVALID_KEY;
				break;
			}else{
				converted_key += (key[i] - '0') * decimal_place;
				decimal_place *= 10;
			}
		}
	}
	
	if(converted_key < 1 || converted_key > 25){
		puts("You've entered an invalid key.");
		return INVALID_KEY;
	}else
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
	FILE *text_file;
	
	if(key == INVALID_KEY)
		return;
	
	if(init_text_file(FILENAME, &text_file) == FAILED)
		return;
		
	if(operation == ENCRYPT){
		FILE *encrypted_file;
		
		if(init_encrypted_file(&encrypted_file) == FAILED)
			return;
	
		encrypt(&text_file, &encrypted_file, key);
		
		fclose(encrypted_file);
	}else{
		FILE *decrypted_file;
	
		if(init_decrypted_file(&decrypted_file) == FAILED)
			return;
	
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
