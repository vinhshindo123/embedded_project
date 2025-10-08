# **Hệ thống Quản lý và Kiểm soát Vật thể Thông minh**

## **Giới thiệu chung**
Dự án Hệ thống Quản lý và Kiểm soát Vật thể Thông minh là một giải pháp bảo mật tự động dựa trên nền tảng Arduino, được thiết kế để kiểm soát và xác minh sự hiện diện của các vật thể quan trọng (như dụng cụ, tài liệu, linh kiện...) trong một khu vực lưu trữ cụ thể.
Hệ thống kết hợp công nghệ RFID (Nhận dạng tần số vô tuyến) và cảm biến Siêu âm để không chỉ xác nhận người dùng có quyền lấy/trả vật thể mà còn xác minh hình dạng/kích thước hình học của vật thể đó. Mục tiêu là đảm bảo rằng vật thể đã được trả về đúng vị trí và không bị thay thế bằng vật thể khác.

## **🚀 Công nghệ sử dụng**
- Arduino Uno/Mega: Vi điều khiển trung tâm, xử lý logic hệ thống.
- MFRC522 RFID Reader: Đọc thẻ/tag vật thể để xác minh danh tính.
- Cảm biến Siêu âm (HC-SR04): Đo khoảng cách để xác định hình dạng/kích thước vật thể.
- Cảm biến Hồng ngoại (IR): Phát hiện sự kiện vật thể bị lấy ra khỏi vị trí.
- Màn hình LCD I2C 16x2: Hiển thị trạng thái, thông báo xác minh và lỗi.
- Servo Motor (SG90): Cơ chế khóa/mở cửa hoặc chốt vật thể.
- EEPROM: Lưu trữ vĩnh viễn dữ liệu đăng ký (UID, Tên, Khoảng cách tham chiếu).

## **🛠️ Nguyên lý hoạt động**
Hệ thống hoạt động dựa trên ba trạng thái chính (IDLE, DETECTED, VERIFYING):
1. IDLE (Sẵn sàng): Cửa/khóa mở, hệ thống chờ cảm biến IR bị ngắt (vật thể bị lấy ra).
2. DETECTED (Phát hiện): Cảm biến IR bị ngắt → Hệ thống khóa cửa (Servo đóng). Hệ thống yêu cầu người dùng quẹt thẻ để xác minh quyền truy cập.
3. VERIFYING (Xác minh):
- Bước 1 (Xác minh Danh tính): Người dùng quẹt thẻ RFID. Nếu thẻ hợp lệ, hệ thống chuyển sang xác minh hình dạng.
- Bước 2 (Xác minh Hình dạng): Hệ thống dùng cảm biến siêu âm để đo khoảng cách thực tế (Act) và so sánh với khoảng cách tham chiếu (Exp) đã lưu trữ trong EEPROM.
  - Nếu ∣Act−Exp∣≤Tolerance → Xác minh OK. Mở khóa và reset về IDLE.
  - Nếu không khớp → Shape Mismatch (Lỗi hình dạng). Còi báo động, khóa vẫn đóng, hệ thống quay lại trạng thái DETECTED.

## **Hướng dẫn kết nối**
![z7093695513255_d39b70999fefde1a284959a638235c12](https://github.com/user-attachments/assets/dea8861e-51ae-467b-97bb-01a03b85af24)
 
## **⚙️ Hướng dẫn Cài đặt & Sử dụng Lệnh Serial**
Tất cả các lệnh quản lý vật thể được thực hiện qua Serial Monitor (Tốc độ 9600 baud, chế độ Newline).
1. Xóa và Liệt kê dữ liệu
- DELALL: Xóa toàn bộ dữ liệu vật thể đã đăng ký trong EEPROM.
- LIST: Hiển thị tất cả 5 slot lưu trữ trong EEPROM (bao gồm UID, Tên và Khoảng cách).
2. Đăng ký Vật thể mới (REG)
Lệnh đăng ký yêu cầu 3 tham số: UID (định danh thẻ), Tên và Khoảng cách tham chiếu (tính bằng cm).
Cú pháp: REG <UID>,<Tên vật thể>,<Khoảng cách cm>

## **Kết quả thu được**
https://drive.google.com/file/d/1Xn1fcgyBr4nznJ_4mX_koAHcTDdmWMf_/view?usp=drive_link
https://drive.google.com/file/d/1OKs_5P4EmU3j0m1pvMpO9p_2xdy7wWxV/view?usp=drive_link
