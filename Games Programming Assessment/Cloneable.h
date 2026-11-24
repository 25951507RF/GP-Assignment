#pragma once

// [NEW FILE] Clone Management

class ICloneable
{
public:
	virtual ICloneable* clone() = 0;
};