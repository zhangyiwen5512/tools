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


### nmap -PR Address

    -PR:-ARP Ping。ARP扫描，--send-ip取消ARP扫描。选项当扫描整个网络的时候自动使用。这种类型的探测比其他的ping方法更快。

    sudo nmap -PR scanme.nmap.org
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 10:29 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.27s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
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

    Nmap done: 1 IP address (1 host up) scanned in 41.36 seconds


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
    1.open：端口是开放的。端口扫描的主要目标。
    2.closed：端口是关闭的。帮助判断主机是活跃的。
    3.filtered：端口被防火墙IDS/IPS屏蔽，无法确定其状态。
    4.unfiltered：端口没有被屏蔽，但是否开放需要进一步确定。
    5.open|filtered：端口是开放的或被屏蔽。打开端口没有响应或数据包被丢弃。UDP，IP协议，FIN，NULL和Xmas扫描产生次结果。
    6.closed|filtered ：端口是关闭的或被屏蔽。它仅用于IP ID空闲扫描

    一次只执行一种端口扫描，除了UDP scan (-sU)和SCTP scan types (-sY, -sZ)将和另一种TCP scan结合

    -p: 1-500指定端口号。-p U(UDP端口):1-5,T(TCP端口):1-5,S(SCTP端口):1-5
    --scanflags: 自定义的TCP扫描选项。-scanflags URGACKPSHRSTSYNFIN所有设置，设置对应的位。结合-sA等选项选择TCP扫描类型。确定如何解释响应。默认按照-sS来解释。-p ftp,http*。
    --exclude-ports: 排除的端口。
    -F: 可能扫描100个端口而不是默认的1000个。根据频率而定。需要nmap-services文件。
    -r: 不打乱端口扫描序列，顺序扫描。
    --port-ratio <ratio><decimal number between 0 and 1>: 根据声明的比例扫描nmap-services文件中的端口。
    --top-ports <n>: 排除-exclude-ports指定的所有端口后，扫描nmap-services文件中找到的<n>最高比率端口。


## -sS/sT/sA/sW/sM:指定使用 TCP SYN/Connect()/ACK/Window/Maimon scans的方式来对目标主机进行扫描。

### nmap -sS Address

    -sS: TCP SYN scan。使用TCP SYN方式扫描端口。该方式发送SYN到目标端口，如果收到SYN/ACK回复，那么可以判断端口是开放的；如果收到RST包，说明该端口是关闭的。如果没有收到回复，那么可以判断该端口被屏蔽了。

    sudo nmap -sS www.baidu.com --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 10:21 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.013s latency).
    Not shown: 439 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap scan report for www.baidu.com (14.215.177.38)
    Host is up (0.016s latency).
    Not shown: 439 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 2 IP addresses (2 hosts up) scanned in 7.13 seconds


### nmap -sT Address 

    -sT: (TCP connect scan）。使用TCP connect方式扫描端口。默认的TCP扫描方式。推荐使用TCP SYN扫描。建立连接，可能被服务器记录而被发现。

    sudo nmap -sT www.baidu.com --resolve-all -p60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 10:39 CST
    Nmap scan report for www.baidu.com (14.215.177.39)
    Host is up (0.016s latency).
    Not shown: 439 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap scan report for www.baidu.com (14.215.177.38)
    Host is up (0.021s latency).
    Not shown: 439 filtered ports
    PORT    STATE SERVICE
    80/tcp  open  http
    443/tcp open  https

    Nmap done: 2 IP addresses (2 hosts up) scanned in 130.09 seconds


### nmap -sU Address

    -sU: UDP扫描。可以和TCP扫描结合。--data, --data-string, --data-length添加发送的内容。
    使用-sV辅助判断。使用--host-timeout跳过慢速主机

    sudo nmap -sU www.baidu.com --resolve-all -p U:60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 11:01 CST
    Nmap scan report for www.baidu.com (180.101.49.11)
    Host is up (0.030s latency).
    All 441 scanned ports on www.baidu.com (180.101.49.11) are open|filtered

    Nmap scan report for www.baidu.com (180.101.49.12)
    Host is up (0.042s latency).
    All 441 scanned ports on www.baidu.com (180.101.49.12) are open|filtered

    Nmap done: 2 IP addresses (2 hosts up) scanned in 6.09 seconds

    sudo nmap -sU scanme.nmap.org --resolve-all -p U:60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 11:02 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.20s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 433 closed ports
    PORT    STATE         SERVICE
    68/udp  open|filtered dhcpc
    123/udp open          ntp
    135/udp open|filtered msrpc
    136/udp open|filtered profile
    137/udp open|filtered netbios-ns
    138/udp open|filtered netbios-dgm
    139/udp open|filtered netbios-ssn
    445/udp open|filtered microsoft-ds

    Nmap done: 1 IP address (1 host up) scanned in 565.20 seconds


### nmap -sY Address

    -sY: SCTP init scan。不建立SCTP连接。相当于TCP SYN扫描。允许在打开，关闭和过滤状态之间进行清晰，可靠的区分。

    sudo nmap -sY scanme.nmap.org --resolve-all -p S:60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 11:16 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.17s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    All 441 scanned ports on scanme.nmap.org (45.33.32.156) are filtered

    Nmap done: 1 IP address (1 host up) scanned in 811.18 seconds


### nmap -sA Address

    -sA: TCP ACK scan。不能确定open(开放的)或者 open|filtered(开放或者过滤的))端口。 它用于发现防火墙规则，确定它们是有状态的还是无状态的，哪些端口是被过滤的。当扫描未被过滤的系统时， open(开放的)和closed(关闭的) 端口都会返回RST报文。Nmap把它们标记为 unfiltered(未被过滤的)。

    sudo nmap -sA scanme.nmap.org --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 15:13 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.16s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    All 441 scanned ports on scanme.nmap.org (45.33.32.156) are filtered

    Nmap done: 1 IP address (1 host up) scanned in 76.05 seconds


