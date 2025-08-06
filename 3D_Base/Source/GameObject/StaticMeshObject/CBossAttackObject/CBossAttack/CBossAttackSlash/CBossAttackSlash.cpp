#include "CBossAttackSlash.h"
#include <iostream> // �f�o�b�O�o�͗p�i�K�v�Ȃ���΍폜�j
#include <windows.h> // OutputDebugStringA �̂���

CBossAttackSlash::CBossAttackSlash()
    : m_bIsSlashing(false)
    , m_fCurrentSlashTime(0.0f)
    , m_fSlashDuration(0.5f)       // �a���̎������Ԃ�0.5�b�ɐݒ� (�����\)
    , m_fZMoveDistance(-2.0f)      // Z��������-2�����i�� (�����\) ����A�j���[�V�������Ȃ����ߓ���Ŋm�F�ł���R�[�h�ɂ��Ă���
    , m_vInitialBossPos(0.0f, 0.0f, 0.0f)
    , m_vCurrentAttackPos(0.0f, 0.0f, 0.0f)
{
    D3DXMatrixIdentity(&m_mAttackWorld); // ���[���h�s���P�ʍs��ŏ�����
}

CBossAttackSlash::~CBossAttackSlash()
{
}

// �a���U�����J�n����
void CBossAttackSlash::StartBossSlash(const D3DXVECTOR3& bossCurrentPos)
{
    if (m_bIsSlashing) return; // ���Ɏa�����Ȃ牽�����Ȃ�

    m_bIsSlashing = true;
    m_fCurrentSlashTime = 0.0f; // �o�ߎ��Ԃ����Z�b�g
    m_vInitialBossPos = bossCurrentPos; // �U���J�n���̃{�X�̈ʒu��ۑ�
    m_vCurrentAttackPos = bossCurrentPos; // ���݈ʒu�������ʒu�ŏ�����

    OutputDebugStringA("Slash Started!\n"); // �f�o�b�O�E�B���h�E�ɏo��
}

// �a���U���̍X�V
void CBossAttackSlash::Update()
{
    if (!m_bIsSlashing) return; // �a�����łȂ���Ή������Ȃ�

    // �f���^�^�C���̎擾�i���ۂ̃Q�[�����[�v���琳�m�Ȓl���擾���Ă��������j
    // ����60FPS�Œ�Ɖ��� (1.0f / 60.0f = ��0.01666f)
    float deltaTime = 1.0f / 60.0f;

    m_fCurrentSlashTime += deltaTime;

    // �a�����I�����ԂɂȂ������~
    if (m_fCurrentSlashTime >= m_fSlashDuration)
    {
        m_bIsSlashing = false;
        m_fCurrentSlashTime = m_fSlashDuration; // �ŏI�t���[���ł̌v�Z�̂��߁A���Ԃ��N�����v
        OutputDebugStringA("Slash Ended.\n"); // �f�o�b�O�E�B���h�E�ɏo��
        // �U���I�����ɃI�u�W�F�N�g���A�N�e�B�u�ɂ���Ȃǂ̏������K�v�ȏꍇ�A�����ɒǉ�
    }

    // ���`��Ԃ��g����Z�������Ɉړ�
    // �i�s�x (0.0f ���� 1.0f)�B���Ԃ��o�߂���ɂ��0����1�֕ω�
    float progress = m_fCurrentSlashTime / m_fSlashDuration;
    if (progress > 1.0f) progress = 1.0f; // 1.0f �𒴂��Ȃ��悤�ɃN�����v

    // Z�������ւ̈ړ��ʂ��v�Z
    float currentZMove = m_fZMoveDistance * progress;

    // �U���ɂ���Čv�Z�����{�X�̌��݈ʒu
    m_vCurrentAttackPos.x = m_vInitialBossPos.x; // X���W�͕ύX���Ȃ�
    m_vCurrentAttackPos.y = m_vInitialBossPos.y; // Y���W�͕ύX���Ȃ�
    m_vCurrentAttackPos.z = m_vInitialBossPos.z + currentZMove; // Z���W�̂ݕω�

    // CStaticMeshObject�̓����ʒu���X�V
    SetPosition(m_vCurrentAttackPos);

    CStaticMeshObject::Update(); // ���N���X��Update���Ăяo�� (���[���h�s��̍X�V�Ȃ�)
}

void CBossAttackSlash::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_bIsSlashing)
    {
        // �U���I�u�W�F�N�g���g�̕`�揈��
        CStaticMeshObject::Draw(View, Proj, Light, Camera); // ���N���X�̕`����Ăяo��
    }
}