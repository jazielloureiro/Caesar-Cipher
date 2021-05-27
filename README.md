# Caesar Cipher

Implementation of Caesar Cipher in C.

## Installation

1. Clone this repository:

```sh
git clone https://github.com/jazielloureiro/Caesar-Cipher
```

2. Go into the new directory and compile the source code:

```sh
cd Caesar-Cipher && gcc caesar.c -o caesar
```

## Usage

```
caesar <options> <key> <input file> <output file>
caesar [-h | --help]
```

### Options:

`-e, --encrypt`: encrypt the input file using the key.

`-d, --decrypt`: decrypt the input file using the key.

`-h, --help`: print usage message.

### Key:

The key must be an integer number from 1 to 25.

## License

[MIT](https://github.com/jazielloureiro/Caesar-Cipher/blob/master/LICENSE)
