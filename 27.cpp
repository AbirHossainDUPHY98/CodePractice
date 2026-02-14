// Use 'fmt' library to format floating-point numbers with scientific notation and   fixed precision.

// fmt (often called fmtlib) is a modern C++ formatting library that:
//   Replaces printf-style formatting
//   Is safer than printf (type-safe)
//   Is cleaner than std::cout stream chains
//   Is faster than iostreams in most cases
// Real engineering contexts:
//  Numerical computing → printing results with controlled precision
//  Scientific computing → scientific notation output
//  Logging systems → structured logs (spdlog uses fmt)
//  Data pipelines → formatted reports
//  Debugging → readable structured output
//  UI / CLI tools → clean formatting
//  Financial systems → fixed precision decimals
//  ML / analytics → readable metrics

#include <fmt/core.h>
#include <fmt/format.h>

enum class FormatType { Sci, Fixed, General };

std::string format(double x, FormatType t, int p) {
  // x: Variable to be formatted, t: Type declared, p: place after decimal.
    switch(t) {
        case FormatType::Sci:   return fmt::format("{:.{}e}", x, p);
        case FormatType::Fixed: return fmt::format("{:.{}f}", x, p);
        case FormatType::General:return fmt::format("{:.{}g}", x, p);
    }
  return {};
}

int main() {
    double x = 12345.6789;

    // Scientific notation (e)
    //fmt::print("Scientific (precision 2): {:.2e}\n", x);
    fmt::print("Scientific (precision 6): {:.6e}\n", x);

    // Fixed-point notation (f)
    fmt::print("Fixed (precision 2): {:.2f}\n", x);
    fmt::print("Fixed (precision 6): {:.6f}\n", x);

    std::string sci2 = format(x, FormatType::Sci, 2);
    fmt::print("Scientific (precision 2): {}\n", sci2);

    return 0;
}

