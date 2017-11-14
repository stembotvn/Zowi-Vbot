# Zowi-Vbot
Zowi-Vbot, một dòng robot 2 chân đơn giản (bipedal Robot) phục vụ cho việc nhập môn STEM (Sicence-Technology-Engineering-Mathematic) dành cho trẻ em, thuộc dự án STEM EduKit của công ty TNHH Công Nghệ Things Changing (Đà Nẵng - Việt Nam).


## OttoDIY opensource Project 
Zowi-Vbot, là một biến thể được chỉnh sửa phần mềm  và thiết kế lại phần hardware từ dự án robot mã nguồn mở ottoDIY (http://ottodiy.com) và kế thừa một số tính năng, Android APP từ sản phẩm Zowi của công ty BQ (http://zowi.bq.com/en/)
  - Website dự án: http://ottodiy.com 
  Thanks OttoDIY Creators team for sharing wonderful project. 

## Zowi-Vbot Design
Zowi-Vbot được stembot.vn thiết kế lại toàn bộ phần khung Hardware sử dụng vật liệu gỗ công nghiệp với công nghệ cắt LaserCNC thay cho bản gốc sử dụng công nghệ in 3D. Người chơi chỉ cần theo hướng dẫn có thể lắp ghép các mảnh gỗ với nhau trong vòng 30-45 phút là sẽ có cho mình một chú robot Zowi-Vbot ngộ nghĩnh với những tính năng không khác gì dự án gốc với giá thành thấp phù hợp với các bạn học sinh sinh viên ở Việt Nam. 
Bộ lắp ghép Zowi-Vbot có thể order tại: http://stembot.vn/products/zowivbot

## Installation - Lắp đặt phần khung
Làm theo hướng dẫn tải tại link: http://stembot.vn/blogs/learn-do/huong-dan-lap-rap-zowi-vbot
Với các sản phẩm Full Combo kit, Arduino Board được stembot.vn nạp sẵn firmware BluetoothAPP, khi bật nguồn lên tất cả Servo sẽ tự động trở về vị trí cân bằng sau tiếng còi báo.
## Hardware 
ZowiVbot use ZowiControl Board from STEMBOT.VN design with many modifications as Orginal due to supply enough Power for Servos (S3003), Bluetooth HC06 in Software Serial for Upload Firmware without remove HC06, disactive Servo power during Arduino boot process.... 
However if you DIY with Arduino Nano Expansion Board as Original ottodiy, please config (assembly) your Hardware as follow for using this library:

Board mạch điều khiển Robot Zowi được STEMbot thiết kế lại với nhiều sửa đổi so với phiên bản gốc sử dụng Board mở rộng Nano, lý do là để cung cấp đủ công suất cho các động cơ Servo lớn, sử dụng Bluetooth interface ở chế độ SoftwareSerial giúp nạp firmware từ Arduino mà không cần phải tháo module Bluetooth, Vô hiệu hóa nguồn cấp cho Servo cho đến khi Arduino khhởi động xong giúp cho việc khởi động Robot không bị xoay chân về vị trí 0 độ do quá trình khởi động của Servo. 
```
#PIN_Buzzer  A2              // Buzzer Pin    ->  Còi 
#PIN_Trigger        9        //SRF04 Trigger Pin -> Chân Trigger cảm biến siêu âm SRF04
#define PIN_Echo    10       //SRF04 Echo Pin   -> Chân Echo 
#define PIN_NoiseSensor 6    // Sound sensor Pin -> Chân Analog in cho cảm biến âm thanh   
#define PIN_Servo_Enable  A3   //Using to Enable Power for Servo, this can help help all Servos is disactive during boot process. 
#define BT_Rx   8    //Bluetooth Rx Pin
#define BT_Tx   7    //Bluetooth Tx Pin

#define HIP_L   2     //Left HIP Servo Pin D2
#define FOOT_L  3     //Left Foot Servo Pin D3
#define HIP_R   4     //Right HIP Servo Pin D4
#define FOOT_R  5     //Right FOOT Servo Pin D5     
```
## Programming 
Zowi-Vbot được build để có thể lập trình bằng ngôn ngữ C/C++ Arduino, Scratch trong môi trường mBlock và Graphical Block từ Android App Zowi dành cho các đối tượng mới tiếp cận với lập trình .

1. Cài đặt Arduino IDE để có thể viết code và nạp chương trình cho các Board tương thích nền tảng Arduino tại đây: https://www.arduino.cc/en/Main/Software (Bỏ qua nếu đã cài đặt Arduino IDE)
2. Tải Driver cho Board Arduino Nano tại đây: http://www.wch.cn/download/CH341SER_EXE.html
3. Download toàn bộ code tại Repo này theo định dạng nén .Zip
4. Add thư viện Arduino thủ công bằng cách : Arduino IDE > vào Sketche/Include Library/Add .ZIP Library , tìm tới đường dẫn chưa file .Zip mới download về. 
  Xem chi tiết hướng dẫn cách cài đặt thư viện tại đây: https://www.arduino.cc/en/Guide/Libraries
5. Khởi động lại Arduino IDE -> Vào File/Examples nếu thấy thư mục ZowiVbot" xuất hiện thì cài đặt thành công, Nạp các chương trình Example để khám phá các khả năng của ZowiVbot Robot. 
## UserGuide - Hướng dẫn sử dụng
  *  Để sử dụng với Android Phone qua Bluetooth, mở Arduino IDE và nạp chương trình Examples/ZowiVbot/Vbot_BT_ZowiApp.ino (Đây là chương trình default với khách hàng mua sản phẩm nguyên kit từ STEMbot.vn)
  Lưu ý: chương trình này cũng có thể tương thích với môi trường Mblock Programming qua Bluetooth 
  *  Để lập trình bằng ngôn ngữ Scratch trong môi trường Mblock thông qua cáp USBSerial, cần nạp chương trình Examples/ZowiVbot/Vbot_Mblock_inScratchMode.ino
  *  Để tiến hành config cho module Bluetooth HC 06 có thể tương thích với Zowi App, cần nạp chương trình Examples/ZowiVbot/HC06_BT_config.ino và bật Serial Monitor để quan sát quá trình. 
  *  Để test chương trình Demo tránh vật cản sử dụng cảm biến siêu âm SRF04, nạp chương trình: Examples/ZowiVbot/Vbot_avoid.ino  
## Arduino Code: Khởi tạo robot và sử dụng các hàm chính
### Khởi tạo (Initialize Robot)
```
#include <ZowiVbot.h>  // khai báo thư viện cho ZowiVbot
ZowiVbot Vbot;  //tạo một đối tượng từ lớp ZowiVbot, ví dụ tên là Vbot, có thể đặt tên tùy ý
 void setup(){
  //Set the servo pins
  Vbot.init(HIP_L, HIP_R, FOOT_L, FOOT_R, false, PIN_NoiseSensor, PIN_Buzzer,PIN_Trigger, PIN_Echo);  // khởi tạo phần cứng cho robot
  Vbot.home();    // đưa các khớp của robot về vị trí cân bằng, Robot vào trạng thái nghỉ. 
  delay(50);
}
```
### Sử dụng các hàm chính (Some useful functions)
```
Vbot.home(); // trở về trạng thái nghỉ, các khớp về vị trí cân bằng
```
#### Các hàm chuyển động Robot  (moving functions)
```
Vbot.jump(step,Time);//động tác nhảy lên và đáp xuống với tham số step (interger) là số bước, Time: thời gian thực thi mỗi bước
```
```
Vbot.walk(step,Time, Dir);// Động tác đi bộ Dir = FORWARD (tới) hoặc BACKWARD (lui)
```
```
Vbot.turn(step,Time, Dir);// động tác rẽ, Dir: LEFT, RIGHT
```
```
Vbot.bend(step,Time, Dir);// động tác nghiên qua một bên đứng một chân, DIR = LEFT, RIGHT
```
```
Vbot.ShakeLeg(step,Time, Dir);// động tác nghiên một bên đứng một chân và vẫy chân còn lại DIR = LEFT, RIGHT
```
```
Vbot.updown(Step,Time,H) ; // động tác nhún lên xuống với H là biên độ nhún đơn vị là góc quay của bàn chân (độ) (cao hay thấp).
```
```
Vbot.swing(Step,Time,H); //động tác lắc lư, tham số tương tự như trên 
```
```
Vbot.tiptoeSwing(Step,Time,H); //động tác vừa lắc vừa nhún, tham số tương tự như trên
```
```
Vbot.jitter(Step,Time,H); //động tác hoảng loạng, xoay hai bàn chân cúm vào nhau
```
```
Vbot.ascendingTurn(Step,Time,H);  //động tác xoay cúm chân vào nhau và nhún lên 
```

```
Vbot.moonwalker(Step,Time, H, Dir); //động tác đi không trọng lực của Michael Jackson, với DIR = LEFT, RIGHT
```
```
Vbot.crusaito(Step,Time,H,Dir); //động tác vui mừng nhảy cởn lên (DIR = FORWARD,BACKWARD)
```
```
Vbot.flapping(Step,Time,H,Dir); //động tác vỗ cánh bằng chân, DIR = FORWARD,BACKWARD)
```
/////////////////////////////////////////////////
#### Các hàm tương tác với cảm biên  (Sensor interface)
```
float distance = Vbot.getDistance(); //đọc cảm biến khoản cách SRF04 và gán vào biến kiểu float là distance (đơn vị Cm);
```
```
int noise = getNoise(); //đọc cảm biến âm thanh và gán vào biến noise (kiểu int) -> biểu diễn mức âm thanh 
```
```
double batteryLevel = getBatteryLevel(); //đọc mức Pin (%)
```
```
double batteryVoltae = getBatteryVoltage(); //đọc điện áp Pin
```
#### Các hàm về hành vi - thái độ (Gesture functions) 
```
Vbot.sing(songname); // Phát ra tiếng kêu với tham số là songname
```
```
Các định nghĩa cho songname: 
với songname = S_connection, S_disconnection, S_buttonPushed,S_surprise, S_OhOoh, _OhOoh2, Scuddly,
S_sleeping, S_happy, S_superHappy, S_happy_short, S_sad, S_confused, S_fart1, S_fart2, S_fart3
```

```
Vbot.playGesture(gesture); // Thể hiện một hành vi nào đó..tham số là gesture với các macro sau: 

```
```
các định nghĩa cho cho gesture: 
gesture = RobotHappy, RobotSuperHappy, RobotSad, RobotSleeping, RobotFart, RobotConfused,
RobotLove, RobotAngry, RobotFretful, RobotMagic, RobotWave, RobotVictory, RobotFail
```
CHÚC CÁC BẠN THỰC HÀNH VUI VẺ VÀ HỨNG THÚ SÁNG TẠO RA NHỮNG VỞ KỊCH HAY, ĐIỆU NHẢY ĐẸP VỚI ROBOT NÀY.
STEMBOT Development team
