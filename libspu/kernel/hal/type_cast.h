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

namespace spu::kernel::hal {

/// cast dtype
// @param in, the input value
// @param to_type, destination dtype
Value dtype_cast(HalContext* ctx, const Value& in, DataType to_type);

/// cast public to secret
// @param in, the input value
Value p2s(HalContext* ctx, const Value& x);

/// reveal a secret
// @param in, the input value
Value reveal(HalContext* ctx, const Value& x);

/// cast in storage type to dest type
Value stype_cast(HalContext* ctx, const Value& in, const Type& to);

}  // namespace spu::kernel::hal
