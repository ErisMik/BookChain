#include "job.hpp"
#include "crypto.hpp"
#include <chrono>
#include <nlohmann/json.hpp>

namespace bookchain {

Job::Job(const std::string& data) :
    _data(data) {
    this->_jobId = data.length();  // TODO(Eric Mikulin): This should be another hash style function
    this->_timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    this->_status = JobStatus::NEW;
}

Job::Job(int64_t jobId, uint64_t timestamp, const std::string& data, JobStatus status) :
    _jobId(jobId), _timestamp(timestamp), _data(data), _status(status) {
}

std::string Job::data() const {
    return this->_data;
}

int64_t Job::jobId() const {
    return this->_jobId;
}

JobStatus Job::status() const {
    return this->_status;
}

void Job::setStatus(JobStatus newStatus) {
    this->_status = newStatus;
}

Job invalidJob() {
    constexpr int64_t invalidJobId = 0;
    constexpr uint64_t invalidJobTimestamp = 0;
    constexpr char invalidJobData[] = "";

    return Job(invalidJobId, invalidJobTimestamp, invalidJobData, JobStatus::INVALID);
}

Job jobFromJsonString(std::string json) {
    try {
        auto jobJson = nlohmann::json::parse(json);
        if (jobJson.contains("jobStatus")) {
            return Job(jobJson["jobId"], jobJson["jobTimestamp"], jobJson["jobData"], JobStatus::UNVERIFIED);
        } else {
            return Job(jobJson["jobData"]);
        }
    } catch (...) {
        return invalidJob();
    }
}

}  // namespace bookchain
