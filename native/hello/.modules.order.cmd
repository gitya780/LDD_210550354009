cmd_/home/pi/device-drivers/native/hello/modules.order := {   echo /home/pi/device-drivers/native/hello/hello.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/hello/modules.order
