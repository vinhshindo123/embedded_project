# **Tóm tắt dự án**
Dự án này là một trò chơi rèn luyện phản xạ và thời gian, được xây dựng trên nền tảng Arduino. Trò chơi có hai giai đoạn chính: một giai đoạn chờ và một giai đoạn tấn công. Người chơi phải phản ứng thật nhanh bằng cách nhấn nút vào đúng thời điểm để chiến thắng.

# **Cơ chế trò chơi**
- Chờ đợi: Màn hình LCD hiển thị thông báo "Nhan nut de choi" (Nhấn nút để chơi).
- Giai đoạn 1 - Rình rập:
  - Sau khi người chơi nhấn nút, trò chơi bắt đầu giai đoạn chờ ngẫu nhiên, kéo dài từ 5 đến 10 giây.
  - Trong thời gian này, đèn LED đỏ nhấp nháy để mô phỏng "kẻ địch" đang ở gần.
  - Người chơi phải chờ đợi và không được nhấn nút. Nếu nhấn nút trong giai đoạn này, trò chơi kết thúc với thông báo thất bại: "HANH DONG QUA SOM!" (Hành động quá sớm!).
- Giai đoạn 2 - Tấn công:
  - Khi thời gian chờ kết thúc, đèn LED đỏ tắt và động cơ Servo quay 90 độ (mô phỏng "kẻ địch" ngủ gật).
  - Màn hình LCD hiển thị "TAN CONG!" (Tấn công!).
  - Người chơi có một giây để nhấn nút.
  - Nếu nhấn nút thành công, đèn LED xanh sáng lên, màn hình hiển thị "TIEN CONG THANH CONG!" (Tiến công thành công!) và phát ra âm thanh chiến thắng.
  - Nếu người chơi chậm trễ và không nhấn nút trong một giây, trò chơi kết thúc với thông báo thất bại: "KE DICH PHAT HIEN!" (Kẻ địch phát hiện!) và phát ra âm thanh báo động.

# **Các thành phần chính**
- Arduino: Bộ não điều khiển toàn bộ trò chơi.
- Màn hình LCD: Hiển thị hướng dẫn và kết quả trò chơi.
- Nút nhấn: Đầu vào chính của người chơi.
- LED đỏ: Chỉ thị trạng thái "rình rập".
- LED xanh: Chỉ thị trạng thái "tấn công thành công".
- Còi báo: Phát âm thanh chiến thắng hoặc thất bại.
- Servo: Mô phỏng một hành động cơ học sau khi giai đoạn chờ kết thúc.
