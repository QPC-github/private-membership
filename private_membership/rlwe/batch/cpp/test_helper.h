// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PRIVATE_MEMBERSHIP_RLWE_BATCH_CPP_TEST_HELPER_H_
#define PRIVATE_MEMBERSHIP_RLWE_BATCH_CPP_TEST_HELPER_H_

#include <vector>

#include "absl/status/statusor.h"
#include "private_membership/rlwe/batch/proto/client.pb.h"
#include "private_membership/rlwe/batch/cpp/constants.h"
#include "private_membership/rlwe/batch/proto/shared.pb.h"
#include "shell_encryption/polynomial.h"
#include "shell_encryption/serialization.pb.h"
#include "shell_encryption/symmetric_encryption.h"

namespace private_membership {
namespace batch {

inline constexpr int kNumberOfShards = 4;
inline constexpr int kNumberOfBucketsPerShard = 200;
inline constexpr int kLevelsOfRecursion = 2;

// Create parameters for testing.
Parameters CreateTestParameters();

// Create keys.
absl::StatusOr<GenerateKeysResponse> CreateTestKeys();

// Create plaintext query.
PlaintextQuery CreatePlaintextQuery(int query_id, int shard_id,
                                    int bucket_index);

// Create encrypted queries.
absl::StatusOr<EncryptedQueries> CreateEncryptedQueries(
    const GenerateKeysResponse& keys,
    const std::vector<PlaintextQuery>& plaintext_queries);

// Deserialize the private key.
absl::StatusOr<rlwe::SymmetricRlweKey<ModularInt>> DeserializePrivateKey(
    const rlwe::SerializedNttPolynomial& serialized_key,
    const Context& context);

// Simple encryption of an integer into first coefficient.
absl::StatusOr<rlwe::SymmetricRlweCiphertext<ModularInt>> EncryptSingleInt(
    const Context& context,
    const rlwe::SymmetricRlweKey<ModularInt>& private_key, Int plaintext);

// Simple decryption of first coefficient.
absl::StatusOr<Int> DecryptSingleInt(
    const Context& context,
    const rlwe::SymmetricRlweKey<ModularInt>& private_key,
    const rlwe::SymmetricRlweCiphertext<ModularInt>& ciphertext);

}  // namespace batch
}  // namespace private_membership

#endif  // PRIVATE_MEMBERSHIP_RLWE_BATCH_CPP_TEST_HELPER_H_
