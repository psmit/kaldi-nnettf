
all:

include ../nnettf.mk 

LDFLAGS += $(CUDA_LDFLAGS)
LDLIBS += $(CUDA_LDLIBS) -lz

BINFILES = nnettf-get-protoegs

OBJFILES =

# Add this dependency to force cuda-compiled.o to be rebuilt when we reconfigure.
# cuda-compiled.o: ../kaldi.mk

TESTFILES =

ADDLIBS = $(KALDIROOT)/src/nnet3/kaldi-nnet3.a $(KALDIROOT)/src/gmm/kaldi-gmm.a \
         $(KALDIROOT)/src/decoder/kaldi-decoder.a $(KALDIROOT)/src/lat/kaldi-lat.a $(KALDIROOT)/src/hmm/kaldi-hmm.a  \
         $(KALDIROOT)/src/transform/kaldi-transform.a $(KALDIROOT)/src/tree/kaldi-tree.a \
         $(KALDIROOT)/src/thread/kaldi-thread.a $(KALDIROOT)/src/cudamatrix/kaldi-cudamatrix.a \
         $(KALDIROOT)/src/matrix/kaldi-matrix.a $(KALDIROOT)/src/fstext/kaldi-fstext.a \
         $(KALDIROOT)/src/util/kaldi-util.a $(KALDIROOT)/src/base/kaldi-base.a ../nnettf/kaldi-nnettf.a

include $(KALDIROOT)/src/makefiles/default_rules.mk
