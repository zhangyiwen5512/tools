# 操作系统探测

## nmap -O Address 或 nmap -A Address 

    使用TCP / IP堆栈指纹识别进行远程操作系统检测。至少一个打开一个关闭的端口时检查很有效。
    --osscan-limit:跳过不符合的主机 。至少一个打开一个关闭的端口时检查很有效。设置此选项，Nmap甚至不会针对不符合此条件的主机尝试操作系统检测。只有在使用-O或-A请求OS检测时才有意义。
    --osscan-guess; --fuzzy: 打印猜测的OS。当Nmap无法检测到完美的OS匹配时，大胆的猜测近似匹配的对象。
    --max-os-tries: 指定重复次数。当Nmap无法检测到完美的OS匹配时,默认重复5次。条件不好时2次。


## sudo nmap -O -v scanme.nmap.org
 
    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-17 08:54 CST
    Initiating Ping Scan at 08:54
    Scanning scanme.nmap.org (45.33.32.156) [4 ports]
    Completed Ping Scan at 08:54, 0.20s elapsed (1 total hosts)
    Initiating Parallel DNS resolution of 1 host. at 08:54
    Completed Parallel DNS resolution of 1 host. at 08:54, 0.42s elapsed
    Initiating SYN Stealth Scan at 08:54
    Scanning scanme.nmap.org (45.33.32.156) [1000 ports]
    Discovered open port 22/tcp on 45.33.32.156
    Discovered open port 80/tcp on 45.33.32.156
    Discovered open port 31337/tcp on 45.33.32.156
    Discovered open port 9929/tcp on 45.33.32.156
    Completed SYN Stealth Scan at 08:54, 16.22s elapsed (1000 total ports)
    Initiating OS detection (try #1) against scanme.nmap.org (45.33.32.156)
    Retrying OS detection (try #2) against scanme.nmap.org (45.33.32.156)
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.17s latency).
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
    Aggressive OS guesses: Linux 2.6.18 (87%), Linux 2.6.32 (87%), Linux 2.6.32 or 3.10 (87%), Linux 2.6.39 (87%), Linux 3.10 - 3.12 (87%), Linux 4.4 (87%), WatchGuard Fireware 11.8 (87%), Synology DiskStation Manager 5.1 (87%), Linux 2.6.35 (87%), Linux 4.9 (87%)
    No exact OS matches for host (test conditions non-ideal).
    Uptime guess: 5.145 days (since Thu Sep 12 05:26:25 2019)
    Network Distance: 15 hops
    TCP Sequence Prediction: Difficulty=255 (Good luck!)
    IP ID Sequence Generation: All zeros

    Read data files from: /usr/bin/../share/nmap
    OS detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 22.65 seconds
            Raw packets sent: 1205 (54.904KB) | Rcvd: 1040 (42.984KB)


## sudo nmap -sV -O -v scanme.nmap.org

    虽然TCP指纹识别是一种强大的OS检测方法，但查询开放端口以获取线索是另一种有效的方法。 某些应用程序（如Microsoft IIS）仅在单个平台上运行（因此将其丢弃），而许多其他应用程序在过于冗长的横幅消息中泄露其平台。 添加-sV选项可启用Nmap版本检测，该版本经过培训可以查找这些线索（以及其他信息）。

    Starting Nmap 7.80 ( https://nmap.org ) at 2019-09-17 09:12 CST
    NSE: Loaded 45 scripts for scanning.
    Initiating Ping Scan at 09:12
    Scanning scanme.nmap.org (45.33.32.156) [4 ports]
    Completed Ping Scan at 09:12, 0.21s elapsed (1 total hosts)
    Initiating Parallel DNS resolution of 1 host. at 09:12
    Completed Parallel DNS resolution of 1 host. at 09:12, 0.00s elapsed
    Initiating SYN Stealth Scan at 09:12
    Scanning scanme.nmap.org (45.33.32.156) [1000 ports]
    Discovered open port 80/tcp on 45.33.32.156
    Discovered open port 22/tcp on 45.33.32.156
    Discovered open port 9929/tcp on 45.33.32.156
    Discovered open port 31337/tcp on 45.33.32.156
    Completed SYN Stealth Scan at 09:12, 17.26s elapsed (1000 total ports)
    Initiating Service scan at 09:12
    Scanning 4 services on scanme.nmap.org (45.33.32.156)
    Completed Service scan at 09:12, 6.38s elapsed (4 services on 1 host)
    Initiating OS detection (try #1) against scanme.nmap.org (45.33.32.156)
    Retrying OS detection (try #2) against scanme.nmap.org (45.33.32.156)
    NSE: Script scanning 45.33.32.156.
    Initiating NSE at 09:13
    Completed NSE at 09:13, 0.80s elapsed
    Initiating NSE at 09:13
    Completed NSE at 09:13, 0.72s elapsed
    Nmap scan report for scanme.nmap.org (45.33.32.156)
    Host is up (0.16s latency).
    Other addresses for scanme.nmap.org (not scanned): 2600:3c01::f03c:91ff:fe18:bb2f
    Not shown: 991 closed ports
    PORT      STATE    SERVICE        VERSION
    22/tcp    open     ssh            OpenSSH 6.6.1p1 Ubuntu 2ubuntu2.13 (Ubuntu Linux; protocol 2.0)
    80/tcp    open     http           Apache httpd 2.4.7 ((Ubuntu))
    135/tcp   filtered msrpc
    139/tcp   filtered netbios-ssn
    445/tcp   filtered microsoft-ds
    593/tcp   filtered http-rpc-epmap
    4444/tcp  filtered krb524
    9929/tcp  open     nping-echo     Nping echo
    31337/tcp open     tcpwrapped
    Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.18 (87%), Linux 3.4 (87%), Linux 3.5 (87%), Linux 4.2 (87%), Linux 4.4 (87%), Synology DiskStation Manager 5.1 (87%), WatchGuard Fireware 11.8 (87%), Linux 2.6.35 (87%), Linux 3.10 (87%)
    No exact OS matches for host (test conditions non-ideal).
    Uptime guess: 5.157 days (since Thu Sep 12 05:26:25 2019)
    Network Distance: 13 hops
    TCP Sequence Prediction: Difficulty=262 (Good luck!)
    IP ID Sequence Generation: All zeros
    Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

    Read data files from: /usr/bin/../share/nmap
    OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
    Nmap done: 1 IP address (1 host up) scanned in 32.76 seconds
            Raw packets sent: 1119 (51.136KB) | Rcvd: 1036 (42.824KB)


### Device type
    所以被识别的指纹都会被分为一个或者多个类型。
    Device Type: router|firewall

### Running
    当没有完全匹配时，nmap将字段更改为running（只是猜测），并在每个候选家族名称后的括号中添加一个准确率百分比（100%是完全匹配）。如果没有指纹是完全匹配的，则忽略该行。
    Linux 2.4.X|2.5.X|2.6.X.

### OS CPE  
    显示了操作系统的通用平台枚举（cpe）表示（如果可用）。它还可以具有硬件类型的cpe表示。os cpe以cpe:/o开头，硬件cpe以cpe:/h开头。
    CPE: cpe:/o:linux:linux_kernel

### OS details
    如果没有任何完美的匹配，但有一些接近的猜测，则将该字段重命名为aggressive os guesses，并在括号中显示指纹，后面跟着一个百分比，指定每个匹配的接近程度。
    Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.18 (87%), Linux 3.4 (87%), Linux 3.5 (87%), Linux 4.2 (87%), Linux 4.4 (87%), Synology DiskStation Manager 5.1 (87%), WatchGuard Fireware 11.8 (87%), Linux 2.6.35 (87%), Linux 3.10 (87%)

### Uptime guess
    检查报头中的时间戳选项。通过观察几个响应，nmap可以确定当前值和增长率。简单的线性外推确定启动时间。如果目标在其syn/ack数据包中提供零或没有时间戳选项，或者根本没有应答，则忽略正常运行时间猜测。如果nmap无法识别时间戳增量率，或者它看起来可疑（如30年的正常运行时间），则该行也将被省略。
    Uptime guess: 5.157 days (since Thu Sep 12 05:26:25 2019)

### Network Distance
    计算nmap和目标主机之间的路由器数量。扫描本地主机时，距离为零，对于同一网段上的计算机，距离为一。路径上的每个附加路由器都会将一个添加到跃点计数中。nmap在无法计算该线时会省略该线（对相关探测没有响应）。
    Network Distance: 13 hops

### TCP Sequence Prediction
    TCP初始序列号生成较差的系统容易受到盲目TCP欺骗攻击。换句话说，您可以与这些系统建立完全连接，并在欺骗不同的IP地址时发送（但不接收）数据。目标的日志将显示欺骗性IP，您可以利用它们之间的任何信任关系。

   许多操作系统已被修复为使用RFC 1948提出的不可预测的初始序列号。出于这些原因，此行仅以详细模式打印。许多供应商仍然提供易受攻击的操作系统和设备，这使得它们对于OS检测目的是有价值的，该类描述了目标使用的ISN生成算法，难度是粗略估计系统进行盲IP欺骗的难度（0是最简单的）。带括号的评论基于难度指数，范围从琐碎的笑话到轻松，中等，强大，值得挑战，最后祝你好运！
    TCP Sequence Prediction: Difficulty=262 (Good luck!)

### IP ID sequence generation
    许多系统基于如何在IP数据包中生成低16位ID字段，无意中泄露了有关其流量级别的敏感信息。这可能被滥用来欺骗针对其他系统的端口扫描，以及用于“TCP空闲扫描（-SI）”一节中讨论的其他恶意目的。此字段描述nmap能够识别的id生成算法。许多系统为与之通信的每个主机使用不同的IP ID空间。在这种情况下，它们可能看起来很脆弱（例如显示增量类），同时仍然能够抵御诸如空闲扫描之类的攻击。出于这个原因，IP ID序列生成行仅以详细模式打印。如果nmap在os检测期间没有收到足够的响应，它将忽略整行。测试主机是否易受空闲扫描僵尸攻击的最佳方法是使用-si对其进行测试。
    IP ID Sequence Generation: All zeros


## tcp/ip指纹识别方法
    发送16个TCP，UDP，ICMP探针确定打开和关闭的端口。这些报文专门利用的RFC文档中的描述不清的地方而设计。侦听响应。分析并组合这些响应中的许多属性以生成指纹。如果没有响应，则每个探测包都被跟踪并重新发送一次。所有这些数据包都是具有随机IP ID值的IPv4数据报文。如果未找到开放的端口，Nmap会跳过对开放的TCP端口的探测。而后Nmap会先检查是否找到了一个确认关闭的TCP或UDP端口。如果还没有，Nmap将随机选择一个端口并希望获得最佳效果。


## Probes Sent发送的探测报文

### Sequence generation (SEQ, OPS, WIN, and T1)序列生成测试（SEQ，OPS，WIN和T1）
    Nmap会发送一系列六个TCP探测报文以生成这四个测试的响应结果。探测报文的时间间隔为精确的100ms，因此发送的总时间为500ms。这里确切的时序是非常重要的，因为我们检测中用到的一些序列算法（初始序列号，IP ID和TCP时间戳）都是与时间密切相关的。 这里总时间被选择为500ms，以便我们可靠地检测常见的2 Hz TCP时间戳序列。

    每个探测都是发送TCP SYN数据包到远程计算机上已检测到的开放端口的。序列seq和确认号ack是随机的（但每一个的情况都会被保留，因此Nmap可以区分每一个的响应）。检测的精度要求探测报文的一致性，因此即使用户主动使用–data-length请求，数据报文中也不会有有效的数据负载。

    这些数据包在TCP选项中有很多不同的使用方式，还有不同的TCP窗口大小值。 以下列表提供了六个数据包的具体选项和值。 列出的窗口大小的值并不会反映窗口缩放的值。EOL是TCP选项结束符，默认情况下许多嗅探工具都不会显示。


    包#1：窗口缩放（10），NOP，MSS（1460），时间戳（TSval：0xFFFFFFFF; TSecr：0），允许SACK。 窗口大小为1。\
![](./assets/52411.png)
    包#2： MSS（1400），窗口缩放（0），允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0），EOL。 窗口大小为63。
![](./assets/52412.png)
    包#3：时间戳（TSval：0xFFFFFFFF; TSecr：0），NOP，NOP，窗口缩放（5），NOP，MSS（640）。 窗口大小为4。
![](./assets/52413.png)
    包#4：允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0），窗口缩放（10），EOL。 窗口大小为4。
![](./assets/52414.png)
    包#5： MSS（536），允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0），窗口缩放（10），EOL。 窗口大小是16。
![](./assets/52415.png)
    包#6： MSS（265），允许SACK，时间戳（TSval：0xFFFFFFFF; TSecr：0）。 窗口大小是512。
![](./assets/52416.png)