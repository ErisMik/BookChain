#include "job.hpp"
#include "crypto.hpp"

namespace bookchain {

Job::Job(const std::string& data) :
    _data(data) {
    this->_jobId = data.length();  // TODO(Eric Mikulin): This should be another hash style function
}

std::string Job::data() const {
    return this->_data;
}

int Job::jobId() const {
    return this->_jobId;
}

}  // namespace bookchain
