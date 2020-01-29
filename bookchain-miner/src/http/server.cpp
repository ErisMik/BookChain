#include "version.hpp"
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/network/server/Server.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <string>

namespace bookchain::http {

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

class BasicMessageDto : public oatpp::data::mapping::type::Object {
    DTO_INIT(BasicMessageDto, Object)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(String, message);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

class HelloHandler : public oatpp::web::server::HttpRequestHandler {
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
    /**
   * Constructor with object mapper.
   * @param objectMapper - object mapper used to serialize objects.
   */
    HelloHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) :
        m_objectMapper(objectMapper) {}

    /**
   * Handle incoming request and return outgoing response.
   */
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& /* request */) override {
        auto message = BasicMessageDto::createShared();
        message->statusCode = 1024;
        message->message = "Hello DTO!";
        return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
    }
};

void run() {
    /* Create json object mapper */
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    /* Create Router for HTTP requests routing */
    auto router = oatpp::web::server::HttpRouter::createShared();

    /* Route GET - "/hello" requests to Handler */
    router->route("GET", "/hello", std::make_shared<HelloHandler>(objectMapper));

    /* Create HTTP connection handler with router */
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    /* Create TCP connection provider */
    auto connectionProvider = oatpp::network::server::SimpleTCPConnectionProvider::createShared(8000);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::server::Server server(connectionProvider, connectionHandler);

    /* Print info about server port */
    OATPP_LOGI("Bookchain Node", "Version %s", versionString);
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