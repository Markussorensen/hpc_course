TARGET= libmatmult.so
OBJS	= matmult_asy_offload.o matmult_blk_offload.o matmult_blk_omp.o matmult_blk.o matmult_lib_offload.o matmult_lib.o \
		  matmult_mkn_offload.o matmult_mkn_omp.o matmult_mkn.o matmult_mnk_offload.o

CC	= nvc
CXX	= nvc++

OPT	= -g -fast -Msafeptr -Minfo -acc -mp=gpu -gpu=pinned -gpu=cc80 -gpu=lineinfo -cuda -mp=noautopar -fopenmp
PIC   = -fpic -shared
ISA	= 
PARA	= 
INC   = -I$(CUDA_ROOT)/include -I/appl/nvhpc/2022_2211/Linux_x86_64/22.11/examples/OpenMP/SDK/include
LIBS	= 

CXXFLAGS= $(OPT) $(PIC) $(INC) $(ISA) $(PARA) $(XOPT)

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@/bin/rm -f $(TARGET) $(OBJS)

