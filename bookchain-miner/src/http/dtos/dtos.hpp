#pragma once

#include "peers.hpp"
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

namespace bookchain::http {

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

class BasicMessageDto : public oatpp::data::mapping::type::Object {
    DTO_INIT(BasicMessageDto, Object)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(String, message);
};

class PeersListDto : public oatpp::data::mapping::type::Object {
    DTO_INIT(PeersListDto, Object)

    DTO_FIELD(Fields<List<BasicMessageDto::ObjectWrapper>::ObjectWrapper>::ObjectWrapper, peers);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

}  // namespace bookchain::http