/* Create by Claude.ai 2025-11-21 
 * A NTP client program using UDP.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#define NTP_TIMESTAMP_DELTA 2208988800LL
#define NTP_PACKET_SIZE 48

typedef struct {
    uint8_t li_vn_mode;
    uint8_t stratum;
    uint8_t poll;
    uint8_t precision;
    uint32_t root_delay;
    uint32_t root_dispersion;
    uint32_t ref_id;
    uint32_t ref_ts_sec;
    uint32_t ref_ts_frac;
    uint32_t orig_ts_sec;
    uint32_t orig_ts_frac;
    uint32_t recv_ts_sec;
    uint32_t recv_ts_frac;
    uint32_t tx_ts_sec;
    uint32_t tx_ts_frac;
} ntp_packet;

time_t get_ntp_time(const char *host, int port) {
    int sock;
    struct sockaddr_in addr;
    struct hostent *he;
    ntp_packet pkt;
    unsigned char buf[NTP_PACKET_SIZE];
    time_t ntp_time;
    struct timeval tv;

    // Resolve hostname
    he = gethostbyname(host);
    if (!he) {
        perror("gethostbyname");
        return -1;
    }

    printf("Resolved %s to %s\n", host, inet_ntoa(*(struct in_addr *)he->h_addr_list[0]));

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    // Set receive timeout
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));

    // Set up address structure
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Initialize NTP packet
    memset(&pkt, 0, sizeof(pkt));
    pkt.li_vn_mode = 0x1B;  // LI=0, VN=3, Mode=3 (Client)
    pkt.poll = 4;
    pkt.precision = 0xEC;

    printf("Sending NTP request...\n");

    // Send NTP request via UDP
    if (sendto(sock, (unsigned char *)&pkt, NTP_PACKET_SIZE, 0, 
               (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("sendto");
        close(sock);
        return -1;
    }

    printf("Waiting for response...\n");

    // Receive NTP response
    int n = recvfrom(sock, buf, NTP_PACKET_SIZE, 0, NULL, NULL);
    if (n < NTP_PACKET_SIZE) {
        perror("recvfrom");
        close(sock);
        return -1;
    }

    close(sock);

    // Extract transmit timestamp (seconds since 1900)
    uint32_t tx_sec = (buf[40] << 24) | (buf[41] << 16) | 
                      (buf[42] << 8) | buf[43];

    // Convert from NTP epoch (1900) to Unix epoch (1970)
    ntp_time = tx_sec - NTP_TIMESTAMP_DELTA;

    return ntp_time;
}

int main() {
    const char *ntp_server = "pool.ntp.org";
    int port = 123;
    time_t ntp_time;
    struct tm *tm_info;
    char time_str[80];

    printf("Connecting to NTP server: %s:%d\n", ntp_server, port);

    ntp_time = get_ntp_time(ntp_server, port);

    if (ntp_time < 0) {
        fprintf(stderr, "Failed to get NTP time\n");
        return 1;
    }
    // Convert to readable format
    tm_info = localtime(&ntp_time);
    
    // Format options:
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Unix timestamp: %ld\n", ntp_time);
    printf("Format 1 (Date and Time): %s\n", time_str);
    
    return 0;
}