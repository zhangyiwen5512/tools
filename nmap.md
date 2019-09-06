# 主机发现

## 探测公网IP

    -Pn: 将所有指定的主机视作开启的，跳过主机发现的过程。
    -P0: 同-Pn

### nmap -sn Address
    Ping Scan 只进行主机发现，不进行端口扫描。
    发送四种数据ICMP echo requset, TCP SYN到443端口(HTTPS), TCP SYN到80端口(HTTP),ICMP timestamp request,只要有一个包返回就认为主机开机。

    nmap -sn www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:14 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.020s latency).
    Other addresses for www.baidu.com (not scanned): 14.215.177.38
    Nmap done: 1 IP address (1 host up) scanned in 0.04 seconds

## -PE/PP/PM: 使用ICMP echo、 ICMP timestamp、ICMP netmask 请求包发现主机。
### nmap  -PE Address
    -PE 通过向目标发送ICMP Echo数据包来探测目标主机是否存活，倘若目标主机在线，该命令还会探测其开放的端口以及运行的服务！   
    许多主机的防火墙会禁止这些报文

    sudo nmap -PE www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:30 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.017s latency).
    Other addresses for www.baidu.com (not scanned): 14.215.177.38
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 6.95 seconds

### nmap  -PP Address
    -PP ICMP time stamp时间戳扫描
    在大多数防火墙配置不当时可能会得到回复。倘若目标主机在线，该命令还会探测其开放的端口以及运行的服务！   

    sudo nmap -PP www.sina.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:35 CST 
    Nmap scan report for www.sina.com (222.76.214.26)
    Host is up (0.028s latency).
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 10.04 seconds

### nmap  -PM Address
    -PM ICMP netmask地址掩码扫描会
    试图用备选的ICMP等级Ping指定主机，可能要加入-Pn选项
    
    ###################################################################################
    sudo nmap -PM scanme.nmap.org
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:44 CST
    Note: Host seems down. If it is really up, but blocking our ping probes, try -Pn
    Nmap done: 1 IP address (0 hosts up) scanned in 2.14 seconds
    ###################################################################################

    sudo nmap -PM -Pn www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:57 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.023s latency).
    Other addresses for www.baidu.com (not scanned): 14.215.177.38
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 8.31 seconds
    
## -PS/PA/PU/PY[portlist]: 使用TCP SYN/TCP ACK或SCTP INIT/ECHO方式进行发现。
### nmap -PS Address
    -PS用TCP SYN ping发送一个SYN包到目标系统，并监听响应

    nmap -PS www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 10:09 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.061s latency).
    Other addresses for www.baidu.com (not scanned): 14.215.177.38
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 25.66 seconds

    nmap -PS220-655 www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 10:45 CST
    Nmap scan report for www.baidu.com (180.101.49.12)
    Host is up (0.039s latency).
    Other addresses for www.baidu.com (not scanned): 180.101.49.11
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 52.30 seconds

### nmap -PA Address
    -PA 对指定主机进行TCP Ack Ping扫描。只扫描确认（ACK）数据包

    nmap -PA www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 10:48 CST
    Nmap scan report for www.baidu.com (180.101.49.12)
    Host is up (0.062s latency).
    Other addresses for www.baidu.com (not scanned): 180.101.49.11
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 33.51 seconds

### nmap -PU Address
    -PU UDP ping，它发送一个空的(除非指定了--data-length UDP报文到给定的端口.
    可以穿越只过滤TCP的防火墙和过滤器

    sudo nmap -PU0-1000 www.sina.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 11:04 CST
    Nmap scan report for www.sina.com (59.36.226.241)
    Host is up (0.023s latency).
    Other addresses for www.sina.com (not scanned): 240e:ff:e030:200:3::3fe 240e:ff:a024:200:3::3fd 240e:ff:e030:200:3::3fd 240e:ff:a024:200:3::3fe 240e:ff:f000:500:3::3f9 59.36.226.242 59.36.226.243 59.36.226.248 59.36.226.239 14.215.55.226 14.215.55.224 14.215.55.225 14.215.55.231 119.147.70.217 119.147.70.230 119.147.70.220 14.215.55.229 59.36.226.244
    rDNS record for 59.36.226.241: 241.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    Nmap done: 1 IP address (1 host up) scanned in 34.08 seconds

### nmap -PY Address
    -PY指示的Nmap执行一个SCTP INIT Ping。只要收到回复就可认为主机是存活的

    sudo nmap -PY0-1000 www.sina.com
    sudo nmap -PY -Pn scanme.nmap.org
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 11:48 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.21s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 989 closed ports
    PORT      STATE    SERVICE
    22/tcp    open     ssh
    80/tcp    open     http
    135/tcp   filtered msrpc
    139/tcp   filtered netbios-ssn
    306/tcp   filtered unknown
    445/tcp   filtered microsoft-ds
    593/tcp   filtered http-rpc-epmap
    1011/tcp  filtered unknown
    4444/tcp  filtered krb524
    9929/tcp  open     nping-echo
    31337/tcp open     Elite

    Nmap done: 1 IP address (1 host up) scanned in 140.53 seconds





### nmap -PO Address
    -PO 进行一个IP协议ping
    IP协议ping用指定的协议发送一个包给目标，填充指定的协议到IP首部。如果没有指定协议，默认的协议是 1 (ICMP), 2 (IGMP)和4 (IP-in-IP),TCP (protocol 6), UDP (protocol 17) and SCTP (protocol 132),若有对应协议回应或ICMP不可达，则主机活跃

    sudo nmap -PO scanme.nmap.org
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 14:18 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.20s latency).
    Other addresses for scanme.nmap.org (not scanned):  2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 991 closed ports
    PORT      STATE    SERVICE
    22/tcp    open     ssh
    80/tcp    open     http
    135/tcp   filtered msrpc
    139/tcp   filtered netbios-ssn
    445/tcp   filtered microsoft-ds
    593/tcp   filtered http-rpc-epmap
    4444/tcp  filtered krb524
    9929/tcp  open     nping-echo
    31337/tcp open     Elite

    Nmap done: 1 IP address (1 host up) scanned in 55.85 seconds

    sudo nmap -PO132,17,6,4,1,2 translate.google.cn
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 14:45 CST
    Nmap scan report for translate.google.cn (203.208.41.95)
    Host is up (0.100s latency).
    Other addresses for translate.google.cn (not scanned): 2a00:1450:4001:81d::2003 203.208.41.79 203.208.41.88 203.208.41.87
    Not shown: 998 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 1 IP address (1 host up) scanned in 30.68 seconds



# 端口扫描

# 版本侦测

# 操作系统侦测