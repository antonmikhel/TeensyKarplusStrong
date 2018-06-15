#include <Audio.h>
#include <AudioStream.h>

#define MAX_INT 32767
#define MIN_INT -32768
#define NUM_BLOCKS 128

typedef int16_t int16;

struct OSCMix 
{
    OSCMix() : sine(0.0f), saw(0.0f), tri(0.0f), square(0.0f), noise(0.0f) {}
    OSCMix(float s, float w, float t, float q, float n) :
        sine(s), saw(w), tri(t), square(q), noise(n) {} 
    float sine;
    float saw;
    float tri;
    float square;
    float noise;
};

class KarplusStrongString : public AudioStream
{
public:
    KarplusStrongString();
    KarplusStrongString(int16 freq);

    void            setMix(OSCMix mix){ m_mix = mix; };
    void            pluck(float velocity);
    void            setFreq(int16 freq);
    void            setDecay(float d);
    virtual void    update();

private:
    int8_t          m_state;
    OSCMix          m_mix;
    int16           m_numSamples;
    int16*          m_KSBuffer;
    int16           m_freq;
    float           m_decayFactor = 0.996f;
    int16           m_bufferIndex = 0;

};
