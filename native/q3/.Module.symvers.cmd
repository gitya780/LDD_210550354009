cmd_/home/pi/device-drivers/native/q3/Module.symvers := sed 's/ko$$/o/' /home/pi/device-drivers/native/q3/modules.order | scripts/mod/modpost -m -a   -o /home/pi/device-drivers/native/q3/Module.symvers -e -i Module.symvers   -T -
