/******************************************************************************
 * Copyright 2020 The Edith Authors. All Rights Reserved.
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

#include "modules/drivers/canbus/can_comm/can_receiver.h"

#include "gtest/gtest.h"

#include "modules/vehicle/proto/chassis_detail.pb.h"
#include "modules/common/proto/error_code.pb.h"
#include "modules/drivers/canbus/can_client/fake/fake_can_client.h"
#include "modules/drivers/canbus/can_comm/message_manager.h"

namespace edith {
namespace drivers {
namespace canbus {

TEST(CanReceiverTest, ReceiveOne) {
  cyber::Init("can_receiver_test");
  can::FakeCanClient can_client;
  MessageManager<::edith::vehicle::ChassisDetail> pm;
  CanReceiver<::edith::vehicle::ChassisDetail> receiver;

  receiver.Init(&can_client, &pm, false);
  EXPECT_EQ(receiver.Start(), common::ErrorCode::OK);
  EXPECT_TRUE(receiver.IsRunning());
  receiver.Stop();
  EXPECT_FALSE(receiver.IsRunning());
  // cyber::Clear();
}

}  // namespace canbus
}  // namespace drivers
}  // namespace edith
