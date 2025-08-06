#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttackObject.h"

/******************************************************
*	�{�X�̍U�����N���X.
**/

class CBossAttack
	: public CBossAttackObject
{
public:
	CBossAttack();
	virtual ~CBossAttack() override;

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	// ���ǉ�: �U�����v�Z�������[���h�ʒu���擾���鏃�����z�֐�
	virtual const D3DXVECTOR3& GetCalculatedAttackPosition() const = 0;
	// ���ǉ�: �U�������݃A�N�e�B�u���ǂ�����Ԃ��������z�֐�
	virtual bool IsAttackActive() const = 0;

protected:

};