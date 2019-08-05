all: build

DEVICE = 	linux_desktop_i386

INCLUDES = 	-I inc 					\
	   	-I device/linux_desktop_i386

FILES = 	src/common/main.c 			\
		src/common/pelion_queue.c		\
		device/$(DEVICE)/device_pelion_mutex.c

build:
	gcc $(INCLUDES) $(FILES) -o trafficshaper

