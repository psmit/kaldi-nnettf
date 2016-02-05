/* Copyright 2016 Aalto University (Peter Smit) All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef KALDI_NNETTF_PROTO_H
#define KALDI_NNETTF_PROTO_H

#include <iostream>
#include <string>

#include "nnettf/example.pb.h"
#include "hmm/posterior.h"
#include "base/kaldi-common.h"


namespace kaldi {
namespace nnettf {

struct NnetTfExample {
  tensorflow::Example example;

  void addFeature(std::string name, int v);
  void addFeature(std::string name, const MatrixBase <BaseFloat> &v);
  void addFeature(std::string name, Posterior v);
  void addFeature(std::string name, std::string v);
};

struct NnetTfProtoWriter {
  std::fstream output;
  explicit NnetTfProtoWriter(std::string wxspecifier) : output(wxspecifier,
                                                      std::ios::out |
                                                      std::ios::trunc |
                                                      std::ios::binary) { }
  void Write(NnetTfExample eg);
};

}  // namespace nnettf
}  // namespace kaldi


#endif  // KALDI_NNETTF_PROTO_H
