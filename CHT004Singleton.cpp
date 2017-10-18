#include <txlib.h>

class Singleton;

class Singleton {
    private:
        Singleton() {}
        Singleton(const Singleton&);
        Singleton& operator=( Singleton& );
    public:
        int a = 0;
        static Singleton& getInstance() {
            static Singleton  instance;
            return instance;
        }
};

int main () {
    while(Singleton::getInstance().a < 20) printf("%d\n", ++Singleton::getInstance().a);
    return 0;
}
