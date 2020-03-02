#include <string>

namespace bookchain {

class Job {
public:
    Job(const std::string& data);
    std::string data() const;
    int jobId() const;

private:
    int _jobId;
    std::string _data;
};

}  // namespace bookchain
