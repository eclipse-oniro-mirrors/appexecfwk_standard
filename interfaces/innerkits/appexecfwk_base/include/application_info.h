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

#ifndef FOUNDATION_APPEXECFWK_INTERFACES_INNERKITS_APPEXECFWK_BASE_INCLUDE_APPLICATION_INFO_H
#define FOUNDATION_APPEXECFWK_INTERFACES_INNERKITS_APPEXECFWK_BASE_INCLUDE_APPLICATION_INFO_H

#include <string>
#include <vector>

#include "parcel.h"

#include "module_info.h"

namespace OHOS {
namespace AppExecFwk {
enum class ApplicationFlag {
    // get the basic ApplicationInfo
    GET_BASIC_APPLICATION_INFO = 0x00000000,
    // get the ApplicationInfo with permission specified
    GET_APPLICATION_INFO_WITH_PERMS = 0x00000008,
};

struct ApplicationInfo;

struct CompatibleApplicationInfo : public Parcelable {    
    // items set when installing.
    std::string name; // application name.
    std::string icon; // application icon resource index.
    std::string label; // application name displayed to the user.
    std::string description; // description of application.
    std::string cpuAbi; // current device cpu abi.
    std::string process;
    bool isCompressNativeLibs = true;

    uint32_t iconId = 0;
    uint32_t labelId = 0;
    uint32_t descriptionId = 0;

    bool systemApp = false;

    std::vector<std::string> permissions;
    std::vector<ModuleInfo> moduleInfos;

    uint32_t supportedModes = 0; // supported modes.
    bool enabled = true;
    bool debug = false;

    bool ReadFromParcel(Parcel& parcel);
    virtual bool Marshalling(Parcel& parcel) const override;
    static CompatibleApplicationInfo* Unmarshalling(Parcel& parcel);
    void ConvertToApplicationInfo(ApplicationInfo& applicationInfo) const;
};

// configuration information about an application
struct ApplicationInfo : public Parcelable {
    std::string name;  // application name is same to bundleName
    std::string bundleName;
    std::string description;
    std::string iconPath;
    std::string label;  // entity.system.home ability label
    int32_t labelId = 0;
    int32_t iconId = 0;
    int32_t descriptionId = 0;
    std::string deviceId;      // should auto-get self device id.
    std::string signatureKey;  // the public key info of this application.
    bool isSystemApp = false;
    bool isLauncherApp = false;
    int supportedModes = 0;  // returns 0 if the application does not support the driving mode
    std::string process;
    std::vector<std::string> permissions;
    std::vector<std::string> moduleSourceDirs;
    std::vector<ModuleInfo> moduleInfos;
    std::string entryDir;
    std::string codePath;
    std::string dataDir;
    std::string dataBaseDir;
    std::string cacheDir;
    int flags = 0;
    bool enabled = false;
    // Clone the required elements
    bool isCloned = false;
    int uid = -1;
    //  element that does not exist for a while
    std::string entryModuleName;
    std::string icon;
    std::string cpuAbi;
    bool isCompressNativeLibs = true;
    bool debug = false;
    bool systemApp = false;

    bool ReadFromParcel(Parcel &parcel);
    virtual bool Marshalling(Parcel &parcel) const override;
    static ApplicationInfo *Unmarshalling(Parcel &parcel);
    void Dump(std::string prefix, int fd);
    void ConvertToCompatibleApplicationInfo(CompatibleApplicationInfo& compatibleApplicationInfo) const;
};
}  // namespace AppExecFwk
}  // namespace OHOS
#endif  // FOUNDATION_APPEXECFWK_INTERFACES_INNERKITS_APPEXECFWK_BASE_INCLUDE_APPLICATION_INFO_H
