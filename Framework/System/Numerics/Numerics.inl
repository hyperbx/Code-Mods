namespace CMF::System::Numerics
{
    inline float ToDegreesF(float in_radians)
    {
        return in_radians * 57.2958f;
    }

    inline float ToRadiansF(float in_degrees)
    {
        return in_degrees * 0.0174533f;
    }

    inline double ToDegrees(double in_radians)
    {
        return in_radians * 57.29578018188477;
    }

    inline double ToRadians(double in_degrees)
    {
        return in_degrees * 0.01745329238474369;
    }
}
