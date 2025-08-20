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
		KnockingBack, // 新しい状態: プレイヤーを吹き飛ばしている間
		Finished
	};
	ShoutState m_eState;

	D3DXVECTOR3 m_vBossPos;
	D3DXVECTOR3 m_vPlayerStartPos;
	D3DXVECTOR3 m_vKnockbackEndPos; // 吹き飛ばし後の着地位置
	float m_fShoutTimer;
	float m_fKnockbackTimer;

	const float SHOUT_DURATION = 1.0f; // 叫び声の持続時間
	const float KNOCKBACK_DURATION = 1.5f; // 吹き飛ばしにかかる時間
	const float KNOCKBACK_HEIGHT = 5.0f; // 吹き飛ばしの最高到達点

	bool m_bIsFinished;
	CPlayer* m_pPlayer = nullptr;
};