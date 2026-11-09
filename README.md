# Cài đặt Thuật toán Nhân 2 Đa thức trên Trường Hữu hạn GF(2^4) và GF(2^8)

## 1. Giới thiệu tổng quan
Dự án cài đặt thuật toán nhân hai đa thức trong trường hữu hạn Galois Field $GF(2^m)$ ứng dụng trong lý thuyết mật mã (Crypto).
- **Ngôn ngữ:** C (GCC)

---

## 2. Cơ sở lý thuyết & Thuật toán

### Phép toán trong $GF(2^m)$
1. **Phép cộng / phép trừ:** Được thực hiện bằng phép toán **XOR** (`^`) giữa các hệ số bit.
2. **Phép nhân:** Sử dụng thuật toán nhân **Shift-and-Add** (Russian Peasant Multiplication):
   - Duyệt qua từng bit của đa thức $b$.
   - Nếu bit tương ứng bằng 1, cộng (XOR) $a$ vào kết quả $res$.
   - Dịch trái $a$ 1 bit (tương đương nhân với $x$).
   - Nếu bit cao nhất tràn vượt quá cấp $m$, tiến hành giảm modulo bằng phép XOR với **đa thức tối giản (Irreducible Polynomial)**.

### Thông số trường
- **Trường $GF(2^4)$:**
  - Đa thức tối giản: $P(x) = x^4 + x + 1$ (Bitmask: `0x13`, phần dư rút gọn: `0x03`).
- **Trường $GF(2^8)$ (Chuẩn AES):**
  - Đa thức tối giản: $P(x) = x^8 + x^4 + x^3 + x + 1$ (Bitmask: `0x11B`, phần dư rút gọn: `0x1B`).

---

## 3. Cấu trúc chương trình (`gfmul.c`)
- `gf16_mul(uint8_t a, uint8_t b)`: Hàm thực hiện phép nhân 2 số trong $GF(2^4)$.
- `gf256_mul(uint8_t a, uint8_t b)`: Hàm thực hiện phép nhân 2 số trong $GF(2^8)$.
- `main()`: Kiểm thử tự động danh sách các cặp số mẫu và in kết quả dưới dạng Hexadecimal.

---

## 4. Hướng dẫn biên dịch & Chạy chương trình

Sử dụng trình biên dịch GCC để build dự án:

```bash
# Biên dịch file nguồn
gcc -O2 -Wall -Wextra -o gfmul gfmul.c

# Chạy file thực thi
./gfmul
