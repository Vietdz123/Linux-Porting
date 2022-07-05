    +, Đề bài:  
            +, Viết 1 driver bật tắt Led ở GPIO31
    
+, Giới thiệu về GPIO của BBB:
    +, Gồm 128 chân được chia làm 4 bank (4*32), mỗi Bank gồm 32 chân
        --> ĐƯợc đánh số từ 0->31
            +, gpio bank 0
            +, gpio bank 1
            +, gpio bank 2
            +, gpio bank 3
        --> GPIO31 thuộc bank 0 và tương đương với gpio0_31
        --> GPIO48 thuộc bank 1 và tương đương với gpio1_16

+, Ta có các thanh ghi quan trọng
    1. GPIO_OE: là output enable
        --> Cho phép bật tắt dữ liệu ở 1 chân
        --> GPIO_OE có 32 bit, mỗi bit điện diện cho 1 bit của các chân GPIO
            ---> Nghĩa là nếu ta set bit thứ 5 của thanh ghi GPIO_OE lên 0 thì ta set chân đó là chân OUTPUT
                                set bit thứ 5 của thanh ghi GPIO_OE xuống 1 thì ta set chân đó là chân INPUT
    2. GPIO_SET_DATA:
        --> Set bật dữ liệu
    2. GPIO_CLEAR_DATA:
        --> Set tắt dữ liệu

+, Các hàm quan trọng:
    +, ioremap()
        Ta có để ta có thể làm việc trực tiếp thanh ghi có địa chỉ vật lý thật của BBB, ta cần mapping không gian địa chỉ user space và địa chỉ kernel space
            Và địa chỉ kernel space tự mapping 1 1 với ko gian địa chỉ vật lý
        --> vậy là mỗi khi ta ghi vào địa chỉ kernel space, cũng có nghĩa ta ghi vào ko gian địa chỉ vật lý
        --> Hàm ioremap cho ta map user space với kernel space