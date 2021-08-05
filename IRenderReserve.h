#pragma once
class IRenderReserve
{
protected:
	int GHandle;
	double Priority;

public:
	IRenderReserve(int GHandle, double Priority);
	virtual ~IRenderReserve() {}

	virtual void Render()const = 0;
	bool operator <(IRenderReserve *rhs);

	friend bool compRenderReserve(IRenderReserve* l, IRenderReserve* r);
};

bool compRenderReserve(IRenderReserve* l, IRenderReserve* r);