#pragma once

#include "http/dtos/dtos.hpp"

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

namespace bookchain::http {

class HelloController : public oatpp::web::server::api::ApiController {
public:
  HelloController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

/* Begin ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_BEGIN(ApiController)

  ENDPOINT("GET", "/hello", root) {
    auto dto = BasicMessageDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

/* Finish ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_END(ApiController)

};

}  // namespace bookchain::http