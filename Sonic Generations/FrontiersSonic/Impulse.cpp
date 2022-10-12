void ProcessVelocityImpulse(Eigen::Vector3f unit, float velocity)
{
    alignas(16) BlueBlurCommon::MsgApplyImpulse message{};
    {
        message.m_position        = BlueBlurCommon::GetPosition();
        message.m_impulse         = BlueBlurCommon::GetRotation() * unit;
        message.m_impulseType     = BlueBlurCommon::ImpulseType::None;
        message.m_outOfControl    = 0.0f;
        message.m_notRelative     = true;
        message.m_snapPosition    = false;
        message.m_pathInterpolate = false;
        message.m_alwaysMinusOne  = -1.0f;

        message.m_impulse *= velocity;
    }

    BlueBlurCommon::ProcessImpulse(message);
}

void Impulse::VelocityY(float velocity)
{
    ProcessVelocityImpulse(Eigen::Vector3f::UnitY(), velocity);
}

void Impulse::VelocityZ(float velocity)
{
    ProcessVelocityImpulse(Eigen::Vector3f::UnitZ(), velocity);
}