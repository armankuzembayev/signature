#include "Signature.h"

using namespace std;

int main(int argc, char *argv[]) {

    try {
        auto config = make_shared<Config>(argc, argv);
        auto reader = make_shared<Reader>(config);
        auto writer = make_shared<Writer>(config);
        auto threadPool = make_unique<ThreadPool>();

        auto signature = make_unique<Signature>(config, reader, writer, move(threadPool));
        signature->threadManager();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "End!" << endl;

    return 0;
}
