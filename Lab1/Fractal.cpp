#include "Fractal.h"



Fractal::Fractal()
{
}


Fractal::~Fractal()
{
	if (this->indexBuff != 0) {
		(this->indexBuff)->Release();
	}
	if (this->pointBuff != 0) {
		(this->pointBuff)->Release();
	}
	if (this->shaderResView != 0) {
		for (unsigned t = 0; t < this->shResViewCount; t++) {
			(this->shaderResView[t])->Release();
		}
	}
	if (this->points != 0) {
		delete[] this->points;
	}
	if (this->indexes != 0) {
		delete[] this->indexes;
	}
}

void Fractal::setDX(ID3D11Device * device, ID3D11DeviceContext * context)
{
	this->device = device;
	this->context = context;
}

void Fractal::setPointsCount(unsigned length, F2 p0, F2 p1, F2 p2)
{
	HRESULT hr = NULL;

	this->points = new Point[length];
	this->indexes = new unsigned[length];
	this->buff = new F4[length];
	this->countOfPoints = length;

	this->sP[0] = p0;
	this->sP[1] = p1;
	this->sP[2] = p2;

	F2 f = { 0.0f, 0.0f };

	for (unsigned t = 0; t < this->countOfPoints; t++) {
		this->points[t] = f;
		this->indexes[t] = t;
	}

	D3D11_SUBRESOURCE_DATA pointSR;

	pointSR.pSysMem = &(this->buff[0]);
	pointSR.SysMemPitch = 0;
	pointSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC* bd = new D3D11_BUFFER_DESC;
	bd->Usage = D3D11_USAGE_DYNAMIC;
	bd->ByteWidth = sizeof(F4) * this->countOfPoints;
	bd->BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd->CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd->MiscFlags = 0;
	bd->StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(bd, &pointSR, &(this->pointBuff));

	D3D11_SUBRESOURCE_DATA indexSR;

	indexSR.pSysMem = &(this->indexes[0]);
	indexSR.SysMemPitch = 0;
	indexSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC* ibd = new D3D11_BUFFER_DESC;
	ibd->Usage = D3D11_USAGE_DEFAULT;
	ibd->ByteWidth = sizeof(unsigned)*this->countOfPoints;
	ibd->BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd->CPUAccessFlags = 0;
	ibd->MiscFlags = 0;
	ibd->StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(ibd, &indexSR, &(this->indexBuff));

	if (FAILED(hr)) {
		MessageBox(NULL, "error create buff", "err", MB_ICONSTOP | MB_OK);
	}

}

void Fractal::update()
{
	this->points[0] = sP[rand() % 3];
	(this->buff[0]).copy(this->points[0]);
	for (unsigned t = 1; t < this->countOfPoints; t++) {
		(this->points[t]).set(this->points[t - 1], sP[rand() % 3]);
		(this->buff[t]).copy(this->points[t]);
	}

	D3D11_MAPPED_SUBRESOURCE mappedSR = { 0 };
	ID3D11Buffer* buff;
	//ZeroMemory(&mappedSR, sizeof(D3D11_MAPPED_SUBRESOURCE));

	(this->context)->Map((this->pointBuff), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSR);

	memcpy(mappedSR.pData, &(this->buff[0]), this->countOfPoints * sizeof(F4));

	(this->context)->Unmap(this->pointBuff, 0);

}

void Fractal::draw() {
	UINT stride = sizeof(F4);
	UINT offset = 0;

	(this->context)->IASetVertexBuffers(0, 1, &this->pointBuff, &stride, &offset);
	(this->context)->IASetIndexBuffer(this->indexBuff, DXGI_FORMAT_R32_UINT, 0);

	(this->context)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	(this->context)->DrawIndexed(this->countOfPoints, 0, 0);
	//(this->context)->Draw(this->countOfPoints, 0);
}
