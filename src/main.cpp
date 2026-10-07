// Copyright 2026 K10-K10

#include <chrono>
#include <csignal>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <vector>

#include "cpp/qrcodegen.hpp"

namespace {

constexpr int kQuietZone = 4;

void PrintUsage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <file>\n";
}

bool ReadFile(const std::string& path, std::vector<std::uint8_t>* contents) {
  std::ifstream input(path, std::ios::binary);
  if (!input) {
    return false;
  }

  contents->assign(std::istreambuf_iterator<char>(input),
                   std::istreambuf_iterator<char>());
  return input.good() || input.eof();
}

void PrintQrCodeTerminal(const qrcodegen::QrCode& qr_code) {
  const int size = qr_code.getSize();
  const int output_size = size + 2 * kQuietZone;
  std::cout << "\x1b[?1049h";
  for (int y = 0; y < output_size; ++y) {
    for (int x = 0; x < output_size; ++x) {
      const int module_x = x - kQuietZone;
      const int module_y = y - kQuietZone;
      const bool dark = module_x >= 0 && module_x < size && module_y >= 0 &&
                        module_y < size &&
                        qr_code.getModule(module_x, module_y);
      std::cout << (dark ? "\033[40m" : "\033[47m") << "  ";
    }
    std::cout << "\033[0m\n";
  }
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

}  // namespace

void signal_handler(int signam) {
  std::cout << "\x1b[?1049l";
  std::exit(0);
}

int main(int argc, char* argv[]) {
  std::signal(SIGINT, signal_handler);
  if (argc != 2) {
    PrintUsage(argv[0]);
    return 2;
  }

  std::vector<std::uint8_t> contents;
  if (!ReadFile(argv[1], &contents)) {
    std::cerr << "Error: cannot read file: " << argv[1] << '\n';
    return 1;
  }

  try {
    const auto qr_code = qrcodegen::QrCode::encodeBinary(
        contents, qrcodegen::QrCode::Ecc::MEDIUM);
    PrintQrCodeTerminal(qr_code);
  } catch (const std::exception& error) {
    std::cerr << "Error: cannot encode file as QR code: " << error.what()
              << '\n';
    return 1;
  }

  return 0;
}
