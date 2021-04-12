# CaesarCipher
Implementation of Caesar Cipher in C using command line arguments.

## Install
1. Clone this repository:

`$ git clone https://github.com/jazielloureiro/Caesar-Cipher`

2. Go into the respository directory:

`$ cd Caesar-Cipher`

3. And then, compile the source code:

`gcc CaesarCipher.c -o CaesarCipher`

## Usage
### Syntax:
`./CaesarCipher [OPTION] [KEY] [INPUT FILE] [OUTPUT FILE]`

### Options:
`-e, --encrypt:` encrypting the input file using the key, It create an encrypted output file in the directory of the program.

`-d, --decrypt:` decrypting the input file using the key, It create a decrypted output file in the directory of the program.

`-h, --help:` show this help and exit.

### Key:
The key must be an integer number from 1 to 25.
