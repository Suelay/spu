// Copyright 2023 Ant Group Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "gflags/gflags.h"

#include "libspu/mpc/semi2k/beaver/ttp_server/beaver_server.h"

DEFINE_int32(port, 9449, "TCP Port of this server");

int main(int argc, char* argv[]) {
  // Parse gflags. We recommend you to use gflags as well.
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  return spu::mpc::semi2k::beaver::ttp_server::RunUntilAskedToQuit(FLAGS_port);
}
