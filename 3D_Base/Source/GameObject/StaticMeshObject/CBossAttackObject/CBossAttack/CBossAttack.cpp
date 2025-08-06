#include "CBossAttack.h"

CBossAttack::CBossAttack()
{
}

CBossAttack::~CBossAttack()
{
}

void CBossAttack::Update()
{
	CBossAttackObject::Update();
}

void CBossAttack::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CBossAttackObject::Draw(View, Proj, Light, Camera);
}
