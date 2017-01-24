#
# test.s for corewar
#

.name "Spartiates"
.comment "This is SPARTAAAAA"

begin:
		sti		r1,			%:live,		%1
		lfork	%:live
		lld 	%1,			r1
		lld 	%400,		r2
		lld 	%11,		r3
		lld		%100,		r5
		lld		%0,			r6
		lld		%:repeat, 	r4
		sti		r4, 		%:live,		r5
		add		r4, 		%4, 		r4
		add		r5, 		%4, 		r5
		add		r6, 		%4, 		r6

repeat:
#		sti 	r1, r2, %:live
#		add		r3, r2, r2
		lld		%0,			r8
		zjmp 	%:repeat

live:
		live	%0
		ld		%0,			r8
		zjmp	%:live
