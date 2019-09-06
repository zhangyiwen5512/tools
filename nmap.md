# 目标申明Target Specification

    凡是不是参数的命令行选项都被认为是主机目标。
    若没有--resolve-all选项，只有第一个被解析的IP地址被扫描。
    若要扫描多个相邻主机，使用CIDR-style地址：IP或者主机名/<numbits>。/0将会扫描整个internet网络，/32扫描一个主机。IPv6最大值为/128.
    Nmap通过八位位组范围寻址支持灵活寻址：192.168.0-255.1-254和192.168.3-5,7.1。192.158.范围.范围，来避开某些地址。
    目标声明选项：
    -iL: 从文件中读入要扫描的主机。
    -iR: 扫描指定数量的随机主机。0为用不停止。
    --exclude <host1>[,<host2>[,...]]: 指定扫描中要排除的主机。
    --excludefile <exclude_file>: 从文件中指定扫描中要排除的主机。

# 主机发现ping scan

## 探测公网IP

    若没有其他P*发现参数，发送四种数据ICMP echo requset, TCP SYN到443端口(HTTPS), TCP SYN到80端口(HTTP),ICMP timestamp request,只要有一个包返回就认为主机开机。

    -Pn: 将所有指定的主机视作开启的，跳过主机发现的过程。
    -P0: 同-Pn
    -n: 永不对它发现的活动IP地址进行反向域名解析。 既然DNS一般比较慢，这可以让事情更快些。
    -R: 永远对目标IP地址作反向域名解析。 一般只有当发现机器正在运行时才进行这项操作。 
    --dns-servers <serv1[,serv2],...>: 指定DNS服务器。   
    --system-dns: 指定使用系统的DNS服务器,除非Nmap的DNS代码有bug.一般不使用该选项 
    --traceroute: 追踪每个路由节点。追踪路径。
    --resolve-all: 如果主机名目标解析为多个地址，请扫描所有地址。 默认行为是仅扫描第一个已解析的地址。
    --disable-arp-ping： 禁用arp来发现主机

### nmap -sn Address
    Ping Scan 只进行主机发现，不进行端口扫描。
    
    nmap -sn www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 09:14 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.020s latency).
    Other addresses for www.baidu.com (not scanned): 14.215.177.38
    Nmap done: 1 IP address (1 host up) scanned in 0.04 seconds

## -PE/PP/PM: 使用ICMP echo、 ICMP timestamp、ICMP netmask 请求包发现主机。
### nmap  -PE Address
    -PE 通过向目标发送ICMP Echo数据包来探测目标主机是否存活，倘若目标主机在线，该命令还会探测其开放的端口以及运行的服务！许多主机的防火墙会禁止这些报文

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

### nmap -sL Address
    -sL: List Scan 列表扫描，仅将指定的目标的IP列举出来，不进行主机发现。对指定的IP地址执行一个反向DNS查询
    
    sudo nmap -sL www.baidu.com/27
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 15:31 CST
    Nmap scan report for 180.101.49.0
    Nmap scan report for 180.101.49.1
    Nmap scan report for 180.101.49.2
    Nmap scan report for 180.101.49.3
    Nmap scan report for 180.101.49.4
    Nmap scan report for 180.101.49.5
    Nmap scan report for 180.101.49.6
    Nmap scan report for 180.101.49.7
    Nmap scan report for 180.101.49.8
    Nmap scan report for 180.101.49.9
    Nmap scan report for 180.101.49.10
    Nmap scan report for www.baidu.com (180.101.49.11)
    Other addresses for www.baidu.com (not scanned): 180.101.49.12
    Nmap scan report for 180.101.49.12
    Nmap scan report for 180.101.49.13
    Nmap scan report for 180.101.49.14
    Nmap scan report for 180.101.49.15
    Nmap scan report for 180.101.49.16
    Nmap scan report for 180.101.49.17
    Nmap scan report for 180.101.49.18
    Nmap scan report for 180.101.49.19
    Nmap scan report for 180.101.49.20
    Nmap scan report for 180.101.49.21
    Nmap scan report for 180.101.49.22
    Nmap scan report for 180.101.49.23
    Nmap scan report for 180.101.49.24
    Nmap scan report for 180.101.49.25
    Nmap scan report for 180.101.49.26
    Nmap scan report for 180.101.49.27
    Nmap scan report for 180.101.49.28
    Nmap scan report for 180.101.49.29
    Nmap scan report for 180.101.49.30
    Nmap scan report for 180.101.49.31
    Nmap done: 32 IP addresses (0 hosts up) scanned in 0.20 seconds


