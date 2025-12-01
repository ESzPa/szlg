//
// Hi
//

#include "dumbq.h"
#include "linkedq.h"
#include "realq.h"

int main(int argc, char** argv) {
    // How dumb, anyways:
    dumb_queue<int> dumbq;

    // A real one:
    real_queue<int, 256> realq;

    return 0;
}
