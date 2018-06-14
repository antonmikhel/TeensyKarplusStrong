#include "CKarplusStrong.h"

KarplusStrongString::KarplusStrongString() : AudioStream(0, NULL)
{
    m_numSamples = FS / DEFAULT_FREQ;
    m_KSBuffer = new int16[m_numSamples];
    m_bufferIndex = 0;

    m_randRangeMin = MIN_INT / 2;
    m_randRangeMax = MAX_INT / 2;
    m_randRangeSize = m_randRangeMax - m_randRangeMin + 1;    
}

KarplusStrongString::KarplusStrongString(int16 freq) : AudioStream(0, NULL), m_freq(freq)
{
    m_numSamples = FS / freq;
    m_KSBuffer = new int16[m_numSamples];
    m_bufferIndex = 0;

    m_randRangeMin = MIN_INT / 2;
    m_randRangeMax = MAX_INT / 2;
    m_randRangeSize = m_randRangeMax - m_randRangeMin + 1;
}

void KarplusStrongString::setFreq(int16 freq)
{
    m_freq = freq;
    m_numSamples = FS / freq;
    m_bufferIndex = 0;
    m_KSBuffer = new int16[m_numSamples];
}

void KarplusStrongString::update()
{
    m_audioBlock = allocate();
    if (m_audioBlock == NULL) return;

    for (int samplesFilled = 0; samplesFilled < NUM_BLOCKS; ++samplesFilled) 
    {
        int16 samp = 0;
        samp += tick();
        m_audioBlock->data[samplesFilled] = samp;
    }

    transmit(m_audioBlock);
    release(m_audioBlock);
}

void KarplusStrongString::pluck(float velocity)
{
    m_hasBeenPlucked = true;

    float incrementer = 1.0f / float(m_numSamples);

    Serial.print(m_mix.sine); Serial.print(" - "); Serial.print(m_mix.saw); Serial.print(" - "); Serial.print(m_mix.tri); Serial.print(" - "); Serial.print(m_mix.square); Serial.print(" - "); Serial.print(m_mix.noise); Serial.print("\n\n");

    for (int i = 0; i < m_numSamples; ++i) 
    {

        int16 square;
        int16 saw;
        int16 sine;
        int16 noise;
        int16 tri;

        // TRI
        tri = 0;
        // NOISE
        noise = random(MAX_INT) - MAX_INT / 2;
        // SQUARE
        if (i < m_numSamples / 2)
            square = velocity * MIN_INT;
        else
            square = velocity * MAX_INT;
        // SAW
        saw = 2 * MAX_INT * (incrementer * i) - MAX_INT;
        // SINE
        sine = sin(incrementer * i * PI * 2) * MAX_INT;
//        Serial.print("sine[");Serial.print(i);Serial.print("]: "); Serial.println(sine);

        int16 total = 0;

        total += (m_mix.sine * sine) / 5;
        total += (m_mix.saw * saw) / 5;
        total += (m_mix.square * square) / 5;
        total += (m_mix.noise * noise) / 5;
        total += (m_mix.tri * tri) / 5;

        m_KSBuffer[i] = total;
    }
}

void KarplusStrongString::leftShiftBuffer()
{
    if (m_numSamples == 0)
        return;

    int16 first = m_KSBuffer[0];
    for (int i = 0; i < m_numSamples - 1; ++i)
    {
        m_KSBuffer[i] = m_KSBuffer[i + 1];
    }
    m_KSBuffer[m_numSamples - 1] = first;
}

int16 KarplusStrongString::tick()
{
    if (!m_hasBeenPlucked)
        return 0;

    if (m_numSamples < 2)
        return 0;

    int16 first  = m_KSBuffer[0];
    int16 second = m_KSBuffer[1];
    m_KSBuffer[0] = (first + second) * 0.5 * m_decayFactor;

    leftShiftBuffer();
    m_ticks++;

    return m_KSBuffer[0];
}

int16 KarplusStrongString::randInt()
{
    return ((rand() % m_randRangeSize) + m_randRangeMin) * 2;
}

void KarplusStrongString::setDecay(float d)
{
    m_decayFactor = d;
}
