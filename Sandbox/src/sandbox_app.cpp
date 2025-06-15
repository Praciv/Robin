#include <Robin.h>
// ------Entry point----------------------
#include "Robin/entry_point.h"
// ---------------------------------------

#include "sandbox_3D.h"

class sandbox : public Robin::application
{
public: 
	sandbox()
	{
		push_layer(new sandbox_3D());
	}

	~sandbox()
	{

	}
};

Robin::application* Robin::create_application()
{
	return new sandbox();
}