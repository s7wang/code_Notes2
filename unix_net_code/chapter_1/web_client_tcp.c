/* Create by Claude.ai 2025-11-21 
 * A web client (TCP) that supports both HTTP and HTTPS.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define BUFFER_SIZE 4096

int connect_http(const char *hostname, int port, const char *path) {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *he;
    char buffer[BUFFER_SIZE];

    printf("Using HTTP (plain text)\n\n");

    // Resolve hostname
    he = gethostbyname(hostname);
    if (!he) {
        perror("gethostbyname failed");
        return 1;
    }

    printf("Resolved IP: %s\n\n", inet_ntoa(*(struct in_addr *)he->h_addr_list[0]));

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation failed");
        return 1;
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected successfully!\n\n");

    // Build HTTP request
    char http_request[BUFFER_SIZE];
    snprintf(http_request, sizeof(http_request),
             "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
             path, hostname);

    printf("Sending HTTP request...\n");
    printf("------- REQUEST -------\n%s", http_request);
    printf("------------------------\n\n");

    // Send HTTP request
    if (send(sock, http_request, strlen(http_request), 0) < 0) {
        perror("send failed");
        close(sock);
        return 1;
    }

    printf("Receiving response...\n");
    printf("------- RESPONSE -------\n");

    // Receive response
    int bytes_received;
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    printf("\n------------------------\n");

    close(sock);
    return 0;
}

int connect_https(const char *hostname, int port, const char *path) {
    SSL_CTX *ctx;
    SSL *ssl;
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *he;
    char buffer[BUFFER_SIZE];

    printf("Using HTTPS (encrypted with SSL/TLS)\n\n");

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Create SSL context
    ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        perror("SSL_CTX_new failed");
        return 1;
    }

    // Resolve hostname
    he = gethostbyname(hostname);
    if (!he) {
        perror("gethostbyname failed");
        SSL_CTX_free(ctx);
        return 1;
    }

    printf("Resolved IP: %s\n\n", inet_ntoa(*(struct in_addr *)he->h_addr_list[0]));

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation failed");
        SSL_CTX_free(ctx);
        return 1;
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        SSL_CTX_free(ctx);
        return 1;
    }

    printf("TCP Connected, performing SSL/TLS handshake...\n\n");

    // Create SSL connection
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, hostname);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return 1;
    }

    printf("SSL/TLS handshake successful!\n\n");

    // Build HTTPS request
    char http_request[BUFFER_SIZE];
    snprintf(http_request, sizeof(http_request),
             "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
             path, hostname);

    printf("Sending HTTPS request...\n");
    printf("------- REQUEST -------\n%s", http_request);
    printf("------------------------\n\n");

    // Send HTTPS request
    if (SSL_write(ssl, http_request, strlen(http_request)) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(sock);
        SSL_CTX_free(ctx);
        return 1;
    }

    printf("Receiving response...\n");
    printf("------- RESPONSE -------\n");

    // Receive response
    int bytes_received;
    while ((bytes_received = SSL_read(ssl, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    printf("\n------------------------\n");

    // Cleanup
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);
    EVP_cleanup();

    return 0;
}

int main() {
    char hostname[256];
    char path[256];
    char protocol[10];
    int port;

    printf("=== TCP Client - HTTP/HTTPS Web Server ===\n\n");

    // Get protocol from user
    printf("Enter protocol (http or https): ");
    fgets(protocol, sizeof(protocol), stdin);
    protocol[strcspn(protocol, "\n")] = '\0';

    // Get hostname from user
    printf("Enter hostname (e.g., google.com, example.com): ");
    fgets(hostname, sizeof(hostname), stdin);
    hostname[strcspn(hostname, "\n")] = '\0';

    // Get path from user
    printf("Enter path (e.g., / or /index.html): ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = '\0';

    // If path is empty, use default root
    if (strlen(path) == 0) {
        strcpy(path, "/");
    }

    // Determine port based on protocol
    if (strcmp(protocol, "https") == 0 || strcmp(protocol, "HTTPS") == 0) {
        port = 443;
        printf("\nConnecting to %s:%d (HTTPS)...\n\n", hostname, port);
        return connect_https(hostname, port, path);
    } else {
        port = 80;
        printf("\nConnecting to %s:%d (HTTP)...\n\n", hostname, port);
        return connect_http(hostname, port, path);
    }
}