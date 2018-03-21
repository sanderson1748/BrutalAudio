/* ////////////////////////////////////////////////////////////////////////// */
/* Brutal Editor                                                              */
/* - Internal Development Version 24                                          */
/* - 2018 March 21                                                            */
/*                                                                            */
/* sanderson1748@gmail.com                                                    */
/* ////////////////////////////////////////////////////////////////////////// */
/* Linux32_Boys.s                                                             */
/*                                                                            */
/* Assembly functions for Linux32                                             */
/*                                                                            */

.data 

.bss

.text
.globl Linux32_Square	# int   Linux32_Square(int);
.globl Linux32_Root	# int   Linux32_Root(int);
.globl Linux32_Pyth	# float Linux32_Pyth(float, float);
.globl Linux32_Sine	# float Linux32_Sine(float, void* (wav_struct*));

# Linux32_Square
# int Linux32_Square(int a);
# ret (a*a)
Linux32_Square:

	# prologue
	pushl	   %ebp				# save old ebp
	movl	   %esp,	   %ebp		# change ebp
	movl	 8(%ebp), 	   %edx		# get a (edx = a)

	# work
	imul	   %edx,	   %edx		# edx *= edx (a *= a)

	# epilogue
	movl	   %edx,	   %eax		# return edx (return a)
	movl	   %ebp,	   %esp		# restore esp
	popl 	   %ebp				# restore ebp
	ret					# return to calling function

# Linux32_Root
# int Linux32_Root(int In);
# ret (sqrt(In))
Linux32_Root:

	# prologue
	pushl	   %ebp				# save old ebp
	movl	   %esp	,	   %ebp		# change ebp
	movl	 8(%ebp),	   %edx		# get In (edx = In)

	subl	   $12,		   %esp		# allocate space for a1,a2
	movl	   %edx,	 4(%esp)	# n = In
	movl	   %edx,	 8(%esp)	# x = n

	# work
	# for (i=0; i<(n/2) i++)
	movl	 4(%esp),	   %ecx		# ecx = highbound_i = n
	shr	   $1,		   %ecx		# highbound_i /= 2
	xorl	   %edi,	   %edi

	this_loop:
	cmp	   %edi	,	   %ecx		# if i == highbound_i
	je	get_out				# { get out }

	#	x = (x + (n / x)) / 2;
	movl	 4(%esp),	   %eax		# jj  = n

	xorl	   %edx	,	   %edx		# (zero edx)
	movl 	 8(%esp),	   %ebx		# (divisor = x)
	idiv	   %ebx				# (ebx = jj/x)
	movl	   %eax	,	   %edx		# jj = ebx

	addl	 8(%esp),	   %eax		# jj += x
	shr	   $1,		   %eax		# jj /= 2
	movl	   %eax	,	 8(%esp)		#  x  = jj

	incl	   %edi				# i++
	jmp this_loop				# loop

	# epilogue
	get_out:
	movl	 8(%esp),	   %eax		# return x
	movl	   %ebp	,	   %esp		# restore esp
	popl	   %ebp				# restore ebp
	ret					# return to calling function

# Linux32_Pyth
# float Linux32_Pyth(float in_1, float in_2);
# ret sqrt((in_1*in_1) + (in_2 * in_2));

	# prologue
	pushl	   %ebp				# store base  pointer
	movl	   %esp,	   %ebp		# store stack pointer

	# epilogue
	movl	   %ebp,	   %esp		# restore stack pointer
	popl	   %ebp				# restore base  pointer
	ret

# Linux32_Sine
# float Linux32_Sine(float theta, void* (wav_struct*) wav);
# -> wav_struct (float amp, float freq, float phi, float con)
# ret (wav.amp * sin(theta * wav.freq + wav.phi) + wav.con);
Linux32_Sine:

	# prologue
	pushl	   %ebp				# store base  pointer
	movl	   %esp,	   %ebp		# store stack pointer
	subl	   $8,		   %esp		# allocate space for a1, b1

	# - set stuff
	movl 	12(%ebp), 	   %ebx		# get stuff for wav_guy

	finit					# initialize floating point

	# work
	# - a1 = theta
	movl	 8(%ebp),	   %ecx		# ecx = theta
	movl	   %ecx,	  (%esp)	#  a1 = ecx (theta)

	# - get freq
	movl	 4(%ebx),	   %ecx		# ecx = *(ebx+ 4) (( *(&freq) ))
	movl	   %ecx,	 4(%esp)	#  b1 = freq

	# - a1 = a1 * freq
	flds	 4(%esp)			# load b1 to multiplier
	fmuls	  (%esp)			# st0 = a1 * multiplier
	fstps	  (%esp)			#  a1 = product; + pop it // later dont pop

	# - get phi
	movl	 8(%ebx),	   %ecx		# ecx = *(ebx+ 8) (( *(&phi) )) 
	movl	   %ecx,	 4(%esp)	#  b1 = phi

	# - a1 = a1 + phi
	flds	 4(%esp)			# load b1 to adderator	
	fadds	  (%esp)			# st0 = a1 + adderator
	fstps	  (%esp)			#  a1 = sum; + pop it // maybe dont pop?

	# - sine(a1)
	flds	  (%esp)			# load a1 to sinerator
	fsin					# st0 = sine(a1)
	fstps	  (%esp)			#  a1 = st0

	# - get amp
	movl	  (%ebx),	   %ecx		# ecx = *(ebx+ 0) (( *(&amp) ))
	movl	   %ecx,	 4(%esp)	#  b1 = amp

	# - a1 * amp
	flds	 4(%esp)			# load b1 to multiplier
	fmuls	  (%esp)			# st0 = a1 * multiplier
	fstps	  (%esp)			#  a1 = product; + pop it // keep it?

	# - get con
	movl	12(%ebx),	   %ecx		# ecx = *(ebx+12) (( *(&con) ))
	movl	   %ecx,	 4(%esp)	#  b1 = con

	# - a1 + con
	flds	 4(%esp)			# load b1 to adderator
	fadds	  (%esp)			# st0 = a1 + adderator
	fstps	  (%esp)			#  a1 = sum; +pop

	# - return a1
	flds	  (%esp)			# load a1 to returnerator

	# epilogue
	movl	   %ebp,	   %esp		# restore stack pointer
	popl	   %ebp				# restore base  pointer
	ret					# get out

/**/
