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

#include "nnettf/nnettf-proto.h"

#include <algorithm>
#include <cstring>

#include "nnettf/crc32c.h"

namespace kaldi {
namespace nnettf {

void NnetTfExample::addFeature(std::string name, int v) {
  auto feature = &(*this->example.mutable_features()->mutable_feature())[name];
  feature->mutable_int64_list()->add_value(v);
}

void NnetTfExample::addFeature(std::string name,
                               const MatrixBase <BaseFloat> &v) {
  auto feature = &(*this->example.mutable_features()->mutable_feature())[name];
  auto vl = feature->mutable_float_list()->mutable_value();

  for (MatrixIndexT i = 0; i < v.NumRows(); i++) {
    std::copy(v.RowData(i),
              v.RowData(i) + v.NumCols(),
              google::protobuf::internal::RepeatedFieldBackInsertIterator<float>(vl));
  }
}

void NnetTfExample::addFeature(std::string name, Posterior v) {
  auto feature = &(*this->example.mutable_features()->mutable_feature())[name];
  int32 num_rows = v.size();

  for (int i = 0; i < num_rows; i++) {
    if (v[i].size() == 0) {
      feature->mutable_int64_list()->add_value(-1);  // no label is -1
    } else if (v[i].size() == 1) {
      feature->mutable_int64_list()->add_value(v[i][0].first);
    } else {
      // We should only have at most one label per frame (at the moment)
      KALDI_ASSERT(false);
    }
  }
}

static uint32 MaskedCrc(const char *data, size_t n) {
  return crc32c::Mask(crc32c::Value(data, n));
}


void NnetTfExample::addFeature(std::string name, std::string v) {
  auto feature = &(*this->example.mutable_features()->mutable_feature())[name];
  feature->mutable_bytes_list()->add_value(v);
}

void NnetTfProtoWriter::Write(NnetTfExample eg) {
  // we assume we are on a little endian system, if not change this stuff
  auto data = eg.example.SerializeAsString();
  auto data_length = data.size();

  char header[sizeof(uint64_t) + sizeof(uint32_t)];
  std::memcpy(header, &data_length, sizeof(uint64_t));
  auto crc = MaskedCrc(header, sizeof(uint64_t));
  std::memcpy(header + sizeof(uint64_t), &crc, sizeof(uint32_t));

  this->output.write(header, sizeof(header));

  this->output.write(data.data(), data.size());

  char footer[sizeof(uint32_t)];
  crc = MaskedCrc(data.data(), data.size());
  std::memcpy(footer, &crc, sizeof(uint32_t));
  this->output.write(footer, sizeof(footer));
}

}  // namespace nnettf
}  // namespace kaldi
