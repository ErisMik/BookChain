#pragma once

#include "http/dtos/blockdtos.hpp"

#include "block.hpp"
#include "chain.hpp"
#include "utils.hpp"

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

namespace bookchain::http {

BlockDto::ObjectWrapper serializeBlockToDTO(Bloock bloock) {
    auto dto = BlockDto::createShared();

    dto->blockHash = utils::hexifystring(bloock.blockHash()).c_str();
    dto->prevHash = utils::hexifystring(bloock.prevHash()).c_str();
    dto->seedHash = utils::hexifystring(bloock.seedHash()).c_str();
    dto->blockHeight = bloock.blockHeight();
    dto->nonce = bloock.nonce();
    dto->signature = utils::hexifystring(bloock.signature()).c_str();
    dto->data = utils::hexifystringTruncated(bloock.data()).c_str();

    return dto;
}

class BlockController : public oatpp::web::server::api::ApiController {
public:
    BlockController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) :
        oatpp::web::server::api::ApiController(objectMapper) {}

public:
/* Begin ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_BEGIN(ApiController)

    ADD_CORS(blocks);
    ENDPOINT("GET", "/blocks", blocks) {
        BlookchainView bloockchainView;
        int bloockchainHeight = bloockchainView.height();

        auto result = oatpp::data::mapping::type::List<BlockDto::ObjectWrapper>::createShared();
        for (int i = 0; i < bloockchainHeight; ++i) {
            Bloock bloock = bloockchainView.bloock(i);

            auto dto = serializeBlockToDTO(bloock);

            result->pushBack(dto);
        }

        return createDtoResponse(Status::CODE_200, result);
    }

    ENDPOINT("GET", "/blocks/latest", blockLatest) {
        BlookchainView bloockchainView;
        Bloock bloock = bloockchainView.latest();

        auto dto = serializeBlockToDTO(bloock);

        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT("GET", "/blocks/{blockHeight}", blockByHeight, PATH(Int64, blockHeight)) {
        BlookchainView bloockchainView;
        Bloock bloock = bloockchainView.bloock(blockHeight);

        auto dto = serializeBlockToDTO(bloock);

        return createDtoResponse(Status::CODE_200, dto);
    }

/* Finish ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_END(ApiController)
};

}  // namespace bookchain::http
