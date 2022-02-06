/*
    Copyright 2021 XITRIX

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <unistd.h>

#include <chrono>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace brls
{

/**
 * Enqueue a function to be executed before
 * the application is redrawn the next time.
 *
 * Borealis is not thread-safe, and sync() provides a mechanism
 * for queuing up UI-related state changes from other threads.
 *
 * It's a shortcut for brls::Application::sync(&func);
 */
extern void sync(const std::function<void()>& func);

/**
 * Enqueue a function to be executed in
 * parallel with application's main thread.
 *
 * It's a shortcut for brls::Application::async(&func);
 */
extern void async(const std::function<void()>& func);

extern void delay(long milliseconds, const std::function<void()>& func);

struct DelayOperation
{
    std::chrono::high_resolution_clock::time_point startPoint;
    long delayMilliseconds;
    std::function<void()> func;
};

class Threading
{
  public:
    Threading();

    /**
     * Enqueue a function to be executed before
     * the application is redrawn the next time.
     *
     * Borealis is not thread-safe, and sync() provides a mechanism
     * for queuing up UI-related state changes from other threads.
     */
    static void sync(const std::function<void()>& func);

    /**
     * Enqueue a function to be executed in
     * parallel with application's main thread.
     */
    static void async(const std::function<void()>& func);

    static void delay(long milliseconds, const std::function<void()>& func);

    static void start();

    static void stop();

    static void performSyncTasks();

    static std::vector<std::function<void()>>* getSyncFunctions()
    {
        return &m_sync_functions;
    }

    static std::vector<std::function<void()>>* getAsyncTasks()
    {
        return &m_async_tasks;
    }

  private:
    inline static std::mutex m_sync_mutex;
    inline static std::vector<std::function<void()>> m_sync_functions;

    inline static std::mutex m_async_mutex;
    inline static std::vector<std::function<void()>> m_async_tasks;

    inline static std::mutex m_delay_mutex;
    inline static std::vector<DelayOperation> m_delay_tasks;

    inline static volatile bool task_loop_active = true;

    static void* task_loop(void* a);

    static void start_task_loop();
};

} // namespace brls
