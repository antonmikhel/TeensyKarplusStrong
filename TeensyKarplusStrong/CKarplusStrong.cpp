#include "CKarplusStrong.h"

void KarplusStrongString::setFreq(int freq)
{
    m_freq = freq;
    m_numSamples = SAMPLE_RATE / freq;
    m_bufferIndex = 0;
    m_KSBuffer = new int16_t[m_numSamples];
}

void KarplusStrongString::pluck(float velocity)
{
    for (int i = 0; i < 64; ++i)
    {
        m_KSBuffer[i] = MIN_INT16;
    }
    for (int i = 64; i < 129; ++i)
    {
        m_KSBuffer[i] = MAX_INT16;
    }
}

void KarplusStrongString::update()
{
    m_audioBlock = allocate();
    if (m_audioBlock == NULL) return;

    //for (int i = 0; i < 64; ++i)
    //    m_audioBlock->data[i] = -32768;
    //
    //for (int i = 64; i < 129; ++i)
    //    m_audioBlock->data[i] = 32768;

    int samplesFilled = 0;
    for (; samplesFilled < DEFAULT_NUM_BLOCKS; ++samplesFilled)
    {
        if (m_bufferIndex == m_numSamples)
            m_bufferIndex = 0;
        m_audioBlock->data[samplesFilled] = m_KSBuffer[m_bufferIndex];
        ++m_bufferIndex;
    }    

    transmit(m_audioBlock);
    release(m_audioBlock);
}