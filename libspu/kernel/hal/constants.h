// Copyright 2021 Ant Group Co., Ltd.
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

#pragma once

#include "libspu/core/xt_helper.h"  // TODO: PtBufferView
#include "libspu/kernel/context.h"
#include "libspu/kernel/value.h"

namespace spu::kernel::hal {

// TODO(jint) PtBufferView is too implicit, we should make it more obvious since
// it will affect the value's dtype.
//
// Create a public value from a given buffer view.
//
// if shape is specified, the value will be broadcasted to given shape.
Value constant(HalContext* ctx, const PtBufferView& bv,
               absl::Span<const int64_t> shape = {});

Value zeros(HalContext* ctx, Visibility vis, DataType dtype,
            absl::Span<const int64_t> shape = {});

// Deprecated:
//
// Warn: this is ANTI-PATTERN, it will not make a `true secret`, but a
// `secret-typed` value that all parties knowns, debug purpose only.
//
// Make a secret from a plaintext buffer.
Value const_secret(HalContext* ctx, const PtBufferView& bv,
                   absl::Span<const int64_t> shape = {});

// Export a value to a buffer.
NdArrayRef dump_public(HalContext* ctx, const Value& v);

// Deprecated:
Value make_value(HalContext* ctx, Visibility vtype, const PtBufferView& bv);

// Return eps
Value epsilon(HalContext* ctx, absl::Span<const int64_t> shape = {});

}  // namespace spu::kernel::hal
