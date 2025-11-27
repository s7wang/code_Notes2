#driver_code/Makefile
options := HelloWorld get_pid_kmod

.DEFAULT: help
.PHONY: help all $(options) clean $(options)-clean

help:
	@echo "============================================================================================";
	@echo "[driver_code] Usage:";
	@echo "\tmake HelloWorld			A simple Hello World kernel module.";
	@echo "\tmake get_pid_kmod			Kernel module to print current process information.";
	@echo "--------------------------------------------------------------------------------------------";
	@echo "\tmake all					Compile all of the above.";
	@echo "\tmake clean					Clean all of the above.";
	@echo "============================================================================================\n";
## @echo "\tmake ntp_client_udp		A NTP client program using UDP.";

all : $(options)

HelloWorld:
	for dir in HelloWorld; do $(MAKE) -C $$dir; done

HelloWorld-clean:
	for dir in HelloWorld; do $(MAKE) -C $$dir clean; done

get_pid_kmod:
	for dir in get_pid_kmod; do $(MAKE) -C $$dir; done

get_pid_kmod-clean:
	for dir in get_pid_kmod; do $(MAKE) -C $$dir clean; done

clean: $(options)-clean