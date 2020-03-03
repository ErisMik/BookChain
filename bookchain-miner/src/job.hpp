#pragma once

#include <string>

namespace bookchain {

enum class JobStatus {
    NEW,
    UNVERIFIED,
    INVALID,
    VALID,
    EXPIRED
};

class Job {
public:
    explicit Job(const std::string& data);
    Job(int64_t jobId, uint64_t timestamp, const std::string& data, JobStatus status);
    int64_t jobId() const;
    std::string data() const;
    JobStatus status() const;
    void setStatus(JobStatus newStatus);

private:
    int64_t _jobId;
    uint64_t _timestamp;
    std::string _data;
    JobStatus _status;
};

}  // namespace bookchain
