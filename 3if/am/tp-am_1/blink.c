unsigned char* p5dir;
unsigned char* p5out;
volatile unsigned long long i;

int main(int argc, char const *argv[]) {
    p5dir = (unsigned char*) 49;
    *p5dir = 2;

    p5out = (unsigned char*) 50;

    while (1) {
        // software delay
        for ( i = 0; i < 20000; i++);

        *p5out=2;

        for ( i = 0; i < 20000; i++);

        *p5out=0;


    }
    return 0;
}