### nmap -sW Address

    -sW: TCP Window scan。根据TCP窗口值是正数还是0，分别把端口标记为open或者 closed。依赖于Internet上少数系统的实现细节。不响应的端口或者发送特定的ICMP错误消息，标记为 filtered(被过滤的)。

    udo nmap -sW scanme.nmap.org --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 15:16 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.16s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    All 441 scanned ports on scanme.nmap.org (45.33.32.156) are filtered

    Nmap done: 1 IP address (1 host up) scanned in 72.11 seconds


### nmap -sM Address

    -sM: TCP Maimon scan。设置FIN/ACK位。当端口打开时丢弃此报文，关闭时返回RST。

    sudo nmap -sM scanme.nmap.org --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 15:51 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.17s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    All 441 scanned ports on scanme.nmap.org (45.33.32.156) are open|filtered

    Nmap done: 1 IP address (1 host up) scanned in 80.33 seconds


## -sN; -sF; -sX (TCP NULL, FIN, and Xmas scans) 

    当端口关闭时，任何不包含SYN，RST，或者ACK位的报文会导致 一个RST返回。而当端口开放时，应该没有任何响应，记为open|filtered。ICMP unreachable时为filtered。


### nmap -sN Address

    -sN: NULL扫描，不设置任何标志位(tcp标志头是0)。

    sudo nmap -sN scanme.nmap.org --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 11:40 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.20s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    All 441 scanned ports on scanme.nmap.org (45.33.32.156) are open|filtered

    Nmap done: 1 IP address (1 host up) scanned in 10.91 seconds


### nmap -sF Address

    -sF: FIN扫描。只设置TCP FIN。

    sudo nmap -sF www.sina.com --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 14:54 CST
    Nmap scan report for www.sina.com (222.76.214.26)
    Host is up (0.026s latency).
    All 441 scanned ports on www.sina.com (222.76.214.26) are open|filtered

    Nmap done: 1 IP address (1 host up) scanned in 20.93 seconds


### nmap -sX Address

    -sX: Xmas扫描。设置FIN，PSH，URG和标志。

    sudo nmap -sX www.sina.com --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 14:55 CST
    Nmap scan report for www.sina.com (183.2.200.242)
    Host is up (0.019s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    All 441 scanned ports on www.sina.com (183.2.200.242) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.238)
    Host is up (0.012s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.238: 238.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.238) are open|filtered

    Nmap scan report for www.sina.com (119.147.70.216)
    Host is up (0.022s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    All 441 scanned ports on www.sina.com (119.147.70.216) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.239)
    Host is up (0.011s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.239: 239.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.239) are open|filtered

    Nmap scan report for www.sina.com (119.147.70.217)
    Host is up (0.013s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    All 441 scanned ports on www.sina.com (119.147.70.217) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.240)
    Host is up (0.011s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.240: 240.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.240) are open|filtered

    Nmap scan report for www.sina.com (119.147.70.218)
    Host is up (0.013s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    All 441 scanned ports on www.sina.com (119.147.70.218) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.241)
    Host is up (0.011s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.241: 241.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.241) are open|filtered

    Nmap scan report for www.sina.com (119.147.70.219)
    Host is up (0.012s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    All 441 scanned ports on www.sina.com (119.147.70.219) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.242)
    Host is up (0.0073s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.242: 242.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.242) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.243)
    Host is up (0.0085s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.243: 243.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.243) are open|filtered

    Nmap scan report for www.sina.com (59.36.226.244)
    Host is up (0.0065s latency).
    Other addresses for www.sina.com (not scanned): 240e:83:201:4a00::3fa 240e:83:201:4a00::3fb
    rDNS record for 59.36.226.244: 244.226.36.59.broad.jm.gd.dynamic.163data.com.cn
    All 441 scanned ports on www.sina.com (59.36.226.244) are open|filtered

    Nmap done: 12 IP addresses (12 hosts up) scanned in 28.92 seconds


### nmap -sZ Address

    -sZ (SCTP COOKIE ECHO scan)。SCTP在开放端口上静默丢弃包含COOKIE ECHO块，如果端口关闭则发送ABORT。不能区分打开和过滤的端口。扫描不像INIT扫描那么明显。

    sudo nmap -sZ scanme.nmap.org --resolve-all -p 60-500
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 15:55 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.18s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    All 441 scanned ports on scanme.nmap.org (45.33.32.156) are open|filtered

    Nmap done: 1 IP address (1 host up) scanned in 83.77 seconds


