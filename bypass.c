#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <netdb.h>
#include <string.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <sys/ioctl.h>
#include <time.h>
#include <pthread.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/pem.h>

// gcc a.c -L/usr/lib -lssl -lcrypto
char get_1[] = { /* Packet 9 */
0x47, 0x45, 0x54, 0x20, 0x2f, 0x20, 0x48, 0x54, 
0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31, 0x0d, 0x0a, 
0x48, 0x6f, 0x73, 0x74, 0x3a, 0x20, 0x77, 0x77, 
0x77, 0x2e, 0x78, 0x76, 0x69, 0x64, 0x65, 0x6f, 
0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x0d, 0x0a, 0x55, 
0x73, 0x65, 0x72, 0x2d, 0x41, 0x67, 0x65, 0x6e, 
0x74, 0x3a, 0x20, 0x4d, 0x6f, 0x7a, 0x69, 0x6c, 
0x6c, 0x61, 0x2f, 0x35, 0x2e, 0x30, 0x20, 0x28, 
0x58, 0x31, 0x31, 0x3b, 0x20, 0x4c, 0x69, 0x6e, 
0x75, 0x78, 0x20, 0x69, 0x36, 0x38, 0x36, 0x3b, 
0x20, 0x72, 0x76, 0x3a, 0x35, 0x32, 0x2e, 0x30, 
0x29, 0x20, 0x47, 0x65, 0x63, 0x6b, 0x6f, 0x2f, 
0x32, 0x30, 0x31, 0x30, 0x30, 0x31, 0x30, 0x31, 
0x20, 0x46, 0x69, 0x72, 0x65, 0x66, 0x6f, 0x78, 
0x2f, 0x35, 0x32, 0x2e, 0x30, 0x0d, 0x0a, 0x41, 
0x63, 0x63, 0x65, 0x70, 0x74, 0x3a, 0x20, 0x74, 
0x65, 0x78, 0x74, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 
0x2c, 0x61, 0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 
0x74, 0x69, 0x6f, 0x6e, 0x2f, 0x78, 0x68, 0x74, 
0x6d, 0x6c, 0x2b, 0x78, 0x6d, 0x6c, 0x2c, 0x61, 
0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x74, 0x69, 
0x6f, 0x6e, 0x2f, 0x78, 0x6d, 0x6c, 0x3b, 0x71, 
0x3d, 0x30, 0x2e, 0x39, 0x2c, 0x2a, 0x2f, 0x2a, 
0x3b, 0x71, 0x3d, 0x30, 0x2e, 0x38, 0x0d, 0x0a, 
0x41, 0x63, 0x63, 0x65, 0x70, 0x74, 0x2d, 0x4c, 
0x61, 0x6e, 0x67, 0x75, 0x61, 0x67, 0x65, 0x3a, 
0x20, 0x65, 0x6e, 0x2d, 0x55, 0x53, 0x2c, 0x65, 
0x6e, 0x3b, 0x71, 0x3d, 0x30, 0x2e, 0x35, 0x0d, 
0x0a, 0x41, 0x63, 0x63, 0x65, 0x70, 0x74, 0x2d, 
0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 
0x3a, 0x20, 0x67, 0x7a, 0x69, 0x70, 0x2c, 0x20, 
0x64, 0x65, 0x66, 0x6c, 0x61, 0x74, 0x65, 0x0d, 
0x0a, 0x43, 0x6f, 0x6f, 0x6b, 0x69, 0x65, 0x3a, 
0x20, 0x6f, 0x6c, 0x6c, 0x5f, 0x6d, 0x61, 0x69, 
0x6e, 0x5f, 0x63, 0x61, 0x74, 0x5f, 0x6c, 0x69, 
0x73, 0x74, 0x5f, 0x6e, 0x62, 0x69, 0x74, 0x65, 
0x6d, 0x73, 0x3d, 0x31, 0x0d, 0x0a, 0x43, 0x6f, 
0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 
0x3a, 0x20, 0x6b, 0x65, 0x65, 0x70, 0x2d, 0x61, 
0x6c, 0x69, 0x76, 0x65, 0x0d, 0x0a, 0x55, 0x70, 
0x67, 0x72, 0x61, 0x64, 0x65, 0x2d, 0x49, 0x6e, 
0x73, 0x65, 0x63, 0x75, 0x72, 0x65, 0x2d, 0x52, 
0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x73, 0x3a, 
0x20, 0x31, 0x0d, 0x0a, 0x0d, 0x0a };

int main (void){

	int err;
	int socket1;	
	struct sockaddr_in socket_addr;

	SSL_CTX *ctx;
	SSL *ssl;
	X509 *server_cert;
	char *str;
	char buf[4096];
	const SSL_METHOD *method;

	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
	method = SSLv23_client_method();
	ctx=SSL_CTX_new(method);

	if(SSL_CTX_use_PrivateKey_file(ctx,"./client.key",SSL_FILETYPE_PEM<=0)){
		printf("cert error");
	}

	if(!SSL_CTX_check_private_key(ctx)){
		printf("key error");
	}

	socket1 = socket(AF_INET, SOCK_STREAM,0);
	socket_addr.sin_family=AF_INET;
	socket_addr.sin_addr.s_addr=inet_addr("185.88.181.10");
	socket_addr.sin_port=htons(443);

	err=connect(socket1,(struct sockaddr*)&socket_addr, sizeof(socket_addr));

	ssl=SSL_new(ctx);
	
	SSL_set_fd(ssl,socket1);
	err=SSL_connect(ssl);

	server_cert = SSL_get_peer_certificate(ssl);
	str = X509_NAME_oneline(X509_get_issuer_name(server_cert),0,0);

	SSL_write(ssl,get_1,sizeof(get_1));

	SSL_read(ssl,buf,sizeof(buf)-1);

	printf("%s\n",buf);


	sleep(1000000);
	printf("aaaa");
}
