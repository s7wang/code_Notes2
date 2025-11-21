# kernel_code/Makefile
options :=


.DEFAULT: help
.PHONY: help all $(options) clean

help:
	@echo "============================================================================================";
	@echo "[kernel_code] Usage:";
	@echo "--------------------------------------------------------------------------------------------";
	@echo "\tmake all					Compile all of the above.";
	@echo "\tmake clean					Clean all of the above.";
	@echo "============================================================================================\n";
## @echo "\tmake ntp_client_udp		A NTP client program using UDP.";

all : $(options)

clean:
	$(RM) $(options)