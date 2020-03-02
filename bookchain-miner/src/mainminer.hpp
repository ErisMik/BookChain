#pragma once

#include "job.hpp"
#include "queue.hpp"

namespace bookchain {

void minerMainLoop(const sharedTSQueue<Job>& jobQueue);

}  // namespace bookchain
