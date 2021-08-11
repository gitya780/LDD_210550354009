cmd_/home/pi/device-drivers/native/q3/modules.order := {   echo /home/pi/device-drivers/native/q3/param.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/q3/modules.order
