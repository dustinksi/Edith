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

#include "modules/drivers/canbus/can_comm/message_manager.h"

#include <memory>
#include <set>

#include "gtest/gtest.h"

#include "modules/vehicle/proto/chassis_detail.pb.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace edith {
namespace drivers {
namespace canbus {

using edith::common::ErrorCode;

class MockProtocolData : public ProtocolData<::edith::vehicle::ChassisDetail> {
 public:
  static const int32_t ID = 0x111;
  MockProtocolData() {}
};

class MockMessageManager
    : public MessageManager<::edith::vehicle::ChassisDetail> {
 public:
  MockMessageManager() {
    AddRecvProtocolData<MockProtocolData, true>();
    AddSendProtocolData<MockProtocolData, true>();
  }
};

TEST(MessageManagerTest, GetMutableProtocolDataById) {
  uint8_t mock_data = 1;
  MockMessageManager manager;
  manager.Parse(MockProtocolData::ID, &mock_data, 8);
  manager.ResetSendMessages();
  EXPECT_NE(manager.GetMutableProtocolDataById(MockProtocolData::ID), nullptr);

  ::edith::vehicle::ChassisDetail chassis_detail;
  chassis_detail.set_car_type(::edith::vehicle::ChassisDetail::QIRUI_EQ_15);
  EXPECT_EQ(manager.GetSensorData(&chassis_detail), ErrorCode::OK);
  EXPECT_EQ(manager.GetSensorData(nullptr), ErrorCode::CANBUS_ERROR);
}

}  // namespace canbus
}  // namespace drivers
}  // namespace edith
