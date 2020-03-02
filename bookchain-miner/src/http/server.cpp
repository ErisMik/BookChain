#include "http/server.hpp"
#include "http/controllers/block.hpp"
#include "http/controllers/hello.hpp"
#include "http/controllers/job.hpp"
#include "http/controllers/peer.hpp"
#include "http/servercomponent.hpp"
#include "version.hpp"
#include <oatpp/network/server/Server.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <string>

namespace bookchain::http {

void run() {
    /* Register Components in scope of run() method */
    ServerComponent components;

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);  // NOLINT

    /* Create controllers and add all of its endpoints to router */
    auto helloController = std::make_shared<HelloController>();
    helloController->addEndpointsToRouter(router);

    auto blockController = std::make_shared<BlockController>();
    blockController->addEndpointsToRouter(router);

    auto jobController = std::make_shared<JobController>();
    jobController->addEndpointsToRouter(router);

    auto peerController = std::make_shared<PeerController>();
    peerController->addEndpointsToRouter(router);

    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, connectionHandler);  // NOLINT

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);  // NOLINT

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::server::Server server(connectionProvider, connectionHandler);

    OATPP_LOGI("Bookchain Node", "Version %s", &versionString[0]);  // NOLINT
    OATPP_LOGI("Bookchain Node", "Server running on port %s", connectionProvider->getProperty("port").getData());  // NOLINT
    server.run();
}

void startNodeServer(const sharedTSQueue<Peer>& peerQueue, const sharedTSQueue<std::string>& dataQueue, const sharedTSQueue<Job>& jobQueue) {
    oatpp::base::Environment::init();

    /* Dependency Injection */
    OATPP_CREATE_COMPONENT(sharedTSQueue<Peer>, peerQueueComponent)
    ([peerQueue] {
        return peerQueue;
    }());

    OATPP_CREATE_COMPONENT(sharedTSQueue<std::string>, dataQueueComponent)
    ([dataQueue] {
        return dataQueue;
    }());

    OATPP_CREATE_COMPONENT(sharedTSQueue<Job>, jobQueueComponent)
    ([jobQueue] {
        return jobQueue;
    }());

    run();
    oatpp::base::Environment::destroy();
}

}  // namespace bookchain::http
