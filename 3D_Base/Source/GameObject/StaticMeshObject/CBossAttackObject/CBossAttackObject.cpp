#include "CBossAttackObject.h"

CBossAttackObject::CBossAttackObject()
{
}

CBossAttackObject::~CBossAttackObject()
{
}

void CBossAttackObject::Update()
{
	CStaticMeshObject::Update();
}

void CBossAttackObject::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CStaticMeshObject::Draw(View, Proj, Light, Camera);
}
