#include "uv_util.h"
#include <atomic>

static std::atomic_int32_t g_step_incr(1);
uint32_t GenerateUniqueID() {
  // Get current time as milliseconds since Unix epoch
  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count();

  // Combine time

  uint32_t id = now << 16 | (g_step_incr.fetch_add(1));
  return id;
}