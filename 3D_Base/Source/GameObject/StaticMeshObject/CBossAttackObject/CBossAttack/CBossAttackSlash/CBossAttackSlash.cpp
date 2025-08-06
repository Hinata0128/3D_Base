#include "CBossAttackSlash.h"

CBossAttackSlash::CBossAttackSlash()
    : m_bIsSlashing(false)
    , m_fCurrentSlashTime(0.0f)
    , m_fSlashDuration(0.5f)       // �a���̎������Ԃ�0.5�b�ɐݒ� (�����\)
    , m_fZMoveDistance(-1.0f)      // Z��������-2�����i�� (�����\) ����A�j���[�V�������Ȃ����ߓ���Ŋm�F�ł���R�[�h�ɂ��Ă���
    , m_vInitialBossPos(0.0f, 0.0f, 0.0f)
    , m_vCurrentAttackPos(0.0f, 0.0f, 0.0f)
{
    D3DXMatrixIdentity(&m_mAttackWorld); //���[���h�s���P�ʍs��ŏ�����
}

CBossAttackSlash::~CBossAttackSlash()
{
}

// �a���U�����J�n����
void CBossAttackSlash::StartBossSlash(const D3DXVECTOR3& bossCurrentPos)
{
    //���Ɏa�����Ȃ牽�����Ȃ�
    if (m_bIsSlashing)
    {
        return;
    }

    m_bIsSlashing       = true;
    m_fCurrentSlashTime = 0.0f;             //�o�ߎ��Ԃ����Z�b�g
    m_vInitialBossPos   = bossCurrentPos;   //�U���J�n���̃{�X�̈ʒu��ۑ�
    m_vCurrentAttackPos = bossCurrentPos;   //���݈ʒu�������ʒu�ŏ�����
}

// �a���U���̍X�V
void CBossAttackSlash::Update()
{
    //�a�����łȂ���Ή������Ȃ�
    if (!m_bIsSlashing)
    {
        return;
    }

    //�f���^�^�C���̎擾.
    //����60FPS�Œ�Ɖ���.
    float deltaTime = 1.0f / 60.0f;

    m_fCurrentSlashTime += deltaTime;

    //�a�����I�����ԂɂȂ������~
    if (m_fCurrentSlashTime >= m_fSlashDuration)
    {
        m_bIsSlashing       = false;
        m_fCurrentSlashTime = m_fSlashDuration; //�ŏI�t���[���ł̌v�Z�̂��߁A���Ԃ��N�����v
    }

    //���`��Ԃ��g����Z�������Ɉړ�
    //�i�s�x (0.0f ���� 1.0f)�B���Ԃ��o�߂���ɂ��0����1�֕ω�
    float progress = m_fCurrentSlashTime / m_fSlashDuration;
    if (progress > 1.0f)
    {
        progress = 1.0f;
    }

    //Z�������ւ̈ړ��ʂ��v�Z
    float currentZMove = m_fZMoveDistance * progress;

    //�U���ɂ���Čv�Z�����{�X�̌��݈ʒu.
    m_vCurrentAttackPos.x = m_vInitialBossPos.x;                //X���W�͕ύX���Ȃ�.
    m_vCurrentAttackPos.y = m_vInitialBossPos.y;                //Y���W�͕ύX���Ȃ�.
    m_vCurrentAttackPos.z = m_vInitialBossPos.z + currentZMove; //Z���W�̂ݕω�.

    //CStaticMeshObject�̓����ʒu���X�V
    SetPosition(m_vCurrentAttackPos);

    CStaticMeshObject::Update(); //���N���X��Update���Ăяo��.
}

void CBossAttackSlash::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_bIsSlashing)
    {
        //�U���I�u�W�F�N�g���g�̕`�揈��.
        CStaticMeshObject::Draw(View, Proj, Light, Camera); //���N���X�̕`����Ăяo��.
    }
}