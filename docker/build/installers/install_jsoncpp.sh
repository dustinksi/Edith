#!/usr/bin/env bash

###############################################################################
# Copyright 2020 The Edith Authors. All Rights Reserved.
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
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

# wget https://apollocache.blob.core.windows.net/apollo-cache/jsoncpp.zip
unzip jsoncpp.zip

pushd jsoncpp/lib
cp -r lib* /usr/local/lib
popd