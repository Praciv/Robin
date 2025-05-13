#include <Robin.h>

class Sandbox : public Robin::Application
{
public: 
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Robin::Application* Robin::Create_Application()
{
	return new Sandbox();
}