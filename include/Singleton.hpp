#ifndef Singleton_hpp
#define Singleton_hpp

namespace warp
{
    template <class T>
    class Singleton
    {
    protected:
        Singleton() {}
        Singleton(Singleton&) = delete;
        void operator=(Singleton&) = delete;
        ~Singleton() {}
        
    public:
        static T* getInstance()
        {
            static T instance{};
            return &instance;
        }
    };
}

#endif /* Singleton_hpp */
