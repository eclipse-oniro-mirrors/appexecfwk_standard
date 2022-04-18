/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_APPEXECFWK_SERVICES_BUNDLEMGR_INCLUDE_BUNDLE_SANDBOX_INSTALLER_H
#define FOUNDATION_APPEXECFWK_SERVICES_BUNDLEMGR_INCLUDE_BUNDLE_SANDBOX_INSTALLER_H

#include <string>

#include "bundle_data_mgr.h"
#include "inner_bundle_info.h"

namespace OHOS {
namespace AppExecFwk {
class BundleSandboxInstaller final {
public:
    BundleSandboxInstaller();
    ~BundleSandboxInstaller();

    /**
     * @brief The main function for sandbox app installing.
     * @param bundleName Indicates the bundleName of the sandbox application to install.
     * @param userId Indicates the sandbox app will be installed under which user id.
     * @return Returns ERR_OK if the sandbox app install successfully; returns error code otherwise.
     */
    ErrCode InstallSandboxApp(const std::string &bundleName, const int32_t &userId);
    /**
     * @brief The main function for sandbox app uninstalling.
     * @param bundleName Indicates the bundleName of the sandbox application to uninstall.
     * @param userId Indicates the sandbox app will be uninstalled under which user id.
     * @return Returns ERR_OK if the sandbox app uninstall successfully; returns error code otherwise.
     */
    ErrCode UninstallSandboxApp(const std::string &bundleName, const int32_t &appIndex, const int32_t &userId);
    /**
     * @brief The main function for sandbox app uninstalling.
     * @param bundleName Indicates the bundleName of the sandbox applications to uninstall.
     * @return Returns ERR_OK if the sandbox apps uninstall successfully; returns error code otherwise.
     */
    ErrCode UninstallAllSandboxApps(const std::string &bundleName);

protected:
    enum class SandboxInstallType : uint32_t {
        INSTALL = 0,
        UNINSTALL,
    };

private:
    ErrCode CreateSandboxDataDir(InnerBundleInfo &info, const int32_t &uid, const int32_t &appIndex) const;
    ErrCode NotifySandboxAppStatus(const InnerBundleInfo &info, const int32_t &uid,
        const SandboxInstallType &type) const;
    void SandboxAppRollBack(InnerBundleInfo &info, const int32_t &userId);
    bool GetInnerBundleInfo(InnerBundleInfo &info, bool &isAppExist);
    ErrCode GetDataMgr();
    ErrCode GetSandboxDataMgr();

    std::shared_ptr<BundleDataMgr> dataMgr_ = nullptr;
    std::shared_ptr<BundleSandboxDataMgr> sandboxDataMgr_ = nullptr;
    std::string bundleName_;
    int32_t userId_ = Constants::INVALID_USERID;
};
} // AppExecFwk
} // OHOS

#endif // FOUNDATION_APPEXECFWK_SERVICES_BUNDLEMGR_INCLUDE_BUNDLE_SANDBOX_INSTALLER_H