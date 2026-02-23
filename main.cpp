#include "Utils.h"

namespace {
const int kSummandForNextIndex = 1;
const int kStartIndexForConsole = 1;
const int kCoincidence = 0;
}  // namespace

int main(int argc, char* argv[]) {
    const char* filename = nullptr;
    for (int i = kStartIndexForConsole; i < argc; ++i) {
        if (std::strcmp(argv[i], "-b") == kCoincidence && i + kSummandForNextIndex < argc) {
            filename = argv[i + kSummandForNextIndex];
            break;
        }
    }
    if (filename == nullptr) {
        filename = "FlatBase.txt";
        std::cout << "Неккоретный ввод, после флага не передано название файла, используется название: " << filename << std::endl;
    }
    App(filename);

    return 0;
}
