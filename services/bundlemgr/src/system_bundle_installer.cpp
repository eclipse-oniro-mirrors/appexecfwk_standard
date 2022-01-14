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

#include "system_bundle_installer.h"

#include "app_log_wrapper.h"

namespace OHOS {
namespace AppExecFwk {
SystemBundleInstaller::SystemBundleInstaller(const std::string &filePath) : filePath_(filePath)
{
    APP_LOGI("system bundle installer instance is created");
}

SystemBundleInstaller::~SystemBundleInstaller()
{
    APP_LOGI("system bundle installer instance is destroyed");
}

bool SystemBundleInstaller::InstallSystemBundle(Constants::AppType appType, int32_t userId)
{
    InstallParam installParam;
    installParam.userId = userId;
    installParam.isPreInstallApp = true;
    if (appType == Constants::AppType::SYSTEM_APP
        || appType == Constants::AppType::THIRD_SYSTEM_APP) {
        installParam.needSavePreInstallInfo = true;
    }
    ErrCode result = InstallBundle(filePath_, installParam, appType);
    if (result != ERR_OK) {
        APP_LOGE("install system bundle fail, error: %{public}d", result);
        return false;
    }
    return true;
}
}  // namespace AppExecFwk
}  // namespace OHOS
