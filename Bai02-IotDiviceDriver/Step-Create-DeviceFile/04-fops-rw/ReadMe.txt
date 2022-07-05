    +, Ta muốn đọc dữ liệu của Device file thì phải qua hàm read:
        static ssize_t m_read(struct file *filp, char __user *user_buffer, size_t size, loff_t *offset)
        {
            size_t to_read;

            pr_info("System call read() called...!!!\n");

            /* Check size doesn't exceed our mapped area size */
            to_read = (size > mdev.  - *offset) ? (mdev.size - *offset) : size;

            /* Copy from mapped area to user buffer */
            if (copy_to_user(user_buffer, mdev.kmalloc_ptr + *offset, to_read))
                return -EFAULT;

            *offset += to_read;

            return to_read;
        }

            --> Để đọc được dữ liệu này, ta cần chuyển dữ liệu từ kernel vào user_buffer qua hàm copy_to_user()
            --> Khi dữ liệu đc paste vào user_buffer, thì ta sẽ tự đọc được ở terminal.
        
    +, Ta muốn ghi dữ liệu vào Device file thì phải qua hàm write:
    static ssize_t m_write(struct file *filp, const char __user *user_buffer, size_t size, loff_t *offset)
    {
        size_t to_write;

        pr_info("System call write() called...!!!\n");

        /* Check size doesn't exceed our mapped area size */
        to_write = (size + *offset > NPAGES * PAGE_SIZE) ? (NPAGES * PAGE_SIZE - *offset) : size;

        /* Copy from user buffer to mapped area */
        memset(mdev.kmalloc_ptr, 0, NPAGES * PAGE_SIZE);
        if (copy_from_user(mdev.kmalloc_ptr + *offset, user_buffer, to_write) != 0)
            return -EFAULT;

        pr_info("Data from usr: %s", mdev.kmalloc_ptr);

        *offset += to_write;
        mdev.size = *offset;

        return to_write;
    }

        --> Dữ liệu từ user_buffer phải ghi vào kernel buffer