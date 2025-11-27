# unix_net_code/Makefile
options := ntp_client_udp web_client_tcp


.DEFAULT: help
.PHONY: help all $(options) clean

help:
	@echo "============================================================================================";
	@echo "[unix_net_code] Usage:";
	@echo "\tmake ntp_client_udp		A NTP client program using UDP.";
	@echo "\tmake web_client_tcp		A web client (TCP) that supports both HTTP and HTTPS.";
	@echo "--------------------------------------------------------------------------------------------";
	@echo "\tmake all					Compile all of the above.";
	@echo "\tmake clean					Clean all of the above.";
	@echo "============================================================================================\n";


all : $(options)

ntp_client_udp:
	$(CC) -o ntp_client_udp ntp_client_udp.c

web_client_tcp:
	$(CC) -o web_client_tcp web_client_tcp.c -lssl -lcrypto

clean:
	$(RM) $(options)