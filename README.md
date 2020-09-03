# CaesarCipher
Implementation of Caesar Cipher in C using command line arguments.

## Compiling
`gcc CaesarCipher.c -o CaesarCipher`

## Executing
### Syntax:
`./CaesarCipher [OPTION] [KEY] [FILENAME]`

Type `./CaesarCipher` for opening the help section.

### Options:
`-e, --encrypt:` encrypting the file using the key, It create an encrypted file in the directory of the program.
`-d, --decrypt:` decrypting the file using the key, It create an decrypted file in the directory of the program.

### Key:
The key must be an integer number from 1 to 25.

### Filename:
The name of the file that will be encypted/decrypted.
