#pragma once
#include <string>

#include "../Scene.h"

namespace builders
{
    class Builder
    {
    public:
        /**
         * \brief
         */
        void Build(std::string exportpath,yougine::Scene* scene);
    };
}
