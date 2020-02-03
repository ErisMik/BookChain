#include "http/server.hpp"
#include "http/controllers/block.hpp"
#include "http/controllers/hello.hpp"
#include "http/servercomponent.hpp"
#include "version.hpp"
#include <oatpp/network/server/Server.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <string>

namespace bookchain::http {

constexpr int httpServerPort = 8000;

void run() {
    /* Register Components in scope of run() method */
    ServerComponent components;

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    /* Create controllers and add all of its endpoints to router */
    auto helloController = std::make_shared<HelloController>();
    helloController->addEndpointsToRouter(router);

    auto blockController = std::make_shared<BlockController>();
    blockController->addEndpointsToRouter(router);

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::server::Server server(connectionProvider, connectionHandler);

    OATPP_LOGI("Bookchain Node", "Version %s", &versionString[0]);
    OATPP_LOGI("Bookchain Node", "Server running on port %s", connectionProvider->getProperty("port").getData());
    server.run();
}

void startMinerHttpServer() {
    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();
}

}  // namespace bookchain::http