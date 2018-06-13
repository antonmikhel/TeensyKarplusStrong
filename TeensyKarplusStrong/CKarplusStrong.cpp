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

    for (int samplesFilled = 0; samplesFilled < NUM_BLOCKS; ++samplesFilled) {
        if (m_bufferIndex == m_numSamples)
            m_bufferIndex = 0;
        m_audioBlock->data[samplesFilled] = m_KSBuffer[m_bufferIndex];
        ++m_bufferIndex;

    }

    transmit(m_audioBlock);
    release(m_audioBlock);
}

void KarplusStrongString::pluck(float velocity)
{
    for (int i = 0; i < m_numSamples / 2; ++i)
    {
        m_KSBuffer[i] = velocity * MIN_INT;
    }
    for (int i = m_numSamples / 2; i < m_numSamples; ++i)
    {
        m_KSBuffer[i] = velocity * MAX_INT;
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

void KarplusStrongString::tick()
{
    if (m_numSamples < 2)
        return;

    int16 first  = m_KSBuffer[0];
    int16 second = m_KSBuffer[1];
    m_KSBuffer[0] = (first + second) * 0.5 * m_decayFactor;

    leftShiftBuffer();
    m_ticks++;
}

int16 KarplusStrongString::randInt()
{
    return ((rand() % m_randRangeSize) + m_randRangeMin) * 2;
}