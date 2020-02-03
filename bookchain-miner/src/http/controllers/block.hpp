#pragma once

#include "http/dtos/dtos.hpp"

#include "block.hpp"
#include "chain.hpp"
#include "utils.hpp"

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

namespace bookchain::http {

class BlockController : public oatpp::web::server::api::ApiController {
public:
    BlockController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) :
        oatpp::web::server::api::ApiController(objectMapper) {}

public:
/* Begin ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_BEGIN(ApiController)

    ENDPOINT("GET", "/blocks", blocks) {
        Bloockchain bloockchainView;
        int bloockchainHeight = bloockchainView.height();

        auto result = oatpp::data::mapping::type::List<BlockDto::ObjectWrapper>::createShared();
        for (int i = 0; i < bloockchainHeight; ++i) {
            Bloock bloock = bloockchainView.bloock(i);

            auto dto = BlockDto::createShared();
            dto->prevHash = utils::hexifystring(bloock.prevHash()).c_str();
            dto->seedHash = utils::hexifystring(bloock.seedHash()).c_str();
            dto->blockHeight = bloock.blockHeight();
            dto->nonce = bloock.nonce();
            dto->signature = utils::hexifystring(bloock.signature()).c_str();
            dto->data = utils::hexifystring(bloock.data()).c_str();

            result->pushBack(dto);
        }

        return createDtoResponse(Status::CODE_200, result);
    }

    ENDPOINT("GET", "/blocks/{blockHeight}", blockByHeight, PATH(Int64, blockHeight)) {
        Bloockchain bloockchainView;
        Bloock bloock = bloockchainView.bloock(blockHeight);

        auto dto = BlockDto::createShared();
        dto->prevHash = utils::hexifystring(bloock.prevHash()).c_str();
        dto->seedHash = utils::hexifystring(bloock.seedHash()).c_str();
        dto->blockHeight = bloock.blockHeight();
        dto->nonce = bloock.nonce();
        dto->signature = utils::hexifystring(bloock.signature()).c_str();
        dto->data = utils::hexifystring(bloock.data()).c_str();

        return createDtoResponse(Status::CODE_200, dto);
    }

/* Finish ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_END(ApiController)
};

}  // namespace bookchain::http
