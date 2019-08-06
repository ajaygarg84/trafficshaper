all: build

DEVICE = 	linux_desktop_i386
APP    =	trafficshaper

INCLUDES = 	-I inc 							\
	   	-I inc/modules						\
	   	-I inc/apps/$(APP)					\
	   	-I src/device/$(DEVICE)

FILES = 	src/bare/modules/pelion_stdlib.c			\
		src/bare/modules/pelion_log.c				\
									\
	 	src/bare/apps/$(APP)/main.c 				\
	 	src/bare/apps/$(APP)/traffic_queue.c 			\
	 	src/bare/apps/$(APP)/threads/request_generator.c 	\
	 	src/bare/apps/$(APP)/threads/token_generator.c 		\
	 	src/bare/apps/$(APP)/threads/request_servicer.c 	\
									\
		src/device/$(DEVICE)/device_pelion_system.c		\
		src/device/$(DEVICE)/device_pelion_log.c		\
		src/device/$(DEVICE)/device_pelion_thread.c		\
		src/device/$(DEVICE)/device_pelion_time.c		\
									\

build:
	@gcc $(INCLUDES) $(FILES) -o trafficshaper -lpthread

