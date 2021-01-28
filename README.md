# Qt_QRCode

Development by Qt 4.8.6 mingw32(GCC 4.8.2)


Version: V1.0 2021-Jan-27
1. Implement the QR Code generator based on libqrencode @https://github.com/fukuchi/libqrencode
2. Implement 2D code decoder based on QZXing @https://github.com/ftylitak/qzxing/
3. This app can encode QR code, decocde (Aztec/CODABAR/Code39/Code93/EAN-8/ITF/MAXICODE/PDF417/RSS14/RSS_EXPANDED/UPC-A/UPC-E/UPC-EAN/Code128GS1/QR/DataMatrix/EAN-13/Code128)
4. Support drag&drop image into Parse area
5. Support Chinese characters in 2D Code



How to build
1. Run qmake
2. Run build
3. Copy the libqrencode.dll in source dir ./libqrencode to shadow build dir, otherwise when run application it will crash
4. Copy the QZXing2.dll in source dir ./QZXing to shadow build dir, otherwise when run application it will crash