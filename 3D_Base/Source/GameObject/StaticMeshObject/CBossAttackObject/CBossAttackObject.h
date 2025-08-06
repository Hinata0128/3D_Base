#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"

/*************************************************************
*	�{�X�U���̃I�u�W�F�N�g�N���X.
*	�{�X�̍U���p���N���X�ƂȂ�BossAttack�̌p�����̎d�������Ă���.
*	�����ł́A��{���������Ȃ�.
*	
*	�쐬��: ���� ����.
**/

class CBossAttackObject
	: public CStaticMeshObject
{
public:
	CBossAttackObject();
	virtual ~CBossAttackObject() override;

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

protected:

};