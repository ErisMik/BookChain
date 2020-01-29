#pragma once

#include "http/dtos.hpp"
#include "peers.hpp"
#include <oatpp/network/server/Server.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>

namespace bookchain::http {

class HelloHandler : public oatpp::web::server::HttpRequestHandler {
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
    HelloHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) :
        m_objectMapper(objectMapper) {}

    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& /* request */) override {
        auto message = BasicMessageDto::createShared();
        message->statusCode = 1024;
        message->message = "Hello DTO!";
        return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
    }
};

class PeersHandler : public oatpp::web::server::HttpRequestHandler {
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
    PeersHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) :
        m_objectMapper(objectMapper) {}

    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& /* request */) override {
        auto peersListWrapper = PeersListDto::createShared();
        peersListWrapper->peers = peersListWrapper->peers->createShared();

        auto peers = oatpp::data::mapping::type::List<BasicMessageDto::ObjectWrapper>::createShared();

        auto message1 = BasicMessageDto::createShared();
        message1->statusCode = 101;
        message1->message = "Hello There!";
        peers->pushBack(message1);

        auto message2 = BasicMessageDto::createShared();
        message2->statusCode = 202;
        message2->message = "General Kenobi";
        peers->pushBack(message2);

        peersListWrapper->peers->put("starwars", peers);

        return ResponseFactory::createResponse(Status::CODE_200, peersListWrapper, m_objectMapper);
    }
};

}  // namespace bookchain::http