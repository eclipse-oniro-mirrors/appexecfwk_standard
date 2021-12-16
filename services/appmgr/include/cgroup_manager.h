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

#ifndef FOUNDATION_APPEXECFWK_SERVICES_APPMGR_INCLUDE_CGROUP_MANAGER_H
#define FOUNDATION_APPEXECFWK_SERVICES_APPMGR_INCLUDE_CGROUP_MANAGER_H

#include <memory>
#include <functional>
#include <shared_mutex>

#include "event_handler.h"
#include "file_descriptor_listener.h"
#include "nocopyable.h"
#include "singleton.h"
#include "unique_fd.h"

namespace OHOS {
namespace AppExecFwk {
class CgroupManager : public FileDescriptorListener, public std::enable_shared_from_this<CgroupManager> {
    DECLARE_DELAYED_SINGLETON(CgroupManager)
public:
    enum SchedPolicy {
        SCHED_POLICY_DEFAULT = 0,
        SCHED_POLICY_BACKGROUND,
        SCHED_POLICY_FREEZED,

        SCHED_POLICY_MAX
    };

    enum LowMemoryLevel {
        LOW_MEMORY_LEVEL_LOW = 0,
        LOW_MEMORY_LEVEL_MEDIUM,
        LOW_MEMORY_LEVEL_CRITICAL,

        LOW_MEMORY_LEVEL_MAX
    };

    enum SchedPolicyCpu {
        SCHED_POLICY_CPU_DEFAULT = 0,
        SCHED_POLICY_CPU_BACKGROUND,

        SCHED_POLICY_CPU_MAX
    };

    enum SchedPolicyFreezer {
        SCHED_POLICY_FREEZER_FROZEN = 0,
        SCHED_POLICY_FREEZER_THAWED,

        SCHED_POLICY_FREEZER_MAX
    };

    std::function<void(CgroupManager::LowMemoryLevel)> LowMemoryAlert;

public:
    virtual bool Init();
    virtual bool InitCheck();
    virtual bool IsInited() const;
    virtual bool SetThreadSchedPolicy(int tid, SchedPolicy schedPolicy);
    virtual bool SetProcessSchedPolicy(int pid, SchedPolicy schedPolicy);
    virtual void OnReadable(int32_t fd) override;

private:
    std::shared_ptr<EventHandler> eventHandler_;
    int cpusetTasksFds_[SCHED_POLICY_CPU_MAX] = {-1};
    int cpuctlTasksFds_[SCHED_POLICY_CPU_MAX] = {-1};
    int freezerTasksFds_[SCHED_POLICY_FREEZER_MAX] = {-1};
    int memoryEventControlFd_ = -1;
    int memoryEventFds_[LOW_MEMORY_LEVEL_MAX] = {-1};
    int memoryPressureFds_[LOW_MEMORY_LEVEL_MAX] = {-1};

    bool RegisterLowMemoryMonitor(const int memoryEventFds[LOW_MEMORY_LEVEL_MAX],
        const int memoryPressureFds[LOW_MEMORY_LEVEL_MAX], const int memoryEventControlFd, const LowMemoryLevel level,
        const std::shared_ptr<EventHandler> &eventHandler);
    bool InitCpusetTasksFds(UniqueFd cpusetTasksFds[SCHED_POLICY_CPU_MAX]);
    bool InitCpuctlTasksFds(UniqueFd cpuctlTasksFds[SCHED_POLICY_CPU_MAX]);
    bool InitFreezerTasksFds(UniqueFd freezerTasksFds[SCHED_POLICY_FREEZER_MAX]);
    bool InitMemoryEventControlFd(UniqueFd &memoryEventControlFd);
    bool InitMemoryEventFds(UniqueFd memoryEventFds[LOW_MEMORY_LEVEL_MAX]);
    bool InitMemoryPressureFds(UniqueFd memoryPressureFds[LOW_MEMORY_LEVEL_MAX]);
    bool SetCpusetSubsystem(const int tid, const SchedPolicy schedPolicy);
    bool SetCpuctlSubsystem(const int tid, const SchedPolicy schedPolicy);
    bool SetFreezerSubsystem(const int tid, const SchedPolicyFreezer state);
};
}  // namespace AppExecFwk
}  // namespace OHOS

#endif  // FOUNDATION_APPEXECFWK_SERVICES_APPMGR_INCLUDE_CGROUP_MANAGER_H
