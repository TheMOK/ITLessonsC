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
/*
#include <txLib.h>

int findStr(char arr[], char str[]);

int main() {
    printf("%d", findStr("mememeow", "meow"));
}

int findStr(char arr[], char str[]) {
    int arrLen = strlen(arr), strLen = strlen(str);

    for(int i = 0, j = 0; i < arrLen; i++) {
        if(arr[i] == str[j]) j++;
        else {
            j = 0;
        }
        if(j == strLen) return i - strLen;
    }

    return -1;
}

*/
