#by zaz, it's not very good, but what did you expect, rainbowdash is way better
#2013

.name		"fluttershyfluttershyfluttershyfluttershyfluttershyfluttershyfluttershyfluttershyfluttershy"
.comment	"oh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projectoh, my, what a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet a scary projet t a scary projet a scary projet sssct"

sti	r1, %:live, %1			;change live by the right value
sti	r1, %:live2, %1			;change live by the right value
ld	%1, r3
ld	%33, r6
#While (r2 < 10)
forks:
	add	r2, r3, r2		;r2++
	xor	r2, %15, r4		;if (r4) {carry = 0} if (r2 == 15 -> r4 = 0)

live2:
	live %4
	zjmp	%:endwhile		;if (carry)
	fork	%:forks

endwhile:
	ld	%0, r4			;carry = 1

live:
	live %4
	zjmp %:live
