#pragma once

#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttackManager/CBossAttackManager.h" // ���ꂪ�C���N���[�h����Ă��邱�Ƃ��m�F

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
    void Init(); // ���������\�b�h

    void InitializeBossPosition(const D3DXVECTOR3& initialPos); // �{�X�̏����ʒu��ݒ肷�郁�\�b�h
    void RadioControl(); // �g�p����Ă��Ȃ��悤�ł����A��������g�p����Ȃ�R�����g���폜
    void HandleGroundCollision(CStaticMeshObject* pGroundObject); // �n�ʂƂ̏Փˏ���

    void SetPlayer(CPlayer* player) { m_pPlayer = player; } // �v���C���[�|�C���^�̐ݒ�

protected:
    float m_TurnSpeed; // ���񑬓x
    float m_MoveSpeed; // �ړ����x

    enum enMoveState
    {
        stop,    // ��~
        walk,    // ���s
        run,     // ���s
        attack,  // �U�� (�����CBossAttackManager�ŊǗ�)
    };
    enMoveState m_MoveState; // �ړ����

    D3DXVECTOR3 m_vCurrentMoveVelocity; // ���݂̈ړ����x�x�N�g��

    // �N�[���^�C���Ǘ�
    float deleta_time; // ���݂͎g���Ă��Ȃ��N�[���^�C���p�ϐ��i�c�[�j
    float m_fSlashCoolTime; // �a������уW�����v�U���̃N�[���^�C���J�E���^�[
    const float SLASH_COOLTIME_DURATION = 2.0f; // �U���N�[���^�C���̒����i�b�j

    std::unique_ptr<CBossAttackManager> m_bossAttackManager; // �{�X�U�����Ǘ�����}�l�[�W���[
    CPlayer* m_pPlayer; // �v���C���[�ւ̃|�C���^�i�����v�Z�Ɏg�p�j
};