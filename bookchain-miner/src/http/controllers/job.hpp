#pragma once

#include "http/dtos/jobdtos.hpp"
#include "job.hpp"

#include <string>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

namespace bookchain::http {

JobDto::ObjectWrapper serializeJobToDTO(Job job) {
    auto dto = JobDto::createShared();

    dto->id = job.jobId();
    dto->data = job.data().c_str();

    return dto;
}

Job deserializeJobFromDTO(JobDto::ObjectWrapper dto) {
    Job job(dto->data->std_str());
    return job;
}

class JobController : public oatpp::web::server::api::ApiController {
public:
    JobController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper), OATPP_COMPONENT(sharedTSQueue<Job>, jobQueueComponent)) :
        oatpp::web::server::api::ApiController(objectMapper), _jobQueue(jobQueueComponent) {}

private:
    sharedTSQueue<std::string> _dataQueue;
    sharedTSQueue<Job> _jobQueue;

public:
/* Begin ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_BEGIN(ApiController)

    ADD_CORS(jobs);
    ENDPOINT("GET", "/jobs", jobs) {
        auto result = oatpp::data::mapping::type::List<JobDto::ObjectWrapper>::createShared();
        _jobQueue->lock();
        for (auto job = _jobQueue->begin(); job != _jobQueue->end(); ++job) {
            auto dto = serializeJobToDTO(*job);
            result->pushBack(dto);
        }
        _jobQueue->unlock();

        return createDtoResponse(Status::CODE_200, result);
    }

    ADD_CORS(jobsPost);
    ENDPOINT("POST", "/jobs", jobsPost, REQUEST(std::shared_ptr<IncomingRequest>, request)) {
        std::string requestBody = request->readBodyToString()->std_str();
        Job job = jobFromJsonString(requestBody);

        _jobQueue->push(job);
        return createResponse(Status::CODE_200, "{\"success\":true}");
    }

    ADD_CORS(jobById);
    ENDPOINT("GET", "/jobs/{jobId}", jobById, PATH(Int64, jobId)) {
        auto dto = JobDto::createShared();
        _jobQueue->lock();
        for (auto job = _jobQueue->begin(); job != _jobQueue->end(); ++job) {
            if (job->jobId() == jobId) {
                auto dto = serializeJobToDTO(*job);
                break;
            }
        }
        _jobQueue->unlock();

        return createDtoResponse(Status::CODE_200, dto);
    }

/* Finish ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_END(ApiController)
};

}  // namespace bookchain::http
