#include "CBossAttackJump.h"
#include <cmath>       //fmaxf ���g�����߂ɕK�v

CBossAttackJump::CBossAttackJump()
    : m_bIsJumping(false)
    , m_fCurrentJumpTime(0.0f)
    , m_fJumpDuration(0.5f)                 //���̃��f���ł͒��ڎg��Ȃ����A�������q�Ƃ��Ďc��
    , m_fJumpHeight(5.0f)                   //���̃��f���ł͒��ڎg��Ȃ����A�������q�Ƃ��Ďc��
    , m_vInitialBossPos(0.0f, 0.0f, 0.0f)
    , m_vCurrentAttackPos(0.0f, 0.0f, 0.0f)
    , m_vJumpVelocity(0.0f, 0.0f, 0.0f)     //�W�����v���x��������
    , m_JumpPower(0.42f)                    //�v���C���[�̃W�����v�͂Ɠ��������l
    , m_Gravity(0.02f)                      //�v���C���[�̏d�͂Ɠ��������l
{
    //�����ɃG�t�F�N�g�̎����R�[�h������.
    //�V���O���g���ō쐬���Ă���Ȃ炱���ɖ��O����͂����ł���.
}

CBossAttackJump::~CBossAttackJump()
{
}

void CBossAttackJump::StartJump(const D3DXVECTOR3& bossCurrentPos)
{
    //���ɃW�����v���ł���Ή������Ȃ�
    if (m_bIsJumping)
    {
        return;
    }

    m_bIsJumping        = true;
    m_fCurrentJumpTime  = 0.0f;           //�o�ߎ��Ԃ����Z�b�g
    m_vInitialBossPos   = bossCurrentPos; //�W�����v�J�n���̃{�X�̃��[���h�ʒu��ۑ�
    //�W�����v�J�n����Y���x�ɃW�����v�͂�^����
    m_vJumpVelocity.y   = m_JumpPower;

    //���݈ʒu�������ʒu�ŏ�����
    m_vCurrentAttackPos = bossCurrentPos;

    //CStaticMeshObject�̊��N���X�̈ʒu���X�V
    SetPosition(m_vInitialBossPos);
}

void CBossAttackJump::Update()
{
    //�W�����v���łȂ���Ή������Ȃ�
    if (!m_bIsJumping)
    {
        return;
    }

    //�f���^�^�C���̎擾 (���ۂ̃Q�[�����[�v���琳�m�Ȓl���擾���Ă�������)
    //�v���C���[�Ɠ����v�Z���W�b�N�ɂ��邽�߁Adelta_time ���g�p
    float delta_time = 1.0f; // ���v���C���[��Update�Ɠ������A�����ŌŒ�l���g�����A���ۂ̃f���^�^�C����n��������
    //�ʏ�� deltaTime = 1.0f / 60.0f; �̂悤�Ɏ��ۂ̌o�ߎ��Ԃ��g���ׂ��ł�
    //����̓v���C���[�ɍ��킹�� 1.0f �Ƃ��܂�

    m_fCurrentJumpTime += delta_time; //�o�ߎ��Ԃ��X�V (�����ɂ� deltaTime �ł͂Ȃ��t���[����)


    //�d�͂̉e�����󂯂�
    m_vJumpVelocity.y -= m_Gravity * delta_time; //Y�����x����d�͂����� (Y���オ���̏ꍇ)

    //���݂�Y���W�𑬓x�ōX�V
    m_vCurrentAttackPos.y += m_vJumpVelocity.y * delta_time;

    //�n�� (Y=0.0f) �ɓ��B�������ǂ����̔���
    //�v���C���[�� HandleGroundCollision �Ɏ������n����
    if (m_vCurrentAttackPos.y <= 0.0f)
    {
        m_vCurrentAttackPos.y = 0.0f; //�n�ʂɂ߂荞�܂Ȃ��悤�� Y=0.0f �ɃN�����v

        //Y���x���������i���j�܂��̓[���ł���΁A���x�����Z�b�g���Ē��n����
        //�����ɂ̓v���C���[�̂悤�ɏՓ˔���͂��Ȃ����AY���x�����ɂȂ����璅�n�Ƃ݂Ȃ�
        if (m_vJumpVelocity.y <= 0.0f)
        {
            m_vJumpVelocity.y = 0.0f; //Y�����̑��x���[���ɂ���

            //�W�����v�I��
            m_bIsJumping = false;
            //�W�����v�I����̏����i�G�t�F�N�g�Ȃǁj�������ɒǉ�
        }
    }


    //CStaticMeshObject�̓����ʒu���X�V
    //�W�����v�J�n����X, Z���W�͈ێ�
    //D3DXVECTOR3 newBossPos = m_vInitialBossPos;
    //newBossPos.y = m_vCurrentAttackPos.y; 
    //Y���W�̂ݕ����v�Z���ꂽ�l���g��
    SetPosition(m_vCurrentAttackPos); //m_vCurrentAttackPos �͊���X, Z�������ʒu

    CStaticMeshObject::Update(); //���N���X��Update���Ăяo�� (���[���h�s��̍X�V�Ȃ�)
}

void CBossAttackJump::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //�W�����v���ł���΁A�U���I�u�W�F�N�g���g (�������b�V���������) ��`��
    if (m_bIsJumping)
    {
        CStaticMeshObject::Draw(View, Proj, Light, Camera); //���N���X�̕`����Ăяo��
    }
}