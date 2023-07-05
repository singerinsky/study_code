// 以下是一个简单的使用VFIO的C++代码实现，它演示了如何初始化VFIO设备、映射设备内存和进行MMIO读写操作：

//```c++
#include "../header.h"
#include <fcntl.h>
#include <iostream>
#include <linux/vfio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

TEST(CPUTest, test_001) {
  int fd = open("/dev/vfio/vfio", O_RDWR);
  if (fd < 0) {
    std::cerr << "Failed to open /dev/vfio/vfio" << std::endl;
    return;
  }

  int group_fd = open("/dev/vfio/1", O_RDWR);
  if (group_fd < 0) {
    std::cerr << "Failed to open /dev/vfio/1" << std::endl;
    return;
  }

  if (ioctl(group_fd, VFIO_GROUP_SET_CONTAINER, &fd) < 0) {
    std::cerr << "Failed to set container" << std::endl;
    return;
  }

  if (ioctl(fd, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU) < 0) {
    std::cerr << "Failed to set IOMMU type" << std::endl;
    return;
  }

  if (ioctl(group_fd, VFIO_GROUP_UNSET_CONTAINER, &fd) < 0) {
    std::cerr << "Failed to unset container" << std::endl;
    return;
  }

  int vfio_device_fd;
  if (ioctl(group_fd, VFIO_GROUP_GET_DEVICE_FD, &vfio_device_fd) < 0) {
    std::cerr << "Failed to get device file descriptor" << std::endl;
    return;
  }

  struct vfio_device_info device_info;
  device_info.argsz = sizeof(struct vfio_device_info);

  if (ioctl(vfio_device_fd, VFIO_DEVICE_GET_INFO, &device_info) < 0) {
    std::cerr << "Failed to get device info" << std::endl;
    return;
  }

  // std::cout << "Device type: " << device_info.device_type << std::endl;
  std::cout << "Number of regions: " << device_info.num_regions << std::endl;

  struct vfio_region_info region_info {};
  region_info.argsz = sizeof(struct vfio_region_info);

  for (int i = 0; i < device_info.num_regions; i++) {
    region_info.index = i;

    if (ioctl(vfio_device_fd, VFIO_DEVICE_GET_REGION_INFO, &region_info) < 0) {
      std::cerr << "Failed to get region info" << std::endl;
      return;
    }

    std::cout << "Region " << i << ": " << region_info.size << " bytes"
              << std::endl;

    void *region_ptr = mmap(NULL, region_info.size, PROT_READ | PROT_WRITE,
                            MAP_SHARED, vfio_device_fd, region_info.offset);
    if (region_ptr == MAP_FAILED) {
      std::cerr << "Failed to map region memory" << std::endl;
      return;
    }

    // Perform MMIO read/write operations on the region
    uint32_t value = *(uint32_t *)((uintptr_t)region_ptr + 0x100);
    *(uint32_t *)((uintptr_t)region_ptr + 0x100) = 0x12345678;

    if (munmap(region_ptr, region_info.size) < 0) {
      std::cerr << "Failed to unmap region memory" << std::endl;
      return;
    }
  }

  close(vfio_device_fd);
  close(group_fd);
  close(fd);
}
//```

// 这段代码首先打开VFIO设备和VFIO组设备，然后将VFIO设备添加到VFIO容器中，并设置VFIO设备的IOMMU类型为Type
// 1。接下来获取设备信息和区域信息，并使用mmap映射设备内存，进行MMIO读写操作，最后释放映射的内存，关闭文件描述符。
