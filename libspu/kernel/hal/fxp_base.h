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

#include "libspu/kernel/context.h"
#include "libspu/kernel/value.h"

// !!please read [README.md] for api naming conventions.
namespace spu::kernel::hal {
namespace detail {

// Extract the most significant bit. see
// https://docs.oracle.com/javase/7/docs/api/java/lang/Integer.html#highestOneBit(int)
Value highestOneBit(HalContext* ctx, const Value& x);

void hintNumberOfBits(const Value& a, size_t nbits);

Value div_goldschmidt(HalContext* ctx, const Value& a, const Value& b);

Value reciprocal_goldschmidt_positive(HalContext* ctx, const Value& b_abs);

Value reciprocal_goldschmidt(HalContext* ctx, const Value& b);

Value f_polynomial(HalContext* ctx, const Value& x,
                   const std::vector<Value>& coeffs);

}  // namespace detail

// This module defines the basic fixed-point arithmetics.
enum class SignType {
  UNKNOWN,
  POSITIVE,
  NEGATIVE,
};

Value f_negate(HalContext* ctx, const Value& x);

Value f_abs(HalContext* ctx, const Value& x);

Value f_reciprocal(HalContext* ctx, const Value& x);

Value f_add(HalContext* ctx, const Value& x, const Value& y);

Value f_sub(HalContext* ctx, const Value& x, const Value& y);

Value f_mul(HalContext* ctx, const Value& x, const Value& y);

Value f_mul_with_sign(HalContext* ctx, const Value& x, const Value& y,
                      SignType sign = SignType::UNKNOWN);

Value f_mmul(HalContext* ctx, const Value& x, const Value& y);

Value f_conv2d(HalContext* ctx, const Value& x, const Value& y,
               absl::Span<const int64_t> window_strides,
               absl::Span<const int64_t> result_shape);

Value f_div(HalContext* ctx, const Value& x, const Value& y);

Value f_equal(HalContext* ctx, const Value& x, const Value& y);

Value f_less(HalContext* ctx, const Value& x, const Value& y);

Value f_square(HalContext* ctx, const Value& x);

Value f_floor(HalContext* ctx, const Value& x);

Value f_ceil(HalContext* ctx, const Value& x);

}  // namespace spu::kernel::hal
