# File_QR.cpp

You can generate a QR code from a file with this program.

## building

When building, you need to obtain
[QR Code generator](https://github.com/nayuki/QR-Code-generator) v1.8.0。

```sh
cmake -S . -B build
cmake --build build
```

## How to use
```sh
./File_QR <file_path>
```
