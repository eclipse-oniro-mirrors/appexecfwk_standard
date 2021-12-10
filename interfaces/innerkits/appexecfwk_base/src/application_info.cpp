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

#include "application_info.h"

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "nlohmann/json.hpp"
#include "string_ex.h"
#include "app_log_wrapper.h"
#include "bundle_constants.h"
#include "parcel_macro.h"
#include "json_serializer.h"

namespace OHOS {
namespace AppExecFwk {

bool ApplicationInfo::ReadFromParcel(Parcel &parcel)
{
    name = Str16ToStr8(parcel.ReadString16());
    bundleName = Str16ToStr8(parcel.ReadString16());
    description = Str16ToStr8(parcel.ReadString16());
    iconPath = Str16ToStr8(parcel.ReadString16());
    label = Str16ToStr8(parcel.ReadString16());
    deviceId = Str16ToStr8(parcel.ReadString16());
    signatureKey = Str16ToStr8(parcel.ReadString16());
    process = Str16ToStr8(parcel.ReadString16());
    entryDir = Str16ToStr8(parcel.ReadString16());
    codePath = Str16ToStr8(parcel.ReadString16());
    dataDir = Str16ToStr8(parcel.ReadString16());
    dataBaseDir = Str16ToStr8(parcel.ReadString16());
    cacheDir = Str16ToStr8(parcel.ReadString16());
    isSystemApp = parcel.ReadBool();
    isCloned = parcel.ReadBool();
    isLauncherApp = parcel.ReadBool();
    enabled = parcel.ReadBool();
    debug = parcel.ReadBool();
    singleUser = parcel.ReadBool();
    supportedModes = parcel.ReadInt32();
    labelId = parcel.ReadInt32();
    iconId = parcel.ReadInt32();
    descriptionId = parcel.ReadInt32();
    flags = parcel.ReadInt32();
    uid = parcel.ReadInt32();

    int32_t permissionsSize;
    READ_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, permissionsSize);
    for (int32_t i = 0; i < permissionsSize; i++) {
        permissions.emplace_back(Str16ToStr8(parcel.ReadString16()));
    }

    int32_t moduleSourceDirsSize;
    READ_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, moduleSourceDirsSize);
    for (int32_t i = 0; i < moduleSourceDirsSize; i++) {
        moduleSourceDirs.emplace_back(Str16ToStr8(parcel.ReadString16()));
    }

    int32_t moduleInfosSize = parcel.ReadInt32();
    for (int32_t i = 0; i < moduleInfosSize; i++) {
        std::unique_ptr<ModuleInfo> moduleInfo(parcel.ReadParcelable<ModuleInfo>());
        if (!moduleInfo) {
            APP_LOGE("ReadParcelable<ModuleInfo> failed");
            return false;
        }
        moduleInfos.emplace_back(*moduleInfo);
    }
    return true;
}

ApplicationInfo *ApplicationInfo::Unmarshalling(Parcel &parcel)
{
    ApplicationInfo *info = new (std::nothrow) ApplicationInfo();
    if (info && !info->ReadFromParcel(parcel)) {
        APP_LOGW("read from parcel failed");
        delete info;
        info = nullptr;
    }
    return info;
}

bool ApplicationInfo::Marshalling(Parcel &parcel) const
{
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(name));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(bundleName));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(description));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(iconPath));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(label));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(deviceId));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(signatureKey));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(process));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(entryDir));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(codePath));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(dataDir));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(dataBaseDir));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(cacheDir));
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Bool, parcel, isSystemApp);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Bool, parcel, isCloned);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Bool, parcel, isLauncherApp);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Bool, parcel, enabled);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Bool, parcel, debug);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Bool, parcel, singleUser);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, supportedModes);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, labelId);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, iconId);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, descriptionId);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, flags);
    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, uid);

    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, permissions.size());
    for (auto &permission : permissions) {
        WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(permission));
    }

    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, moduleSourceDirs.size());
    for (auto &moduleSourceDir : moduleSourceDirs) {
        WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(String16, parcel, Str8ToStr16(moduleSourceDir));
    }

    WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Int32, parcel, moduleInfos.size());
    for (auto &moduleInfo : moduleInfos) {
        WRITE_PARCEL_AND_RETURN_FALSE_IF_FAIL(Parcelable, parcel, &moduleInfo);
    }
    return true;
}

void ApplicationInfo::Dump(std::string prefix, int fd)
{
    APP_LOGI("called dump ApplicationInfo");
    if (fd < 0) {
        APP_LOGE("dump ApplicationInfo fd error");
        return;
    }
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        APP_LOGE("dump ApplicationInfo fcntl error %{public}s", strerror(errno));
        return;
    }
    uint uflags = static_cast<uint>(flags);
    uflags &= O_ACCMODE;
    if ((uflags == O_WRONLY) || (uflags == O_RDWR)) {
        nlohmann::json jsonObject = *this;
        std::string result;
        result.append(prefix);
        result.append(jsonObject.dump(Constants::DUMP_INDENT));
        int ret = TEMP_FAILURE_RETRY(write(fd, result.c_str(), result.size()));
        if (ret < 0) {
            APP_LOGE("dump ApplicationInfo write error %{public}s", strerror(errno));
        }
    }
    return;
}

