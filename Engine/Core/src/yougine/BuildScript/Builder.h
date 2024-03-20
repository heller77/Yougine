#pragma once
#include <string>

#include "UserShare/Scene.h"

namespace builders
{
    class Builder
    {
    public:
        /**
         * \brief
         */
        void Build(std::string exportpath, yougine::Scene* scene);
    };
}
