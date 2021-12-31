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
#ifndef AMS_ST_KIT_DATA_ABILITY_DATA_A1_H
#define AMS_ST_KIT_DATA_ABILITY_DATA_A1_H
#include <string>

#include "ability.h"
#include "ability_lifecycle_callbacks.h"
#include "ability_lifecycle_observer_interface.h"
#include "ability_loader.h"
#include "common_event_manager.h"
#include "event.h"
#include "skills.h"
#include "stoperator.h"
#include "abs_shared_result_set.h"
#include "data_ability_predicates.h"
#include "values_bucket.h"

namespace OHOS {
namespace AppExecFwk {
using namespace OHOS::EventFwk;

const std::string abilityEventName = "event_data_ability_callback";
const std::string testEventName = "event_data_test_action";

class KitTestDataA1EventSubscriber;
class AmsStKitDataAbilityDataA1 : public Ability {
public:
    void SubscribeEvent(const Want &want);
    bool PublishEvent(const std::string &eventName, const int &code, const std::string &data);
    STtools::Event event;
    FILE *fd1 = nullptr;
    void TestLifeCycle();
    ~AmsStKitDataAbilityDataA1();

protected:
    virtual void OnStart(const Want &want) override;
    virtual void OnStop() override;
    virtual void OnActive() override;
    virtual void OnInactive() override;
    virtual void OnForeground(const Want &want) override;
    virtual void OnBackground() override;
    virtual void OnNewWant(const Want &want) override;

    void Init(const std::shared_ptr<AbilityInfo> &abilityInfo, const std::shared_ptr<OHOSApplication> &application,
        std::shared_ptr<AbilityHandler> &handler, const sptr<IRemoteObject> &token) override;
    virtual int Insert(const Uri &uri, const NativeRdb::ValuesBucket &value) override;
    virtual int Delete(const Uri &uri, const NativeRdb::DataAbilityPredicates &predicates) override;
    virtual int Update(const Uri &uri, const NativeRdb::ValuesBucket &value, const NativeRdb::DataAbilityPredicates &predicates) override;
    virtual std::shared_ptr<NativeRdb::AbsSharedResultSet> Query(
        const Uri &uri, const std::vector<std::string> &columns, const NativeRdb::DataAbilityPredicates &predicates) override;
    virtual std::vector<std::string> GetFileTypes(const Uri &uri, const std::string &mimeTypeFilter) override;
    virtual int OpenFile(const Uri &uri, const std::string &mode) override;

private:
    Want originWant_;
    std::shared_ptr<KitTestDataA1EventSubscriber> subscriber_;
};

class AmsStKitDataAbilityDataA1LifecycleCallbacks : public AbilityLifecycleCallbacks {
public:
    AmsStKitDataAbilityDataA1LifecycleCallbacks()
    {
        mainAbility_ = nullptr;
    };
    virtual ~AmsStKitDataAbilityDataA1LifecycleCallbacks() = default;

    virtual void OnAbilityStart(const std::shared_ptr<Ability> &ability) override;
    virtual void OnAbilityInactive(const std::shared_ptr<Ability> &ability) override;
    virtual void OnAbilityBackground(const std::shared_ptr<Ability> &ability) override;
    virtual void OnAbilityForeground(const std::shared_ptr<Ability> &ability) override;
    virtual void OnAbilityActive(const std::shared_ptr<Ability> &ability) override;
    virtual void OnAbilityStop(const std::shared_ptr<Ability> &ability) override;
    virtual void OnAbilitySaveState(const PacMap &outState) override;
    AmsStKitDataAbilityDataA1 *mainAbility_;
};

class AmsStKitDataAbilityDataA1LifecycleObserver : public ILifecycleObserver {
public:
    AmsStKitDataAbilityDataA1LifecycleObserver() = default;
    virtual ~AmsStKitDataAbilityDataA1LifecycleObserver() = default;
    void OnActive() override;
    void OnBackground() override;
    void OnForeground(const Want &want) override;
    void OnInactive() override;
    void OnStart(const Want &want) override;
    void OnStop() override;
    void OnStateChanged(LifeCycle::Event event, const Want &want) override;
    void OnStateChanged(LifeCycle::Event event) override;
    AmsStKitDataAbilityDataA1 *mainAbility_;
};

class KitTestDataA1EventSubscriber : public CommonEventSubscriber {
public:
    KitTestDataA1EventSubscriber(const CommonEventSubscribeInfo &sp, AmsStKitDataAbilityDataA1 *ability)
        : CommonEventSubscriber(sp)
    {
        mainAbility_ = ability;
    };

    virtual void OnReceiveEvent(const CommonEventData &data);

    void TestPost(const std::string funName = "");
    std::vector<std::string> vectorOperator_;
    AmsStKitDataAbilityDataA1 *mainAbility_;
    ~KitTestDataA1EventSubscriber(){};
};
}  // namespace AppExecFwk
}  // namespace OHOS
#endif  // AMS_ST_KIT_DATA_ABILITY_DATA_A1_H