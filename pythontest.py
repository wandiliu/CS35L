with open("test.csv") as f:
	s = f.read()
	values = s.split(",")
	for value in values:
		print value
