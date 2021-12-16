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
#include "context_container.h"
#include "app_log_wrapper.h"
#include "ability_manager_errors.h"
#include "application_context.h"
#include "bundle_constants.h"
#include "ability_manager_client.h"

namespace OHOS {
namespace AppExecFwk {
/**
 * Attaches a Context object to the current ability.
 * Generally, this method is called after Ability is loaded to provide the application context for the current ability.
 *
 * @param base Indicates a Context object.
 */
void ContextContainer::AttachBaseContext(const std::shared_ptr<Context> &base)
{
    if (base == nullptr) {
        APP_LOGE("ContextDeal::AttachBaseContext failed, base is nullptr");
        return;
    }
    baseContext_ = base;
}

/**
 * Called when getting the ProcessInfo
 *
 * @return ProcessInfo
 */
std::shared_ptr<ProcessInfo> ContextContainer::GetProcessInfo() const
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetProcessInfo();
    }
    return nullptr;
}

/**
 * @brief Obtains information about the current application. The returned application information includes basic
 * information such as the application name and application permissions.
 *
 * @return Returns the ApplicationInfo for the current application.
 */
std::shared_ptr<ApplicationInfo> ContextContainer::GetApplicationInfo() const
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetApplicationInfo();
    } else {
        APP_LOGE("ContextContainer::GetApplicationInfo baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains the Context object of the application.
 *
 * @return Returns the Context object of the application.
 */
std::shared_ptr<Context> ContextContainer::GetApplicationContext() const
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetApplicationContext();
    } else {
        APP_LOGE("ContextContainer::GetApplicationContext baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains the path of the package containing the current ability. The returned path contains the resources,
 *  source code, and configuration files of a module.
 *
 * @return Returns the path of the package file.
 */
std::string ContextContainer::GetBundleCodePath()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetBundleCodePath();
    } else {
        APP_LOGE("ContextContainer::GetBundleCodePath baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains information about the current ability.
 * The returned information includes the class name, bundle name, and other information about the current ability.
 *
 * @return Returns the AbilityInfo object for the current ability.
 */
const std::shared_ptr<AbilityInfo> ContextContainer::GetAbilityInfo()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetAbilityInfo();
    } else {
        APP_LOGE("ContextContainer::GetAbilityInfo baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains the Context object of the application.
 *
 * @return Returns the Context object of the application.
 */
std::shared_ptr<Context> ContextContainer::GetContext()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetContext();
    } else {
        APP_LOGE("ContextContainer::GetContext baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains an IBundleMgr instance.
 * You can use this instance to obtain information about the application bundle.
 *
 * @return Returns an IBundleMgr instance.
 */
sptr<IBundleMgr> ContextContainer::GetBundleManager() const
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetBundleManager();
    } else {
        APP_LOGE("ContextContainer::GetBundleManager baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains a resource manager.
 *
 * @return Returns a ResourceManager object.
 */
std::shared_ptr<Global::Resource::ResourceManager> ContextContainer::GetResourceManager() const
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetResourceManager();
    } else {
        APP_LOGE("ContextContainer::GetResourceManager baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Deletes the specified private file associated with the application.
 *
 * @param fileName Indicates the name of the file to delete. The file name cannot contain path separators.
 *
 * @return Returns true if the file is deleted successfully; returns false otherwise.
 */
bool ContextContainer::DeleteFile(const std::string &fileName)
{
    if (baseContext_ != nullptr) {
        return baseContext_->DeleteFile(fileName);
    } else {
        APP_LOGE("ContextContainer::DeleteFile baseContext_ is nullptr");
        return false;
    }
}

/**
 * @brief Obtains the application-specific cache directory on the device's internal storage. The system
 * automatically deletes files from the cache directory if disk space is required elsewhere on the device.
 * Older files are always deleted first.
 *
 * @return Returns the application-specific cache directory.
 */
std::string ContextContainer::GetCacheDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetCacheDir();
    } else {
        APP_LOGE("ContextContainer::GetCacheDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the application-specific code-cache directory on the device's internal storage.
 * The system will delete any files stored in this location both when your specific application is upgraded,
 * and when the entire platform is upgraded.
 *
 * @return Returns the application-specific code-cache directory.
 */
std::string ContextContainer::GetCodeCacheDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetCodeCacheDir();
    } else {
        APP_LOGE("ContextContainer::GetCodeCacheDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the local database path.
 * If the local database path does not exist, the system creates one and returns the created path.
 *
 * @return Returns the local database file.
 */
std::string ContextContainer::GetDatabaseDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetDatabaseDir();
    } else {
        APP_LOGE("ContextContainer::GetDatabaseDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the absolute path where all private data files of this application are stored.
 *
 * @return Returns the absolute path storing all private data files of this application.
 */
std::string ContextContainer::GetDataDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetDataDir();
    } else {
        APP_LOGE("ContextContainer::GetDataDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the directory for storing custom data files of the application.
 * You can use the returned File object to create and access files in this directory. The files
 * can be accessible only by the current application.
 *
 * @param name Indicates the name of the directory to retrieve. This directory is created as part
 * of your application data.
 * @param mode Indicates the file operating mode. The value can be 0 or a combination of MODE_PRIVATE.
 *
 * @return Returns a File object for the requested directory.
 */
std::string ContextContainer::GetDir(const std::string &name, int mode)
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetDir(name, mode);
    } else {
        APP_LOGE("ContextContainer::GetDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the absolute path to the application-specific cache directory
 * on the primary external or shared storage device.
 *
 * @return Returns the absolute path to the application-specific cache directory on the external or
 * shared storage device; returns null if the external or shared storage device is temporarily unavailable.
 */
std::string ContextContainer::GetExternalCacheDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetExternalCacheDir();
    } else {
        APP_LOGE("ContextContainer::GetExternalCacheDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the absolute path to the directory for storing files for the application on the
 * primary external or shared storage device.
 *
 * @param type Indicates the type of the file directory to return
 *
 * @return Returns the absolute path to the application file directory on the external or shared storage
 * device; returns null if the external or shared storage device is temporarily unavailable.
 */
std::string ContextContainer::GetExternalFilesDir(std::string &type)
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetExternalFilesDir(type);
    } else {
        APP_LOGE("ContextContainer::GetExternalFilesDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the directory for storing files for the application on the device's internal storage.
 *
 * @return Returns the application file directory.
 */
std::string ContextContainer::GetFilesDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetFilesDir();
    } else {
        APP_LOGE("ContextContainer::GetFilesDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the absolute path which app created and will be excluded from automatic backup to remote storage.
 * The returned path maybe changed if the application is moved to an adopted storage device.
 *
 * @return The path of the directory holding application files that will not be automatically backed up to remote
 * storage.
 */
std::string ContextContainer::GetNoBackupFilesDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetNoBackupFilesDir();
    } else {
        APP_LOGE("ContextContainer::GetNoBackupFilesDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Checks whether the calling process for inter-process communication has the given permission.
 * The calling process is not the current process.
 *
 * @param permission Indicates the permission to check. This parameter cannot be null.
 *
 * @return Returns 0 (IBundleManager.PERMISSION_GRANTED) if the calling process has the permission;
 * returns -1 (IBundleManager.PERMISSION_DENIED) otherwise.
 */
int ContextContainer::VerifyCallingPermission(const std::string &permission)
{
    if (baseContext_ != nullptr) {
        return baseContext_->VerifyCallingPermission(permission);
    } else {
        APP_LOGE("ContextContainer::VerifyCallingPermission baseContext_ is nullptr");
        return AppExecFwk::Constants::PERMISSION_NOT_GRANTED;
    }
}

/**
 * @brief Checks whether the current process has the given permission.
 * You need to call requestPermissionsFromUser(java.lang.std::string[],int) to request a permission only
 * if the current process does not have the specific permission.
 *
 * @param permission Indicates the permission to check. This parameter cannot be null.
 *
 * @return Returns 0 (IBundleManager.PERMISSION_GRANTED) if the current process has the permission;
 * returns -1 (IBundleManager.PERMISSION_DENIED) otherwise.
 */
int ContextContainer::VerifySelfPermission(const std::string &permission)
{
    if (baseContext_ != nullptr) {
        return baseContext_->VerifySelfPermission(permission);
    } else {
        APP_LOGE("ContextContainer::VerifySelfPermission baseContext_ is nullptr");
        return AppExecFwk::Constants::PERMISSION_NOT_GRANTED;
    }
}

/**
 * @brief Obtains the bundle name of the current ability.
 *
 * @return Returns the bundle name of the current ability.
 */
std::string ContextContainer::GetBundleName()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetBundleName();
    } else {
        APP_LOGE("ContextContainer::GetBundleName baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Obtains the path of the OHOS Ability Package (HAP} containing this ability.
 *
 * @return Returns the path of the HAP containing this ability.
 */
std::string ContextContainer::GetBundleResourcePath()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetBundleResourcePath();
    } else {
        APP_LOGE("ContextContainer::GetBundleResourcePath baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Remove permissions for all users who have access to specific permissions
 *
 * @param permission Indicates the permission to unauth. This parameter cannot be null.
 * @param uri Indicates the URI to unauth. This parameter cannot be null.
 * @param uid Indicates the UID of the unauth to check.
 *
 */
void ContextContainer::UnauthUriPermission(const std::string &permission, const Uri &uri, int uid)
{
    if (baseContext_ != nullptr) {
        baseContext_->UnauthUriPermission(permission, uri, uid);
    } else {
        APP_LOGE("ContextContainer::UnauthUriPermission baseContext_ is nullptr");
    }
}

/**
 * @brief Obtains an ability manager.
 * The ability manager provides information about running processes and memory usage of an application.
 *
 * @return Returns an IAbilityManager instance.
 */
sptr<AAFwk::IAbilityManager> ContextContainer::GetAbilityManager()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetAbilityManager();
    } else {
        APP_LOGE("ContextContainer::GetAbilityManager baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains the type of this application.
 *
 * @return Returns system if this application is a system application;
 * returns normal if it is released in OHOS AppGallery;
 * returns other if it is released by a third-party vendor;
 * returns an empty string if the query fails.
 */
std::string ContextContainer::GetAppType()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetAppType();
    } else {
        APP_LOGE("ContextContainer::GetAppType baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Confirms with the permission management module to check whether a request prompt is required for granting a
 * certain permission. You need to call the current method to check whether a prompt is required before calling
 * requestPermissionsFromUser(java.lang.String[],int) to request a permission. If a prompt is not required, permission
 * request will not be initiated.
 *
 * @param requestCode Indicates the permission to be queried. This parameter cannot be null.
 *
 * @return Returns true if the current application does not have the permission and the user does not turn off further
 * requests; returns false if the current application already has the permission, the permission is rejected by the
 * system, or the permission is denied by the user and the user has turned off further requests.
 */
bool ContextContainer::CanRequestPermission(const std::string &permission)
{
    if (baseContext_ != nullptr) {
        return baseContext_->CanRequestPermission(permission);
    } else {
        APP_LOGE("ContextContainer::CanRequestPermission baseContext_ is nullptr");
        return true;
    }
}

/**
 * @brief When there is a remote call to check whether the remote has permission, otherwise check whether it has
 * permission
 *
 * @param permissions Indicates the list of permissions to be requested. This parameter cannot be null.
 * @return Returns 0 (IBundleManager.PERMISSION_GRANTED) if the current process has the permission;
 * returns -1 (IBundleManager.PERMISSION_DENIED) otherwise.
 */
int ContextContainer::VerifyCallingOrSelfPermission(const std::string &permission)
{
    if (baseContext_ != nullptr) {
        return baseContext_->VerifyCallingOrSelfPermission(permission);
    } else {
        APP_LOGE("ContextContainer::VerifyCallingOrSelfPermission baseContext_ is nullptr");
        return AppExecFwk::Constants::PERMISSION_NOT_GRANTED;
    }
}

/**
 * @brief Query whether the application of the specified PID and UID has been granted a certain permission
 *
 * @param permissions Indicates the list of permissions to be requested. This parameter cannot be null.
 * @param pid Process id
 * @param uid
 * @return Returns 0 (IBundleManager.PERMISSION_GRANTED) if the current process has the permission;
 * returns -1 (IBundleManager.PERMISSION_DENIED) otherwise.
 */
int ContextContainer::VerifyPermission(const std::string &permission, int pid, int uid)
{
    if (baseContext_ != nullptr) {
        return baseContext_->VerifyPermission(permission, pid, uid);
    } else {
        APP_LOGE("ContextContainer::VerifyPermission baseContext_ is nullptr");
        return AppExecFwk::Constants::PERMISSION_NOT_GRANTED;
    }
}

/**
 * @brief Obtains the distributed file path.
 * If the distributed file path does not exist, the system creates one and returns the created path. This method is
 * applicable only to the context of an ability rather than that of an application.
 *
 * @return Returns the distributed file.
 */
std::string ContextContainer::GetDistributedDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetDistributedDir();
    } else {
        APP_LOGE("ContextContainer::GetDistributedDir baseContext_ is nullptr");
        return "";
    }
}
/**
 * @brief Sets the pattern of this Context based on the specified pattern ID.
 *
 * @param patternId Indicates the resource ID of the pattern to set.
 */
void ContextContainer::SetPattern(int patternId)
{
    if (baseContext_ != nullptr) {
        baseContext_->SetPattern(patternId);
    } else {
        APP_LOGE("ContextContainer::SetPattern baseContext_ is nullptr");
    }
}

/**
 * @brief Obtains the Context object of this ability.
 *
 * @return Returns the Context object of this ability.
 */
std::shared_ptr<Context> ContextContainer::GetAbilityPackageContext()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetAbilityPackageContext();
    } else {
        APP_LOGE("ContextContainer::GetAbilityPackageContext baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains the HapModuleInfo object of the application.
 *
 * @return Returns the HapModuleInfo object of the application.
 */
std::shared_ptr<HapModuleInfo> ContextContainer::GetHapModuleInfo()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetHapModuleInfo();
    } else {
        APP_LOGE("ContextContainer::GetHapModuleInfo baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains the name of the current process.
 *
 * @return Returns the current process name.
 */
std::string ContextContainer::GetProcessName()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetProcessName();
    } else {
        APP_LOGE("ContextContainer::GetProcessName baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Requests certain permissions from the system.
 * This method is called for permission request. This is an asynchronous method. When it is executed,
 * the Ability.onRequestPermissionsFromUserResult(int, String[], int[]) method will be called back.
 *
 * @param permissions Indicates the list of permissions to be requested. This parameter cannot be null.
 * @param requestCode Indicates the request code to be passed to the Ability.onRequestPermissionsFromUserResult(int,
 * String[], int[]) callback method. This code cannot be a negative number.
 *
 */
void ContextContainer::RequestPermissionsFromUser(std::vector<std::string> &permissions, int requestCode)
{
    if (baseContext_ != nullptr) {
        baseContext_->RequestPermissionsFromUser(permissions, requestCode);
    } else {
        APP_LOGE("ContextContainer::RequestPermissionsFromUser baseContext_ is nullptr");
    }
}

/**
 * @brief Creates a Context object for an application with the given bundle name.
 *
 * @param bundleName Indicates the bundle name of the application.
 *
 * @param flag  Indicates the flag for creating a Context object. It can be 0, any of
 * the following values, or any combination of the following values: CONTEXT_IGNORE_SECURITY,
 * CONTEXT_INCLUDE_CODE, and CONTEXT_RESTRICTED. The value 0 indicates that there is no restriction
 * on creating contexts for applications.
 *
 * @return Returns a Context object created for the specified application.
 */
std::shared_ptr<Context> ContextContainer::CreateBundleContext(std::string bundleName, int flag)
{
    if (bundleName.empty()) {
        APP_LOGE("ContextContainer::CreateBundleContext bundleName is empty");
        return nullptr;
    }

    if (strcmp(bundleName.c_str(), GetBundleName().c_str()) == 0) {
        return GetApplicationContext();
    }

    sptr<IBundleMgr> bundleMgr = GetBundleManager();
    if (nullptr == bundleMgr) {
        APP_LOGE("ContextContainer::CreateBundleContext GetBundleManager is nullptr");
        return nullptr;
    }

    BundleInfo bundleInfo;
    APP_LOGI("ContextContainer::CreateBundleContext length: %{public}zu, bundleName: %{public}s",
        bundleName.length(),
        bundleName.c_str());
    bundleMgr->GetBundleInfo(bundleName, BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo);

    if (bundleInfo.name.empty() || bundleInfo.applicationInfo.name.empty()) {
        APP_LOGE("ContextContainer::CreateBundleContext GetBundleInfo is error");
        return nullptr;
    }

    std::shared_ptr<ApplicationContext> appContext = std::make_shared<ApplicationContext>();
    if (appContext == nullptr) {
        APP_LOGE("ContextContainer::CreateBundleContext appContext is nullptr");
        return nullptr;
    }
    std::shared_ptr<ContextDeal> deal = std::make_shared<ContextDeal>();
    if (deal == nullptr) {
        APP_LOGE("ContextContainer::CreateBundleContext bundleName is empty");
        return nullptr;
    }

    // init resourceManager.
    InitResourceManager(bundleInfo, deal);

    deal->SetApplicationInfo(std::make_shared<ApplicationInfo>(bundleInfo.applicationInfo));
    appContext->AttachBaseContext(deal);
    return appContext;
}

void ContextContainer::InitResourceManager(BundleInfo &bundleInfo, std::shared_ptr<ContextDeal> &deal)
{
    std::shared_ptr<Global::Resource::ResourceManager> resourceManager(Global::Resource::CreateResourceManager());
    if (deal == nullptr || resourceManager == nullptr) {
        APP_LOGE("ContextContainer::InitResourceManager create resourceManager failed");
        return;
    }

    APP_LOGI(
        "ContextContainer::InitResourceManager moduleResPaths count: %{public}zu", bundleInfo.moduleResPaths.size());
    for (auto moduleResPath : bundleInfo.moduleResPaths) {
        if (!moduleResPath.empty()) {
            APP_LOGI("ContextContainer::InitResourceManager length: %{public}zu, moduleResPath: %{public}s",
                moduleResPath.length(),
                moduleResPath.c_str());
            if (!resourceManager->AddResource(moduleResPath.c_str())) {
                APP_LOGE("ContextContainer::InitResourceManager AddResource failed");
            }
        }
    }

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    resConfig->SetLocaleInfo("zh", "Hans", "CN");
    if (resConfig->GetLocaleInfo() != nullptr) {
        APP_LOGI("ContextContainer::InitResourceManager language: %{public}s, script: %{public}s, region: %{public}s,",
            resConfig->GetLocaleInfo()->getLanguage(),
            resConfig->GetLocaleInfo()->getScript(),
            resConfig->GetLocaleInfo()->getCountry());
    } else {
        APP_LOGI("ContextContainer::InitResourceManager language: GetLocaleInfo is null.");
    }
    resourceManager->UpdateResConfig(*resConfig);
    deal->initResourceManager(resourceManager);
}
/**
 * @brief Obtains information about the caller of this ability.
 *
 * @return Returns the caller information.
 */
Uri ContextContainer::GetCaller()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetCaller();
    } else {
        APP_LOGE("ContextContainer::GetCaller baseContext_ is nullptr");
        Uri uri("");
        return uri;
    }
}

/**
 * @brief Get the string of this Context based on the specified resource ID.
 *
 * @param resId Indicates the resource ID of the string to get.
 *
 * @return Returns the string of this Context.
 */
std::string ContextContainer::GetString(int resId)
{
    if (baseContext_ != nullptr) {
        std::string ret = baseContext_->GetString(resId);
        return ret;
    } else {
        APP_LOGE("ContextContainer::GetString baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Get the string array of this Context based on the specified resource ID.
 *
 * @param resId Indicates the resource ID of the string array to get.
 *
 * @return Returns the string array of this Context.
 */
std::vector<std::string> ContextContainer::GetStringArray(int resId)
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetStringArray(resId);
    } else {
        return std::vector<std::string>();
        APP_LOGE("ContextContainer::GetStringArray baseContext_ is nullptr");
    }
}

/**
 * @brief Get the integer array of this Context based on the specified resource ID.
 *
 * @param resId Indicates the resource ID of the integer array to get.
 *
 * @return Returns the integer array of this Context.
 */
std::vector<int> ContextContainer::GetIntArray(int resId)
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetIntArray(resId);
    } else {
        APP_LOGE("ContextContainer::GetIntArray baseContext_ is nullptr");
        return std::vector<int>();
    }
}

/**
 * @brief Obtains the theme of this Context.
 *
 * @return theme Returns the theme of this Context.
 */
std::map<std::string, std::string> ContextContainer::GetTheme()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetTheme();
    } else {
        APP_LOGE("ContextContainer::GetTheme baseContext_ is nullptr");
        return std::map<std::string, std::string>();
    }
}

/**
 * @brief Sets the theme of this Context based on the specified theme ID.
 *
 * @param themeId Indicates the resource ID of the theme to set.
 */
void ContextContainer::SetTheme(int themeId)
{
    if (baseContext_ != nullptr) {
        baseContext_->SetTheme(themeId);
    } else {
        APP_LOGE("ContextContainer::SetTheme baseContext_ is nullptr");
    }
}

/**
 * @brief Obtains the pattern of this Context.
 *
 * @return getPattern in interface Context
 */
std::map<std::string, std::string> ContextContainer::GetPattern()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetPattern();
    } else {
        APP_LOGE("ContextContainer::GetPattern baseContext_ is nullptr");
        return std::map<std::string, std::string>();
    }
}

/**
 * @brief Get the color of this Context based on the specified resource ID.
 *
 * @param resId Indicates the resource ID of the color to get.
 *
 * @return Returns the color value of this Context.
 */
int ContextContainer::GetColor(int resId)
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetColor(resId);
    } else {
        APP_LOGE("ContextContainer::GetColor baseContext_ is nullptr");
        return INVALID_RESOURCE_VALUE;
    }
}

/**
 * @brief Obtains the theme id of this Context.
 *
 * @return int Returns the theme id of this Context.
 */
int ContextContainer::GetThemeId()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetThemeId();
    } else {
        APP_LOGE("ContextContainer::GetThemeId baseContext_ is nullptr");
        return -1;
    }
}

/**
 * @brief Obtains the current display orientation of this ability.
 *
 * @return Returns the current display orientation.
 */
int ContextContainer::GetDisplayOrientation()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetDisplayOrientation();
    } else {
        APP_LOGE("ContextContainer::GetDisplayOrientation baseContext_ is nullptr");
        return static_cast<int>(DisplayOrientation::UNSPECIFIED);
    }
}

/**
 * @brief Obtains the path storing the preference file of the application.
 *        If the preference file path does not exist, the system creates one and returns the created path.
 *
 * @return Returns the preference file path .
 */
std::string ContextContainer::GetPreferencesDir()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetPreferencesDir();
    } else {
        APP_LOGE("ContextContainer::GetPreferencesDir baseContext_ is nullptr");
        return "";
    }
}

/**
 * @brief Set color mode
 *
 * @param the value of color mode.
 */
void ContextContainer::SetColorMode(int mode)
{
    if (baseContext_ == nullptr) {
        APP_LOGE("ContextContainer::SetColorMode baseContext_ is nullptr");
        return;
    }

    baseContext_->SetColorMode(mode);
}

/**
 * @brief Obtains color mode.
 *
 * @return Returns the color mode value.
 */
int ContextContainer::GetColorMode()
{
    if (baseContext_ == nullptr) {
        APP_LOGE("ContextContainer::GetColorMode baseContext_ is nullptr");
        return -1;
    }

    return baseContext_->GetColorMode();
}

/**
 * @brief Obtains the unique ID of the mission containing this ability.
 *
 * @return Returns the unique mission ID.
 */
int ContextContainer::GetMissionId()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetMissionId();
    } else {
        APP_LOGE("ContextContainer::GetMissionId baseContext_ is nullptr");
        return -1;
    }
}

/**
 * @brief Call this when your ability should be closed and the mission should be completely removed as a part of
 * finishing the root ability of the mission.
 */
void ContextContainer::TerminateAndRemoveMission()
{
    if (baseContext_ != nullptr) {
        baseContext_->TerminateAndRemoveMission();
    } else {
        APP_LOGE("ContextContainer::TerminateAndRemoveMission baseContext_ is nullptr");
    }
}

/**
 * @brief Obtains a task dispatcher that is bound to the UI thread.
 *
 * @return Returns the task dispatcher that is bound to the UI thread.
 */
std::shared_ptr<TaskDispatcher> ContextContainer::GetUITaskDispatcher()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetUITaskDispatcher();
    } else {
        APP_LOGE("ContextContainer::GetUITaskDispatcher baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains a task dispatcher that is bound to the application main thread.
 *
 * @return Returns the task dispatcher that is bound to the application main thread.
 */
std::shared_ptr<TaskDispatcher> ContextContainer::GetMainTaskDispatcher()
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetMainTaskDispatcher();
    } else {
        APP_LOGE("ContextContainer::GetMainTaskDispatcher baseContext_ is nullptr");
        return nullptr;
    }
}
/**
 * @brief Creates a parallel task dispatcher with a specified priority.
 *
 * @param name Indicates the task dispatcher name. This parameter is used to locate problems.
 * @param priority Indicates the priority of all tasks dispatched by the parallel task dispatcher.
 *
 * @return Returns a parallel task dispatcher.
 */
std::shared_ptr<TaskDispatcher> ContextContainer::CreateParallelTaskDispatcher(
    const std::string &name, const TaskPriority &priority)
{
    if (baseContext_ != nullptr) {
        return baseContext_->CreateParallelTaskDispatcher(name, priority);
    } else {
        APP_LOGE("ContextContainer::CreateParallelTaskDispatcher baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Creates a serial task dispatcher with a specified priority.
 *
 * @param name Indicates the task dispatcher name. This parameter is used to locate problems.
 * @param priority Indicates the priority of all tasks dispatched by the created task dispatcher.
 *
 * @return Returns a serial task dispatcher.
 */
std::shared_ptr<TaskDispatcher> ContextContainer::CreateSerialTaskDispatcher(
    const std::string &name, const TaskPriority &priority)
{
    if (baseContext_ != nullptr) {
        return baseContext_->CreateSerialTaskDispatcher(name, priority);
    } else {
        APP_LOGE("ContextContainer::CreateSerialTaskDispatcher baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Obtains a global task dispatcher with a specified priority.
 *
 * @param priority Indicates the priority of all tasks dispatched by the global task dispatcher.
 *
 * @return Returns a global task dispatcher.
 */
std::shared_ptr<TaskDispatcher> ContextContainer::GetGlobalTaskDispatcher(const TaskPriority &priority)
{
    if (baseContext_ != nullptr) {
        return baseContext_->GetGlobalTaskDispatcher(priority);
    } else {
        APP_LOGE("ContextContainer::GetGlobalTaskDispatcher baseContext_ is nullptr");
        return nullptr;
    }
}

/**
 * @brief Requires that tasks associated with a given capability token be moved to the background
 *
 * @param nonFirst If nonfirst is false and not the lowest ability of the mission, you cannot move mission to end
 *
 * @return Returns true on success, others on failure.
 */
bool ContextContainer::MoveMissionToEnd(bool nonFirst)
{
    sptr<IRemoteObject> token = GetToken();
    if (token == nullptr) {
        APP_LOGE("ContextContainer::MoveMissionToEnd GetToken return nullptr");
        return false;
    }

    auto abilityClient = AAFwk::AbilityManagerClient::GetInstance();
    if (abilityClient == nullptr) {
        APP_LOGE("ContextContainer::MoveMissionToEnd abilityClient is nullptr");
        return false;
    }

    ErrCode errval = abilityClient->MoveMissionToEnd(token, nonFirst);
    if (errval != ERR_OK) {
        APP_LOGE("ContextContainer::MoveMissionToEnd MoveMissionToEnd retval is %d", errval);
    }

    return (errval == ERR_OK) ? true : false;
}

/**
 * @brief Sets the application to start its ability in lock mission mode.
 */
void ContextContainer::LockMission()
{
    auto abilityClient = AAFwk::AbilityManagerClient::GetInstance();
    if (abilityClient == nullptr) {
        APP_LOGE("ContextContainer::LockMission abilityClient is nullptr");
        return;
    }

    ErrCode errval = abilityClient->LockMission(GetMissionId());
    if (errval != ERR_OK) {
        APP_LOGE("ContextContainer::LockMission LockMission retval is %d", errval);
    }
}

/**
 * @brief Unlocks this ability by exiting the lock mission mode.
 */
void ContextContainer::UnlockMission()
{
    auto abilityClient = AAFwk::AbilityManagerClient::GetInstance();
    if (abilityClient == nullptr) {
        APP_LOGE("ContextContainer::UnlockMission abilityClient is nullptr");
        return;
    }

    ErrCode errval = abilityClient->UnlockMission(GetMissionId());
    if (errval != ERR_OK) {
        APP_LOGE("ContextContainer::UnlockMission UnlockMission retval is %d", errval);
    }
}

/**
 * @brief Sets description information about the mission containing this ability.
 *
 * @param MissionInformation Indicates the object containing information about the
 *                               mission. This parameter cannot be null.
 * @return Returns true on success, others on failure.
 */
bool ContextContainer::SetMissionInformation(const MissionInformation &missionInformation)
{
    sptr<IRemoteObject> token = GetToken();
    if (token == nullptr) {
        APP_LOGE("ContextContainer::SetMissionInformation GetToken return nullptr");
        return false;
    }

    auto abilityClient = AAFwk::AbilityManagerClient::GetInstance();
    if (abilityClient == nullptr) {
        APP_LOGE("ContextContainer::SetMissionInformation abilityClient is nullptr");
        return false;
    }

    AAFwk::MissionDescriptionInfo missionInfoMat;
    missionInfoMat.label = missionInformation.label;
    missionInfoMat.iconPath = missionInformation.iconPath;

    ErrCode errval = abilityClient->SetMissionDescriptionInfo(token, missionInfoMat);
    if (errval != ERR_OK) {
        APP_LOGE("ContextContainer::SetMissionInformation SetMissionDescriptionInfo retval is %d", errval);
    }

    return (errval == ERR_OK) ? true : false;
}

/**
 * set lock screen white list
 *
 * @param isAllow Whether to allow lock screen.
 *
 */
void ContextContainer::SetShowOnLockScreen(bool isAllow)
{
    if (baseContext_ == nullptr) {
        APP_LOGE("ContextContainer::SetShowOnLockScreen baseContext_ is nullptr");
        return;
    }

    baseContext_->SetShowOnLockScreen(isAllow);
    APP_LOGI("ContextContainer::SetShowOnLockScreen called end.");
}
}  // namespace AppExecFwk
}  // namespace OHOS
