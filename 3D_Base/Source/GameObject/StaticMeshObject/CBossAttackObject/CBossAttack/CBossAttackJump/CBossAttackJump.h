#pragma once

#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"

class CBossAttackJump
    : public CBossAttack
{
public:
    CBossAttackJump();
    ~CBossAttackJump() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

    void StartJump(const D3DXVECTOR3& bossCurrentPos);

    bool IsAttackActive() const override { return m_bIsJumping; }
    const D3DXVECTOR3& GetCalculatedAttackPosition() const override { return m_vCurrentAttackPos; }

private:
    bool m_bIsJumping;             // �W�����v�����ǂ������Ǘ�����t���O
    float m_fCurrentJumpTime;      // ���݂̃W�����v�o�ߎ��� (�b)
    float m_fJumpDuration;         // �W�����v�̎������� (�b) - ���̃��f���ł͒��ڎg��Ȃ����A�ڈ��Ƃ��Ďc��
    float m_fJumpHeight;           // �W�����v�̍ő卂�� - ���̃��f���ł͒��ڎg��Ȃ����A�ڈ��Ƃ��Ďc��

    // ���ǉ��E�ύX: �����W�����v�ɕK�v�ȕϐ�
    D3DXVECTOR3 m_vInitialBossPos; // �W�����v�J�n���̃{�X�̏����ʒu (X, Z�͈ێ��AY�̓W�����v�O�̒n�ʂ�Y��ێ�)
    D3DXVECTOR3 m_vCurrentAttackPos; // �W�����v���̃{�X�̌��݈ʒu (���̃N���X�Ōv�Z�����ʒu)

    D3DXVECTOR3 m_vJumpVelocity;   // �W�����v���̌��݂�Y�������x
    float       m_JumpPower;       // �W�����v�̏����x�i�v���C���[��m_JumpPower�ɑ����j
    float       m_Gravity;         // �d�͉����x�i�v���C���[��m_Gravity�ɑ����j
    // bool        m_GroundedFlag; // �{�X�U�����ł͊O���iCBoss�j���Ǘ�����̂ŕs�v
};