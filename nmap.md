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
    --scanflags: 自定义的TCP扫描选项。-scanflags URGACKPSHRSTSYNFIN所有设置，设置对应的位。结合-sA等选项选择TCP扫描类型。确定如何解释响应。默认按照-sS来解释。


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

    1 寻找合适的僵尸主机。
    2 利用nmap进行僵尸扫描。

    确定TCP端口是否打开的一种方法是向端口发送SYN（会话建立）数据包。如果端口打开，目标机器将响应SYN / ACK（会话请求确认）数据包，如果端口关闭，则响应RST（重置）。这是前面讨论的SYN扫描的基础。接收未经请求的SYN / ACK数据包的计算机将使用RST进行响应。未经请求的RST将被忽略。Internet上的每个IP数据包都有一个片段标识号（IP ID）。 由于许多操作系统只是为它们发送的每个数据包递增此数字，因此探测IPID可以告诉攻击者自上次探测以来已发送了多少数据包。
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


# 版本侦测

# 操作系统侦测