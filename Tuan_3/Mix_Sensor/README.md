## **Dữ án kết hợp các cảm biến**
## **Tóm tắt dự án**
Dự án Hệ thống Giám sát và Điều khiển Môi trường Tự động sử dụng Arduino để đọc dữ liệu từ nhiều cảm biến khác nhau như nhiệt độ, độ ẩm, ánh sáng, mực nước và âm thanh. Dữ liệu này được hiển thị liên tục trên màn hình LCD, đồng thời được phân tích để kích hoạt các hành động điều khiển tự động (như bật quạt/đèn) và đưa ra cảnh báo bằng còi báo. Đây là một mô hình thu nhỏ lý tưởng cho một Ngôi nhà thông minh hoặc Hệ thống giám sát nông nghiệp.

## **Chức năng điều khiển**
Dự án hoạt động dựa trên các ngưỡng giá trị (thresholds) được lập trình sẵn để tự động phản ứng với môi trường:
1. Điều khiển Nhiệt độ và Thông gió
- Điều kiện kích hoạt: Nếu Nhiệt độ (T) lớn hơn 35∘C.
- Hành động:
+ Bật Động cơ DC (mô phỏng bật quạt).
+ Mở Servo Motor đến góc 90∘ (mô phỏng mở cửa sổ/cửa thông gió).
+ Phát cảnh báo bằng Còi báo trong 2 giây.
+ LCD hiển thị thông báo: Temp > 35C / Bat quat! Mo cua!.
2. Điều khiển Ánh sáng Tự động
- Điều kiện kích hoạt: Nếu giá trị đọc từ Cảm biến LDR (Ánh sáng) nhỏ hơn 300 (Trời tối).
- Hành động:
+ Bật Đèn LED (mô phỏng bật đèn nhà).
+ Phát cảnh báo bằng Còi báo trong 2 giây.
+ LCD hiển thị thông báo: Troi toi bat den.
3. Cảnh báo Nguy cơ (Nước và Âm thanh)
* Cảnh báo Mực nước:
- Điều kiện: Giá trị đọc từ Cảm biến Nước lớn hơn 300 (Mực nước cao hoặc phát hiện rò rỉ).
- Hành động: LCD hiển thị CANH BAO!/Muc nuoc cao! và bật Còi báo 1 giây.
* Cảnh báo Âm thanh:
- Điều kiện: Giá trị đọc từ Cảm biến Âm thanh lớn hơn 190 (Âm thanh quá lớn).
- Hành động: LCD hiển thị CANH BAO!/Am thanh qua lon! và bật Còi báo 1 giây.

## **Cảm biến sử dụng:**
- DTH11 đo cảm biến nhiệt độ, độ ẩm -> khi nhiệt độ lớn hơn 35 độ C thì cảnh báo, mở cửa, bật quạt
- LDR cảm biến ánh sáng -> khi độ sáng nhỏ hơn 300 cảnh báo bật đèn
- Cảm biến nước -> mức nước lơn hơn 300 đưa ra cảnh báo ngập nước
- Cảm biến âm thanh -> khi mức âm thanh vượt quá 190 thì cảnh báo mức âm thanh quá lớn

## **Sơ đồ kết nối**
![mix_sensor](https://github.com/user-attachments/assets/defb3d4d-3e6d-4944-9dde-2dfbd7972e3b)

## Video Kết Quả
<video src="https://github.com/user-attachments/assets/00cbe7d8-4b2d-4f16-ba37-5dd8806f20f7" controls>
    Trình duyệt của bạn không hỗ trợ thẻ video.
</video>
<video src="https://github.com/user-attachments/assets/00cbe7b18b8d55-fa3c-4441-9739-59bb03fdb1ea" controls>
    Trình duyệt của bạn không hỗ trợ thẻ video.
</video>
<video src="https://github.com/user-attachments/assets/b962cf2c-b63b-401a-b383-6c205bbb1a5b" controls>
    Trình duyệt của bạn không hỗ trợ thẻ video.
</video>
<video src="https://github.com/user-attachments/assets/ad9eea21-e066-4924-9b1a-af28e767178b" controls>
    Trình duyệt của bạn không hỗ trợ thẻ video.
</video>
