/******************************************************************************
 * Copyright 2020 The Edith Author. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "cyber/common/global_data.h"
#include "cyber/common/log.h"
#include "cyber/init.h"
#include "cyber/mainboard/module_argument.h"
#include "cyber/mainboard/module_controller.h"
#include "cyber/state.h"

#include "gflags/gflags.h"

using edith::cyber::mainboard::ModuleArgument;
using edith::cyber::mainboard::ModuleController;

int main(int argc, char** argv) {
  google::SetUsageMessage("we use this program to load dag and run user apps.");

  // parse the argument
  ModuleArgument module_args;
  module_args.ParseArgument(argc, argv);

  // initialize cyber
  edith::cyber::Init(argv[0]);

  // start module
  ModuleController controller(module_args);
  if (!controller.Init()) {
    controller.Clear();
    AERROR << "module start error.";
    return -1;
  }

  edith::cyber::WaitForShutdown();
  controller.Clear();
  AINFO << "exit mainboard.";

  return 0;
}
