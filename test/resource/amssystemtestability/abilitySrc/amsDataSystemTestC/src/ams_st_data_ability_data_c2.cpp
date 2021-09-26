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
#include "ams_st_data_ability_data_c2.h"

#include <condition_variable>
#include <mutex>
#include <stdio.h>

#include "app_log_wrapper.h"
#include "data_ability_helper.h"

namespace OHOS {
namespace AppExecFwk {
namespace {
static const int ABILITY_DATA_C2_CODE = 240;
static const std::string OPERATOR_INSERT = "Insert";
static const std::string OPERATOR_DELETE = "Delete";
static const std::string OPERATOR_UPDATE = "Update";
static const std::string OPERATOR_QUERY = "Query";
static const std::string OPERATOR_GETFILETYPES = "GetFileTypes";
static const std::string OPERATOR_OPENFILE = "OpenFile";
static const int DEFAULT_INSERT_RESULT = 1111;
static const int DEFAULT_DELETE_RESULT = 2222;
static const int DEFAULT_UPDATE_RESULT = 3333;
static const std::string ABILITY_TYPE_PAGE = "0";
static const std::string ABILITY_TYPE_SERVICE = "1";
static const std::string ABILITY_TYPE_DATA = "2";
constexpr int charCnt = 5;
}

bool AmsStDataAbilityDataC2::PublishEvent(const std::string &eventName, const int &code, const std::string &data)
{
    Want want;
    want.SetAction(eventName);
    CommonEventData commonData;
    commonData.SetWant(want);
    commonData.SetCode(code);
    commonData.SetData(data);
    return CommonEventManager::PublishCommonEvent(commonData);
}

void DataTestDataC2EventSubscriber::OnReceiveEvent(const CommonEventData &data)
{
    APP_LOGI("DataTestDataC2EventSubscriber::OnReceiveEvent:event=%{public}s", data.GetWant().GetAction().c_str());
    APP_LOGI("DataTestDataC2EventSubscriber::OnReceiveEvent:data=%{public}s", data.GetData().c_str());
    APP_LOGI("DataTestDataC2EventSubscriber::OnReceiveEvent:code=%{public}d", data.GetCode());
    auto eventName = data.GetWant().GetAction();
    if (eventName.compare(testEventName) == 0 && ABILITY_DATA_C2_CODE == data.GetCode()) {
        std::string target = data.GetData();
        STtools::Completed(mainAbility_->event, target, ABILITY_DATA_C2_CODE);
    }
}

AmsStDataAbilityDataC2::~AmsStDataAbilityDataC2()
{
    CommonEventManager::UnSubscribeCommonEvent(subscriber_);
}

void AmsStDataAbilityDataC2::SubscribeEvent(const Want &want)
{
    std::vector<std::string> eventList = {
        testEventName,
    };
    MatchingSkills matchingSkills;
    for (const auto &e : eventList) {
        matchingSkills.AddEvent(e);
    }
    CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    subscribeInfo.SetPriority(1);
    subscriber_ = std::make_shared<DataTestDataC2EventSubscriber>(subscribeInfo, this);

    CommonEventManager::SubscribeCommonEvent(subscriber_);
}

void AmsStDataAbilityDataC2::OnStart(const Want &want)
{
    APP_LOGI("AmsStDataAbilityDataC2 OnStart");
    SubscribeEvent(want);
    originWant_ = want;
    Ability::OnStart(want);
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, "OnStart");
}

int AmsStDataAbilityDataC2::Insert(const Uri &uri, const NativeRdb::ValuesBucket &value)
{
    APP_LOGI("AmsStDataAbilityDataC2 <<<<Insert>>>>");
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, "Insert");
    return DEFAULT_INSERT_RESULT;
}

int AmsStDataAbilityDataC2::Delete(const Uri &uri, const NativeRdb::DataAbilityPredicates &predicates)
{
    APP_LOGI("AmsStDataAbilityDataC2 <<<<Delete>>>>");
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, "Delete");
    return DEFAULT_DELETE_RESULT;
}

int AmsStDataAbilityDataC2::Update(const Uri &uri, const NativeRdb::ValuesBucket &value, const NativeRdb::DataAbilityPredicates &predicates)
{
    APP_LOGI("AmsStDataAbilityDataC2 <<<<Update>>>>");
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, "Update");
    return DEFAULT_UPDATE_RESULT;
}

std::shared_ptr<NativeRdb::AbsSharedResultSet> AmsStDataAbilityDataC2::Query(
    const Uri &uri, const std::vector<std::string> &columns, const NativeRdb::DataAbilityPredicates &predicates)
{
    subscriber_->vectorOperator_ = columns;
    APP_LOGI("AmsStDataAbilityDataC2 <<<<Query>>>>");
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, OPERATOR_QUERY);

    STtools::WaitCompleted(event, OPERATOR_QUERY, ABILITY_DATA_C2_CODE);
    subscriber_->TestPost();

    std::shared_ptr<NativeRdb::AbsSharedResultSet> resultValue = std::make_shared<NativeRdb::AbsSharedResultSet>(OPERATOR_QUERY);
    AppDataFwk::SharedBlock *pSharedBlock = resultValue->GetBlock();
    if (pSharedBlock) {
        pSharedBlock->PutString(0, 0, OPERATOR_QUERY.c_str(), OPERATOR_QUERY.size() + 1);
    }
    return resultValue;
}

