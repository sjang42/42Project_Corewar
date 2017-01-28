.name "try_again"
.comment "izi"

defense:
	and %0, %0, r2
	zjmp %:stg
	and %0, %0, r2
	zjmp %:defense
	
stg:
	ld %1, r3
	ld %0, r5
	ld %12, r6
	ld %500, r7
	ld %197098, r10
	ld %880, r11
	ld %66023, r15
	sti r3, %:defense, %2
	sti r3, %:defense, %6
	sti r1, %:prep, %1
	sti r1, %:live, %1
	sti r1, %:live, %6
	sti r1, %:last_live, %1

	ld %5, r4
	fork %:prep
	and %0, %0, r2

	st r7, 507
	st r6, 500

	st r3, 490
	st r1, 489

	st r3, 400
	st r6, 393

live:
	live %0
	live %0

loop:
	zjmp %:live


prep:
	live %0
	st r3, 501
	st r1, 500
	st r10, 510
	st r11, 502
	st r15, 507
	st r11, 499
	fork %:prep

last_live:
	live %0
