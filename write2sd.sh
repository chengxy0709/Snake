#!/bin/sh
sudo dd iflag=dsync oflag=dsync if=./BL1/BL1.bin of=/dev/sdb seek=1
sudo dd iflag=dsync oflag=dsync if=./BL2/system/main.bin of=/dev/sdb seek=45
