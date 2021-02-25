#pragma once

#include "Windows.h"
#include "d3d11.h"
#include "DirectXMath.h"
#include "Point.h"

struct F4
{
	void copy(Point p) {
		F2 f2b = p.getPos();
		this->x = f2b.x;
		this->y = f2b.y;
		this->z = 1.0;
		this->w = 1.0;
	}
	float x;
	float y;
	float z;
	float w;
};

struct cBuffer
{
	DirectX::XMMATRIX projection;
	F4 pointColor;
};

class Fractal
{
public:
	Fractal();
	~Fractal();

	void setDX(ID3D11Device* device, ID3D11DeviceContext* context);

	void setPointsCount(unsigned length, F2 p0, F2 p1, F2 p2);
	void update();
	void draw();

private:
	Point* points;
	unsigned* indexes;
	F4* buff;
	Point sP[3];
	unsigned countOfPoints;

	ID3D11Buffer* pointBuff;
	ID3D11Buffer* indexBuff;
	ID3D11DeviceContext* context;
	ID3D11Device* device;
	ID3D11ShaderResourceView** shaderResView;
	unsigned shResViewCount;

};

