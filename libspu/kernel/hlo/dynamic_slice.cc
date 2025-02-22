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

#include "libspu/kernel/hlo/dynamic_slice.h"

#include "llvm/ADT/STLExtras.h"

#include "libspu/kernel/hal/debug.h"
#include "libspu/kernel/hal/hal.h"
#include "libspu/kernel/hlo/utils.h"
#include "libspu/kernel/value.h"

namespace spu::kernel::hlo {

spu::Value DynamicUpdateSlice(
    HalContext *ctx, const spu::Value &operand, const spu::Value &update,
    absl::Span<const spu::Value>
        start_indicies) {  // Basic idea here, get a ref slice and
                           // update the whole slice..
  // Start indicies
  std::vector<int64_t> start_indicies_i64(start_indicies.size());
  for (const auto &idx : llvm::enumerate(start_indicies)) {
    auto v_idx = idx.value();
    if (v_idx.isSecret() && ctx->rt_config().reveal_secret_indicies()) {
      v_idx = hal::reveal(ctx, v_idx);
      SPDLOG_WARN("Reveal {}th start index of DynamicUpdateSlice", idx.index());
    }
    start_indicies_i64[idx.index()] = getIndicies(ctx, v_idx)[0];
    // Transform start_indicies
    // start_indices[i] = clamp(start_indices[i], 0, operand.dimension_size[i] -
    // update.dimension_size[i])
    start_indicies_i64[idx.index()] = std::min(
        std::max(start_indicies_i64[idx.index()], static_cast<int64_t>(0)),
        operand.shape()[idx.index()] - update.shape()[idx.index()]);
  }

  auto ret = operand.clone();
  UpdateSliceInPlace(ctx, ret, update, start_indicies_i64);
  return ret;
}

void UpdateSliceInPlace(HalContext *ctx, spu::Value &operand,
                        const spu::Value &update,
                        absl::Span<const int64_t> start_indicies) {
  auto u = hal::stype_cast(ctx, update, operand.storage_type());
  operand.data().update_slice(u.data(), start_indicies);
}

spu::Value DynamicSlice(HalContext *ctx, const spu::Value &operand,
                        absl::Span<const int64_t> slice_size,
                        absl::Span<const spu::Value> start_indicies) {
  // Start indicies
  std::vector<int64_t> start_indicies_i64(start_indicies.size());
  for (const auto &idx : llvm::enumerate(start_indicies)) {
    auto v_idx = idx.value();
    if (v_idx.isSecret() && ctx->rt_config().reveal_secret_indicies()) {
      v_idx = hal::reveal(ctx, v_idx);
      SPDLOG_WARN("Reveal {}th start index of DynamicSlice", idx.index());
    }
    start_indicies_i64[idx.index()] = getIndicies(ctx, v_idx)[0];
    // Transform start_indicies
    // start_indices[i] = clamp(start_indices[i], 0, operand.dimension_size[i] -
    // size_indices[i])
    start_indicies_i64[idx.index()] = std::min(
        std::max(start_indicies_i64[idx.index()], static_cast<int64_t>(0)),
        operand.shape()[idx.index()] - slice_size[idx.index()]);
  }

  // Limit
  std::vector<int64_t> limit(start_indicies_i64);
  for (size_t idx = 0; idx < limit.size(); ++idx) {
    limit[idx] += slice_size[idx];
  }

  // Strides is always 1
  std::vector<int64_t> strides(limit.size(), 1);

  return hal::slice(ctx, operand, start_indicies_i64, limit, strides);
}

}  // namespace spu::kernel::hlo
