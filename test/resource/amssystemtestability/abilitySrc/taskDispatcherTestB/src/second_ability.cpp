/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "second_ability.h"
#include "app_log_wrapper.h"
#include "test_utils.h"

namespace OHOS {
namespace AppExecFwk {
using namespace OHOS::EventFwk;
namespace {
constexpr int numZero = 0;
constexpr int numOne = 1;
constexpr int numTwo = 2;
constexpr int numThree = 3;
}

void SecondAbility::Init(const std::shared_ptr<AbilityInfo> &abilityInfo,
    const std::shared_ptr<OHOSApplication> &application, std::shared_ptr<AbilityHandler> &handler,
    const sptr<IRemoteObject> &token)
{
    APP_LOGI("SecondAbility::Init");
    Ability::Init(abilityInfo, application, handler, token);
}

SecondAbility::~SecondAbility()
{
    CommonEventManager::UnSubscribeCommonEvent(subscriber_);
}

void SecondAbility::OnStart(const Want &want)
{
    APP_LOGI("SecondAbility::onStart");
    SubscribeEvent();
    Ability::OnStart(want);
    TestUtils::PublishEvent(g_EVENT_RESP_SECOND_B, Ability::GetState(), "onStart");
}

void SecondAbility::OnStop()
{
    APP_LOGI("SecondAbility::OnStop");
    Ability::OnStop();
    CommonEventManager::UnSubscribeCommonEvent(subscriber_);
    TestUtils::PublishEvent(g_EVENT_RESP_SECOND_B, Ability::GetState(), "OnStop");
}

void SecondAbility::OnActive()
{
    APP_LOGI("SecondAbility::OnActive");
    Ability::OnActive();
    TestUtils::PublishEvent(g_EVENT_RESP_SECOND_B, Ability::GetState(), "OnActive");
}

void SecondAbility::OnInactive()
{
    APP_LOGI("SecondAbility::OnInactive");
    Ability::OnInactive();
    TestUtils::PublishEvent(g_EVENT_RESP_SECOND_B, Ability::GetState(), "OnInactive");
}

void SecondAbility::OnBackground()
{
    APP_LOGI("SecondAbility::OnBackground");
    Ability::OnBackground();
    TestUtils::PublishEvent(g_EVENT_RESP_SECOND_B, Ability::GetState(), "OnBackground");
}

void SecondAbility::OnForeground(const Want &want)
{
    APP_LOGI("SecondAbility::OnForeground");
    Ability::OnForeground(want);
    TestUtils::PublishEvent(g_EVENT_RESP_SECOND_B, Ability::GetState(), "OnForeground");
}

void SecondAbility::SubscribeEvent()
{
    std::vector<std::string> eventList = {
        g_EVENT_REQU_SECOND_B,
    };
    MatchingSkills matchingSkills;
    for (const auto &e : eventList) {
        matchingSkills.AddEvent(e);
    }
    CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    subscribeInfo.SetPriority(1);
    subscriber_ = std::make_shared<SecondEventSubscriber>(subscribeInfo);
    subscriber_->mainAbility = this;
    CommonEventManager::SubscribeCommonEvent(subscriber_);
}

void SecondEventSubscriber::OnReceiveEvent(const CommonEventData &data)
{
    APP_LOGI("SecondEventSubscriber::OnReceiveEvent:event=%{public}s", data.GetWant().GetAction().c_str());
    APP_LOGI("SecondEventSubscriber::OnReceiveEvent:data=%{public}s", data.GetData().c_str());
    APP_LOGI("SecondEventSubscriber::OnReceiveEvent:code=%{public}d", data.GetCode());
    auto eventName = data.GetWant().GetAction();
    if (std::strcmp(eventName.c_str(), g_EVENT_REQU_SECOND_B.c_str()) == 0) {
        auto target = data.GetData();
        auto caseInfo = TestUtils::split(target, "_");
        if (caseInfo.size() < numThree) {
            return;
        }
        if (mapTestFunc_.find(caseInfo[numZero]) != mapTestFunc_.end()) {
            mapTestFunc_[caseInfo[numZero]](std::stoi(caseInfo[numOne]), std::stoi(caseInfo[numTwo]), data.GetCode());
        } else {
            APP_LOGI("OnReceiveEvent: CommonEventData error(%{public}s)", target.c_str());
        }
    }
}

void SecondAbility::TestDispatcher(int apiIndex, int caseIndex, int code)
{
    APP_LOGI("SecondAbility::TestAbility");
    if (mapCase_.find(apiIndex) != mapCase_.end()) {
        if (caseIndex < (int)mapCase_[apiIndex].size()) {
            mapCase_[apiIndex][caseIndex](code);
        }
    }
}

void SecondAbility::ExtraCase1(int code)
{}

REGISTER_AA(SecondAbility)
}  // namespace AppExecFwk
}  // namespace OHOS
