from collections import deque
N, M, K = map(int, input().split())
 
cows = []
for _ in range(N):
	w, a = map(int, input().split())
	cows += [w] * a
cows.sort(reverse=True)
 
answer = 0
towers = deque([1e10]*min(M, len(cows)))
for cow in cows:
	if cow + K <= towers[0]:
		answer += 1
		towers.popleft()
		towers.append(cow)
 
print(answer)