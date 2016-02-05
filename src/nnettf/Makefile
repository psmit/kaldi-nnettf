
all:

include ../nnettf.mk

LDFLAGS += $(CUDA_LDFLAGS)
LDLIBS += $(CUDA_LDLIBS)

TESTFILES =

OBJFILES = nnettf-proto.o example.pb.o feature.pb.o crc32c.o

LIBNAME = kaldi-nnettf

nnettf-proto.o: example.pb.cc example.pb.h feature.pb.cc feature.pb.h



include $(KALDIROOT)/src/makefiles/default_rules.mk

%.pb.h %.pb.cc: %.proto
	$(PROTOCTOOL) --cpp_out=. $<
