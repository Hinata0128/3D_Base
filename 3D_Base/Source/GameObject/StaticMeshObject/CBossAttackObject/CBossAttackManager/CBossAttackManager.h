#pragma once
#include <vector>
#include <memory>
// CBossAttackObject/CBossAttackObject.h �͒��ڎg�p���Ȃ��Ȃ�폜
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttackSlash/CBossAttackSlash.h"
// ���ǉ�: Jump Attack�̃w�b�_���C���N���[�h
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttackJump/CBossAttackJump.h" // �������p�X�ɒ������Ă�������

/***********************************************************************
*	�{�X�}�l�[�W���[�N���X.
**/

class CBossAttackManager
{
public:
	//�񋓌^���쐬(BossList�p)
	enum class BossAttackList
	{
		Slash,
		Jump, // ���ǉ�: �W�����v�U��
		max,
	};

public:
	CBossAttackManager();
	~CBossAttackManager();

	void Update();
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera);

	// �{�X�A�^�b�N�̐����Ɛݒ���s���֐�
	// Parameters:
	//    attackType: �U���̎��
	//    bossCurrentPos: �U���J�n���̃{�X�̌��݂̃��[���h���W
	void CreateBossAttack(BossAttackList attackType, const D3DXVECTOR3& bossCurrentPos);

	// ���݃A�N�e�B�u�ȃ{�X�A�^�b�N�����݂��邩�ǂ������`�F�b�N����
	bool HasActiveAttack() const { return m_pAttack != nullptr && m_pAttack->IsAttackActive(); }

	// ���݃A�N�e�B�u�ȃ{�X�A�^�b�N�I�u�W�F�N�g�ւ̃|�C���^���擾�i�ǂݎ���p�j
	// CBoss�N���X���U���̏�Ԃ�ʒu���擾���邽�߂Ɏg�p
	CBossAttack* GetActiveAttack() const { return m_pAttack.get(); }

	// ���݂̃{�X�A�^�b�N�������I�ɏI��������i�K�v�ł���΁j
	void ResetCurrentAttack();


private:
	std::unique_ptr<CBossAttack> m_pAttack; // ���݃A�N�e�B�u�ȃ{�X�A�^�b�N��ێ�
};