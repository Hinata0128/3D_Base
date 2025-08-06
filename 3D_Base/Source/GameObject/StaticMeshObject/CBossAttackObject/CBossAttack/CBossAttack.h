#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttackObject.h"

/******************************************************
*	�{�X�̍U�����N���X.
*	�����ł́A�p��������q�N���X�S�̂Ɏg�p����֐��Ȃǂ������Ă���.
*	���̃N���X�͊�{�g�p�͂��Ă��Ȃ����A�K�v�Ȋ֐����^�X�N���X�Ƃ��Ďg�p���Ă��܂�.
* 
*	�S����: ���� ����.
**/

class CBossAttack
	: public CBossAttackObject
{
public:
	CBossAttack();
	virtual ~CBossAttack() override;

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//�U�����v�Z�������[���h�ʒu���擾���鏃�����z�֐�
	virtual const D3DXVECTOR3& GetCalculatedAttackPosition() const = 0;
	//�U�������݃A�N�e�B�u���ǂ�����Ԃ��������z�֐�
	virtual bool IsAttackActive() const = 0;

protected:

};