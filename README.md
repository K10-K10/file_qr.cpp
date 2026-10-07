# file_qr

You can generate a QR code from a file with this program. The file is read in
binary mode, so line breaks (`LF`, `CRLF`, and `CR`) are preserved as part of
the QR code data.

## Building

When building, CMake obtains
[QR Code generator](https://github.com/nayuki/QR-Code-generator) v1.8.0.

```sh
cmake -S . -B build
cmake --build build
```

## Usage

```sh
./build/file_qr <file_path>
```

The generated QR code is displayed directly in the terminal using black and
white ANSI backgrounds. The terminal must support ANSI colors.
