# Sử dụng Subsystem trong hệ thống Linux:

> - Linux cung cấp cho ta 2 hệ thống Subsystem để chúng ta làm việc thuận tiện hơn:
>   - GPIO Subsystem: Cung cấp cho chúng ta 1 bộ API gồm 2 phần để chúng ta điều khiển các chân GPIO dễ dàng hơn
>       - interger base:    Ta sẽ điều khiển chân GPIO qua 1 số nguyên
>       - descriptor base:  Ta sử dụng device tree
>   - Pinctrl Subsystem

## I. Giới thiệu về các hàm hay sử dụng trong GPIO integer base:
- gpio_request(31, "led");
  - Sử dụng chân 31 là chân có chức năng GPIO
- gpio_direction_output(31, 0);
  - Gán chân 31 là output và điện áp ra ban đầu có giá trị 0V
- gpio_set_value(31, 1); 
    - Sét output ra của chân 31 có giá trị 3.3V.
- gpio_free(31);
  - Giải phóng chân.

## II. Linux Device Model
- Nhiệm vụ chính là trừu tượng hóa các đối tượng.
- Có thành phần quan trọng là **Sysfs** --> folder /sys/
- Trong bài Device Character ta đã khai báo biến thuộc 1 class.
  - Class đó trong file /sys/class/
  - Ta cũng thấy 1 đối tượng **gpio trong /sys/class/**
- Khi ta viết driver để điều khiển 1 chân, nhưng khi để đk 1 chân thì rất vất vả. Nên linux cung cấp ta class gpio và support cho user space mà ko phải viết lại driver nữa.
  - **Cách làm:**
    - Đầu tiên ta: Export the pin  
      - Giống như gọi gpio_request().
      - VD: **echo 31 > /sys/class/gpio/export **
    - Set Output hoặc input cho pin.
      - echo in > /sys/class/gpio/gpio31/direction
      - echo out > /sys/class/gpio/gpio31/direction
    - Set value cho chân 
      - echo 1 > /sys/class/gpio/gpio31/direction
    - Unexport khi ko sử dụng:
      - echo 31 >  /sys/class/gpio/exprort