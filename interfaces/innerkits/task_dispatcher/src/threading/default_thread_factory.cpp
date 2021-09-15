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

#include "default_thread_factory.h"

namespace OHOS {
namespace AppExecFwk {

DefaultThreadFactory::DefaultThreadFactory() : index_(1)
{}

std::shared_ptr<Thread> DefaultThreadFactory::Create()
{
    std::shared_ptr<Thread> pThread = std::make_shared<Thread>();
    if (pThread != nullptr) {
        int value = std::atomic_fetch_add(&index_, 1);
        std::string name = std::string("PoolThread-") + std::to_string(value);
        pThread->thread_name_ = name;
        APP_LOGI("DefaultThreadFactory::Create thread name is %{public}s", name.c_str());
    } else {
        APP_LOGE("DefaultThreadFactory::Create error, thread is nullptr");
    }

    return pThread;
}

}  // namespace AppExecFwk
}  // namespace OHOS
