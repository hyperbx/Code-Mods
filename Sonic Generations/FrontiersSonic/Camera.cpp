bool isShaking = false;

float shakeAmount   = 1.0f;
float shakeDuration = 1.0f;
float shakeSpeed    = 1.0f;

void CameraShakeUpdate(BlueBlurCommon::CPlayer3DNormalCamera* _this)
{
    if (isShaking)
    {
        if (shakeDuration > 0.0f)
        {
            _this->m_CameraPositionVisual = _this->m_CameraPositionVisual + _this->m_CameraPositionVisual.Random() * shakeAmount;

            shakeDuration -= Player::DeltaTime * shakeSpeed;
        }
        else
        {
            shakeDuration = 0.0f;

            isShaking = false;
        }
    }
}

HOOK(void, __fastcall, NormalCameraCalculate, 0x10EC7E0, BlueBlurCommon::CPlayer3DNormalCamera* _this)
{
    originalNormalCameraCalculate(_this);

    CameraShakeUpdate(_this);
}

void Camera::Shake(float amount, float duration, float speed)
{
    shakeAmount   = amount;
    shakeDuration = duration;
    shakeSpeed    = speed;

    isShaking = true;
}

void Camera::Install()
{
    INSTALL_HOOK(NormalCameraCalculate);
}