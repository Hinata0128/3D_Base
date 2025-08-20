#pragma once

#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttackManager/CBossAttackManager.h"

// �v���C���[�ւ̑O���錾
class CPlayer;

/***********************************************************************
*	�{�X�L�����N���X.
**/
class CBoss
	: public CCharacter
{
public:
	CBoss();
	~CBoss() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;
	void Init();
	void InitializeBossPosition(const D3DXVECTOR3& initialPos);
	void RadioControl();
	void HandleGroundCollision(CStaticMeshObject* pGroundObject);

	void SetPlayer(CPlayer* player) { m_pPlayer = player; }

protected:
	float m_TurnSpeed;
	float m_MoveSpeed;

	enum enMoveState
	{
		stop,
		walk,
		run,
		attack,
	};
	enMoveState m_MoveState;

	D3DXVECTOR3 m_vCurrentMoveVelocity;

	float deleta_time;
	float m_fSlashCoolTime;
	const float SLASH_COOLTIME_DURATION = 2.0f;

	std::unique_ptr<CBossAttackManager> m_bossAttackManager;
	CPlayer* m_pPlayer;

	// ���C��: Special��񋓌^�ɒǉ�
	enum class AttackSequenceState {
		Jump,
		Slash,
		Charge,
		Special,
		Shout, // ���ǉ�
	};
	AttackSequenceState m_eCurrentAttackSequenceState;
};