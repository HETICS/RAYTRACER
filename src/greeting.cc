#include "greeting.h"

std::string greeting(std::string_view name) {
    return "Hello, " + std::string(name) + "!";
}
