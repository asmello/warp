// Taken from http://www.ilikebigbits.com/blog/2014/5/6/type-safe-identifiers-in-c

#ifndef Identifier_hpp
#define Identifier_hpp

template<class Tag, class impl, impl default_value>
class Identifier
{
public:
    static Identifier invalid() { return Identifier(); }
    
    // Defaults to Identifier::invalid()
    Identifier() : m_val(default_value) { }
    
    // Explicit constructor:
    explicit Identifier(impl val) : m_val(val) { }
    
    // Explicit conversion to get back the impl:
    explicit operator impl() const { return m_val; }
    
    friend bool operator==(Identifier a, Identifier b) { return a.m_val == b.m_val; }
    friend bool operator!=(Identifier a, Identifier b) { return a.m_val != b.m_val; }
    
private:
    impl m_val;
};

#endif /* Identifier_hpp */
