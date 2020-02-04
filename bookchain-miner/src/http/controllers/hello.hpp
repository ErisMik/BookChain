#pragma once

#include "http/dtos/dtos.hpp"
#include "utils.hpp"
#include "version.hpp"

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

namespace bookchain::http {

class HelloController : public oatpp::web::server::api::ApiController {
public:
    HelloController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) :
        oatpp::web::server::api::ApiController(objectMapper) {}

public:
/* Begin ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_BEGIN(ApiController)

    ENDPOINT("GET", "/", root) {
        auto dto = HelloMessageDto::createShared();
        dto->identifier = utils::identifierHash();
        dto->version = versionString;
        return createDtoResponse(Status::CODE_200, dto);
    }

/* Finish ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_END(ApiController)
};

}  // namespace bookchain::http
