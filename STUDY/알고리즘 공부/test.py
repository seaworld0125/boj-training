from math import *

def intToBin(n: int, binList: list):
    if n == 0:
        return
    
    a = n // 2
    b = n % 2
    binList.append(str(b))
    
    intToBin(a, binList)

def decToBin(n: float, binList: list, patternList: list) -> float:
    if(n == 0):
        return 0
    
    n = n * 2
    
    # 나왔던 패턴이라면
    if patternList.count(n) > 0:
        return n
    
    patternList.append(n)
    
    a = int(n)
    binList.append(str(a))
    
    decimal_ = str(n).split('.')[1]
    decimal_ = float(decimal_) / pow(10, len(decimal_))
    
    return decToBin(decimal_, binList, patternList)

# 시작
dec = input("입력: ")

# 입력 처리
sp = dec.split('.')
a = int(sp[0])
b = float(sp[1]) / pow(10, len(sp[1])) if len(sp) > 1 else 0.0

# 정수부 2진수 변환
binList = []

intToBin(a, binList)
binList.reverse()
integerStr = ''.join(binList)
integerStr = integerStr if len(integerStr) else '0'

# 소수부 2진수 변환
binList = []
patternList = []

pattern = decToBin(b, binList, patternList)
decimalStr = ''.join(binList)
decimalStr = decimalStr if len(decimalStr) else '0'

# 무한 소수라면
if pattern:
    start_ = patternList.index(pattern)
    decimalStr = decimalStr[0:start_] + '[' + decimalStr[start_:] + ']'

# 결과
print(integerStr + '.' + decimalStr)