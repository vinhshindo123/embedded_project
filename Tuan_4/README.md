## **Tóm tắt dự án**
Dự án này là một trò chơi tương tác, thách thức người chơi đoán một số ngẫu nhiên được tạo ra bằng cách sử dụng một biến trở. Trò chơi cung cấp phản hồi theo thời gian thực thông qua đèn LED RGB và còi báo, với các tín hiệu hình ảnh và âm thanh rõ ràng để hướng dẫn người chơi đến câu trả lời đúng. Logic của trò chơi được thiết kế đơn giản và hấp dẫn, mang lại một cách rõ ràng để giành chiến thắng hoặc thử lại.

## **Các tính năng chính**
- Giao diện trực quan: Màn hình LCD hiển thị số đoán hiện tại của người chơi và đưa ra các gợi ý (Lớn hơn/Nhỏ hơn) một cách trực tiếp.
- Phản hồi động: Đèn LED RGB và còi báo cung cấp phản hồi theo thời gian thực dựa trên khoảng cách của người chơi so với số mục tiêu.
- Gợi ý bằng màu sắc: Đèn LED RGB đổi màu để chỉ ra mức độ gần của số đoán:
  + Đỏ: Số đoán còn rất xa.
  + Vàng/Xanh da trời: Số đoán đang đến gần hơn.
  + Xanh lá: Số đoán đã rất gần với số mục tiêu.
- Đầu vào cảm ứng: Nút nhấn cho phép người chơi xác nhận số đoán và quyết định họ thắng hay thua.
- Hiệu ứng thắng/thua: Trò chơi có các hiệu ứng ăn mừng độc đáo khi đoán đúng và phản hồi khác biệt khi đoán sai, làm cho trải nghiệm trở nên hấp dẫn hơn.

## **Cài đặt và sử dụng**
Linh kiện cần thiết:
- 1x Arduino Uno
- 1x Cảm biến biến trở (Potentiometer)
- 1x Màn hình LCD 16x2 với module I2C
- 1x Đèn LED RGB
- 1x Còi báo (Buzzer)
- 1x Nút nhấn (Pushbutton)
- Các dây nối và điện trở

## **Sơ đồ mạch điện**
![z7069429821932_d559a7e00863b4c37af1fa2c313143dd](https://github.com/user-attachments/assets/83ffd383-683c-4f7d-92b6-5de92e747e44)

Bắt đầu trò chơi và xoay biến trở để đoán số bí mật!
## **Kết quả**
https://github.com/user-attachments/assets/1348897a-8d0b-4bd3-b4b1-bec7a197de6b

