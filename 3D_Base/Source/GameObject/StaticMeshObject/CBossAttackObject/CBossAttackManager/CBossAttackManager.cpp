#include "CBossAttackManager.h"
#include <windows.h> // OutputDebugStringA �̂���
#include "../../CCharacter/Player/CPlayer.h"

CBossAttackManager::CBossAttackManager()
{
}

CBossAttackManager::~CBossAttackManager()
{
	// unique_ptr�͎����ŉ������邽�߁A�����I�ȉ�������͒ʏ�s�v�ł��B
}

void CBossAttackManager::Update()
{
	// �A�N�e�B�u�ȍU��������΍X�V
	if (m_pAttack)
	{
		m_pAttack->Update();
		// �U�����I���������ǂ������`�F�b�N���A�I�����Ă����unique_ptr�����Z�b�g
		if (!m_pAttack->IsAttackActive())
		{
			m_pAttack.reset(); // �U�����I�������̂ŉ��
			OutputDebugStringA("BossAttackManager: Attack finished and reset.\n");
		}
	}
}

void CBossAttackManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	// �A�N�e�B�u�ȍU��������Ε`��
	if (m_pAttack)
	{
		m_pAttack->Draw(View, Proj, Light, Camera);
	}
}

// �{�X�A�^�b�N�̐����Ɛݒ���s��
void CBossAttackManager::CreateBossAttack(BossAttackList attackType, const D3DXVECTOR3& bossCurrentPos, const D3DXVECTOR3& playerTargetPos, CPlayer* player)
{
	// �V�����U���𐶐�����O�ɁA���݂̍U��������Δj������
	m_pAttack.reset(); // ���݂�unique_ptr���ێ����Ă���I�u�W�F�N�g�����

	switch (attackType)
	{
	case BossAttackList::Slash:
		m_pAttack = std::make_unique<CBossAttackSlash>();
		// �a���J�n���\�b�h���Ăяo���A�{�X�̌��݈ʒu��n��
		if (CBossAttackSlash* slash = dynamic_cast<CBossAttackSlash*>(m_pAttack.get()))
		{
			slash->StartBossSlash(bossCurrentPos);
		}
		else
		{
			OutputDebugStringA("Error: Failed to cast to CBossAttackSlash in CreateBossAttack.\n");
		}
		break;

	case BossAttackList::Jump:
		m_pAttack = std::make_unique<CBossAttackJump>();
		if (CBossAttackJump* jump = dynamic_cast<CBossAttackJump*>(m_pAttack.get()))
		{
			jump->StartJump(bossCurrentPos);
		}
		else
		{
			OutputDebugStringA("Error: Failed to cast to CBossAttackJump in CreateBossAttack.\n");
		}
		break;

	case BossAttackList::Charge:
		m_pAttack = std::make_unique<CBossAttackSlashCharge>();
		if (CBossAttackSlashCharge* charge = dynamic_cast<CBossAttackSlashCharge*>(m_pAttack.get()))
		{
			charge->StartBossSlashCharge(bossCurrentPos);
		}
		else
		{
			OutputDebugStringA("Error: Failed to cast to CBossAttackSlashCharge in CreateBossAttack.\n");
		}
		break;

	case BossAttackList::Special:
		m_pAttack = std::make_unique<CBossAttackSpecial>();
		if (CBossAttackSpecial* special = dynamic_cast<CBossAttackSpecial*>(m_pAttack.get()))
		{
			special->StartSpecialAttack(bossCurrentPos, playerTargetPos);
		}
		else
		{
			OutputDebugStringA("Error: Failed to cast to CBossAttackSpecial in CreateBossAttack.\n");
		}
		break;

	case BossAttackList::Shout:
		m_pAttack = std::make_unique<CBossAttackShout>();
		if (CBossAttackShout* shout = dynamic_cast<CBossAttackShout*>(m_pAttack.get()))
		{
			// �C��: StartShoutAttack�̈�����CPlayer*��ǉ�
			shout->StartShoutAttack(bossCurrentPos, player);
		}
		else
		{
			OutputDebugStringA("Error: Failed to cast to CBossAttackShout in CreateBossAttack.\n");
		}
		break;

	case BossAttackList::max:
		// �G���[�n���h�����O�܂��͉������Ȃ�
		break;
	}
}

void CBossAttackManager::ResetCurrentAttack()
{
	m_pAttack.reset(); // ���݂̍U���������I�ɏI�������A�����������
	OutputDebugStringA("BossAttackManager: Current attack force reset.\n");
}