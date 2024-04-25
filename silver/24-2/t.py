import sys
sys.stdin = open('2.in', 'r')
sys.stdout = open('2.out', 'w')

def to_reduced_list(s):
    """Compress runs of equal chars in a string s, and converts to int
    >>> to_reduced_list('2211')
    [2, 1]
    """
    l = []
    for c in s:
        c = int(c)
        if len(l) > 0 and l[-1] == c:
            continue
        l.append(c)
    return l


def solve():
    N, P = map(int, input().split())
    tubes = [to_reduced_list(input()) for _ in range(2)]
    tubes.append([])
    if tubes[0][0] == tubes[1][0]:  # ensure f and s start with different chars
        tubes[0].insert(0, tubes[0][0] ^ 3)

    ans = len(tubes[0]) + len(tubes[1]) - 2
    if ans > 1:
        ans += 1

    print(ans)
    if P == 1:
        return

    moves = []

    def move(src, dst):
        moves.append((src, dst))
        if len(tubes[dst]) == 0 or tubes[dst][-1] != tubes[src][-1]:
            tubes[dst].append(tubes[src][-1])
        tubes[src].pop()

    if tubes[0][-1] == tubes[1][-1]:  # step 1: if equal last chars
        if len(tubes[0]) > len(tubes[1]):
            move(0, 1)
        else:
            move(1, 0)

    for i in range(2):
        if len(tubes[i]) > 1:
            move(i, 2)  # step 2: move from any tube with string length > 1 to beaker
            idx_to_empty = 0  # step 3: choose a tube to (almost) empty first
            if tubes[idx_to_empty][0] == tubes[2][0]:
                idx_to_empty ^= 1
            while len(tubes[idx_to_empty]) > 1:
                if tubes[idx_to_empty][-1] == tubes[2][0]:
                    move(idx_to_empty, 2)
                else:
                    move(idx_to_empty, idx_to_empty ^ 1)
            idx_to_empty ^= 1  # step 4: next, (almost) empty the other tube
            while len(tubes[idx_to_empty]) > 1:
                if tubes[idx_to_empty][-1] == tubes[2][0]:
                    move(idx_to_empty, 2)
                else:
                    move(idx_to_empty, idx_to_empty ^ 1)
            move(2, idx_to_empty)  # step 5: finish
            break

    assert len(moves) == ans
    # for a, b in moves:
    #     print(1 + a, 1 + b)


T = int(input())
for _ in range(T):
    solve()