.name "cheburek"
.comment "Power of Cheburek's humanity"

        ld %0,r11
        live %18
loop:   sti r1, %:live, %1
live:   live %42
        ld %0, r2
        fork %5
        zjmp %:loop

tail:   ldi %1, %5, r3
        ld %0, r4
        sti r3, %10, %5
        ldi r2, %4, r7
        ld %42424242,r6
        st r6,r14
        st r6,r15
        sti r7, %156, %10
        fork %420
        zjmp %:tail

        live %0
        sti r1, %:live, %1

        sti r4,r1, %228
        st r2, %1488
