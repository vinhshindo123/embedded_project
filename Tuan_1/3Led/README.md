## **Tóm tắt dự án**
Dự án này là một bài thực hành đơn giản về điều khiển đầu ra số (digital output) trên Arduino. Nó sử dụng ba đèn LED, được nối với các chân số 11, 12 và 13, để tạo ra hiệu ứng nhấp nháy tuần tự. Đây là một dự án cơ bản thường được sử dụng để làm quen với các lệnh pinMode(), digitalWrite() và delay() trong lập trình Arduino.

## **Cơ chế hoạt động**
Chương trình hoạt động theo một vòng lặp vô hạn, thực hiện các bước sau một cách liên tục:

**Thiết lập:**
Các chân 11, 12 và 13 được cấu hình là OUTPUT (pinMode()) để có thể gửi tín hiệu điện đến các đèn LED.
Vòng lặp (loop):
- Đèn LED 1 (chân 11) được bật (HIGH), sau đó tạm dừng 1 giây.
- Đèn LED 1 được tắt (LOW), sau đó tạm dừng 1 giây.
- Quá trình tương tự lặp lại cho Đèn LED 2 (chân 12).
- Cuối cùng, quá trình tương tự lặp lại cho Đèn LED 3 (chân 13).
![3led](https://github.com/user-attachments/assets/5e0dd3b7-0b98-4539-bf8a-ab6b1234c48c)

**Kết quả** là ba đèn LED sẽ lần lượt sáng lên và tắt đi theo thứ tự: đèn 1 -> đèn 2 -> đèn 3, và chu trình này sẽ lặp lại không ngừng.
<div style="display: flex; justify-content: center; align-items: center;">
  <video src="https://github.com/user-attachments/assets/87646db2-d78b-44d5-9c73-e666bbec8c44" controls style="width: 80%; max-width: 600px;">
    Trình duyệt của bạn không hỗ trợ thẻ video.
  </video>
</div>
