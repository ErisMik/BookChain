#include "http/server.hpp"
#include "http/handlers.hpp"
#include "version.hpp"
#include <oatpp/network/server/Server.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <string>

namespace bookchain::http {

constexpr int httpServerPort = 8000;

void run() {
    /* Create json object mapper */
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    /* Create Router for HTTP requests routing */
    auto router = oatpp::web::server::HttpRouter::createShared();

    /* Route requests to Handler */
    router->route("GET", "/hello", std::make_shared<HelloHandler>(objectMapper));
    router->route("GET", "/connect-peer", std::make_shared<HelloHandler>(objectMapper));
    router->route("GET", "/peers", std::make_shared<PeersHandler>(objectMapper));

    /* Create HTTP connection handler with router */
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    /* Create TCP connection provider */
    auto connectionProvider = oatpp::network::server::SimpleTCPConnectionProvider::createShared(httpServerPort);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::server::Server server(connectionProvider, connectionHandler);

    /* Print info about server port */
    OATPP_LOGI("Bookchain Node", "Version %s", &versionString[0]);
    OATPP_LOGI("Bookchain Node", "Server running on port %s", connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
}

void startMinerHttpServer() {
    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();
}

}  // namespace bookchain::http