### sudo nmap -PE --resolve-all www.sina.com --dns-servers 8.8.8.8,114.114.114.114 --traceroute 
### sudo nmap -P* --resolve-all Address --dns-servers <>,<> --traceroute
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-06 16:12 CST
    Stats: 0:02:58 elapsed; 0 hosts completed (14 up), 14 undergoing SYN Stealth Scan
    SYN Stealth Scan Timing: About 64.48% done; ETC: 16:17 (0:01:37 remaining)
    Nmap scan report for www.sina.com (59.36.226.243)
    Host is up (0.030s latency).
    rDNS record for 59.36.226.243: 243.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    1   6.54 ms  10.10.0.1
    2   3.85 ms  100.64.0.1
    3   ... 4
    5   14.67 ms 183.61.220.114
    6   27.35 ms 183.47.228.93
    7   67.26 ms 183.61.88.206
    8   75.42 ms 243.226.36.59.broad.jm.gd.dynamic.163data.com.cn (59.36.226.243)

    Nmap scan report for www.sina.com (14.215.55.225)
    Host is up (0.024s latency).
    Not shown: 997 filtered ports
    PORT     STATE SERVICE
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-2 are the same as for 59.36.226.243
    3   25.04 ms 121.8.141.41
    4   11.02 ms 116.23.46.33
    5   14.57 ms 113.96.5.38
    6   ...
    7   7.17 ms  125.94.53.162
    8   10.86 ms 14.215.55.225

    Nmap scan report for www.sina.com (59.36.226.242)
    Host is up (0.034s latency).
    rDNS record for 59.36.226.242: 242.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 59.36.226.243
    8   13.79 ms 242.226.36.59.broad.jm.gd.dynamic.163data.com.cn (59.36.226.242)

    Nmap scan report for www.sina.com (14.215.55.224)
    Host is up (0.019s latency).
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT     ADDRESS
    -   Hops 1-7 are the same as for 14.215.55.229
    8   7.85 ms 14.215.55.224

    Nmap scan report for www.sina.com (59.36.226.241)
    Host is up (0.032s latency).
    rDNS record for 59.36.226.241: 241.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-3 are the same as for 14.215.55.225
    4   ...
    5   8.47 ms  113.96.255.62
    6   20.07 ms 121.9.100.169
    7   4.64 ms  183.61.88.130
    8   6.19 ms  241.226.36.59.broad.jm.gd.dynamic.163data.com.cn (59.36.226.241)

    Nmap scan report for www.sina.com (14.215.55.231)
    Host is up (0.034s latency).
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT     ADDRESS
    -   Hops 1-7 are the same as for 14.215.55.225
    8   6.47 ms 14.215.55.231

    Nmap scan report for www.sina.com (59.36.226.240)
    Host is up (0.036s latency).
    rDNS record for 59.36.226.240: 240.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 59.36.226.241
    8   74.42 ms 240.226.36.59.broad.jm.gd.dynamic.163data.com.cn (59.36.226.240)

    Nmap scan report for www.sina.com (119.147.70.218)
    Host is up (0.042s latency).
    Not shown: 997 filtered ports
    PORT     STATE SERVICE
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 119.147.70.216
    8   70.61 ms 119.147.70.218

    Nmap scan report for www.sina.com (14.215.55.230)
    Host is up (0.029s latency).
    Not shown: 997 filtered ports
    PORT     STATE SERVICE
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 14.215.55.225
    8   64.44 ms 14.215.55.230

    Nmap scan report for www.sina.com (59.36.226.239)
    Host is up (0.045s latency).
    rDNS record for 59.36.226.239: 239.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 59.36.226.243
    8   72.16 ms 239.226.36.59.broad.jm.gd.dynamic.163data.com.cn (59.36.226.239)

    Nmap scan report for www.sina.com (119.147.70.217)
    Host is up (0.027s latency).
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 119.147.70.216
    8   71.24 ms 119.147.70.217

    Nmap scan report for www.sina.com (14.215.55.229)
    Host is up (0.035s latency).
    Not shown: 997 filtered ports
    PORT     STATE SERVICE
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-2 are the same as for 59.36.226.243
    3   ... 4
    5   19.09 ms 113.96.4.246
    6   14.45 ms 113.96.6.109
    7   8.65 ms  125.94.53.254
    8   67.55 ms 14.215.55.229

    Nmap scan report for www.sina.com (59.36.226.238)
    Host is up (0.045s latency).
    rDNS record for 59.36.226.238: 238.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    Not shown: 996 filtered ports
    PORT     STATE SERVICE
    80/tcp   open  http
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-7 are the same as for 59.36.226.243
    8   67.49 ms 238.226.36.59.broad.jm.gd.dynamic.163data.com.cn (59.36.226.238)

    Nmap scan report for www.sina.com (119.147.70.216)
    Host is up (0.038s latency).
    Not shown: 997 filtered ports
    PORT     STATE SERVICE
    443/tcp  open  https
    843/tcp  open  unknown
    1935/tcp open  rtmp

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    -   Hops 1-2 are the same as for 59.36.226.243
    3   ... 4
    5   18.90 ms 119.147.221.246
    6   12.47 ms 121.14.112.82
    7   5.97 ms  121.14.87.74
    8   64.01 ms 119.147.70.216

    Nmap done: 14 IP addresses (14 hosts up) scanned in 268.19 seconds

# 端口扫描port scan

    用于确定目标主机的TCP/UDP端口的开放情况。默认情况下，Nmap会扫描1000个最有可能开放的TCP端口
    Nmap通过探测将端口划分为6个状态：
    1.open：端口是开放的。
    2.closed：端口是关闭的。
    3.filtered：端口被防火墙IDS/IPS屏蔽，无法确定其状态。
    4.unfiltered：端口没有被屏蔽，但是否开放需要进一步确定。
    5.open|filtered：端口是开放的或被屏蔽。
    6.closed|filtered ：端口是关闭的或被屏蔽



## 

# 版本侦测

# 操作系统侦测