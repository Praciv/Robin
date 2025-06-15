#include <Robin.h>
#include <Robin/entry_point.h>

#include "editor_layer.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Robin
{
	class robin_editor : public application
	{
	public:
		robin_editor()
		{
			push_layer(new editor_layer());
		}

		~robin_editor()
		{

		}
	};

	application* create_application()
	{
		return new robin_editor();
	}
}