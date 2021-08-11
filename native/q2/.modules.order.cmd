cmd_/home/pi/device-drivers/native/q2/modules.order := {   echo /home/pi/device-drivers/native/q2/module.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/q2/modules.order
