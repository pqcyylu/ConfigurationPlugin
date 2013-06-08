#pragma once

class ControlLayoutHelper
{
protected:
	ControlLayoutHelper(void);

public:
	~ControlLayoutHelper(void);

public:
	static int CalculateHeaderTextHeight(CWnd& calculateWnd);
};

