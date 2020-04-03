#include "job.hpp"
#include "crypto.hpp"
#include <chrono>
#include <nlohmann/json.hpp>

namespace bookchain {

Job::Job(const std::string& data) :
    _data(data) {
    this->_id = data.length();  // TODO(Eric Mikulin): This should be another hash style function that includes the whole job data (timestamp)
    this->_timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    this->_status = JobStatus::NEW;
}

Job::Job(int64_t id, uint64_t timestamp, const std::string& data, JobStatus status) :
    _id(id), _timestamp(timestamp), _data(data), _status(status) {
}

std::string Job::data() const {
    return this->_data;
}

int64_t Job::id() const {
    return this->_id;
}

uint64_t Job::timestamp() const {
    return this->_timestamp;
}

JobStatus Job::status() const {
    return this->_status;
}

void Job::setStatus(JobStatus newStatus) {
    this->_status = newStatus;
}

std::string Job::statusAsString() const {
    return jobStatusString.at(this->_status);
}

nlohmann::json Job::dataAsJson() const {
    return nlohmann::json::parse(this->_data);
}

Job Job::invalidJob() {
    constexpr int64_t invalidId = 0;
    constexpr uint64_t invalidJobTimestamp = 0;
    constexpr char invalidJobData[] = "";

    return Job(invalidId, invalidJobTimestamp, invalidJobData, JobStatus::INVALID);
}

Job Job::jobFromJsonString(std::string json) {
    try {
        auto parsedJson = nlohmann::json::parse(json);
        auto jobJson = parsedJson["job"];

        if (jobJson.contains("status")) {
            return Job(jobJson["id"], jobJson["timestamp"], jobJson["data"].dump(), JobStatus::UNVERIFIED);
        } else {
            return Job(jobJson["data"].dump());
        }
    } catch (...) {
        return Job::invalidJob();
    }
}

std::string Job::jobToJsonString(Job job) {
    nlohmann::json jobJson = {
        {"job", {
                    {"id", job.id()},
                    {"timestamp", job.timestamp()},
                    {"status", job.statusAsString()},
                    {"data", job.dataAsJson()},
                }}};

    return jobJson.dump();
}

}  // namespace bookchain
