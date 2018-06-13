#include <Audio.h>
#include <AudioStream.h>

#define FS 44100
#define MAX_INT 32767
#define MIN_INT -32768
#define NUM_BLOCKS 128

struct OSCmix 
{
    OSCmix() : sine(0.0f), saw(0.0f), tri(0.0f), square(0.0f), noise(0.0f) {}
    OSCmix(float s, float w, float t, float q, float n) :
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
    KarplusStrongString() : AudioStream(0, NULL) {};
    KarplusStrongString(int freq) : AudioStream(0, NULL), m_freq(freq)
    {
        m_numSamples = FS / freq;
        m_KSBuffer = new int16_t[m_numSamples];
        m_bufferIndex = 0;
    };

    void pluck(float velocity);
    void setFreq(int freq);
    void tick();
    virtual void update();

private:
    void leftShiftBuffer();

    OSCmix          m_mix;
    int16_t         m_numSamples;
    int16_t*        m_KSBuffer;
    bool            m_mode = false;
    int             m_freq;
    float           m_decayFactor = 0.996;
    audio_block_t*  m_audioBlock;

    int16_t         m_bufferIndex = 0;
    int16_t         m_ticks = 0;
};