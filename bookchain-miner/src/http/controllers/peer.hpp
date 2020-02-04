#pragma once

#include "http/dtos/peerdtos.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include "utils.hpp"

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

namespace bookchain::http {

class PeerController : public oatpp::web::server::api::ApiController {
public:
    PeerController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper), OATPP_COMPONENT(sharedTSQueue<Peer>, peerQueueComponent)) :
        oatpp::web::server::api::ApiController(objectMapper), _peerQueue(peerQueueComponent) {}

private:
    sharedTSQueue<Peer> _peerQueue;

public:
/* Begin ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_BEGIN(ApiController)

    ENDPOINT("GET", "/peers", peers) {
        auto dto = PeerLinkDto::createShared();
        dto->identifier = utils::identifierHash();
        dto->version = versionString;

        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT("GET", "/peers/link", peersLinkGet) {
        auto dto = PeerLinkDto::createShared();
        dto->identifier = utils::identifierHash();
        dto->version = versionString;

        Peer peer("localhost");
        this->_peerQueue->push(peer);

        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT("POST", "/peers/link", peersLinkPost) {
        auto dto = PeerLinkDto::createShared();
        dto->identifier = utils::identifierHash();
        dto->version = versionString;

        return createDtoResponse(Status::CODE_200, dto);
    }

/* Finish ENDPOINTs generation ('ApiController' codegen) */
#include OATPP_CODEGEN_END(ApiController)
};

}  // namespace bookchain::http
