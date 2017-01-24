.name "roller"

start:
	sti r1, %:live, %1

live:
	live %0

preend:
	xor %1, %1, r16
	zjmp %:start

end:
