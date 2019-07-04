# command + / 批量注释
# alt + shift + 箭头 移动代码

# 序列分解位单独变量,只要是可迭代对象都可以分解
# data = ['A', 'X', (1, 2)]
# data = {'A', 'X', (1, 2)}
# A, X, n = data
#
# print(A, X, n)


# *表达式可以提取序列中的一部分, num中包含了多个值
# record = ["A", 50, 123, 111, 'XC', (1, 2, 3), [3, 4, 5]]
# a, *num, xc, t, m = record
# print(a, num, xc, t, m)
#
# A, *NUM, M = record
# print(NUM)


# 输出最后的N个元素
# from collections import deque
#
#
# def s(n):
#     q = deque(maxlen=n)  # 新记录进入时旧记录自动删除
#     yield q  # 生成器函数，产生迭代器输出最后的N的元素


# # 找到最大或最小的N个元素
# nums = [1, 8, 2, 23, 7, -4, 18, 23, 42, 37, 2]
# # N = 1 使用max()或min()
# print(max(nums), min(nums))

# # N不大时用heapq.nlargest()或heapq.nsmallest(),
# # heapq可以按照键值排序字典
# import heapq
# heapq.heapify(nums)
# print(nums, heapq.nlargest(3, nums), heapq.nsmallest(3, nums))

# # N接近序列长度时排序后切片
# print(sorted(nums)[:10], sorted(nums)[-10:])


