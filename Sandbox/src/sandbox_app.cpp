#include <Robin.h>

class sandbox : public Robin::application
{
public: 
	sandbox()
	{

	}

	~sandbox()
	{

	}
};

Robin::application* Robin::create_application()
{
	return new sandbox();
}