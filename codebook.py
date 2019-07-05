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
# from collections import deque  # 队列
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

# # 字典defaultdict, OrderedDict
# from collections import defaultdict, OrderedDict
# d = defaultdict(list)  # 允许重复元素
# d = defaultdict(set)  # 消除重复元素
# d = OrderedDict()  # 始终有序的字典

# # 字典计算,利用zip(),将键值对翻转，只能使用一次
# # 字典对key()和items()支持集合操作，可以找出相同的键值对&，减去部分键值对-
# prices = {'A': 10, 'B': 20, 'C': 30, 'D': 40}
# print(min(zip(prices.values(), prices.keys())))
# print(max(zip(prices.values(), prices.keys())))

# # 字典排序 itemgetter可以用lambda表达式代替
# from operator import itemgetter
# b = [{'x': 2, 'y': 4}, {'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}, {'x': 1, 'y': 4}]
# print(sorted(b, key=itemgetter('x')))
# print(sorted(b, key=itemgetter('y')))

# # 顺序不变的情况下删去重复元素
# a = [1, 5, 2, 1, 9, 1, 5, 10]
# b = [{'x': 2, 'y': 4}, {'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}, {'x': 1, 'y': 4}]
#
# # def deldupe(a):
# #     already = set()
# #     for ele in a:
# #
# #         if ele not in already:
# #             yield ele
# #             already.add(ele)
#
#
# def deldupe(a, key=None):
#     already = []
#     for ele in a:
#         if key is None:
#             if ele not in already:
#                 yield ele
#                 already.append(ele)
#         else:
#             for k in ele.keys():
#                 if k in key:
#                     if ele not in already:
#                         yield ele
#                         already.append(ele)
#
#
# print(list(deldupe(a)))
# print(list(deldupe(b, ['x', 'y'])))
# print(list(deldupe(b, ['x'])))
#
# # 顺序可变
# print(set(a))


# # 智能切片并命名
# i = [1, 5, 2, 1, 9, 1, 5, 10]
# a = slice(0, 4, 2)  # 切刀
# a = i.indices(len(i))
# print(i[a], i[a.start], i[a.stop], i[a.step])


# # 智能计数 Counter对象可以作运算
# from collections import Counter
# words = ['s', 'f', 'g', 'g', 'w', 'w', 'f', 'h', 'i', 'y', 't', 'g', 'k', 'v', 'c', 'v', 'a', 's', 's', 's', 's', 'v', 'q', ]
# more_words = ['f', 'h', 'i', 'y', 't', 'g', 'k', 'v', 'c', 'v', 'a', ]
# b = Counter(more_words)
# c = Counter(words)
# print(c)
# c.update(more_words)
# print(c)
#
# print(b)
# print(b + c, '\n', c - b)