std::vector<std::string> AmsStDataAbilityDataC2::GetFileTypes(const Uri &uri, const std::string &mimeTypeFilter)
{
    APP_LOGI("AmsStDataAbilityDataC2 <<<<GetFileTypes>>>>");
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, "GetFileTypes");
    std::vector<std::string> fileType {"filetypes"};
    return fileType;
}

int AmsStDataAbilityDataC2::OpenFile(const Uri &uri, const std::string &mode)
{
    APP_LOGI("AmsStDataAbilityDataC2 <<<<OpenFile>>>>");
    FILE *fd1 = fopen("/system/app/test.txt", "r");
    if (fd1 == nullptr)
        return -1;
    int fd = fileno(fd1);
    APP_LOGI("AmsStDataAbilityDataC2 fd: %{public}d", fd);
    PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, "OpenFile");
    fclose(fd1);
    return fd;
}

static void GetResult(std::shared_ptr<STtools::StOperator> child, std::shared_ptr<DataAbilityHelper> helper,
    Uri dataAbilityUri, string &result)
{
    NativeRdb::DataAbilityPredicates predicates;
    NativeRdb::ValuesBucket bucket;
    result = "failed";
    if (child->GetOperatorName() == OPERATOR_INSERT) {
        result = std::to_string(helper->Insert(dataAbilityUri, bucket));
    } else if (child->GetOperatorName() == OPERATOR_DELETE) {
        result = std::to_string(helper->Delete(dataAbilityUri, predicates));
    } else if (child->GetOperatorName() == OPERATOR_UPDATE) {
        result = std::to_string(helper->Update(dataAbilityUri, bucket, predicates));
    } else if (child->GetOperatorName() == OPERATOR_QUERY) {
        std::vector<std::string> columns = STtools::SerializationStOperatorToVector(*child);
        std::shared_ptr<NativeRdb::AbsSharedResultSet> resultValue = helper->Query(dataAbilityUri, columns, predicates);
        result = "failed";
        if (resultValue != nullptr) {
            resultValue->GoToRow(0);
            resultValue->GetString(0, result);
        }
    } else if (child->GetOperatorName() == OPERATOR_GETFILETYPES) {
        std::vector<std::string> types = helper->GetFileTypes(dataAbilityUri, child->GetMessage());
        result = (types.size() > 0) ? types[0] : "failed";
    } else if (child->GetOperatorName() == OPERATOR_OPENFILE) {
        int fd = helper->OpenFile(dataAbilityUri, child->GetMessage());
        if (fd < 0) {
            return;
        }
        FILE *file = fdopen(fd, "r");
        if (file == nullptr) {
            return;
        }
        result = std::to_string(fd);
        char str[charCnt];
        if (!feof(file)) {
            fgets(str, charCnt, file);
        }
        result = str;
        fclose(file);
    }
}

void DataTestDataC2EventSubscriber::TestPost(const std::string funName)
{
    APP_LOGI("DataTestDataC2EventSubscriber::TestPost %{public}s", funName.c_str());
    STtools::StOperator allOperator {};
    STtools::DeserializationStOperatorFromVector(allOperator, vectorOperator_);
    std::shared_ptr<DataAbilityHelper> helper = DataAbilityHelper::Creator(mainAbility_->GetContext());
    for (auto child : allOperator.GetChildOperator()) {
        /// data ability
        if (child->GetAbilityType() == ABILITY_TYPE_DATA) {
            APP_LOGI("---------------------targetAbility_--------------------");
            Uri dataAbilityUri("dataability:///" + child->GetBundleName() + "." + child->GetAbilityName());
            std::string result;
            if (helper != nullptr) {
                APP_LOGI("---------------------helper--------------------");
                GetResult(child, helper, dataAbilityUri, result);
            }
            mainAbility_->PublishEvent(abilityEventName, ABILITY_DATA_C2_CODE, child->GetOperatorName() + " " + result);
        } else if (child->GetAbilityType() == ABILITY_TYPE_PAGE) {
            APP_LOGI("---------------------StartPageAbility--------------------");
            std::vector<std::string> vectoroperator;
            if (child->GetChildOperator().size() != 0) {
                vectoroperator = STtools::SerializationStOperatorToVector(*child);
            }
            std::string targetBundle = child->GetBundleName();
            std::string targetAbility = child->GetAbilityName();
            Want want;
            want.SetElementName(targetBundle, targetAbility);
            want.SetParam("operator", vectoroperator);
            mainAbility_->StartAbility(want);
        }
    }
}
REGISTER_AA(AmsStDataAbilityDataC2);
}  // namespace AppExecFwk
}  // namespace OHOS