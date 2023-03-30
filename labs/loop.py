

def loop_ll(tail, l_length):
    a = {}
    a['tail'] = tail
    a['loop_length'] = l_length
    a['vals'] = range(tail, l_length) 
    def next(index, list):
        tl = list['tail']
        ll = list['loop_length']
        vals = list['vals']
        if index + 1 <= tl:
            index = index + 1
        else:
            index = (index + 1 - tl) % ll + tl
        return index
    return a, next

def loopfinding(a, a_next, p, q):
    index0 = 0
    index1 = 1
    ops = 0
    def next(x):
        return a_next(x, a)
    sw = 0
    while sw == 0:
        for i in range(p):
            index0 = next(index0)
            ops = ops + 1
        for i in range(q):
            index1 = next(index1)
            ops = ops + 1
        if index0 == index1:
            print(f'loop! length: {ops//3+1}, operations: {ops}')
            return

index = 0
first = 0
a, next = loop_ll(1121342, 3)
print(a)
print()
loopfinding(a, next, 1, 2)

    
    