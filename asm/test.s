.name "jex"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"

start:
	live %42
zjmp %:start

sti r1, %:start, %1
ld %0, r3;

fork %:start

zjmp1:
	ld %0, r6
	ld %0, r6
	zjmp %:zjmp1
