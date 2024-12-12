#include "TaskHandler.h"

void TaskHandler::taskInitializer(void* taskPointer) {
    Task* task = static_cast<Task*>(taskPointer);
    vTaskDelay(task->getStartupDelay() / portTICK_PERIOD_MS);
    if (task->isCyclic()) {
        unsigned int notification;
        for (;;) {
            task->execute();
            // execute each task->getLoopDelay() millis or onNotify
            xTaskNotifyWait(0, 0, &notification, task->getLoopDelay() / portTICK_PERIOD_MS);
        }
    } else if (task->isReactive()) {
        // will be executed once and then react onto the vTaskResume(taskId)
        for (;;) {
            task->execute();
            vTaskSuspend(nullptr);
        }
    } else {
        // one-time execution task
        task->execute();
        vTaskDelete(nullptr);
    }
}

void TaskHandler::gc(void* taskHandler) {
    TaskHandler* handler = static_cast<TaskHandler*>(taskHandler);
    unsigned int notification;
    for (;;) {
        xTaskNotifyWait(0, 0, &notification, handler->constants.HANDLER_GC_INTERVAL / portTICK_PERIOD_MS);
        for (int i = 0; i < handler->constants.HANDLER_HOLDER_SIZE; ++i) {
            if (handler->taskHandleHolder[i]) {
                if (eTaskGetState(handler->taskHandleHolder[i]) == eDeleted) {
                    delete handler->taskHandleHolder[i];
                    handler->taskHandleHolder[i] = nullptr;
                    delete handler->taskHolder[i];
                    handler->taskHolder[i] = nullptr;
                    handler->taskIdHolder[i] = 0;
                }
            }
        }
    }
}

void TaskHandler::clean(const int& onIndex) {
    while (lock) {
    }
    lock = true;
    delete taskHolder[onIndex];
    taskHolder[onIndex] = nullptr;
    delete taskHandleHolder[onIndex];
    ;
    taskHandleHolder[onIndex] = nullptr;
    taskIdHolder[onIndex] = 0;
    lock = false;
}

TaskHandler::TaskHandler(const TaskConstants& constants) : constants(constants) {
    taskIdHolder = new int[constants.HANDLER_HOLDER_SIZE];
    taskHandleHolder = new TaskHandle_t*[constants.HANDLER_HOLDER_SIZE];
    taskHolder = new Task*[constants.HANDLER_HOLDER_SIZE];
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        taskIdHolder[i] = 0;
        taskHandleHolder[i] = nullptr;
        taskHolder[i] = nullptr;
    }
    xTaskCreatePinnedToCore(
        gc,
        "gc_task",
        2048,
        this,
        constants.PRIOTITY_LOW | portPRIVILEGE_BIT,
        &gcTaskHandle,
        constants.HANDLER_ACTIVE_CORE);
}

int TaskHandler::create(Task* task) {
    if (task) {
        while (lock) {
        }
        lock = true;
        int taskId = nextTaskId++;
        TaskHandle_t* handle = new TaskHandle_t();
        for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
            if (!taskIdHolder[i]) {
                taskIdHolder[i] = taskId;
                taskHandleHolder[i] = handle;
                taskHolder[i] = task;
                lock = false;
                xTaskCreatePinnedToCore(
                    taskInitializer,
                    task->getName(),
                    task->getStackSize(),
                    task,
                    task->getPriority() | portPRIVILEGE_BIT,
                    handle,
                    constants.HANDLER_ACTIVE_CORE);
                return taskId;
            }
        }
        lock = false;
    }
    return 0;
}

bool TaskHandler::suspend(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i]) {
                int state = eTaskGetState(taskHandleHolder[i]);
                if (state == eDeleted || state == eInvalid) return false;
                if (state != eSuspended) vTaskSuspend(taskHandleHolder[i]);
                return true;
            } else
                clean(i);
            return false;
        }
    }
    return false;
}

bool TaskHandler::resume(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i]) {
                int state = eTaskGetState(taskHandleHolder[i]);
                if (state == eDeleted || state == eInvalid) return false;
                if (state == eSuspended) vTaskResume(taskHandleHolder[i]);
                return true;
            } else
                clean(i);
            return false;
        }
    }
    return false;
}

bool TaskHandler::invoke(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i]) {
                int state = eTaskGetState(taskHandleHolder[i]);
                if (state == eSuspended) vTaskResume(taskHandleHolder[i]);
                if (state == eBlocked) xTaskNotify(taskHandleHolder[i], 0, eNoAction);
                return true;
            } else
                clean(i);
            return false;
        }
    }
    return false;
}

void TaskHandler::cancel(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i]) {
                if (eTaskGetState(taskHandleHolder[i]) != eDeleted) vTaskDelete(taskHandleHolder[i]);
            } else
                clean(i);
            return;
        }
    }
}

int TaskHandler::getAvailableStackSize(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i])
                return eTaskGetState(taskHandleHolder[i]) == eDeleted ? 0 : uxTaskGetStackHighWaterMark(taskHandleHolder[i]);
            else
                clean(i);
            return 0;
        }
    }
    return 0;
}

void TaskHandler::setPriority(const int& taskId, int priority) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i]) {
                if (eTaskGetState(taskHandleHolder[i]) == eDeleted) vTaskPrioritySet(taskHandleHolder[i], priority);
            } else
                clean(i);
            return;
        }
    }
}

int TaskHandler::getPriority(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i])
                return taskHandleHolder[i] && eTaskGetState(taskHandleHolder[i]) == eDeleted ? 0 : uxTaskPriorityGet(taskHandleHolder[i]);
            else
                clean(i);
            return constants.PRIOTITY_LOW;
        }
    }
    return constants.PRIOTITY_LOW;
}

const char* TaskHandler::getName(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHolder[i])
                return taskHolder[i]->getName();
            else
                clean(i);
            return "";
        }
    }
    return "";
}

int TaskHandler::getState(const int& taskId) {
    for (int i = 0; i < constants.HANDLER_HOLDER_SIZE; ++i) {
        if (taskId == taskIdHolder[i]) {
            if (taskHandleHolder[i]) {
                switch (eTaskGetState(taskHandleHolder[i])) {
                    case eRunning:
                        return constants.TASK_STATE_RUNNING;
                    case eReady:
                        return constants.TASK_STATE_AWAITS_IN_QUEUE;
                    case eBlocked:
                        return constants.TASK_STATE_AWAINTS_NOTIFICATION;
                    case eSuspended:
                        return constants.TASK_STATE_SUSPENDED;
                    case eDeleted:
                        return constants.TASK_STATE_DELETED;
                    default:
                        return constants.TASK_STATE_UNDEFINED;
                }
            } else
                clean(i);
            return constants.TASK_STATE_UNDEFINED;
        }
    }
    return constants.TASK_STATE_UNDEFINED;
}

void TaskHandler::gc() {
    xTaskNotify(gcTaskHandle, 0, eNoAction);
}
