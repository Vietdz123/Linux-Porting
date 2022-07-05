+, Để build thông thường thì Makefile chạy
    make all
    hoặc make

+, Để build với toolchain của BBB thì dùng 
     make ARCH=arm

+, Lệnh check bao nhiêu usb đang kết nối với máy
    lsusb

+, Các file trong phần cứng sẽ đại diện bởi 1 file
            --> Dùng lệnh lsblk để kiểm tra các file 
                --> Với usb trong trường hợp này là sda1
    --> Nằm trong file dev
    --> ta sẽ ko thể truy cập vào file dev này mà 
    --> Ta cần mount nó vào 1 file ta tạo sẵn
        VD: 
            mount /dev/sda1 /home/debian/working_space/media/usb/
