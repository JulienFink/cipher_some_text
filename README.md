cipher_some_text
=============================

Simple encryption and decryption (AES-ECB) of some text providing a 256 bit key and a 128 bit IV  ✔️

------------------------------------
### Compilation :

Just compile the files :
```
make
```

------------------------------------
### Usage :

Command example :
```
./simple_cipher -k 4894be88e41188c40abc703fb3ba1195 -p "Some text" -v 023446789012145
```

Output:
```
Ciphertext is:
39860a7aa1d17b7a9beb13dcba8dc250

Decrypted text is:
Some text
```

