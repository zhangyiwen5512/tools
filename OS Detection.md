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



## 原理

    