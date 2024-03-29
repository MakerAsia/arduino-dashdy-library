#ifndef DashdyParam_h
#define DashdyParam_h

#include <string.h>
#include <stdlib.h>

extern char*        dtostrf_internal(double number, signed char width, unsigned char prec, char *s);
extern long long    atoll_internal(const char *s);

class DashdyParam
{
public:
    class iterator
    {
    public:
        iterator(const char* c, const char* l) : ptr(c), limit(l) {}
        static iterator invalid() { return iterator(NULL, NULL); }

        operator const char* () const   { return asStr(); }
        operator    int ()      const   { return asInt(); }
        const char* asStr()     const   { return ptr; }
        const char* asString()  const   { return ptr; }
        int         asInt()     const   { if(!isValid()) return 0; return atoi(ptr); }
        long        asLong()    const   { if(!isValid()) return 0; return atol(ptr); }
        long long   asLongLong()const   { return atoll_internal(ptr); }
        //long long   asLongLong()const   { return atoll(ptr); }
        double      asDouble()  const   { if(!isValid()) return 0; return atof(ptr); }
        float       asFloat()   const   { if(!isValid()) return 0; return atof(ptr); }
        bool        isValid()   const   { return ptr != NULL && ptr < limit; }
        bool        isEmpty()   const   { if(!isValid()) return true; return *ptr == '\0'; }

        bool operator <  (const iterator& it) const { return ptr < it.ptr; }
        bool operator >= (const iterator& it) const { return ptr >= it.ptr; }

        iterator& operator ++() {
            if(isValid()) {
                ptr += strlen(ptr) + 1;
            }
            return *this;
        }
    private:
        const char* ptr;
        const char* limit;
    };

public:
    explicit
    DashdyParam(const void* addr, size_t length)
        : buff((char*)addr), len(length), buff_size(length)
    {}

    explicit
    DashdyParam(void* addr, size_t length, size_t buffsize)
        : buff((char*)addr), len(length), buff_size(buffsize)
    {}

    const char* asStr() const       { return buff; }
    const char* asString() const    { return buff; }
    int         asInt() const       { return atoi(buff); }
    long        asLong() const      { return atol(buff); }
    long long   asLongLong() const  { return atoll_internal(buff); }
    //long long   asLongLong() const  { return atoll(buff); }
    double      asDouble() const    { return atof(buff); }
    float       asFloat() const     { return atof(buff); }
    bool isEmpty() const            { return *buff == '\0'; }

    iterator begin() const { return iterator(buff, buff+len); }
    iterator end() const   { return iterator(buff+len, buff+len); }

    iterator operator[](int index) const;
    iterator operator[](const char* key) const;

    void*  getBuffer() const { return (void*)buff; }
    size_t getLength() const { return len; }

    // Modification
    void add(int value);
    void add(unsigned int value);
    void add(long value);
    void add(unsigned long value);
    void add(long long value);
    void add(unsigned long long value);
    void add(float value);
    void add(double value);
    void add(const char* str);
    void add(const void* b, size_t l);
    void add(const String& str);
    void add(const __FlashStringHelper* str);

    template<typename T, typename... Args>
    void add_multi(T last) {
        add(last);
    }

    template<typename T, typename... Args>
    void add_multi(T head, Args... tail) {
        add(head);
        add_multi(tail...);
    }

    template <typename TV>
    void add_key(const char* key, const TV& val) {
        add(key);
        add(val);
    }

protected:
    char*    buff;
    size_t   len;
    size_t   buff_size;
};


class DashdyParamAllocated : public DashdyParam {
public:
    DashdyParamAllocated(size_t size)
        : DashdyParam(malloc(size), 0, size)
    {}
    ~DashdyParamAllocated() {
        free(buff);
    }
};

inline
DashdyParam::iterator DashdyParam::operator[](int index) const
{
    const iterator e = end();
    for (iterator it = begin(); it < e; ++it) {
        if (!index--) {
            return it;
        }
    }
    return iterator::invalid();
}

inline
DashdyParam::iterator DashdyParam::operator[](const char* key) const
{
    const iterator e = end();
    for (iterator it = begin(); it < e; ++it) {
        if (!strcmp(it.asStr(), key)) {
            return ++it;
        }
        ++it;
        if (it >= e) break;
    }
    return iterator::invalid();
}

