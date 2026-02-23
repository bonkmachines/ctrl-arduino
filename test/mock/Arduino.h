#ifndef Arduino_h
#define Arduino_h

#include <cstdint>
#include <cstdlib>
#include <cstring>

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

#ifndef INPUT_PULLUP
    #define INPUT_PULLUP 2
#endif

#ifndef INPUT_PULLDOWN
    #define INPUT_PULLDOWN 3
#endif

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

typedef bool boolean;

inline unsigned long& _mock_millis_ref() {
    static unsigned long val = 0;
    return val;
}

inline unsigned long& _mock_micros_ref() {
    static unsigned long val = 0;
    return val;
}

inline unsigned long millis() { return _mock_millis_ref(); }
inline unsigned long micros() { return _mock_micros_ref()++; }

inline void delay(unsigned long ms) {
    _mock_millis_ref() += ms;
    _mock_micros_ref() += ms * 1000;
}

inline void delayMicroseconds(unsigned int us) {
    _mock_micros_ref() += us;
}

static constexpr uint8_t MOCK_PIN_COUNT = 64;

inline int* _mock_digital_pins() {
    static int pins[MOCK_PIN_COUNT] = {};
    return pins;
}

inline int* _mock_analog_pins() {
    static int pins[MOCK_PIN_COUNT] = {};
    return pins;
}

static constexpr uint8_t MOCK_SEQ_MAX = 8;

struct _MockDigitalSequence {
    int values[MOCK_SEQ_MAX] = {};
    uint8_t length = 0;
    uint8_t index = 0;
};

inline _MockDigitalSequence* _mock_digital_sequences() {
    static _MockDigitalSequence seqs[MOCK_PIN_COUNT] = {};
    return seqs;
}

inline void _mock_set_digital_sequence(uint8_t pin, const int* vals, uint8_t len) {
    if (pin >= MOCK_PIN_COUNT || len == 0 || len > MOCK_SEQ_MAX) return;
    auto& seq = _mock_digital_sequences()[pin];
    for (uint8_t i = 0; i < len; ++i) seq.values[i] = vals[i];
    seq.length = len;
    seq.index = 0;
}

inline void _mock_reset_pins() {
    for (uint8_t i = 0; i < MOCK_PIN_COUNT; ++i) {
        _mock_digital_pins()[i] = 0;
        _mock_analog_pins()[i] = 0;
        _mock_digital_sequences()[i].length = 0;
        _mock_digital_sequences()[i].index = 0;
    }
}

inline void pinMode(uint8_t, uint8_t) {}
inline void digitalWrite(uint8_t pin, uint8_t val) {
    if (pin < MOCK_PIN_COUNT) _mock_digital_pins()[pin] = val;
}
inline int digitalRead(uint8_t pin) {
    if (pin >= MOCK_PIN_COUNT) return 0;
    auto& seq = _mock_digital_sequences()[pin];
    if (seq.length > 0) {
        int val = seq.values[seq.index];
        seq.index = (seq.index + 1) % seq.length;
        return val;
    }
    return _mock_digital_pins()[pin];
}
inline int analogRead(uint8_t pin) {
    return (pin < MOCK_PIN_COUNT) ? _mock_analog_pins()[pin] : 0;
}
inline void analogWrite(uint8_t pin, int val) {
    if (pin < MOCK_PIN_COUNT) _mock_analog_pins()[pin] = val;
}

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
    if (in_max == in_min) return out_min;
    return (int32_t)(x - in_min) * (int32_t)(out_max - out_min) / (int32_t)(in_max - in_min) + out_min;
}

class String {
    char* buffer;
    unsigned int len;
public:
    String() : buffer(new char[1]{'\0'}), len(0) {}

    String(const char* cstr) : buffer(nullptr), len(0) {
        if (cstr) {
            len = strlen(cstr);
            buffer = new char[len + 1];
            strcpy(buffer, cstr);
        } else {
            buffer = new char[1]{'\0'};
        }
    }

    String(const String& other) : buffer(new char[other.len + 1]), len(other.len) {
        strcpy(buffer, other.buffer);
    }

    String(String&& other) noexcept : buffer(other.buffer), len(other.len) {
        other.buffer = nullptr;
        other.len = 0;
    }

    ~String() { delete[] buffer; }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] buffer;
            len = other.len;
            buffer = new char[len + 1];
            strcpy(buffer, other.buffer);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] buffer;
            buffer = other.buffer;
            len = other.len;
            other.buffer = nullptr;
            other.len = 0;
        }
        return *this;
    }

    bool operator==(const String& other) const {
        return strcmp(buffer, other.buffer) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    const char* c_str() const { return buffer ? buffer : ""; }
};

class _MockSerial {
public:
    void begin(unsigned long) {}
    void print(const char*) {}
    void println(const char*) {}
    void print(int) {}
    void println(int) {}
    operator bool() const { return true; }
};

inline _MockSerial& Serial_instance() {
    static _MockSerial instance;
    return instance;
}

#define Serial Serial_instance()

#endif
