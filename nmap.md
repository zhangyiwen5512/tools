# 主机发现

## 探测公网IP

    -Pn: 将所有指定的主机视作开启的，跳过主机发现的过程。

### nmap -sn Address
    Ping Scan 只进行主机发现，不进行端口扫描。
    发送四种数据ICMP echo requset, TCP SYN到443端口(HTTPS), TCP SYN到80端口(HTTP),ICMP timestamp request,只要有一个包返回就认为主机开机。

    nmap -sn www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:14 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.020s latency).
    Other addresses for www.baidu.com (not scanned): 14.215.177.38
    Nmap done: 1 IP address (1 host up) scanned in 0.04 seconds

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
    
### nmap - PS Address
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


# -PS/PA/PU/PY[portlist]: 使用TCP SYN/TCP ACK或SCTP INIT/ECHO方式进行发现。


# 端口扫描

# 版本侦测

# 操作系统侦测