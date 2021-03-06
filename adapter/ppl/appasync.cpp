#include "appasync.h"
#include "thread/workerpool.h"

#include "adapter/qt/qasync.h"

namespace AppUI
{

    struct AppUITaskpplSchedule : public concurrency::scheduler_interface
    {
        virtual void schedule(Concurrency::TaskProc_t proc, void* param)
        {
            AppUI::async([proc, param]() {
                proc(param);
            });
        }
    };

    void async(const std::function<void()>& cb)
    {
        Qx::async(cb);
    }

    void async(std::function<void()>&& cb)
    {
        Qx::async(cb);
    }

    void asyncDelayed(const std::function<void()>& cb, int milliSecs)
    {
        Qx::asyncDelayed(cb, milliSecs);
    }

    void asyncDelayed(std::function<void()>&& cb, int milliSecs)
    {
        Qx::asyncDelayed(cb, milliSecs);
    }

    std::shared_ptr<concurrency::scheduler_interface> static_pplScheduler()
    {
        static std::shared_ptr<concurrency::scheduler_interface>  s = std::make_shared<AppUITaskpplSchedule>();
        return s;
    }

    std::thread::id threadId()
    {
        return Qx::threadId();
    }

}


namespace concurrency_
{
    struct WorkerPoolTaskpplSchedule : public concurrency::scheduler_interface
    {
        virtual void schedule(concurrency::TaskProc_t proc, void* param)
        {
            WorkerPool::async([proc, param]() {
                proc(param);
            });
        }
    };


    std::shared_ptr<concurrency::scheduler_interface>& static_pplScheduler()
    {
        static std::shared_ptr<concurrency::scheduler_interface>  s = std::make_shared<WorkerPoolTaskpplSchedule>();
        return s;
    }
}
