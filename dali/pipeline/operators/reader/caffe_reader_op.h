// Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DALI_PIPELINE_OPERATORS_READER_CAFFE_READER_OP_H_
#define DALI_PIPELINE_OPERATORS_READER_CAFFE_READER_OP_H_

#include "dali/pipeline/operators/reader/reader_op.h"
#include "dali/pipeline/operators/reader/loader/lmdb.h"
#include "dali/pipeline/operators/reader/parser/caffe_parser.h"

namespace dali {

class CaffeReader : public DataReader<CPUBackend> {
 public:
  explicit CaffeReader(const OpSpec& spec)
  : DataReader<CPUBackend>(spec) {
    loader_.reset(new LMDBReader(spec));
    parser_.reset(new CaffeParser(spec));
  }

  DEFAULT_READER_DESTRUCTOR(CaffeReader, CPUBackend);

  void RunImpl(SampleWorkspace* ws, const int i) override {
    const int idx = ws->data_idx();

    auto* raw_data = prefetched_batch_[idx];

    parser_->Parse(raw_data->data<uint8_t>(), raw_data->size(), ws);

    return;
  }

 protected:
  USE_READER_OPERATOR_MEMBERS(CPUBackend);
};

}  // namespace dali

#endif  // DALI_PIPELINE_OPERATORS_READER_CAFFE_READER_OP_H_
