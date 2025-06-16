#include "rbpch.h"
#include "timer.h"

namespace Robin
{
	scope<timer_manager> timer_manager::s_manager = std::make_unique<timer_manager>();
}