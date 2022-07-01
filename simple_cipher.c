
/* -------------------------------------------------------------------------- */
/* --- DEPENDENCIES --------------------------------------------------------- */

#include <unistd.h>
#include <string.h>

#include <openssl/err.h>
#include <openssl/evp.h>

/* -------------------------------------------------------------------------- */
/* --- GLOBAL VARIABLES ----------------------------------------------------- */

unsigned char* plain;

// 256 bit key
unsigned char* key;

// 128 bit key
unsigned char* iv;

/* -------------------------------------------------------------------------- */
/* --- FUNCTIONS ------------------------------------------------------------ */

// Function for printing bytes as hexadecimal
void printBytes(unsigned char *buf, size_t len) 
{
	for(int i=0; i<len; i++)
		printf("%02x", buf[i]);
	printf("\n\n");
}

void what_is_my_error(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int cipher_text(unsigned char *plain, int plain_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new()))
        what_is_my_error();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv))
        what_is_my_error();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plain, plain_len))
        what_is_my_error();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        what_is_my_error();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int uncipher_text(unsigned char *cipher, int cipher_len, unsigned char *key, unsigned char *iv, unsigned char *plain)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plain_len;

    if(!(ctx = EVP_CIPHER_CTX_new()))
        what_is_my_error();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv))
        what_is_my_error();

    if(1 != EVP_DecryptUpdate(ctx, plain, &len, cipher, cipher_len))
        what_is_my_error();
    plain_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plain + len, &len))
        what_is_my_error();
    plain_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plain_len;
}

/* -------------------------------------------------------------------------- */
/* --- MAIN FUNCTION -------------------------------------------------------- */

int main(int argc, char **argv)
{
	// GET ARGS
	int c;
	while ((c = getopt (argc, argv, "k:p:v:")) != -1) 
	{
		switch (c)
		{
			case 'k':
				key = optarg;
				break;
			case 'p':
				plain = optarg;
				break;
			case 'v':
				iv = optarg;
		}
	}

    unsigned char cipher[128];

    unsigned char decrypted[128];

    int decrypted_len, cipher_len;

    cipher_len = cipher_text(plain, strlen ((char *)plain), key, iv, cipher);

    printf("Ciphertext is:\n");
    //BIO_dump_fp (stdout, (const char *)cipher, cipher_len);

    printBytes(cipher, cipher_len);

    decrypted_len = uncipher_text(cipher, cipher_len, key, iv, decrypted);

    /* Add a NULL terminator. We are expecting printable text */
    decrypted[decrypted_len] = '\0';

    printf("Decrypted text is:\n");
    printf("%s\n", decrypted);

    return 0;
}

/* --- EOF ------------------------------------------------------------------ */
