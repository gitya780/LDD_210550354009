cmd_/home/pi/device-drivers/native/carr/q2/modules.order := {   echo /home/pi/device-drivers/native/carr/q2/main.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/carr/q2/modules.order
