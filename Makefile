all: build

DEVICE = 	linux_desktop_i386

INCLUDES = 	-I inc 							\
	   	-I src/device/$(DEVICE)

FILES = 	src/common/main.c 					\
		src/common/pelion_queue.c				\
		src/common/pelion_cmd_args.c				\
		src/common/pelion_log.c					\
									\
		src/device/$(DEVICE)/device_pelion_system.c		\
		src/device/$(DEVICE)/device_pelion_log.c		\
		src/device/$(DEVICE)/device_pelion_thread.c		\
		src/device/$(DEVICE)/device_pelion_mutex.c		\
		src/device/$(DEVICE)/device_pelion_time.c		\
									\
		src/common/apps/threads/request_generator.c

build:
	gcc $(INCLUDES) $(FILES) -o trafficshaper -lpthread

