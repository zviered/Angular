TOOLCHAIN_DIR   = /6113_sw/module/RCMCR_FLYTRAP/linux4.9.20/toolchain/crosstool/release/bin
OBJ_DIR = ./Debug_x86_64-unknown-linux-gnu

CC = $(TOOLCHAIN_DIR)/x86_64-unknown-linux-gnu-gcc
CP = cp

INC_DIR =   -I../../release \
			-I../../common

AR	= $(TOOLCHAIN_DIR)/x86_64-unknown-linux-gnu-ar
ARFLAGS = rs
 
RELEASE = ../../release/x86_64-unknown-linux-gnu

OBJS = \
	$(OBJ_DIR)/TcpServer.o 

$(RELEASE)/libTcpServer.a: $(OBJS)
	 mkdir -p $(RELEASE)
	 $(AR) $(ARFLAGS) $(RELEASE)/libTcpServer.a $(OBJS)
	 $(CP) TcpServer.h $(RELEASE)

$(OBJ_DIR)/TcpServer.o: TcpServer.cpp
	 $(CC) $(CCFLAGS) -c TcpServer.cpp -o $(OBJ_DIR)/TcpServer.o
				 	
clean:
	rm $(OBJ_DIR)/*.o
	rm $(RELEASE)/libTcpServer.a