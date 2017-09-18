#!/bin/bash

EXECUTABLE=${1:-./freq}
INPUT_FILE=test_freq.input
OUTPUT_FILE=test_freq.output

cleanup() {
    rm -f $INPUT_FILE $OUTPUT_FILE
}

trap cleanup HUP INT QUIT TERM EXIT

if [ ! -x "$EXECUTABLE" ]; then
    echo "Failure: $EXECUTABLE is not executable"
    exit 1
fi

cat > $INPUT_FILE <<EOF
I stay out too late, got nothing in my brain
That's what people say, that's what people say
I go on too many dates, but I can't make them stay
At least that's what people say, that's what people say
But I keep cruising
Can't stop, won't stop moving
It's like I got this music in my mind
Saying it's gonna be alright
Cause the players gonna play, play, play, play, play
And the haters gonna hate, hate, hate, hate, hate
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
Heartbreakers gonna break, break, break, break, break
And the fakers gonna fake, fake, fake, fake, fake
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
I never miss a beat, I'm lightning on my feet
And that's what they don’t see, that's what they don’t see
I'm dancing on my own, I make the moves up as I go
And that's what they don't know, that’s what they don’t know
But I keep cruising
Can't stop, won't stop grooving
It's like I got this music in my mind
Saying it's gonna be alright
Cause the players gonna play, play, play, play, play
And the haters gonna hate, hate, hate, hate, hate
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
Heartbreakers gonna break, break, break, break, break
And the fakers gonna fake, fake, fake, fake, fake
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
Hey, hey, hey!
Just think while you've been getting down and out about the liars
And dirty, dirty cheats of the world you could've been getting down to this sick beat
My ex-man brought his new girlfriend
She's like, “oh my God”, but I'm just gonna shake
And to the fella over there with the hella good hair
Won't you come on over, baby, we can shake, shake, shake
Cause the players gonna play, play, play, play, play
And the haters gonna hate, hate, hate, hate, hate
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
Heartbreakers gonna break, break, break, break, break
And the fakers gonna fake, fake, fake, fake, fake
Baby, I'm just gonna shake, shake, shake, shake, shake
I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
I, I shake it off, I shake it off
EOF

cat > $OUTPUT_FILE <<EOF
54	I
52	shake
44	it
26	shake,
22	off,
22	off
21	gonna
16	I,
14	the
12	play,
12	hate,
12	fake,
12	break,
10	And
9	I'm
8	what
7	just
6	that's
6	my
6	Baby,
4	they
4	people
4	on
3	this
3	players
3	play
3	in
3	Heartbreakers
3	haters
3	hate
3	got
3	fakers
3	fake
3	don’t
3	Cause
3	break
2	you
2	won't
2	too
2	to
2	stop,
2	stop
2	stay
2	Saying
2	say,
2	say
2	out
2	music
2	mind
2	make
2	like
2	keep
2	It's
2	it's
2	go
2	getting
2	down
2	cruising
2	Can't
2	But
2	but
2	been
2	be
2	alright
1	you've
1	world
1	Won't
1	with
1	while
1	we
1	up
1	think
1	there
1	them
1	That's
1	that’s
1	sick
1	She's
1	see,
1	see
1	own,
1	over,
1	over
1	“oh
1	of
1	nothing
1	new
1	never
1	My
1	moving
1	moves
1	miss
1	many
1	like,
1	lightning
1	liars
1	least
1	late,
1	know,
1	know
1	Just
1	his
1	Hey,
1	hey!
1	hey,
1	hella
1	hair
1	grooving
1	good
1	God”,
1	girlfriend
1	fella
1	feet
1	ex-man
1	don't
1	dirty,
1	dirty
1	dates,
1	dancing
1	could've
1	come
1	cheats
1	can't
1	can
1	brought
1	brain
1	beat,
1	beat
1	baby,
1	At
1	as
1	and
1	about
1	a
EOF

if ! $EXECUTABLE < $INPUT_FILE | sort -rn | diff -u - $OUTPUT_FILE; then
    echo "FAILURE: Probably stayed out too late and got nothing in your brain. Shake it off!"
    echo "REASON:  Output doesn't match"
    exit 3
fi

if ! $EXECUTABLE -h < /dev/null 2>&1 | grep -q -i 'usage'; then
    echo "FAILURE: You kept cruising, didn't stop and inform about using. Shake it off!"
    echo "REASON:  Didn't display usage message"
    exit 2
fi

if ! diff -u <($EXECUTABLE -f KEY < $INPUT_FILE | sort) <(awk '{print $2}' $OUTPUT_FILE | sort); then
    echo "FAILURE: Heartbreakers gonna break, break, break, break, break. Shake it off!"
    echo "REASON:  Doesn't handle -f KEY properly"
    exit 4
fi

if ! diff -u <($EXECUTABLE -f KEY_VALUE < $INPUT_FILE | sort) <(awk '{printf "%s\t%d\n", $2, $1}' $OUTPUT_FILE | sort); then
    echo "FAILURE: Cause the players gonna play, play, play, play, play. Shake it off!"
    echo "REASON:  Doesn't handle -f KEY_VALUE properly"
    exit 5
fi

if ! diff -u <($EXECUTABLE -f VALUE < $INPUT_FILE | sort) <(awk '{print $1}' $OUTPUT_FILE | sort); then
    echo "FAILURE: And the haters gonna hate, hate, hate, hate, hate. Shake it off!"
    echo "REASON:  Doesn't handle -f VALUE properly"
    exit 6
fi

if ! $EXECUTABLE -f VALUE_KEY < $INPUT_FILE | sort -rn | diff -u - $OUTPUT_FILE; then
    echo "FAILURE: And the fakers gonna fake, fake, fake, fake, fake. Shake it off!"
    echo "REASON:  Doesn't handle -f VALUE_KEY properly"
    exit 7
fi

exit 0
