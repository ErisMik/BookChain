#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

namespace bookchain {

enum class JobStatus {
    NEW,
    UNVERIFIED,
    INVALID,
    VALID,
    EXPIRED
};

const std::unordered_map<JobStatus, std::string> jobStatusString {
    {JobStatus::NEW, "NEW"},
    {JobStatus::UNVERIFIED, "UNVERIFIED"},
    {JobStatus::INVALID, "INVALID"},
    {JobStatus::VALID, "VALID"},
    {JobStatus::EXPIRED, "EXPIRED"},
};

class Job {
public:
    explicit Job(const std::string& data);
    Job(int64_t id, uint64_t timestamp, const std::string& data, JobStatus status);

    int64_t id() const;
    uint64_t timestamp() const;
    std::string data() const;
    JobStatus status() const;
    void setStatus(JobStatus newStatus);

    std::string statusAsString() const;
    nlohmann::json dataAsJson() const;

    static Job invalidJob();
    static Job jobFromJsonString(std::string json);
    static std::string jobToJsonString(Job job);

private:
    int64_t _id;
    uint64_t _timestamp;
    std::string _data;
    JobStatus _status;
};

}  // namespace bookchain
