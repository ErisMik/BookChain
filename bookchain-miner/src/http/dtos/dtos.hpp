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

class BlockDto : public oatpp::data::mapping::type::Object {
    DTO_INIT(BlockDto, Object)

    DTO_FIELD(String, prevHash);
    DTO_FIELD(String, seedHash);

    DTO_FIELD(Int64, blockHeight);
    DTO_FIELD(Int64, nonce);

    DTO_FIELD(String, signature);
    DTO_FIELD(String, data);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

}  // namespace bookchain::http