// Copyright 2022 Ant Group Co., Ltd.
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

#include "libspu/kernel/hlo/rand.h"

#include "libspu/kernel/hal/random.h"

namespace spu::kernel::hlo {

spu::Value Uniform_rand(HalContext *ctx, const spu::Value &lo,
                        const spu::Value &hi,
                        absl::Span<const int64_t> to_shape) {
  return hal::rng_uniform(ctx, lo, hi, to_shape);
}

}  // namespace spu::kernel::hlo
