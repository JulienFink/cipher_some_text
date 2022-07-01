APP_ := simple_cipher

openssl_include = -L/usr/local/ssl/lib -I/usr/local/ssl/include

CFLAGS = -lcrypto -O0 -Wall -ldl

all : $(APP_)

clean:
	rm -f $(APP_)

$(APP_) : $(APP_).c
	gcc $(APP_).c $(openssl_include) -o $(APP_) $(CFLAGS)

### EOF
