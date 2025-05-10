#pragma once
#include <iostream>

#pragma warning(disable: 26495)


class Module
{
public:
	bool enable;
	std::string name;
	//virtual bool tick() = 0;
	virtual void status() { printf(" %15s: %s                     \n", name.c_str(), (enable) ? "Enabled" : "Disabled"); }
};
#pragma warning(default: 26495)