#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

namespace bookchain::http {

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

class PeerLinkDto : public oatpp::data::mapping::type::Object {
    DTO_INIT(PeerLinkDto, Object)

    DTO_FIELD(UInt64, identifier);
    DTO_FIELD(String, version);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

}  // namespace bookchain::http