void to_json(nlohmann::json &jsonObject, const ApplicationInfo &applicationInfo)
{
    jsonObject = nlohmann::json{
        {"name", applicationInfo.name},
        {"bundleName", applicationInfo.bundleName},
        {"description", applicationInfo.description},
        {"iconPath", applicationInfo.iconPath},
        {"label", applicationInfo.label},
        {"labelId", applicationInfo.labelId},
        {"descriptionId", applicationInfo.descriptionId},
        {"iconId", applicationInfo.iconId},
        {"deviceId", applicationInfo.deviceId},
        {"signatureKey", applicationInfo.signatureKey},
        {"isSystemApp", applicationInfo.isSystemApp},
        {"isCloned", applicationInfo.isCloned},
        {"isLauncherApp", applicationInfo.isLauncherApp},
        {"enabled", applicationInfo.enabled},
        {"debug", applicationInfo.debug},
        {"supportedModes", applicationInfo.supportedModes},
        {"process", applicationInfo.process},
        {"permissions", applicationInfo.permissions},
        {"moduleSourceDirs", applicationInfo.moduleSourceDirs},
        {"moduleInfos", applicationInfo.moduleInfos},
        {"entryDir", applicationInfo.entryDir},
        {"codePath", applicationInfo.codePath},
        {"dataDir", applicationInfo.dataDir},
        {"dataBaseDir", applicationInfo.dataBaseDir},
        {"cacheDir", applicationInfo.cacheDir},
        {"flags", applicationInfo.flags},
        {"uid", applicationInfo.uid},
        {"singleUser", applicationInfo.singleUser}
    };
}

void from_json(const nlohmann::json &jsonObject, ApplicationInfo &applicationInfo)
{
    applicationInfo.name = jsonObject.at("name").get<std::string>();
    applicationInfo.bundleName = jsonObject.at("bundleName").get<std::string>();
    applicationInfo.description = jsonObject.at("description").get<std::string>();
    applicationInfo.iconPath = jsonObject.at("iconPath").get<std::string>();
    applicationInfo.label = jsonObject.at("label").get<std::string>();
    applicationInfo.labelId = jsonObject.at("labelId").get<int32_t>();
    applicationInfo.descriptionId = jsonObject.at("descriptionId").get<int32_t>();
    applicationInfo.iconId = jsonObject.at("iconId").get<int32_t>();
    applicationInfo.deviceId = jsonObject.at("deviceId").get<std::string>();
    applicationInfo.signatureKey = jsonObject.at("signatureKey").get<std::string>();
    applicationInfo.isSystemApp = jsonObject.at("isSystemApp").get<bool>();
    applicationInfo.isCloned = jsonObject.at("isCloned").get<bool>();
    applicationInfo.isLauncherApp = jsonObject.at("isLauncherApp").get<bool>();
    applicationInfo.singleUser = jsonObject.at("singleUser").get<bool>();
    applicationInfo.enabled = jsonObject.at("enabled").get<bool>();
    applicationInfo.debug = jsonObject.at("debug").get<bool>();
    applicationInfo.supportedModes = jsonObject.at("supportedModes").get<int>();
    applicationInfo.process = jsonObject.at("process").get<std::string>();
    applicationInfo.permissions = jsonObject.at("permissions").get<std::vector<std::string>>();
    applicationInfo.moduleSourceDirs = jsonObject.at("moduleSourceDirs").get<std::vector<std::string>>();
    applicationInfo.moduleInfos = jsonObject.at("moduleInfos").get<std::vector<ModuleInfo>>();
    applicationInfo.entryDir = jsonObject.at("entryDir").get<std::string>();
    applicationInfo.codePath = jsonObject.at("codePath").get<std::string>();
    applicationInfo.dataDir = jsonObject.at("dataDir").get<std::string>();
    applicationInfo.dataBaseDir = jsonObject.at("dataBaseDir").get<std::string>();
    applicationInfo.cacheDir = jsonObject.at("cacheDir").get<std::string>();
    applicationInfo.flags = jsonObject.at("flags").get<int>();
    applicationInfo.uid = jsonObject.at("uid").get<int>();
}

void ApplicationInfo::ConvertToCompatibleApplicationInfo(CompatibleApplicationInfo& compatibleApplicationInfo) const
{
    APP_LOGD("ApplicationInfo::ConvertToCompatibleApplicationInfo called");
    compatibleApplicationInfo.name = name;
    compatibleApplicationInfo.icon = icon;
    compatibleApplicationInfo.label = label;
    compatibleApplicationInfo.description = description;
    compatibleApplicationInfo.cpuAbi = cpuAbi;
    compatibleApplicationInfo.process = process;
    compatibleApplicationInfo.systemApp = isSystemApp;
    compatibleApplicationInfo.isCompressNativeLibs = isCompressNativeLibs;
    compatibleApplicationInfo.iconId = iconId;
    compatibleApplicationInfo.labelId = labelId;
    compatibleApplicationInfo.descriptionId = descriptionId;
    compatibleApplicationInfo.permissions = permissions;
    compatibleApplicationInfo.moduleInfos = moduleInfos;
    compatibleApplicationInfo.supportedModes = supportedModes;
    compatibleApplicationInfo.enabled = enabled;
    compatibleApplicationInfo.debug = debug;
}

}  // namespace AppExecFwk
}  // namespace OHOS