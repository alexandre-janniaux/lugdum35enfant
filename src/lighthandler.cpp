#include "lighthandler.hpp"

void LightHandler::computeLights()
{
    for (auto& it : m_lamps)
        it->computeLight(m_obstacles);
}