inline
void DashdyParam::add(const void* b, size_t l)
{
    if (len + l > buff_size)
        return;
    memcpy(buff+len, b, l);
    len += l;
}

inline
void DashdyParam::add(const char* str)
{
    if (str == NULL) {
        buff[len++] = '\0';
        return;
    }
    add(str, strlen(str)+1);
}

#if defined(ARDUINO) || defined(SPARK) || defined(PARTICLE)
inline
void DashdyParam::add(const String& str)
{
#if defined(ARDUINO_AVR_DIGISPARK) \
    || defined(__ARDUINO_X86__) \
    || defined(__RFduino__)

    size_t len = str.length()+1;
    char buff[len];
    const_cast<String&>(str).toCharArray(buff, len);
    add(buff, len);
#else
    add(str.c_str());
#endif
}

#if defined(BLYNK_HAS_PROGMEM)

inline
void DashdyParam::add(const __FlashStringHelper* ifsh)
{
    PGM_P p = reinterpret_cast<PGM_P>(ifsh);
    size_t l = strlen_P(p) + 1;
    if (len + l > buff_size)
        return;
    memcpy_P(buff+len, p, l);
    len += l;
    buff[len] = '\0';
}

#endif

#endif

#if defined(__AVR__) || defined (ARDUINO_ARCH_ARC32)

    #include <stdlib.h>

    inline
    void DashdyParam::add(int value)
    {
        char str[2 + 8 * sizeof(value)];
        itoa(value, str, 10);
        add(str);
    }

    inline
    void DashdyParam::add(unsigned int value)
    {
        char str[1 + 8 * sizeof(value)];
        utoa(value, str, 10);
        add(str);
    }

    inline
    void DashdyParam::add(long value)
    {
        char str[2 + 8 * sizeof(value)];
        ltoa(value, str, 10);
        add(str);
    }

    inline
    void DashdyParam::add(unsigned long value)
    {
        char str[1 + 8 * sizeof(value)];
        ultoa(value, str, 10);
        add(str);
    }

    inline
    void DashdyParam::add(long long value)  // TODO: this currently adds just a long
    {
        char str[2 + 8 * sizeof(value)];
        ltoa(value, str, 10);
        add(str);
    }

    inline
    void DashdyParam::add(unsigned long long value) // TODO: this currently adds just a long
    {
        char str[1 + 8 * sizeof(value)];
        ultoa(value, str, 10);
        add(str);
    }


    inline
    void DashdyParam::add(float value)
    {
        char str[33];
        dtostrf(value, 5, 3, str);
        add(str);
    }

    inline
    void DashdyParam::add(double value)
    {
        char str[33];
        dtostrf(value, 5, 7, str);
        add(str);
    }

#else

    #include <stdio.h>

    inline
    void DashdyParam::add(int value)
    {
        len += snprintf(buff+len, buff_size-len, "%i", value)+1;
    }

    inline
    void DashdyParam::add(unsigned int value)
    {
        len += snprintf(buff+len, buff_size-len, "%u", value)+1;
    }

    inline
    void DashdyParam::add(long value)
    {
        len += snprintf(buff+len, buff_size-len, "%li", value)+1;
    }

    inline
    void DashdyParam::add(unsigned long value)
    {
        len += snprintf(buff+len, buff_size-len, "%lu", value)+1;
    }

    inline
    void DashdyParam::add(long long value)
    {
        len += snprintf(buff+len, buff_size-len, "%lli", value)+1;
    }

    inline
    void DashdyParam::add(unsigned long long value)
    {
        len += snprintf(buff+len, buff_size-len, "%llu", value)+1;
    }


#if defined(BLYNK_USE_INTERNAL_DTOSTRF)

    inline
    void DashdyParam::add(float value)
    {
        char str[33];
        dtostrf_internal(value, 5, 3, str);
        add(str);
    }

    inline
    void DashdyParam::add(double value)
    {
        char str[33];
        dtostrf_internal(value, 5, 7, str);
        add(str);
    }

#else

    inline
    void DashdyParam::add(float value)
    {
        len += snprintf(buff+len, buff_size-len, "%2.3f", value)+1;
    }

    inline
    void DashdyParam::add(double value)
    {
        len += snprintf(buff+len, buff_size-len, "%2.7f", value)+1;
    }

#endif

#endif


#endif
