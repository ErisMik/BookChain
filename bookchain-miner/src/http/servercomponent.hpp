#pragma once

#include <oatpp/core/macro/component.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>

namespace bookchain::http {

class ServerComponent {
private:
    int serverPort;

public:
    ServerComponent(int customServerPort) :
        serverPort(customServerPort) {};

public:
    /**
    *  Create ConnectionProvider component which listens on the port
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
    ([this] {
        return oatpp::network::server::SimpleTCPConnectionProvider::createShared(this->serverPort);
    }());

    /**
    *  Create Router component
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
    ([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    /**
    *  Create ConnectionHandler component which uses Router component to route requests
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, serverConnectionHandler)
    ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);  // get Router component
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    /**
    *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
    ([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());
};

}  // namespace bookchain::http
