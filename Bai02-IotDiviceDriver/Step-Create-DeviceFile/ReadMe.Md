                /**************** Overview Step Tạo Device file ****************\

    struct m_foo_dev {
        dev_t dev_num;
        struct class *m_class;
        struct cdev m_cdev;
    } mdev;

    +, Ta có các chú ý:
        +, struct cdev là một phần tử của struct inode.
        +, struct cdev đại diện cho Character device Driver.        --> cdev đại diện cho Driver, Device file đại diện cho Device.  
            +, struct file_operation là một phần tử của struct cdev.
                --> struct file_operation định nghĩa toàn bộ các hành động của 1 file như: open/read/write/close/mmap/ioctl.
    
    B1. Tạo Device number:
        --> Device number là số đại diện cho Device file (Device file đại diện cho một Device).
        +, Cách phổ biến:   --> Cấp phát động
            alloc_chrdev_region(&mdev.dev_num, 0, 1, "wibu-number");

            --> Hàm hủy tương ứng: unregister_chrdev_region(mdev.dev_num, 1);
    
    B2. Tạo Operation(open/read/write/close/mmap/ioctl) cho Device file.
        static int      __init hello_world_init(void);
        static void     __exit hello_world_exit(void);
        static int      m_open(struct inode *inode, struct file *file);
        static int      m_release(struct inode *inode, struct file *file);
        static ssize_t  m_read(struct file *filp, char __user *user_buf, size_t size,loff_t * offset);
        static ssize_t  m_write(struct file *filp, const char *user_buf, size_t size, loff_t * offset);

        static struct file_operations fops =
        {
            .owner      = THIS_MODULE,
            .read       = m_read,
            .write      = m_write,
            .open       = m_open,
            .release    = m_release,
        };

        --> Biến fops thuộc struct file_operation đã được đăng kí các hành động Open, Read, write, release

        --> Sau đó ta sẽ khởi tạo Character Device(Character Device Đại diện cho Driver) với các Operation thông qua biến fops
                cdev_init(&mdev.m_cdev, &fops);
            Chú ý: m_cdev: là Device number đã tạo ở B1  -->Các hành động của file được gán vào biến Device number.

        --> Sau đó ta cần thêm Character Device này vào hệ thống.
                cdev_add(&mdev.m_cdev, mdev.dev_num, 1);
            --> Số 1 là số lương minor number muốn add.

    B3. Tạo Device FIle qua Device number và các Operation đã tạo bên trên.
        
        B3.1 Tạo class cho Device FIle:
                mdev.m_class = class_create(THIS_MODULE, "m_class");
        B3.2 Tạo Device FIle:
                device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "m_device");