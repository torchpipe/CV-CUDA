#!/bin/bash -e

# SPDX-FileCopyrightText: Copyright (c) 2022-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Builds documentation based on sphinx and doxygen
# Usage: build_docs.sh [build folder]

build_type="release"
build_dir="build"

if [[ $# -ge 1 ]]; then
   build_dir=$1
fi

./ci/build.sh $build_type $build_dir "-DBUILD_DOCS=ON -DBUILD_TESTS=OFF -DBUILD_PYTHON=ON -DPYTHON_VERSIONS=';3.9;3.10'"
