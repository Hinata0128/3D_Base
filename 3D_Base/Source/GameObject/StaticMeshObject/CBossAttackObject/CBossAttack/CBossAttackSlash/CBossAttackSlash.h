#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"

class CBossAttackSlash
    : public CBossAttack
{
public:
    CBossAttackSlash();
    ~CBossAttackSlash() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

    //�a���U�����J�n���郁�\�b�h
    //Parameters:
    //  bossCurrentPos: �U���J�n���̃{�X�̌��݂̃��[���h���W
    void StartBossSlash(const D3DXVECTOR3& bossCurrentPos);

    //���ݎa�����ł��邩��Ԃ����\�b�h
    bool IsSlashing() const { return m_bIsSlashing; }

    //�a�����쒆�̃{�X�̃��[���h�s����擾���郁�\�b�h
    //�{�X�̕`���ʒu�X�V�ɂ�����g�p���܂�
    const D3DXMATRIX& GetAttackWorldMatrix() const { return m_mAttackWorld; }

    //CBossAttack�̏������z�֐����I�[�o�[���C�h
    bool IsAttackActive() const override { return m_bIsSlashing; }
    const D3DXVECTOR3& GetCalculatedAttackPosition() const override { return m_vCurrentAttackPos; }

private:
    bool        m_bIsSlashing;              //�a�������ǂ������Ǘ�����t���O
    float       m_fCurrentSlashTime;        //���݂̎a���o�ߎ��� (�b)
    float       m_fSlashDuration;           //�a���̎������� (�b)
    float       m_fZMoveDistance;           //Z�������ւ̈ړ����� (�����-2.0f)
    D3DXVECTOR3 m_vInitialBossPos;          //�a���J�n���̃{�X�̏����ʒu
    D3DXVECTOR3 m_vCurrentAttackPos;        //�a�����̃{�X�̌��݈ʒu (�U���ɂ���Čv�Z�����ʒu)
    D3DXMATRIX  m_mAttackWorld;             //�a�����쒆�̃{�X�̃��[���h�s��
};