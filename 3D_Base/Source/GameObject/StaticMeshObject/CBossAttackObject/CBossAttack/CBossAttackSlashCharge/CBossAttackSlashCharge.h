#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"

/********************************************************************
* �{�X�̃`���[�W�U������.
* ��莞�ԃ`���[�W������AZ�������ɓːi����U�����������܂��B
* �`���[�W���ɓ���̏����𖞂�����X���Ɉړ�����@�\���ǉ����܂��B
**/
class CBossAttackSlashCharge
    : public CBossAttack
{
public:
    CBossAttackSlashCharge();
    ~CBossAttackSlashCharge() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

    // �`���[�W�U�����J�n���郁�\�b�h
    // Parameters:
    //   bossCurrentPos: �U���J�n���̃{�X�̌��݂̃��[���h���W
    void StartBossSlashCharge(const D3DXVECTOR3& bossCurrentPos);

    // ���ݍU�����ł��邩��Ԃ����\�b�h
    // IsSlashing�Ƃ������̂̓`���[�W�U���̈Ӑ}������ŕύX���邱�Ƃ��\�ł�
    bool IsSlashing() const { return m_bIsAttacking; }

    // �U�����쒆�̃{�X�̃��[���h�s����擾���郁�\�b�h
    // �{�X�̕`���ʒu�X�V�ɂ�����g�p���܂�
    const D3DXMATRIX& GetAttackWorldMatrix() const { return m_mAttackWorld; }

    // CBossAttack�̏������z�֐����I�[�o�[���C�h
    bool IsAttackActive() const override { return m_bIsAttacking; }
    const D3DXVECTOR3& GetCalculatedAttackPosition() const override { return m_vCurrentAttackPos; }

private:
    //
    // �U���t�F�[�Y�Ǘ��p�t���O
    //
    enum class AttackPhase
    {
        None,           // �U���ҋ@��
        Charging,       // �`���[�W��
        Slashing        // �ːi��
    };

    AttackPhase m_CurrentPhase; // ���݂̍U���t�F�[�Y

    bool        m_bIsAttacking;           // �U���S�̂��A�N�e�B�u���ǂ������Ǘ�����t���O

    float       m_fCurrentTime;           // �U���S�̂̌o�ߎ��� (�b)
    float       m_fChargeDuration;        // �`���[�W�̎������� (�b)
    float       m_fSlashDuration;         // �ːi�̎������� (�b)

    float       m_fXMoveDistance;         // X�������Ɉړ����鋗�� (����̗v�� - 1.0f)

    D3DXVECTOR3 m_vInitialBossPos;        // �U���J�n���̃{�X�̏����ʒu
    D3DXVECTOR3 m_vCurrentAttackPos;      // �U���ɂ���Čv�Z�����{�X�̌��݈ʒu
    D3DXMATRIX  m_mAttackWorld;           // �U�����쒆�̃{�X�̃��[���h�s��
};