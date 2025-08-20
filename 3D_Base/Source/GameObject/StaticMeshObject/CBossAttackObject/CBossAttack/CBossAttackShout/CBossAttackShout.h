#pragma once
#include "..//CBossAttack.h"
#include "..//..//..//CCharacter/Player/CPlayer.h"

class CBossAttackShout
	: public CBossAttack
{
public:
	CBossAttackShout();
	~CBossAttackShout() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void StartShoutAttack(const D3DXVECTOR3& bossPos, CPlayer* player);

	const D3DXVECTOR3& GetCalculatedAttackPosition() const override;
	bool IsAttackActive() const override;

private:
	enum class ShoutState
	{
		Shouting,
		KnockingBack, // �V�������: �v���C���[�𐁂���΂��Ă����
		Finished
	};
	ShoutState m_eState;

	D3DXVECTOR3 m_vBossPos;
	D3DXVECTOR3 m_vPlayerStartPos;
	D3DXVECTOR3 m_vKnockbackEndPos; // ������΂���̒��n�ʒu
	float m_fShoutTimer;
	float m_fKnockbackTimer;

	const float SHOUT_DURATION = 1.0f; // ���ѐ��̎�������
	const float KNOCKBACK_DURATION = 1.5f; // ������΂��ɂ����鎞��
	const float KNOCKBACK_HEIGHT = 5.0f; // ������΂��̍ō����B�_

	bool m_bIsFinished;
	CPlayer* m_pPlayer = nullptr;
};