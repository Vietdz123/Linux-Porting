# Tạo Linux Device Model

## I. Các bước tạo 1 đối tượng trong sysfs và thêm các thuộc tính cho đối tượng đấy.
- Thuộc tính là:
  - direction
  - value
  - device
  - edge
  - label
  - active-low
  - subsystem
  - uevent

- Ta có: cứ 1 đối tượng nằm trong sysfs thì được đại diện bởi 1 struct, và struct đó là struct kobject.

> - Starting tạo đối tượng:
  - B1: **struct kobject * kobject_create_and_add(const char * name, struct kobject * parent);**
   - Hàm này tạo ra 1 *struct kboject*, và đăng kí nó vào *sysfs*.
   - VD: struct m_foo_dev {
            struct kobject *kobj_ref;
            // Có thể có thêm các thuộc tính đằng sau....
        } mdev;
        mdev.kobj_ref = kobject_create_and_add("bbb_gpios", NULL);
    - file: bbb_gpios đã được đăng kí(chứ chưa được thêm) vào trong folder sysfs
    - </br>
   - B2: **sysfs_create_file (struct kobject * kobj, const struct attribute * attr);**
     - Hàm này sẽ thêm struct kobject vừa đăng kí vào folder sysfs 
       - Sẽ tạo file bbb_gpios trong folder sysfs.
       - attr: là thuộc tính cho file đó. Đọc vd để hiểu.

> - Giả sử ta có 4 thuộc tính, thì ta cần phải gọi 4 hàm cùng lúc 
>   - Thừa thãi
> - Ta sẽ sử dụng 2 hàm khác để tạo cùng lúc nhiều thuộc tính.
>   - **int sysfs_create_group(struct kobject *kobj, const struct attribute_group *grp)**


