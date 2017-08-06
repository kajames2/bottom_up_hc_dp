#include "health_state.h"

namespace healthcare {

bool IsAlive(const HealthState& state) { return state.health > 0; }
} // namespace healthcare
