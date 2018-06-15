#include "CKarplusStrong.h"
KarplusStrongString::KarplusStrongString() : AudioStream(0, NULL)
{
    m_state = 0;
    m_bufferIndex = 0;
}

void KarplusStrongString::setFreq(int16 freq)
{
    m_freq = freq;
    m_numSamples = AUDIO_SAMPLE_RATE_EXACT / freq + 0.5;
    m_bufferIndex = 0;
    m_KSBuffer = new int16[m_numSamples];
    m_state = 0;
}

void KarplusStrongString::update()
{
        audio_block_t *block;
        if (m_state == 0) return;

        block = allocate();
        if (!block){
          m_state = 0;
          return;
        }
        
        int16_t prior;
        if (m_bufferIndex > 0){
          prior = m_KSBuffer[m_bufferIndex-1];
        }else{
          prior = m_KSBuffer[m_numSamples-1];
        }

        int16_t *data = block->data;
    for (int i = 0; i< NUM_BLOCKS; ++i) 
    {
               int16_t in = m_KSBuffer[m_bufferIndex];
               int16_t out = (in + prior)/2.0f;
               *data++ = out;
               m_KSBuffer[m_bufferIndex] = out;
               prior = in;
               if (++m_bufferIndex>=m_numSamples) m_bufferIndex=0;

    }

      transmit(block);
      release(block);
}

void KarplusStrongString::pluck(float velocity)
{
    m_state = 0;
    
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

        int16 total = 0;
        
        total += (m_mix.sine * sine) / 5;
        total += (m_mix.saw * saw) / 5;
        total += (m_mix.square * square) / 5;
        total += (m_mix.noise * noise) / 5;
        total += (m_mix.tri * tri) / 5;
        
        m_KSBuffer[i] = total;
    }
    
    Serial.println("\n\n\nFinished Plucking... Update should Begin\n\n\n");
    m_state = 1;
}


void KarplusStrongString::setDecay(float d)
{ m_decayFactor = d; }
