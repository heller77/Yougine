#include "ComponentViewerTest.h"

namespace editor
{
    ComponentViewerTest::ComponentViewerTest()
    {
        component_viewer_ = new ComponentViewer(new yougine::components::Component(yougine::managers::ComponentName::kCollider));
    }

}