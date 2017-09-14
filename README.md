# Zowi-Vbot
Zowi-Vbot, một dòng robot 2 chân đơn giản (bipedal Robot) phục vụ cho việc nhập môn STEM (Sicence-Technology-Engineering-Mathematic) dành cho trẻ em, thuộc dự án STEM EduKit của công ty TNHH Công Nghệ Things Changing (Đà Nẵng - Việt Nam).


## OttoDIY opensource Project 
Zowi-Vbot, là một biến thể được chỉnh sửa phần mềm  và thiết kế lại phần hardware từ dự án robot mã nguồn mở ottoDIY (http://ottodiy.com) và kế thừa một số tính năng, Android APP từ sản phẩm Zowi của công ty BQ (http://zowi.bq.com/en/)
  - Website dự án: http://ottodiy.com

## Zowi-Vbot Design
Zowi-Vbot được stembot.vn thiết kế lại toàn bộ phần khung Hardware sử dụng vật liệu gỗ công nghiệp với công nghệ cắt LaserCNC thay cho bản gốc sử dụng công nghệ in 3D. Người chơi chỉ cần theo hướng dẫn có thể lắp ghép các mảnh gỗ với nhau trong vòng 30-45 phút là sẽ có cho mình một chú robot Zowi-Vbot ngộ nghĩnh với những tính năng không khác gì dự án gốc với giá thành thấp phù hợp với các bạn học sinh sinh viên ở Việt Nam. 
Bộ lắp ghép Zowi-Vbot có thể order tại: http://stembot.vn/products/zowivbot

## Installation - Lắp đặt phần khung
Làm theo hướng dẫn tải tại link: http://stembot.vn/products/zowivbot
Với các sản phẩm Full Combo kit, Arduino Board được stembot.vn nạp sẵn firmware BluetoothAPP, khi bật nguồn lên tất cả Servo sẽ tự động trở về vị trí gốc sau tiếng còi báo, vì vậy không cần thiết phải nạp chương trình OTTO_ServoHome để cân chỉnh vị trí gốc servo. 

## Programming 
Zowi-Vbot được build để có thể lập trình bằng ngôn ngữ C/C++ Arduino, Scratch Mblock và Graphical Block từ Android App Zowi dành cho các đối tượng mới tiếp cận với lập trình . Phiên bản hiện tại chỉ mới cơ bản ở ngôn ngữ Arduino C/C++ kết hợp với APP Zowi. 

1. Cài đặt Arduino IDE để có thể viết code và nạp chương trình cho các Board tương thích nền tảng Arduino tại đây: https://www.arduino.cc/en/Main/Software (Bỏ qua nếu đã cài đặt Arduino IDE)
2. Tải Driver cho Board Arduino Nano tại đây: http://www.wch.cn/download/CH341SER_EXE.html
3. Download toàn bộ code tại Repo này theo định dạng nén .Zip
4. Add thư viện Arduino thủ công bằng cách : Arduino IDE > vào Sketche/Include Library/Add .ZIP Library , tìm tới đường dẫn chưa file .Zip mới download về. 
  Xem chi tiết hướng dẫn cách cài đặt thư viện tại đây: https://www.arduino.cc/en/Guide/Libraries
5. Khởi động lại Arduino IDE -> Vào File/Examples nếu thấy thư mục ZowiVbot" xuất hiện thì cài đặt thành công, Nạp các chương trình Example để khám phá các khả năng của ZowiVbot Robot. 
## UserGuide - Hướng dẫn sử dụng
  *  Để sử dụng với Android Phone qua Bluetooth, mở Arduino IDE và nạp chương trình Examples/ZowiVbot/Vbot_BT_ZowiApp.ino (Đây là chương trình default với khách hàng mua sản phẩm nguyên kit từ STEMbot.vn)
  Lưu ý: chương trình này cũng có thể tương thích với môi trường Mblock Programming qua Bluetooth tuy nhiên hiện tại việc thử nghiệm Scratch với Bluetooth vẫn chưa hoàn tất, chúng tôi sẽ cung cấp bản cập nhật ngay khi hoàn thành.  
  *  Để lập trình bằng ngôn ngữ Scratch trong môi trường Mblock thông qua cáp USBSerial, cần nạp chương trình Examples/ZowiVbot/Vbot_Mblock_inScratchMode.ino
  *  Để tiến hành config cho module Bluetooth HC 06 có thể tương thích với Zowi App, cần nạp chương trình Examples/ZowiVbot/HC06_BT_config.ino và bật Serial Monitor để quan sát quá trình. 
  *  Để test chương trình Demo tránh vật cản sử dụng cảm biến siêu âm SRF04, nạp chương trình: Examples/ZowiVbot/Vbot_avoid.ino  
  *  Để chạy các Demo về nhảy một số bài nhạc của Michael Jackson, sử dụng các chương trình: Examples/ZowiVbot/Dance/.....

    
  


Thư viện ZowiVbot được stembot.vn sửa đổi , tối giản và sắp xếp lại các files so với dự án gốc sao cho chỉ cần cài đặt 1 thư viện "ZowiVbot" và khai báo file header <ZowiVbot.h> đầu chương trình là có thể sử dụng toàn bộ các thư viện con bên trong. Phương pháp này hạn chế lỗi biên dịch do thiếu các thư viện bổ sung thường gặp khi download từ dự án gốc. 
