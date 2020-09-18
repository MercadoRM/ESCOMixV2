ip address add 1.1.1.2/24 dev eth0
ip route add default via 1.1.1.254 dev eth0
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
                     
tce-load -wi gcc.tcz   
tce-load -wi compiletc 