### nmap -sI Address

    -sI: <zombie host>[:<probeport>] (空闲扫描)。真正的盲目扫描。数据包不是从自己IP中发出，使用指定的僵尸主机。默认使用80端口。
    

    确定TCP端口是否打开的一种方法是向端口发送SYN（会话建立）数据包。如果端口打开，目标机器将响应SYN / ACK（会话请求确认）数据包，如果端口关闭，则响应RST（重置）。这是前面讨论的SYN扫描的基础。接收未经请求的SYN / ACK数据包的计算机将使用RST进行响应。未经请求的RST将被忽略。Internet上的每个IP数据包都有一个片段标识号（IP ID）。 由于许多操作系统只是为它们发送的每个数据包递增此数字，因此探测IPID可以告诉攻击者自上次探测以来已发送了多少数据包。
    Idle scanning映射出一种信任关系。绕过一些过滤机制和路由器。
    1 探测僵尸的IP ID并记录下来。
    2 伪造来自僵尸的SYN数据包并将其发送到目标上的所需端口。根据端口状态，目标的反应可能会也可能不会导致僵尸的IP ID递增。
    3 再次探测僵尸的IP ID。 然后通过将该新IP ID与步骤1中记录的IP ID进行比较来确定目标端口状态。

    探测打开的端口IP ID增2:
    1 取得僵尸的IP ID。主机向僵尸发送SYN/ACK，僵尸认为这是一个意外的SYN/ACK，发送RST和IP ID。
    2 伪造IP ID发送到目的主机。若端口打开，则会对僵尸进行回应SYN/ACK。僵尸认为这也是一个意外的SYN/ACK，发生一个RST，IP ID增1,。
    3 再次探测僵尸的IP ID。增2,说明端口打开。

    探测关闭的端口IP ID增1:
    1 取得僵尸的IP ID。主机向僵尸发送SYN/ACK，僵尸认为这是一个意外的SYN/ACK，发送RST和IP ID。
    2 伪造IP ID发送到目的主机。若端口关闭，则会对僵尸进行回应RST。僵尸忽略RST，IP ID不变,。
    3 再次探测僵尸的IP ID。增1,说明端口关闭。

    探测被屏蔽的端口IP ID增1:
    1 取得僵尸的IP ID。主机向僵尸发送SYN/ACK，僵尸认为这是一个意外的SYN/ACK，发送RST和IP ID。
    2 伪造IP ID发送到目的主机。僵尸和目的都不回应。
    3 再次探测僵尸的IP ID。增1,说明端口关闭或者被屏蔽。

    ///////////////////////////////////////////////////////////////////////////
    1 寻找合适的僵尸主机。
    僵尸主机因该是空闲的，需要防止无关流量增加IP ID序列。
    在僵尸候选网络上同时使用端口扫描，OS检测和ping扫描。加上 -v选项，OS检测可以确定IP ID的生成方式，如果类型为Incremental或Broken little-endian incremental则是一个好的候选僵尸。操作系统检测和开放端口列表还可以帮助识别可能空闲的系统。
    对一个主机使用ipidseq NSE script。此脚本判断IP ID的生成方式。

    sudo nmap scanme.nmap.org --script=ipidseq.nse -d --resolve-all
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-10 15:02 CST
    PORTS: Using top 1000 ports found open (TCP:1000, UDP:0, SCTP:0)
    --------------- Timing report ---------------
    hostgroups: min 1, max 100000
    rtt-timeouts: init 1000, min 100, max 10000
    max-scan-delay: TCP 1000, UDP 1000, SCTP 1000
    parallelism: min 0, max 0
    max-retries: 10, host-timeout: 0
    min-rate: 0, max-rate: 0
    ---------------------------------------------
    NSE: Using Lua 5.3.
    NSE: Arguments from CLI: 
    NSE: Loaded 1 scripts for scanning.
    NSE: Script Pre-scanning.
    NSE: Starting runlevel 1 (of 1) scan.
    Initiating NSE at 15:02
    Completed NSE at 15:02, 0.00s elapsed
    Initiating Ping Scan at 15:02
    Scanning scanme.nmap.org (45.33.32.156) [4 ports]
    Packet capture filter (device eth0): dst host 10.10.0.121 and (icmp or icmp6 or ((tcp or udp or sctp) and (src host 45.33.32.156)))
    We got a TCP ping packet back from 45.33.32.156 port 443 (trynum = 0)
    Completed Ping Scan at 15:02, 0.22s elapsed (1 total hosts)
    Overall sending rates: 18.25 packets / s, 693.38 bytes / s.
    mass_rdns: Using DNS server 10.10.0.1
    mass_rdns: Using DNS server 240e:f8:600b:5400::1
    Initiating Parallel DNS resolution of 1 host. at 15:02
    mass_rdns: 0.36s 0/1 [#: 2, OK: 0, NX: 0, DR: 0, SF: 0, TR: 1]
    Completed Parallel DNS resolution of 1 host. at 15:02, 0.36s elapsed
    DNS resolution of 1 IPs took 0.36s. Mode: Async [#: 2, OK: 1, NX: 0, DR: 0, SF: 0, TR: 1, CN: 0]
    Initiating SYN Stealth Scan at 15:02
    Scanning scanme.nmap.org (45.33.32.156) [1000 ports]
    Packet capture filter (device eth0): dst host 10.10.0.121 and (icmp or icmp6 or ((tcp or udp or sctp) and (src host 45.33.32.156)))
    Discovered open port 22/tcp on 45.33.32.156
    Discovered open port 80/tcp on 45.33.32.156
    Increased max_successful_tryno for 45.33.32.156 to 1 (packet drop)
    Increased max_successful_tryno for 45.33.32.156 to 2 (packet drop)
    Discovered open port 9929/tcp on 45.33.32.156
    Discovered open port 31337/tcp on 45.33.32.156
    Completed SYN Stealth Scan at 15:03, 26.38s elapsed (1000 total ports)
    Overall sending rates: 42.08 packets / s, 1851.51 bytes / s.
    NSE: Script scanning 45.33.32.156.
    NSE: Starting runlevel 1 (of 1) scan.
    Initiating NSE at 15:03
    NSE: Starting ipidseq against scanme.nmap.org (45.33.32.156).
    NSE: ipidseq against scanme.nmap.org (45.33.32.156) threw an error!
    /usr/bin/../share/nmap/scripts/ipidseq.nse:228: bad argument #2 to 'pack' (string contains zeros)
    stack traceback:
        [C]: in function 'string.pack'
        /usr/bin/../share/nmap/scripts/ipidseq.nse:228: in function </usr/bin/../share/nmap/scripts/ipidseq.nse:205>
        (...tail calls...)

    Completed NSE at 15:03, 0.23s elapsed
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up, received reset ttl 52 (0.18s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Scanned at 2019-09-10 15:02:57 CST for 27s
    Not shown: 991 closed ports
    Reason: 991 resets
    PORT      STATE    SERVICE        REASON
    22/tcp    open     ssh            syn-ack ttl 51
    80/tcp    open     http           syn-ack ttl 52
    135/tcp   filtered msrpc          no-response
    139/tcp   filtered netbios-ssn    no-response
    445/tcp   filtered microsoft-ds   no-response
    593/tcp   filtered http-rpc-epmap no-response
    4444/tcp  filtered krb524         no-response
    9929/tcp  open     nping-echo     syn-ack ttl 52
    31337/tcp open     Elite          syn-ack ttl 51
    Final times for host: srtt: 180034 rttvar: 18274  to: 253130

    NSE: Script Post-scanning.
    NSE: Starting runlevel 1 (of 1) scan.
    Initiating NSE at 15:03
    Completed NSE at 15:03, 0.00s elapsed
    Read from /usr/bin/../share/nmap: nmap-payloads nmap-services.
    Nmap done: 1 IP address (1 host up) scanned in 27.75 seconds
            Raw packets sent: 1115 (49.036KB) | Rcvd: 1042 (41.740KB)



    2 利用nmap进行僵尸扫描。

    ///////////////////////////////////////////////////////////////////////////

### nmap -sO Address

    -sO: IP协议扫描。IP 协议扫描可以让您确定目标机支持哪些IP协议 (TCP，ICMP，IGMP，等等)。从目标主机收到任何协议的任何响应，Nmap就把那个协议标记为open。ICMP协议不可到达 错误(类型 3，代号 2) 导致协议被标记为 closed。其它ICMP不可到达协议(类型 3，代号 1，3，9，10，或者13)导致协议被标记为 filtered (虽然同时他们证明ICMP是 open )。如果重试之后仍没有收到响应，该协议就被标记为open|filtered。

    sudo nmap -sO scanme.nmap.org --resolve-all
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-09 16:32 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.16s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 254 open|filtered protocols
    PROTOCOL STATE SERVICE
    1        open  icmp
    17       open  udp

    Nmap done: 1 IP address (1 host up) scanned in 10.26 seconds


### nmap -b Address

    -b: <ftp relay host> (FTP弹跳扫描)。代理ftp连接允许用户连接到一台FTP服务器，然后要求文件送到一台第三方服务器。导致FTP服务器对其它主机端口扫描。参数格式<username>:<password>@<server>:<port>。<Server>是某个脆弱的FTP服务器的名字或者IP地址也许可以省略<username>:<password>，如果服务器上开放了匿名用户(user:anonymous password:-wwwuser@)。端口号(以及前面的冒号)也可以省略，如果<server>使用默认的FTP端口(21)。但现在大部分已经被fix了。


# 服务和版本检测Service and Version Detection

    试图确定端口对应的服务，应用，版本号，主机名，设备类型，OS类型和其他信息。当RPC服务被发现时，会自动用于确定RPC程序和版本号，即使在防火墙之后。当找到一个在数据库里不存在的协议时nmap提供一个URL上传这个服务的信息。
    --allports: 默认情况下会跳过TCP端口9100。设置后会检测此端口。
    --version-intensity <intensity>: 探测强度，细粒度0-9。级别越高越准确，但时间也越长，默认7.
    --version-light: 即 --version-intensity 2。
    --version-all: 即 --version-intensity 9。
    --version-trace: --packet-trace的子集。打印出调试信息。


### nmap -sV Address
    
    -sV: 开启版本检测。同-sR或者-A

    sudo nmap -A www.baidu.com
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-10 18:50 CST
    Nmap scan report for www.baidu.com (180.101.49.11)
    Host is up (0.043s latency).
    Other addresses for www.baidu.com (not scanned): 180.101.49.12
    Not shown: 998 filtered ports
    PORT    STATE SERVICE  VERSION
    80/tcp  open  http     Apache httpd
    | http-robots.txt: 9 disallowed entries 
    | /baidu /s? /ulink? /link? /home/news/data/ /shifen/ 
    |_/homepage/ /cpro /
    |_http-server-header: BWS/1.1
    |_http-title: \xE7\x99\xBE\xE5\xBA\xA6\xE4\xB8\x80\xE4\xB8\x8B\xEF\xBC\x8C\xE4\xBD\xA0\xE5\xB0\xB1\xE7\x9F\xA5\xE9\x81\x93
    443/tcp open  ssl/http Apache httpd
    | http-robots.txt: 9 disallowed entries 
    | /baidu /s? /ulink? /link? /home/news/data/ /shifen/ 
    |_/homepage/ /cpro /
    |_http-server-header: BWS/1.1
    |_http-title: Site doesn't have a title (text/html).
    |_http-trane-info: Problem with XML parsing of /evox/about
    | ssl-cert: Subject: commonName=baidu.com/organizationName=Beijing Baidu Netcom Science Technology Co., Ltd/stateOrProvinceName=beijing/countryName=CN
    | Subject Alternative Name: DNS:baidu.com, DNS:click.hm.baidu.com, DNS:cm.pos.baidu.com, DNS:log.hm.baidu.com, DNS:update.pan.baidu.com, DNS:wn.pos.baidu.com, DNS:*.91.com, DNS:*.aipage.cn, DNS:*.aipage.com, DNS:*.apollo.auto, DNS:*.baidu.com, DNS:*.baidubce.com, DNS:*.baiducontent.com, DNS:*.baidupcs.com, DNS:*.baidustatic.com, DNS:*.baifae.com, DNS:*.baifubao.com, DNS:*.bce.baidu.com, DNS:*.bcehost.com, DNS:*.bdimg.com, DNS:*.bdstatic.com, DNS:*.bdtjrcv.com, DNS:*.bj.baidubce.com, DNS:*.chuanke.com, DNS:*.dlnel.com, DNS:*.dlnel.org, DNS:*.dueros.baidu.com, DNS:*.eyun.baidu.com, DNS:*.fanyi.baidu.com, DNS:*.gz.baidubce.com, DNS:*.hao123.baidu.com, DNS:*.hao123.com, DNS:*.hao222.com, DNS:*.im.baidu.com, DNS:*.map.baidu.com, DNS:*.mbd.baidu.com, DNS:*.mipcdn.com, DNS:*.news.baidu.com, DNS:*.nuomi.com, DNS:*.safe.baidu.com, DNS:*.smartapps.cn, DNS:*.ssl2.duapps.com, DNS:*.su.baidu.com, DNS:*.trustgo.com, DNS:*.xueshu.baidu.com, DNS:apollo.auto, DNS:baifae.com, DNS:baifubao.com, DNS:dwz.cn, DNS:mct.y.nuomi.com, DNS:www.baidu.cn, DNS:www.baidu.com.cn
    | Not valid before: 2019-05-09T01:22:02
    |_Not valid after:  2020-06-25T05:31:02
    |_ssl-date: 2019-09-10T10:49:09+00:00; -1m38s from scanner time.
    | tls-alpn: 
    |_  http/1.1
    | tls-nextprotoneg: 
    |_  http/1.1
    Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
    OS fingerprint not ideal because: Missing a closed TCP port so results incomplete
    No OS matches for host
    Network Distance: 13 hops

    Host script results:
    |_clock-skew: -1m38s

    TRACEROUTE (using port 443/tcp)
    HOP RTT      ADDRESS
    1   9.50 ms  Gprs_R6900 (10.10.0.1)
    2   9.58 ms  100.64.0.1
    3   9.63 ms  121.8.141.41
    4   15.06 ms 218.19.193.13
    5   40.60 ms 202.97.19.113
    6   36.58 ms 58.213.94.110
    7   ...
    8   36.66 ms 58.213.96.86
    9   ... 12
    13  29.26 ms 180.101.49.11

    OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 28.38 seconds

    sudo nmap -A scanme.nmap.org
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-10 18:51 CST
    Stats: 0:00:00 elapsed; 0 hosts completed (0 up), 0 undergoing Script Pre-Scan
    NSE Timing: About 0.00% done
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.21s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 991 closed ports
    PORT      STATE    SERVICE        VERSION
    22/tcp    open     ssh            OpenSSH 6.6.1p1 Ubuntu 2ubuntu2.13 (Ubuntu Linux; protocol 2.0)
    | ssh-hostkey: 
    |   1024 ac:00:a0:1a:82:ff:cc:55:99:dc:67:2b:34:97:6b:75 (DSA)
    |   2048 20:3d:2d:44:62:2a:b0:5a:9d:b5:b3:05:14:c2:a6:b2 (RSA)
    |   256 96:02:bb:5e:57:54:1c:4e:45:2f:56:4c:4a:24:b2:57 (ECDSA)
    |_  256 33:fa:91:0f:e0:e1:7b:1f:6d:05:a2:b0:f1:54:41:56 (ED25519)
    80/tcp    open     http           Apache httpd 2.4.7 ((Ubuntu))
    |_http-server-header: Apache/2.4.7 (Ubuntu)
    |_http-title: Go ahead and ScanMe!
    135/tcp   filtered msrpc
    139/tcp   filtered netbios-ssn
    445/tcp   filtered microsoft-ds
    593/tcp   filtered http-rpc-epmap
    4444/tcp  filtered krb524
    9929/tcp  open     nping-echo     Nping echo
    31337/tcp open     tcpwrapped
    Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.18 (87%), Linux 2.6.39 (87%), Linux 3.10 - 3.12 (87%), Linux 3.4 (87%), Linux 3.5 (87%), Linux 4.2 (87%), Linux 4.4 (87%), Synology DiskStation Manager 5.1 (87%), WatchGuard Fireware 11.8 (87%)
    No exact OS matches for host (test conditions non-ideal).
    Network Distance: 13 hops
    Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

    TRACEROUTE (using port 53/tcp)
    HOP RTT       ADDRESS
    1   7.68 ms   Gprs_R6900 (10.10.0.1)
    2   14.12 ms  100.64.0.1
    3   ...
    4   14.41 ms  121.8.109.81
    5   ...
    6   24.08 ms  202.97.94.102
    7   363.56 ms 202.97.22.122
    8   371.31 ms 202.97.50.30
    9   371.38 ms 218.30.54.245
    10  371.43 ms be3271.ccr41.lax01.atlas.cogentco.com (154.54.42.101)
    11  371.48 ms be3176.ccr21.sjc01.atlas.cogentco.com (154.54.31.190)
    12  371.54 ms be2095.rcr21.b001848-1.sjc01.atlas.cogentco.com (154.54.3.138)
    13  371.56 ms scanme.nmap.org (45.33.32.156)

    OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 56.31 seconds


# 操作系统侦测OS Detection

    使用TCP / IP堆栈指纹识别进行远程操作系统检测。至少一个打开一个关闭的端口时检查很有效。
    --osscan-limit:跳过不符合的主机 。至少一个打开一个关闭的端口时检查很有效。设置此选项，Nmap甚至不会针对不符合此条件的主机尝试操作系统检测。只有在使用-O或-A请求OS检测时才有意义。
    --osscan-guess; --fuzzy: 打印猜测的OS。当Nmap无法检测到完美的OS匹配时，大胆的猜测近似匹配的对象。
    --max-os-tries: 指定重复次数。当Nmap无法检测到完美的OS匹配时,默认重复5次。条件不好时2次。


### nmap -O Address

    -O: 开启OS检测。同-A。Nmap将一系列TCP和UDP数据包发送到远程主机，并检查响应中的每一位。 在执行TCP ISN采样，TCP选项支持和排序，IP ID采样以及初始窗口大小检查等几十项测试后，Nmap将结果与其超过2,600种已知操作系统指纹的nmap-os-db数据库进行比较并打印出来操作系统详细信息。

    sudo nmap -O scanme.nmap.org
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-10 19:05 CST
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.16s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
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
    Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.18 (87%), Linux 3.5 (87%), Linux 4.2 (87%), Linux 4.4 (87%), Synology DiskStation Manager 5.1 (87%), WatchGuard Fireware 11.8 (87%), Linux 2.6.35 (87%), Linux 3.10 (87%), Linux 2.6.32 or 3.10 (86%)
    No exact OS matches for host (test conditions non-ideal).
    Network Distance: 15 hops

    OS detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 25.40 seconds


 # 脚本Nmap Scripting Engine (NSE)

    --script <filename>|<category>|<directory>|<expression>[,...]: 运行指定的脚本。每个元素首先解释为表达式，然后解释为类别，最后解释为文件或目录名称。all可用于指定Nmap数据库中的每个脚本。+号强制运行。只加载路径下以.nse结尾的文件。可以使用and，或，而不是运算符来构建布尔表达式，从而完成更复杂的脚本选择。可以使用括号更改优先级。
    --script-args <n1>=<v1>,<n2>={<n3>=<v3>},<n4>={<v4>,<v5>}: 提供NSE脚本的参数。脚本名.参数名限定使用的脚本，否则为通用参数。
    --script-args-file <filename>: 从文件加载NSE脚本的参数。命令行上的任何参数都将取代文件中的参数。 
    --script-help <filename>|<category>|<directory>|<expression>|all[,...]: 获得脚本帮助。
    --script-trace: 打印脚本执行的所有传入和传出通信。做和--packet-trace相同的事情。
    --script-updatedb: 更新scripts/script.db。
    -sC: 等同于--script=default。


 # 性能设置Timing and Performance

    --min-hostgroup <numhosts>; --max-hostgroup <numhosts>: 调整平行扫描的组的大小。一次并行扫描一组。
    --min-parallelism <numprobes>; --max-parallelism <numprobes>: 调整探测的平行度。根据网络条件自动在上下限内设置。
    --min-rtt-timeout <time>, --max-rtt-timeout <time>，--initial-rtt-timeout <time>: 设定在超时时间。用于确定在放弃或重新传输探测。根据先前探测的响应时间计算而来。
    --max-retries <numtries>: 设置端口扫描出错后的重传次数。
    --host-timeout <time>: 设置主机的超时时间。跳过超时的主机。
    --script-timeout <time>: 设置脚本执行时间的上限。任何超过该时间的脚本实例都将被终止，并且不会显示任何输出。如果启用了调试（-d），Nmap将报告每个超时。
    --scan-delay <time>; --max-scan-delay <time>: 设置每个探测前的延迟时间。保持一定探测率。
    --min-rate <number>; --max-rate <number>: 直接控制探测的频率。控制发包的速率。影响所有主机的探测。只影响主机发现和端口扫描。
    --defeat-rst-ratelimit: 忽略ICMP RST速率限制。没有等待足够长的时间来进行速率限制的RST响应。
    --defeat-icmp-ratelimit: 提高UDP扫描速度，针对ICMP错误消息的速率限制。
    --nsock-engine epoll|kqueue|poll|select: 强制使用给定的nsock IO多路复用引擎。引擎支持受平台限制。
    -T paranoid|sneaky|polite|normal|aggressive|insane: 细粒度控制，指定希望的积极程度。(0–5)或名称是偏执（0），偷偷摸摸（1），礼貌（2），正常（3），激进（4）和疯狂（5）。前两个是用于IDS逃避。礼貌模式会降低扫描速度，从而减少带宽并降低目标机器资源。普通模式是默认模式，因此-T3不执行任何操作。积极模式通过假设您处于合理快速且可靠的网络上来加快扫描速度。最后，疯狂模式假设您处于一个非常快速的网络或者愿意为速度牺牲一些准确性。可以与细粒度控件结合使用，指定的细粒度控件将优先于该参数的计时模板默认值。建议在扫描合理的现代可靠网络时使用-T4。
    -T4相当于--max-rtt-timeout 1250ms --min-rtt-timeout 100ms --initial-rtt-timeout 500ms --max-retries 6并将最大TCP扫描延迟设置为10毫秒。 
    T5相当于--max-rtt-timeout 300ms --min-rtt-timeout 50ms --initial-rtt-timeout 250ms --max-retries 2 --host-timeout 15m --script-timeout 10m以及将最大TCP扫描延迟设置为5 ms。


 # 防火墙绕过/IDS躲避Firewall/IDS Evasion and Spoofing

    -f ; --mtu: 报文分段，使用指定的MTU。
    -D <decoy1>[,<decoy2>][,ME][,...]: 使用诱饵隐蔽扫描，造成多个主机同时扫描的假象。使用ME选项说明用自己的真实IP作为诱饵的位置，否则随机指定。在版本检测和TCP连接扫描中不起作用。
    -S <IP_Address>: 使用另一个地址进行扫描。
    -e <interface>: 使用指定的接口，收发包。
    --source-port <portnumber>; -g <portnumber>: 源端口哄骗。改变发送的端口号。仅依赖于源端口号就信任数据流是一种常见的错误配置，即允许来自于这些端口的数据进入网络。
    --data <hex string>: 加入自定义负载。二进制数据。
    --data-string <string>: 加入自定义的字符串数据。
    --data-length <number>: 加入随机数据作为负载。而不是使用任何特定于协议的有效负载。可以使扫描稍微不那么显眼。
    --ip-options <S|R [route]|L [route]|T|U ... >; --ip-options <hex string>: 指定IP选项。
    --ttl <value>: 设定IPv4 time-to-live字段。
    --randomize-hosts: 打乱扫描目标主机的顺序。做多16384个。当结合小的timing options时减少引起的注意。
    --spoof-mac <MAC address, prefix, or vendor name>: MAC地址欺骗。字符串“0”，Nmap选择一个完全随机的MAC地址。如果给定的字符品是一个16进制偶数(使用:分隔)，Nmap将使用这个MAC地址。如果是小于12的16进制数字，随机填充剩下的6个字节。如果参数不是0或16进制字符串，通过nmap-mac-prefixes查找厂商的名称(大小写区分)，如果找到匹配，使用厂商的OUI(3字节前缀)，然后随机填充剩余的3个节字。正确的--spoof-mac参数有，Apple，0，01:02:03:04:05:06，deadbeefcafe，0020F2，和Cisco.
    --proxies <Comma-separated list of proxy URLs>: 设置代理，支持http代理和socks4代理。此功能仍处于开发阶段且存在局限性。
    --badsum: 使用无效的checksum。收到的任何响应都可能来自防火墙或IDS，它们无需验证校验和。主机IP堆栈都正确地丢弃了这些数据包。
    --adler32: 使用Adler32算法(已弃用)计算SCTP校验和。为了从旧的传统SCTP实现中获得响应，可能最好使用Adler32。


 # 输出Output

    将连字符作为参数传递给其中一种格式类型。这会导致Nmap停用交互式输出，而是以指定的格式打印结果。所以命令nmap -oX-target只会将XML输出发送到stdout。文件名或连字符之间的空格是必需的，否则会创建新文件。'scan-％T-％D.xml'将使用一个名为scan-144840-121307.xml的XML文件。

    -oN <filespec>: 请求将正常输出定向到给定的文件名。
    -oX <filespec>: 将XML输出写入指定文件。XML输出引用一个XSL样式表，可用于将结果格式化为HTML。
    -oS <filespec>: 脚本小子输出。
    -oG <filespec>: Grep输出(已弃用)。只需要一个简单的grep主机说明，使用通道并通过awk或cut命令打印所需的域。
    -oA <basename>: 为使用方便，利用-oA<basename>选项可将扫描结果以标准格式、XML格式和Grep格式一次性输出。分别存放在 <basename>.nmap，<basename>.xml和 <basename>.gnmap文件中。


## 输出的详细程度和调试选项Verbosity and debugging options
    
    -v<level>: 增加详细级别，使Nmap打印有关正在进行的扫描的更多信息。
    -d<level>: 启用调试，并且可以指定调试等级。-d9设置为九级。这是最高的有效级别
    --reason: 显示每个端口设置为特定状态的原因以及每个主机启动或关闭的原因。通过-d选项打开，或默认出现于XML文件中。
    --stats-every <time>: 定期打印状态消息。
    --packet-trace: 追踪数据的接收和发送。--version-trace若只关心版本检测，--script-trace若只关心脚本追踪。
    --open: 只显示打开或可能打开的端口。
    --iflist: 输出Nmap检测到的接口列表和系统路由，用于调试路由问题或设备描述失误(如Nmap把PPP连接当作以太网对待)。


## 其他输出选项Miscellaneous output options

    --append-output: 在输出文件中追加内容。这对于XML（-oX）扫描数据不起作用。
    --resume <filename>: 如果保留了扫描输出文件，用户可以要求Nmap在执行停止时继续使用正在处理的目标进行扫描。只需指定--resume选项并将输出文件作为参数传递。不允许其他参数，因为Nmap解析输出文件以使用先前指定的相同。只需将Nmap称为nmap --resume <logfilename>即可。Nmap会将新结果附加到上一次执行中指定的数据文件中。可以从以下3种主要输出格式中的任何一种恢复扫描：正常，可涂抹或XML
    --stylesheet <path or URL>: 附带一个名为nmap.xsl的XSL样式表，用于查看或将XML输出转换为HTML。如果要使用其他样式表，请将其指定为--stylesheet的参数。
    --webxml: 即--stylesheet https://nmap.org/svn/docs/nmap.xsl。
    --no-stylesheet: 防止Nmap将任何XSL样式表与其XML输出相关联。


# 其他选项Miscellaneous Options

    -6: 开启IPv6扫描。Ping扫描，端口扫描，版本检测和Nmap脚本引擎都支持IPv6。除了添加-6选项之外，命令语法与通常相同。
    -A: 开启强力模式。启用其他高级和激进选项。目前，这可以实现OS检测（-O），版本扫描（-sV），脚本扫描（-sC）和traceroute（--traceroute）。
    --datadir <directoryname>: Nmap在运行时在名为nmap-service-probes，nmap-services，nmap-protocols，nmap-rpc，nmap-mac-prefixes和nmap-os-db的文件中获取一些特殊数据。使用--datadir选项指定的目录中搜索这些文件。
    --servicedb <services file>: 要求Nmap使用指定的服务文件，而不是Nmap附带的nmap-services数据文件。使用此选项还会导致使用快速扫描（-F）。
    --versiondb <service probes file>: 要求Nmap使用指定的服务探测文件，而不是Nmap附带的nmap-service-probes数据文件。
    --send-eth: 要求Nmap在原始以太网（数据链路）层而不是更高IP（网络）层发送数据包。
    --send-ip: 要求Nmap通过原始IP套接字发送数据包，而不是发送较低级别的以太网帧。
    --privileged: 假定用户具有全部权限。如果请求此类操作但是geteuid不为零，则Nmap将退出。
    --unprivileged: 它告诉Nmap将用户视为缺少网络原始套接字和嗅探权限。 这对于测试，调试或操作系统的原始网络功能以某种方式被破坏非常有用。
    --release-memory: 此选项仅对内存泄漏调试有用。 它导致Nmap在退出之前释放已分配的内存，以便更容易发现实际的内存泄漏。 通常，Nmap会跳过此，因为操作系统会在进程终止时执行此操作。


# 运行时交互Runtime Interaction

    v / V: 升高/降低详细等级
    d / D: 升高/降低调试等级。
    p / P: 开启/关闭packet tracing。
    ?: 帮助。
    其他: 打印状态信息