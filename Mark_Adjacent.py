def mark_adjacent(s,x,y,real,pos):
	adj = [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]
	# remove point which is out side of the range
	for i in adj:
		if i[0] > 3 or i[0] < 0 or i[1] > 3 or i[1] < 0:
			adj.remove(i)

	# 2 dict, one for the real situation and the other for the possible situation
	# real = dict()
	# pos = dict()
	if s == 0:
		for i in adj:
			real[i] = 0
	elif s == 1:
		for i in adj:
			if i not in pos:
				pos[i] = [1]
			else:
				pos[i].append(1)

	elif s == 2:
		for i in adj:
			# if the block already had a real situation
			if i in real:
				continue
			# if not
			else:
				if i in pos:
					# if this block was marked as possible 2 before
					# it must be 2
					if 2 in pos[i]:
						real[i] = 2
						break
					else:
						pos[i].append(2)
				else:
					pos[i] = [2]

	elif s == 3:
		for i in adj:
			if i in real:
				continue
			else:
				if i in pos:
					# see if it could be 2 first
					if 2 in pos[i]:
						real[i] = 2
						continue
					# if not, mark it
					else:
						if 1 in pos[i]:
							pos[i].append(2)
						else:
							pos[i] += [1,2]
				else:
					pos[i] = [1,2]

	elif s == 4:
		for i in adj:
			if i in real:
				continue
			else:
				if i in pos:
					# see if it was marked as possible 4 before
					# if so, it must be 4
					if 4 in pos[i]:
						real[i] == 4
						break
					else:
						pos[i].append(4)
				else:
					pos[i] = [4]

	elif s == 5:
		for i in adj:
			if i in real:
				continue
			else:
				if i in pos:
					if 4 in pos[i]:
						real[i] = 4
						continue
					else:
						if 1 in pos[i]:
							pos[i].append(4)
						else:
							pos[i] += [1,4]
				else:
					pos[i] = [1,4]

	elif s == 6:
		for i in adj:
			if i in real:
				continue
			else:
				if i in pos:
					if 4 in pos[i]:
						real[i] = 4
						continue
					elif 2 in pos[i]:
						real[i] = 2
					else:
						pos[i] += [2,4]
				else:
					pos[i] = [2,4]

	elif s == 7:
		for i in adj:
			if i in real:
				continue
			else:
				if i in pos:
					if 4 in pos[i]:
						real[i] = 4
						continue
					elif 2 in pos[i]:
						real[i] = 2
					else:
						pos[i] += [2,4]

def move_forward(x,y,d):
	d = d % 4
	if d == 0:
		x += 1
	elif d == 1:
		y += 1
	elif d == 2:
		x -= 1
	elif d == 3:
		y -= 1

def face_edge(x,y,d):
	# this may work
	d = d % 4

	if d == 0:
		if x + 1 > 3:
			return True
	elif d == 1:
		if y + 1 > 3:
			return True
	elif d == 2:
		if x - 1 < 0:
			return True
	elif d == 3:
		if y - 1 < 0:
			return True

# whenever the signal is not 0, use this function
# move back one step and move to another direction
def turn_and_move(x,y,d):
	d += 2
	move_forward(x,y,d)
	d += 3
	move_forward(x,y,d)

def kill():
	pass

def move_back(path,d):
	for i in range(len(path)-1,0,-1):
		if path[i-1][0] == path[i][0] - 1:
			d = 3
			move_forward(path[i][0],path[i][1],d)
		elif path[i-1][0] == path[i][0] + 1:
			d = 0
			move_forward(path[i][0],path[i][1],d)

		if path[i-1][1] == path[i][1] + 1:
			d = 3
			move_forward(path[i][0],path[i][1],d)
		elif path[i-1][1] == path[i][1] + 1:
			d = 0
			move_forward(path[i][0],path[i][1],d)


if __name__ == '__main__':
	real = dict()
	pos = dict()
	path = [(0,0)]

	x = 0
	y = 0
	d = 0

	adj = [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]
	
	while True:
		signal = int(input('Signal => '))
		mark_adjacent(signal,x,y,real,pos)

		if signal == 8:
			break
		else:
			if signal == 0:
				move_forward(x,y,d)
			elif signal == 1:
				turn_and_move(x,y,d)
			elif signal == 2:
				k = 0
				for i in adj:
					if i in real and real[i] == 2:
						# kill
						k += 1
						move_forward(x,y,d)
						break

				if k == 0:
					turn_and_move(x,y,d)
				else:
					continue
			elif signal == 4 or signal == 5 or signal == 6 or signal == 7:
				k = 0
				for i in adj:
					if i in real and real[i] == 4:
						# kill
						k += 1
						move_forward(x,y,d)
						break

				if k == 0:
					turn_and_move(x,y,d)
				else:
					continue

				k = 0
				if i in real and real[i] == 2:
						# kill
						k += 1
						move_forward(x,y,d)
						break

				if k == 0:
					turn_and_move(x,y,d)
				else:
					continue

		path.append((x,y))

	move_back(path,d)





