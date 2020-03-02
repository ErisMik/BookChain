#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

namespace bookchain::http {

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

class JobDto : public oatpp::data::mapping::type::Object {
    DTO_INIT(JobDto, Object)

    DTO_FIELD(UInt64, id);
    DTO_FIELD(String, data);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

}  // namespace bookchain::http
