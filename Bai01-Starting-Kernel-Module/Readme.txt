        /********* Hello Kernel Module *********\

1. Linux Kernel header:
    +, Là thành phần biên dịch cho module của Kernel
    +, uname -r
        --> Xem phiên bản nhân linux-kerner
    +, Tải linux-header:
        sudo apt install linux-headers-$(uname -r)
    +, Xem vị trí phiên bản linux:
        ls /lib/modules
    +, Kernel như 1 bức tranh, và cần nhiều mảnh ghép để tạo bức tranh đấy
            --> Lệnh ghép: insmode
                +, tương ứng với hàm __init được chạy
                static __int hello_world_init() {
                    printk(KERN_INFOR "hello world");
                } 
            --> Lệnh xóa: rmode
                +, tương ứng với hàm __exit được chạy
                static __int hello_world_static() {
                    printk(KERN_INFOR "exit world");
                } 
    --> Ta cần 2 hàm để đki 2 hàm này
        module_init(hello_world_init);
        module_exit(hello_world_static);
    +, Để build kernel module:
        Makefile
        --> Ta cần insmod hello.ko vào hệ thống để chạy
            insmod hello.ko
        --> Muốn gỡ ra khỏi hệ thống dùng Lệnh

    +, để in log thì dùng lênh:
        +, dmesg | tail

2.  Cross compile:
    +, Vì linux kernel và 1 máy khác có thể có nhân và kiến trúc khác
        --> Khi ta biên dịch từ 1 bên máy kernel sang máy khác VD như máy BBB thì chương trình đó sẽ ko chạy được
                (Ta vẫn có thể gcc trực tiếp trên BBB)
    
        +, Nhưng VD ta có 1 source rất lớn, nếu build trên BBB thì nếu Build được sẽ build rất lâu
            --> Trong dự án ta sẽ build trên 1 máy khỏe, và build làm sao để có thể chạy trên BBB
        
    --> Khái niệm cross compile: build 2 máy khác nhau, khác kiến trúc nhưng máy kia vẫn chạy được
        --> Để cross compile được thì ta cần toolchain của kiến trúc ta muốn cross compile qua. 
    
    +, Ta có trình biên dịch trên beagle bone Là    
            gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf


    
