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

#include <memory>
#include <string>

#include "cyber/cyber.h"
#include "cyber/proto/unit_test.pb.h"
#include "cyber/py_wrapper/py_cyber.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

using edith::cyber::Rate;
using edith::cyber::Time;
using edith::cyber::proto::Chatter;

using edith::cyber::message::PyMessageWrap;

int main(int argc, char *argv[]) {
  // init cyber framework
  edith::cyber::Init("cyber_python");
  auto msgChat = std::make_shared<edith::cyber::proto::Chatter>();
  edith::cyber::PyNode node("talker");
  edith::cyber::PyWriter *pw =
      node.create_writer("channel/chatter", msgChat->GetTypeName());
  Rate rate(1.0);
  while (edith::cyber::OK()) {
    static uint64_t seq = 0;
    msgChat->set_timestamp(Time::Now().ToNanosecond());
    msgChat->set_lidar_timestamp(Time::Now().ToNanosecond());
    msgChat->set_seq(seq++);
    msgChat->set_content("Hello, edith!");

    std::string org_data;
    msgChat->SerializeToString(&org_data);
    AINFO << "write->[ " << org_data << " ]";
    pw->write(org_data);
    AINFO << "talker sent a message!" << org_data;
    rate.Sleep();
  }
  delete pw;
  return 0;
}
